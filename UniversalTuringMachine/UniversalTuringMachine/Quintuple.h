#ifndef QUINTUPLE_H_
#define QUINTUPLE_H_

#include <string>
#include <sstream>
using namespace std;

class Quintuple
{
public:

	string inputState;
	char readSymbol;
	char writeSymbol;
	char direction;
	string outputState;

	Quintuple();
	Quintuple(string inputState, char readSymbol, char writeSymbol, char direction, string outputState);
	~Quintuple();

	string ToString();
};

#endif // QUINTUPLE_H_

