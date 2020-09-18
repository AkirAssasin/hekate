#include <iostream>
#include <random>

#include "../src/HekateDiagram.h"

// example diagram structs
struct ExampleState {
	std::string m_str;
};
struct ExampleTransition {
	int m_num;
};

// example agent interpreter
struct ExampleAgentInterpreter {

	// interpreter must have this function
	bool UpdateState (ExampleState &state) {
		std::cout << "running state: " << state.m_str << std::endl;
		return true;
	}

	// interpreter must also have this function
	bool UpdateTransition (ExampleTransition &transition) {
		std::cout << "transitioning, num: " << transition.m_num << std::endl;
		return true;
	}
};

// quick aliases
using Diagram = Hekate::Diagram<ExampleState, ExampleTransition>;
using Agent = Hekate::Agent<Diagram, ExampleAgentInterpreter>;

// forward declarations
Diagram MakeTestDiagram ();
void TestDiagramAgent (const Diagram &diagram);

// main test program
int main () {
	
	// test diagram copy c-tor
 	Diagram diagram { MakeTestDiagram() };

	// debug print
	std::cout << "=== PRINTING DIAGRAM ===" << std::endl;
	diagram.DebugOut(std::cout);

	// test diagram agent
	std::cout << "\n=== RUNNING AGENT ===" << std::endl;
	TestDiagramAgent(diagram);
}

// make test diagram
Diagram MakeTestDiagram () {

	// make a empty diagram
	Diagram diagram;

	// test state making and naming
	Hekate::stateid stateID = diagram.AddNewState("sucky");
	diagram.GetName(stateID) = "sucky state";

	Hekate::stateid stateID2 = diagram.AddNewState("kekw");
	diagram.GetName(stateID2) = "kekw state";

	Hekate::stateid stateID3 = diagram.AddNewState("waifu");
	diagram.GetName(stateID3) = "waifu state";

	// test state id and removal
	diagram.RemoveState(stateID);
	stateID = diagram.AddNewState("sucky");
	diagram.GetName(stateID) = "sucky state 2";

	// test group making
	Hekate::stateid groupID = diagram.AddNewGroup();
	diagram.GetName(groupID) = "hololive";

	// test group assigning and removing state
	diagram.AddStateIntoGroup(stateID, groupID);
	diagram.AddStateIntoGroup(stateID2, groupID);
	diagram.AddStateIntoGroup(stateID3, groupID);
	diagram.RemoveStateFromGroup(stateID, groupID);

	// test group deleting
	Hekate::stateid groupID2 = diagram.AddNewGroup();
	diagram.GetName(groupID2) = "loner group";
	diagram.RemoveGroup(groupID);
	groupID = diagram.AddNewGroup();
	diagram.GetName(groupID) = "hololive 2";
	diagram.AddStateIntoGroup(stateID2, groupID);
	diagram.AddStateIntoGroup(stateID3, groupID);

	// test condition making
	diagram.AddNewCondition("isAyaya");
	diagram.AddNewCondition("isFriend", true);

	// test transition making
	Hekate::transid transID = diagram.AddNewTransition(stateID, stateID2, 0);
	Hekate::transid transID2 = diagram.AddNewTransition(groupID, stateID, 1);

	// test condition adding
	diagram.SetConditionToTransition("isAyaya", transID, true);
	diagram.SetConditionToTransition("isAsacoco", transID, true);
	diagram.SetConditionToTransition("isFriend", transID2, false);
	diagram.SetConditionToTransition("isAyaya", transID2, false);

	// test condition deleting
	diagram.RemoveConditionFromTransition("isAyaya", transID2);
	diagram.RemoveCondition("isAsacoco");

	// test condition renaming
	diagram.RenameCondition("isAyaya", "isWatame");

	// set starting point
	diagram.SetStartingState(stateID);

	// return the test diagram
	return diagram;
}

// run diagram agent
void TestDiagramAgent (const Diagram &diagram) {

	// make random distribution engine
	std::default_random_engine gen;
	std::uniform_int_distribution<int> roll { 0, 1 };


	// make agent
	Agent agent { diagram };

	// update agent
	for (int i = 0; i < 50; ++i) {

		// run update function
		agent.Update();

		// alternately change condition
		std::string conName { (i % 4 < 2) ? "isFriend" : "isWatame" };
		bool conVal { (i + 1) % 4 < 2 };
		std::cout << "setting agent's " << conName << " to " << conVal << std::endl;
		agent.SetConditionValue(conName, conVal);
		std::cout << std::endl;
	}
}