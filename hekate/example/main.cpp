#include <iostream>

#include "../src/HekateDiagram.h"

struct ExampleState {};
struct ExampleTransition {};

int main () {

	// quick aliases
	using Diagram = Hekate::Diagram<ExampleState, ExampleTransition>;
	Diagram diagram;

	// test state making and naming
	Hekate::stateid stateID = diagram.AddNewState();
	diagram.GetName(stateID) = "sucky state";

	Hekate::stateid stateID2 = diagram.AddNewState();
	diagram.GetName(stateID2) = "kekw state";

	Hekate::stateid stateID3 = diagram.AddNewState();
	diagram.GetName(stateID3) = "waifu state";

	// test state id and removal
	diagram.RemoveState(stateID);
	stateID = diagram.AddNewState();
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
	Hekate::transid transID = diagram.AddNewTransition(stateID, stateID2);
	Hekate::transid transID2 = diagram.AddNewTransition(groupID, stateID);

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

	// debug print
	diagram.DebugOut(std::cout);

}