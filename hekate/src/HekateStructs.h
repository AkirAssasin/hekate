// <insert file header>

#pragma once

#include <set>

#include "HekateDeclarations.h"

namespace Hekate {

	// a wrapper of a state type
	template <typename T>
	struct State {

		// id and inner state
		stateid m_id;
		T m_inner;

		// set of groups this state belongs to
		std::set<stateid> m_groups;
		
		// forwarding constructor
		template <typename ...Ts>
		State (stateid id, Ts &&...args) : 
			m_id { id }, 
			m_inner { std::forward<Ts>(args)... } {}

		// default copy and move constructor
		State (const State<T> &rhs) = default;
		State (State<T> &&rhs) noexcept = default;

		// default copy and move assignment
		State<T>& operator= (const State<T> &rhs) = default;
		State<T>& operator= (State<T> &&rhs) noexcept = default;
	};

	// a wrapper of a transition type,
	// containing from-tags and to-id.
	template <typename T>
	struct Transition {

		// id and inner state
		transid m_id;
		T m_inner;

		// from and to ids
		std::set<stateid> m_from;
		stateid m_to;

		// conditions for transition
		std::map<std::string, bool> m_conditions;

		// forwarding constructor
		template <typename ...Ts>
		Transition (transid id, stateid from, stateid to, Ts &&...args) : 
			m_id { id },
			m_from { from }, m_to { to }, 
			m_inner { std::forward<Ts>(args)... } {}

		// default copy and move constructor
		Transition (const Transition<T> &rhs) = default;
		Transition (Transition<T> &&rhs) noexcept = default;

		// default copy and move assignment
		Transition<T>& operator= (const Transition<T> &rhs) = default;
		Transition<T>& operator= (Transition<T> &&rhs) noexcept = default;
	};

}