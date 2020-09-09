// <insert file header>

#pragma once

#include "HekateDiagram.h"

namespace Hekate {

	// add a new state and return its stateid
	template <typename S, typename T>
	template <typename ...Ts>
	stateid Diagram<S, T>::AddNewState (Ts &&...args) {
	}

	// remove a state
	template <typename S, typename T>
	void Diagram<S, T>::RemoveState (stateid id) {
	}

	// add a new group and return its stateid
	template <typename S, typename T>
	stateid Diagram<S, T>::AddNewGroup () {
	}

	// remove a group
	template <typename S, typename T>
	void Diagram<S, T>::RemoveGroup (stateid id) {
	}

	// add a state into a group
	template <typename S, typename T>
	void Diagram<S, T>::AddStateIntoGroup (stateid stateID, stateid groupID) {
	}

	// remove a state from a group
	template <typename S, typename T>
	void Diagram<S, T>::RemoveStateFromGroup (stateid stateID, stateid groupID) {
	}

	// add new transition and return its transid
	template <typename S, typename T>
	template <typename ...Ts>
	transid Diagram<S, T>::AddNewTransition (stateid fromID, stateid toID, Ts &&...args) {
	}

	// remove a transition
	template <typename S, typename T>
	void Diagram<S, T>::RemoveTransition (transid id) {
	}

	// get a reference to the string-name of an id
	template <typename S, typename T>
	std::string& Diagram<S, T>::GetName (stateid id) {
	}

}