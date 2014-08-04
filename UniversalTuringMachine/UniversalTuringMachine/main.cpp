#include <iostream>
#include <conio.h>
using namespace std;

#include <curses.h>

#include "TuringMachine.h"

WINDOW* SetupCurses();
void TearDownCurses(WINDOW *mainWindow);

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << argc << "Usage: turing [Turing Instructions Filepath] [Input String]" << endl
			<< "Example: turing \"C:\\my_turing_instructions.txt\" abbabaabaa" << endl;
		return 1;
	}

	string filepath = argv[1];
	string inputString = argv[2];
	bool isAutoStepped = false;
	
	WINDOW *console = SetupCurses();

	TuringMachine tm(filepath, inputString);
	tm.PrintRuleset();
	tm.Start(isAutoStepped);

	TearDownCurses(console);
	return 0;
}

WINDOW* SetupCurses()
{
	WINDOW *mainWindow = initscr();	// Start curses mode
	scrollok(mainWindow, true);		// Scroll terminal when text exceeds terminal height
	start_color();					// Initialise curses' color definitions & macros
	init_pair(0, COLOR_WHITE, COLOR_BLACK);		// Default text color
	init_pair(1, COLOR_GREEN, COLOR_YELLOW);	// Highlighted text color for turing machine tape position

	return mainWindow;
}

void TearDownCurses(WINDOW *mainWindow)
{
	_getch();
	delwin(mainWindow);
	endwin();
}