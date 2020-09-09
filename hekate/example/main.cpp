#include <iostream>

#include "../src/HekateDiagram.h"

struct ExampleState {};
struct ExampleTransition {};

int main () {

	// quick aliases
	using Diagram = Hekate::Diagram<ExampleState, ExampleTransition>;
	Diagram diagram;

	// test state id-making and naming
	Hekate::stateid stateID = diagram.AddNewState();
	diagram.GetName(stateID) = "sucky state";
	std::cout << "new state's id is " << stateID << ", name is " << diagram.GetName(stateID) << std::endl;
	Hekate::stateid stateID2 = diagram.AddNewState();
	std::cout << "new state's id is " << stateID2 << ", name is " << diagram.GetName(stateID2) << std::endl;
	diagram.RemoveState(stateID);
	stateID = diagram.AddNewState();
	std::cout << "new state's id is " << stateID << ", name is " << diagram.GetName(stateID) << std::endl;

	// test transition-making
	diagram.AddNewTransition(stateID, stateID2);

}