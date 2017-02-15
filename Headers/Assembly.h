#ifndef ASSEMBLY_H
#define ASSEMBLY_H
#include<iostream>
#include<iomanip>
#include<string>
//#include<fstream>
using namespace std;

class Assembly {

public:
	Assembly();
	Assembly(int myInstrLoc, const string & instruct, const string & memLoc);
	//Getter functions.
	int getInstLoc() const;
	string getInstruction() const;
	string getOprnd() const;
	//Setter Location.
	void setInstLoc(int newLocation);
	void setInstruction(const string & myInstruction);
	void setOprnd(const string & newOprnd);
private:
	int instructLocation;
	string instruction;
	string oprnd;
};

#endif
