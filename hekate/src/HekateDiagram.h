// <insert file header>

#pragma once

#include <vector>
#include <string>
#include <set>
#include <map>
#include <optional>
#include <algorithm>
#include <forward_list>
#include <iterator>

namespace Hekate {

	template <typename TDiagram>
	class Agent;

	template <typename TState, typename TTransition>
	class Diagram {

		using InnerState = TState;
		using InnerTransition = TTransition;

		// agent of this diagram is a friend.
		friend class Agent<Diagram<TState, TTransition>>;
	
		// a wrapper of a state type,
		// containing its tags. the state's
		// unique ID is its index.
		struct State {

			InnerState m_inner;
			std::set<long> m_tags;

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
		
			InnerTransition m_inner;
			long m_to;
			std::set<long> m_from;
			std::map<std::string, bool> m_conditions;

			// forwarding constructor
			template <typename ...Ts>
			Transition (Ts &&...args) : m_inner { std::forward<Ts>(args)... } {}

			// default copy constructor
			Transition (const Transition &rhs) = default;

			// default move constructor
			Transition (Transition &&rhs) = default;
		};
		std::vector<Transition> m_transitions;

		// a map of long to string tags and IDs
		// positive values are IDs, negative values are tags
		std::map<long, std::string> m_tags;

		// the starting ID of this state machine
		long m_startPoint;

		// a map of conditionals and their default values
		std::map<std::string, bool> m_conditions;

		// getter functions
		State CopyState (long id) const {
			return m_states[id];
		}

		template <typename TIt>
		void CopyTransitions (long from, TIt iterator) const {
		
			std::copy_if(std::begin(m_transitions), std::end(m_transitions),
				iterator, [](const Transition &t) => bool {
					return t.m_from.count(from) > 0;
				}
			);
		}
	
	};

	template <typename TDiagram>
	class Agent {
	public:
	
		// using aliases from the target diagram type
		using Diagram = TDiagram;
		using State = typename TDiagram::State;
		using Transition = typename TDiagram::Transition;

	private:

		// the diagram to reference
		const Diagram &m_diagram;

		// a map of string to bool conditionals
		std::map<std::string, bool> m_conditions;

		// the current state of this agent in the diagram
		long m_currentID;
		std::optional<State> m_currentState;
		std::optional<Transition> m_currentTransition;

		// a list of possible transitions
		std::forward_list<Transition> m_transitions;

	public:

		// construct from a machine
		Agent (const Diagram &diagram) : 
			m_diagram { diagram },
			m_conditions { m_diagram.m_conditions },
			m_currentID { m_diagram.m_startPoint },
			m_currentState { m_diagram.CopyState(m_currentID).m_inner },
			m_transitions {},
			m_currentTransition { std::nullopt } {
		
			m_diagram.CopyTransitions(m_currentID, std::front_inserter(m_transitions));
		}

		// update function
		void Update () {
		
			if (m_currentState.has_value()) {
			
				m_currentState->Update();

				if (m_currentState->IsUnlocked()) {
				
					for (Transition &t : m_transitions) {
					
						
					
					}
				
				}

			} else if (m_currentTransition.has_value()) {
			
			}
		
		}
		

	};
	
}