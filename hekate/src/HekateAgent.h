// <insert file header>

#pragma once

#include <map>
#include <optional>
#include <string>
#include <forward_list>

namespace Hekate {

	template <typename TDiagram, typename TInterpreter>
	class Agent : public TInterpreter {
	public:

		// using aliases
		using Diagram = TDiagram;
		using StateType = typename TDiagram::StateType;
		using TransType = typename TDiagram::TransType;
		using Interpreter = TInterpreter;

		// give access to diagram
		friend class Diagram;

	private:

		// the diagram to reference
		const Diagram &m_diagram;

		// a map of string to bool conditionals
		std::map<std::string, bool> m_conditions;

		// the current state of this agent in the diagram
		std::optional<StateType> m_currentState;
		std::optional<TransType> m_currentTransition;

		// a list of possible transitions
		std::forward_list<TransType> m_transitions;

	public:

		// construct from a diagram
		template <typename ...Ts>
		Agent (const Diagram &diagram, Ts &&...args);

		// update function
		void Update ();

		// set condition value
		void SetConditionValue (const std::string &name, bool value);
	};
}

#include "HekateAgent.hpp"