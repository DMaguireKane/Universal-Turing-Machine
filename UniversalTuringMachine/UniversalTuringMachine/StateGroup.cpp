#include "StateGroup.h"


StateGroup::StateGroup()
{
}


StateGroup::~StateGroup()
{
}

void StateGroup::AddQuintuple(Quintuple quintuple)
{
	quintuples[quintuple.readSymbol] = quintuple;
}

Quintuple* StateGroup::FindQuintuple(char readSymbol)
{
	unordered_map<char, Quintuple>::iterator quintupleIt;
	unordered_map<char, Quintuple>::iterator wildcardIt = quintuples.end();

	for (quintupleIt = quintuples.begin(), wildcardIt = quintuples.end(); quintupleIt != quintuples.end(); ++quintupleIt)
	{
		if (quintupleIt->second.readSymbol == readSymbol)
		{
			return new Quintuple(quintupleIt->second);
		}
		else if (quintupleIt->second.readSymbol == '*')
		{
			wildcardIt = quintupleIt;
		}
	}

	if (wildcardIt != quintuples.end())
	{
		return new Quintuple(wildcardIt->second);
	}

	return NULL;
}

Quintuple& StateGroup::operator[](char readSymbol)
{
	if (quintuples.find(readSymbol) == quintuples.end())
	{
		if (quintuples.find('*') != quintuples.end())
		{
			return quintuples['*'];
		}
		
		stringstream ss;
		ss << "Read Symbol: '" << readSymbol << "' does not exist.";
		throw invalid_argument(ss.str().c_str());
	}

	return quintuples[readSymbol];
}

string StateGroup::ToString()
{
	stringstream ss;
	for (unordered_map<char, Quintuple>::iterator it = quintuples.begin(); it != quintuples.end(); ++it)
	{
		ss << it->second.ToString();
	}

	return ss.str();
}