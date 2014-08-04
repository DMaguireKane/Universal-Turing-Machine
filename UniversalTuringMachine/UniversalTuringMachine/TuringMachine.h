#ifndef TURINGMACHINE_H_
#define TURINGMACHINE_H_

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#include "StateGroup.h"
#include "Quintuple.h"

class TuringMachine
{
private:
	unordered_map<string, StateGroup> stateGroups;

	vector<string> LoadTuringMachineInstructions(string filepath);
	Quintuple* FindQuintuple(string currentState, char readSymbol);
	void WriteSymbol(char symbol);
	void MoveCursor(char direction);
	void ChangeState(string outputState);

public:
	vector<string> instructions;
	vector<char> *tape;
	string currentState;
	char currentReadSymbol;
	int index;
	int stepCount;
	bool isHalted;

	TuringMachine(string instructionsFilePath, string input);
	~TuringMachine();

	vector<string> Split(const string &s);
	void AddQuintuple(Quintuple quintuple);
	void Step();
	void TuringMachine::TrimTape(char charToTrim);
	void PrintTape();
	string ToString();
	void Start(bool isAutoStepped);
	void PrintRuleset();
};

#endif // TURINGMACHINE_H_