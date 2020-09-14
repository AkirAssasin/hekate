// <insert file header>

#pragma once

#include <string>
#include <map>

#include "HekateStructs.h"

namespace Hekate {

	template <typename TState, typename TTransition>
	class Diagram {

		// stl type aliases
		using Group = std::set<stateid>;

		// inner type aliases
		using InnerStateType = TState;
		using InnerTransType = TTransition;

		// wrapper type aliases
		using StateType = State<InnerStateType>;
		using TransType = Transition<InnerTransType>;
	
		// a map of id-to-states;
		// all the ids here must be positive
		std::map<stateid, StateType> m_states;

		// a map of id-to-groups;
		// all the ids here must be negative
		std::map<stateid, Group> m_groups;

		// a map of id-to-names
		std::map<stateid, std::string> m_names;

		// a map of id-to-transitions
		std::map<transid, TransType> m_transitions;

		// the starting ID of this state machine;
		// must be positive (aka start from state, not group)
		stateid m_startPoint { undefinedState };

		// a map of conditionals and their default values
		std::map<std::string, bool> m_conditions;

	public:

		// add a new state and return its stateid
		template <typename ...Ts>
		stateid AddNewState (Ts &&...args);

		// remove a state
		void RemoveState (stateid id);

		// add a new group and return its stateid
		stateid AddNewGroup ();

		// remove a group
		void RemoveGroup (stateid id);

		// add a state into a group
		void AddStateIntoGroup (stateid stateID, stateid groupID);

		// remove a state from a group
		void RemoveStateFromGroup (stateid stateID, stateid groupID);

		// add new transition and return its transid
		template <typename ...Ts>
		transid AddNewTransition (stateid fromID, stateid toID, Ts &&...args);

		// remove a transition
		void RemoveTransition (transid id);

		// get a reference to the string-name of an id
		std::string& GetName (stateid id);

		// get a reference to the string-name of an id (const)
		const std::string& GetName (stateid id) const;

		// get an id of a string-name
		stateid GetID (const std::string &name) const;

		// debug-print all data
		void DebugOut (std::ostream &stream) const;

		// add a new transition condition
		void AddNewCondition (const std::string &name, bool val = false);

		// remove a transition condition
		void RemoveCondition (const std::string &name);

		// get a reference to the transition condition's default value
		bool& GetConditionDefault (const std::string &name);

		// rename a condition
		void RenameCondition (const std::string &oldName, const std::string &newName);

		// set a condition to a transition
		void SetConditionToTransition (const std::string &con, transid id, bool conVal);

		// remove a condition from a transition
		void RemoveConditionFromTransition (const std::string &con, transid id);
	
	};
	
}

#include "HekateDiagram.hpp"