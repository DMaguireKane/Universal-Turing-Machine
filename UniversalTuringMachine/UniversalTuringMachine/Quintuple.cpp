#include "Quintuple.h"


Quintuple::Quintuple()
{
}

Quintuple::Quintuple(string inputState, char readSymbol, char writeSymbol, char direction, string outputState)
	:inputState(inputState), readSymbol(readSymbol), writeSymbol(writeSymbol), direction(direction), outputState(outputState)
{
}

Quintuple::~Quintuple()
{
}

string Quintuple::ToString()
{
	char readSymbolForDisplay = readSymbol != ' ' ? readSymbol : '_';
	char writeSymbolForDisplay = writeSymbol != ' ' ? writeSymbol : '_';

	stringstream ss;
	ss << inputState << " "
		<< readSymbolForDisplay << " "
		<< writeSymbolForDisplay << " "
		<< direction << " "
		<< outputState << endl;

	return ss.str();
}