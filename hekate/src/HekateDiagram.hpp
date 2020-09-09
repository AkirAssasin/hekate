// <insert file header>

#pragma once

#include <vector>

#include "HekateDiagram.h"

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
		stateid id { FindUnoccupiedKey(m_states, -1, -1) };
		m_groups.emplace(id, {});

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

		// remove all transitions from group
		for (std::pair<transid, TransType> &pair : m_transitions) {

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

}