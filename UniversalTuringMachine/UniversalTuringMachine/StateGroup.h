#ifndef STATEGROUP_H_
#define STATEGROUP_H_

#include <string>
#include <sstream>
#include <unordered_map>
using namespace std;

#include "Quintuple.h"

class StateGroup
{
public:
	unordered_map<char, Quintuple> quintuples;

	StateGroup();
	~StateGroup();

	void AddQuintuple(Quintuple quintuple);
	Quintuple* StateGroup::FindQuintuple(char readSymbol);
	Quintuple& operator[](char readSymbol);
	string ToString();
};

#endif // STATEGROUP_H_