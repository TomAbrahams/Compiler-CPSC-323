#include "Assembly.h"


Assembly::Assembly()
{
	instructLocation = -1;
	instruction = "N/A";
	oprnd = "Not initialized";
}
Assembly::Assembly(int myInstrLoc, const string & instruct, const string & memLoc)
{
	instructLocation = myInstrLoc;
	instruction = instruct;
	if (memLoc == "nil")
		oprnd = "";
	else
		oprnd = memLoc;
}
//Getter functions.
int Assembly::getInstLoc() const
{
	return instructLocation;
}
string Assembly::getInstruction() const
{
	return instruction;
}
string Assembly::getOprnd() const
{
	return oprnd;
}
//Setter Location.
void Assembly::setInstLoc(int newLocation)
{
	instructLocation = newLocation;
}
void Assembly::setInstruction(const string & myInstruction)
{
	instruction =myInstruction;
}
void Assembly::setOprnd(const string & newOprnd)
{
	oprnd = newOprnd;
}
