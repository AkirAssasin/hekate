// <insert file header>

#pragma once

#include <vector>

#include "HekateDiagram.h"
#include "HekateAgent.h"

namespace Hekate {

	// helper function to find unoccupied key
	template <typename TKey, typename TVal>
	TKey FindUnoccupiedKey (const std::map<TKey, TVal> &map, TKey start, TKey inc) {
	
		while (map.find(start) != map.cend()) {
			start += inc;
		}
		return start;
	}

	// add a new state and return its stateid
	template <typename S, typename T>
	template <typename ...Ts>
	stateid Diagram<S, T>::AddNewState (Ts &&...args) {

		// add new state
		stateid id { FindUnoccupiedKey<stateid, StateType>(m_states, 1, 1) };
		m_states.emplace(id, StateType{ id, std::forward<Ts>(args)... });

		// add new name
		m_names[id] = "New State";

		// return stateid
		return id;
	}

	// remove a state
	template <typename S, typename T>
	void Diagram<S, T>::RemoveState (stateid id) {

		// check for existence
		auto stateIt { m_states.find(id) };
		if (stateIt == m_states.end()) return;

		// remove state from all its groups
		for (stateid groupID : stateIt->second.m_groups) {
			m_groups.find(groupID)->second.erase(id);
		}

		// remove all transitions to and from state
		std::vector<transid> toRemove;
		for (std::pair<const transid, TransType> &pair : m_transitions) {
			
			TransType &trans { pair.second };
			trans.m_from.erase(id);
			if (trans.m_to == id) toRemove.push_back(pair.first);
		}
		for (transid rem : toRemove) m_transitions.erase(rem);

		// remove its name
		m_names.erase(id);

		// if is start point, set it to undefined
		if (m_startPoint == id) m_startPoint = undefinedState;

		// remove the state itself
		m_states.erase(id);
	}

	// add a new group and return its stateid
	template <typename S, typename T>
	stateid Diagram<S, T>::AddNewGroup () {

		// add new group
		stateid id { FindUnoccupiedKey<stateid, Group>(m_groups, -1, -1) };
		m_groups.emplace(id, Group{});

		// add new name
		m_names[id] = "New Group";

		// return stateid
		return id;
	}

	// remove a group
	template <typename S, typename T>
	void Diagram<S, T>::RemoveGroup (stateid id) {

		// check for existence
		auto groupIt { m_groups.find(id) };
		if (groupIt == m_groups.end()) return;

		// remove group from all its states
		for (stateid stateID : groupIt->second) {
			m_states.find(stateID)->second.m_groups.erase(id);
		}

		// remove group from all transitions
		for (auto &pair : m_transitions) {

			TransType &trans { pair.second };
			trans.m_from.erase(id);
		}

		// remove its name
		m_names.erase(id);

		// remove the group itself
		m_groups.erase(id);
	}

	// add a state into a group
	template <typename S, typename T>
	void Diagram<S, T>::AddStateIntoGroup (stateid stateID, stateid groupID) {

		// add record in state and group
		m_states.find(stateID)->second.m_groups.emplace(groupID);
		m_groups.find(groupID)->second.emplace(stateID);
	}

	// remove a state from a group
	template <typename S, typename T>
	void Diagram<S, T>::RemoveStateFromGroup (stateid stateID, stateid groupID) {

		// remove record in state and group
		m_states.find(stateID)->second.m_groups.erase(groupID);
		m_groups.find(groupID)->second.erase(stateID);
	}

	// add new transition and return its transid
	template <typename S, typename T>
	template <typename ...Ts>
	transid Diagram<S, T>::AddNewTransition (stateid fromID, stateid toID, Ts &&...args) {

		// add new transition
		transid id { FindUnoccupiedKey<transid, TransType>(m_transitions, 0, 1) };
		m_transitions.emplace(id, TransType{ id, fromID, toID, std::forward<Ts>(args)... });

		// return transid
		return id;
	}

	// remove a transition
	template <typename S, typename T>
	void Diagram<S, T>::RemoveTransition (transid id) {

		// very straightforward, since nothing else tracks transids
		m_transitions.erase(id);
	}

	// get a reference to the string-name of an id
	template <typename S, typename T>
	std::string& Diagram<S, T>::GetName (stateid id) {

		return m_names.find(id)->second;
	}

	// get a reference to the string-name of an id
	template <typename S, typename T>
	const std::string& Diagram<S, T>::GetName (stateid id) const {

		return m_names.find(id)->second;
	}

	// get an id of a string-name
	template <typename S, typename T>
	stateid Diagram<S, T>::GetID (const std::string &name) const {
	
		for (auto &i : m_names) {
		
			if (i.second == name) return i.first;
		}
		return undefinedState;
	}

