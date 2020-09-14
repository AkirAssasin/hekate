// <insert file header>

#pragma once

#include "HekateAgent.h"

namespace Hekate {

	// construct from a diagram
	template <typename D, typename I>
	template <typename ...Ts>
	Agent<D, I>::Agent (const Diagram &diagram, Ts &&...args) :
		Interpreter { std::forward<Ts>(args)... },
		m_diagram { diagram } {
	
		// call helper function in diagram
		m_diagram.InitializeAgent(*this);
	}

	// helper function for condition matching
	bool MatchMap (const std::map<std::string, bool> values, 
		const std::map<std::string, bool> conditions) {

		for (auto const &i : conditions) {
		
			// if can't find condition name, no match
			auto fv { values.find(i.first) };
			if (fv == values.cend()) return false;

			// if can't match condition value, no match
			if (fv->second != i.second) return false;
		}

		// all matched
		return true;
	}

	// update function
	template <typename D, typename I>
	void Agent<D, I>::Update () {
	
		if (m_currentState.has_value()) {
			
			// pass inner state to interpreter
			bool transable { I::UpdateState(m_currentState->m_inner) };

			// ask interpreter if transition is allowed
			if (transable) {
			
				// search for a valid transition
				for (auto const &i : m_transitions) {
				
					// try to match conditions
					if (MatchMap(m_conditions, i.second.m_conditions)) {

						// if matched, change to transition
						m_currentTransition = i.second;
						m_currentState = std::nullopt;
					}
				}
			}

		} else if (m_currentTransition.has_value()) {
		
			// pass inner state to interpreter
			bool transable { I::UpdateTransition(m_currentTransition->m_inner) };

			// ask interpreter if transition is allowed
			if (transable) {
				m_currentState = m_diagram.hmmmmmmm
				m_currentTransition = std::nullopt;
			}
		}
	}

	// set condition value
	template <typename D, typename I>
	void Agent<D, I>::SetConditionValue (const std::string &name, bool value);

}