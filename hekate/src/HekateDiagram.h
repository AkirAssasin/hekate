// <insert file header>

#pragma once

#include <vector>
#include <string>
#include <set>
#include <map>

namespace Hekate {

	template <typename TDiagram>
	class Agent;

	template <typename TState, typename TTransition>
	class Diagram {

		// agent of this diagram is a friend.
		friend class Agent<Diagram<TState, TTransition>>;
	
		// a wrapper of a state type,
		// containing tags and its unique id.
		struct State {

			TState m_inner;
			size_t m_uid;
			std::set<size_t> m_tags;

			// forwarding constructor
			template <typename ...Ts>
			State (Ts &&...args) : m_inner { std::forward<Ts>(args)... } {}

			// default copy constructor
			State (const State &rhs) = default;

			// default move constructor
			State (State &&rhs) = default;
		};
		std::vector<State> m_states;

		// a wrapper of a transition type,
		// containing from-tags and to-id.
		struct Transition {
		
			TTransition m_inner;
			size_t m_to;
			std::set<size_t> m_from;

			// forwarding constructor
			template <typename ...Ts>
			Transition (Ts &&...args) : m_inner { std::forward<Ts>(args)... } {}

			// default copy constructor
			Transition (const Transition &rhs) = default;

			// default move constructor
			Transition (Transition &&rhs) = default;
		};
		std::vector<Transition> m_transitions;

		// a map of size_t to string tags and IDs
		std::map<size_t, std::string> m_tags;
	
	};

	template <typename TDiagram>
	class Agent {
	
		// using aliases from the target diagram type
		using State = typename TDiagram::State;
		using Transition = typename TDiagram::Transition;
	
	};

}