	// debug-print all data
	template <typename S, typename T>
	void Diagram<S, T>::DebugOut (std::ostream &stream) const {
	
		// print all states
		stream << "States:" << std::endl;
		for (auto const &i : m_states) {
		
			stream << i.first << ") " << GetName(i.first) << std::endl;
		}
		stream << "starting state is [" << m_startPoint << "] a.k.a. " << GetName(m_startPoint) << std::endl;

		// print all groups
		stream << "\nGroups:" << std::endl;
		for (auto const &i : m_groups) {
		
			stream << i.first << ") ";
			for (stateid k : i.second) {
				stream << GetName(k) << ", ";
			}
			stream << "is part of " << GetName(i.first) << std::endl;
		}

		// print all conditions
		stream << "\nConditions (default values):" << std::endl;
		for (auto const &i : m_conditions) {
		
			stream << i.first << " = " << i.second << std::endl;
		}

		// print all transitions
		stream << "\nTransitions:" << std::endl;
		for (auto const &i : m_transitions) {
		
			// print from and to
			stream << i.first << ") ";
			for (stateid k : i.second.m_from) {
				stream << GetName(k) << ", ";
			}
			stream << "to " << GetName(i.second.m_to) << " (when";

			// print conditions
			for (auto const &k : i.second.m_conditions) {
				stream << ", " << k.first << " = " << k.second;
			}
			stream << ")" << std::endl;
		}
	
	}

	// add a new transition condition
	template <typename S, typename T>
	void Diagram<S, T>::AddNewCondition (const std::string &name, bool val) {
	
		if (m_conditions.find(name) == m_conditions.end()) {
			m_conditions.emplace(name, val);
		}
	}

	// remove a transition condition
	template <typename S, typename T>
	void Diagram<S, T>::RemoveCondition (const std::string &name) {
	
		// stop if name doesn't exist
		auto ni { m_conditions.find(name) };
		if (ni == m_conditions.end()) return;

		// remove the condition in all transitions
		for (auto &i : m_transitions) {

			i.second.m_conditions.erase(name);
		}

		// erase from default-value map
		m_conditions.erase(ni);
	}

	// get a reference to the transition condition's default value
	template <typename S, typename T>
	bool& Diagram<S, T>::GetConditionDefault (const std::string &name) {
	
		return m_conditions.find(name)->second;
	}

	// rename a condition
	template <typename S, typename T>
	void Diagram<S, T>::RenameCondition (const std::string &oldName, const std::string &newName) {

		// stop if old name doesn't exist
		auto oi { m_conditions.find(oldName) };
		if (oi == m_conditions.end()) return;

		// stop if new name is already occupied
		if (m_conditions.find(newName) != m_conditions.end()) return;

		// change the condition name in all transitions
		for (auto &i : m_transitions) {
		
			// find and replace
			auto &cons { i.second.m_conditions };
			auto f { cons.find(oldName) };
			if (f != cons.end()) {

				cons.emplace(newName, f->second);
				cons.erase(f);
			}
		}

		// change the condition name in default-value map
		m_conditions.emplace(newName, oi->second);
		m_conditions.erase(oi);
	}

	// add a condition to a transition
	template <typename S, typename T>
	void Diagram<S, T>::SetConditionToTransition (const std::string &con, transid id, bool conVal) {
	
		// add new condition if it doesn't exist
		AddNewCondition(con);

		// set the value in the transition condition map
		m_transitions.find(id)->second.m_conditions[con] = conVal;

	}

	// remove a condition from a transition
	template <typename S, typename T>
	void Diagram<S, T>::RemoveConditionFromTransition (const std::string &con, transid id) {
	
		m_transitions.find(id)->second.m_conditions.erase(con);
	}

	// initialize an agent
	template <typename S, typename T>
	template <typename I>
	void Diagram<S, T>::InitializeAgent (AgentType<I> &agent) const {
	
		// copy all conditions' default values
		agent.m_conditions = m_conditions;

		// set current state to start point
		auto fs { m_states.find(m_startPoint) };
		if (fs == m_states.cend()) {
			agent.m_currentState = std::nullopt;
		} else {
			agent.m_currentState = fs->second;
		}

		// set transition to null
		agent.m_currentTransition = std::nullopt;

		// update agent transitions
		UpdateAgentTransitions(agent);
	}

	// update agent's transition list
	template <typename S, typename T>
	template <typename I>
	void Diagram<S, T>::UpdateAgentTransitions (AgentType<I> &agent) const {
	
		// clear original list
		agent.m_transitions.clear();

		// stop if agent doesn't have state
		if (!agent.m_currentState.has_value()) return;
		StateType &currentState { *agent.m_currentState };

		// look through all transitions
		for (auto const &i : m_transitions) {
			
			// look through all from-ids
			bool found { false };
			for (auto const &k : i.second.m_from) {

				// check if same group or id
				if (k < 0) {
					if (currentState.m_groups.count(k) > 0) {
						found = true;
						break;
					}
				} else {
					if (currentState.m_id == k) {
						found = true;
						break;
					}
				}
			}

			// add into list if found
			if (found) agent.m_transitions.push_front(i.second);
		}
	}

	// update agent's current state
	template <typename S, typename T>
	template <typename I>
	void Diagram<S, T>::UpdateAgentState (AgentType<I> &agent, stateid id) const {
	
		// set the agent's current state to the given id
		agent.m_currentState = m_states.find(id)->second;

		// update agent transitions
		UpdateAgentTransitions(agent);
	}

	// set starting point
	template <typename S, typename T>
	void Diagram<S, T>::SetStartingState (stateid id) {
	
		m_startPoint = id;
	}
}