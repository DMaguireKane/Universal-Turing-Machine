#include <conio.h>
#include <curses.h>

#include "TuringMachine.h"

vector<string> TuringMachine::LoadTuringMachineInstructions(string filepath)
{
	string line;
	vector<string> myLines;
	ifstream file(filepath);

	while (getline(file, line))
	{
		myLines.push_back(line);
	}

	return myLines;
}

Quintuple* TuringMachine::FindQuintuple(string currentState, char readSymbol)
{
	unordered_map<string, StateGroup>::iterator sgIt = stateGroups.find(currentState);
	if (sgIt != stateGroups.end())
	{
		return sgIt->second.FindQuintuple(readSymbol);
	}

	return NULL;
}

void TuringMachine::WriteSymbol(char symbolToWrite)
{
	if (symbolToWrite == '*')
	{
		(*tape)[index] = currentReadSymbol;
	}
	else
	{
		(*tape)[index] = symbolToWrite;
	}
}

void TuringMachine::MoveCursor(char direction)
{
	if (direction == '*')
		return;

	if (direction == 'L')
	{
		if (index == 0)
			tape->insert(tape->begin(), ' ');
		else
			index--;
	}
	else if (direction == 'R')
	{
		index++;
		if (index == tape->size())
			tape->insert(tape->begin() + index, ' ');
	}
}

void TuringMachine::ChangeState(string outputState)
{
	currentState = outputState;
	if (currentState == "halt")
	{
		printw("%7s: Halted", " ");
		isHalted = true;
	}
}

TuringMachine::~TuringMachine()
{
	delete tape;
}

vector<string> TuringMachine::Split(const string &s)
{
	vector<string> symbols;
	stringstream stream(s);
	string symbol;

	while (getline(stream, symbol, ' '))
	{
		symbols.push_back(symbol);
	}

	return symbols;
}

TuringMachine::TuringMachine(string instructionsFilePath, string input)
: currentState("0"),
index(0),
stepCount(0),
isHalted(false)
{
	if (input.empty())
	{
		input = " ";
	}

	tape = new vector<char>(input.begin(), input.end());

	for each(string s in LoadTuringMachineInstructions(instructionsFilePath))
	{
		if (!s.empty())
		{
			vector<string> parts = Split(s);

			Quintuple quintuple;
			quintuple.inputState = parts[0];
			quintuple.readSymbol = parts[1][0] != '_' ? parts[1][0] : ' ';
			quintuple.writeSymbol = parts[2][0] != '_' ? parts[2][0] : ' ';
			quintuple.direction = parts[3][0];
			quintuple.outputState = parts[4];

			AddQuintuple(quintuple);
		}
	}
}

void TuringMachine::AddQuintuple(Quintuple quintuple)
{
	if (stateGroups.find(quintuple.inputState) == stateGroups.end())
	{
		StateGroup stateGroup;
		stateGroups[quintuple.inputState] = stateGroup;
	}

	stateGroups[quintuple.inputState].AddQuintuple(quintuple);
}

void TuringMachine::Step()
{
	if (isHalted)
	{
		return;
	}

	currentReadSymbol = (*tape)[index];

	Quintuple *q = FindQuintuple(currentState, currentReadSymbol);
	if (!q)
	{
		printw("No rule found for state '%s', symbol '%c'. Halted.\n", currentState.c_str(), currentReadSymbol);
		isHalted = true;
		return;
	}

	WriteSymbol(q->writeSymbol);
	MoveCursor(q->direction);
	ChangeState(q->outputState);
	
	TrimTape(' ');
	stepCount++;

	if (q)
		delete q;
}

void TuringMachine::TrimTape(char charToTrim)
{
	vector<char>::iterator it;

	// Trim matched leading characters
	for (it = tape->begin(); (*it) == charToTrim && it != tape->end(); ++it)
	{
		if (it >= tape->begin() + index)
			break;
	}
	tape->erase(tape->begin(), it);

	// Trim matched trailing characters
	for (it = tape->end()-1; (*it) == charToTrim && it != tape->begin(); --it)
	{
		if (it <= tape->begin() + index)
			break;
	}
	tape->erase(it + 1, tape->end());
}

void TuringMachine::PrintTape()
{
	printw("%7d%s", stepCount, ": ");
	for (vector<char>::iterator it = tape->begin(); it != tape->end(); ++it)
	{
		if (it == tape->begin() + index)
		{
			color_set(1, NULL);
			addch(*it | A_STANDOUT | A_BOLD);
		}
		else
		{
			color_set(0, NULL);
			addch(*it | A_NORMAL);
		}
	}
	printw("\n");
}

string TuringMachine::ToString()
{
	stringstream ss;
	for (unordered_map<string, StateGroup>::iterator it = stateGroups.begin(); it != stateGroups.end(); ++it)
	{
		ss << it->second.ToString();
	}

	return ss.str();
}

/* Prints each step of the input string as processed by the universal turing machine.
   If isAutoStepped then all steps are printed to the console
   otherwise the program waits for a keypress before printing the next step.*/
void TuringMachine::Start(bool isAutoStepped)
{
	if (!isAutoStepped)
	{
		printw("Press any key to step through the turing operation\n");
	}

	PrintTape();
	refresh(); // Print the curses buffer to the screen

	while (!isHalted && (isAutoStepped || _getch() != 'q'))
	{
		Step();

		if (!isHalted)
			PrintTape();

		refresh();
		color_set(0, NULL);
	}
}

void TuringMachine::PrintRuleset()
{
	printw(ToString().c_str());
}