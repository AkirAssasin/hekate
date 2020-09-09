// <insert file header>
/*
#pragma once

namespace Hekate {

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
}*/