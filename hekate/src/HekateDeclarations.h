// <insert file header>

#pragma once

namespace Hekate {

	// primitive type aliases
	using stateid = long;
	using transid = size_t;

	// undefineds
	constexpr stateid undefinedState = 0;

	// class declarations
	template <typename TDiagram, typename TInterpreter>
	class Agent;
}