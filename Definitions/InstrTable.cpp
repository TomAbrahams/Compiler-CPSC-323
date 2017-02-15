#include "TokenList.h"

void TokenList::back_patch(const string & jump_address)
{
	int address = atoi(jumpstack.top().c_str());	//Get the address of the top.
	jumpstack.pop();								//Pop the stack
	instrTable[address].setOprnd(jump_address);		//Table assembly address  sets the item to the jump location for the next instruction.
}
void TokenList::back_patch(int jump_address)
{

	int address = atoi(jumpstack.top().c_str());
	jumpstack.pop();
	instrTable[address-1].setOprnd(to_string(jump_address));

}
void TokenList::push_jumpstack(const string & instr_address)
{
	jumpstack.push(instr_address);
}
void TokenList::push_jumpstack(int instr_address)
{
	string str_instr_address = to_string(instr_address);
	jumpstack.push(str_instr_address);
}
int TokenList::get_address(const Token & myToken)
{
	bool found = false;
	int address = -1;
	for (unsigned int i = 0; (i < symbolTable.size()) && !found; i++)
	{
		if (myToken.getLexeme() == symbolTable[i].getLexeme())
		{
			found = true;
			address = symbolTable[i].getAddress();
		}
	}
	return address;
}
void TokenList::gen_instr(const string & command, const string & myOprnd)
{
	//if (myOprnd != "-1")
	//{
		Assembly assembleInst(Instruct_location, command, myOprnd);
		instrTable.push_back(assembleInst);
		Instruct_location++;
	//}
	/*
	if (myOprnd == ")
	{
		//Creates the assemble instruction
		Assembly assembleInst(Instruct_location, command, 0);
		//Adds the instruction to the vector.
		Instruc.push_back(assembleInst);
		//Increment the vector.
		Instruct_location++;
	}
	else if (address > 0)
	{
		//Creates the assemble instruction
		Assembly assembleInst(Instruct_location, command, address);
		//Adds the instruction to the vector.
		vecAssembly.push_back(assembleInst);
		//Increment the vector.
		Instruct_location++;
	}
	*/
}
void TokenList::gen_instr(const string & command, int myOprnd)
{
	if (myOprnd != -1)
	{
		string value = to_string(myOprnd);
		gen_instr(command, value);
	}
}
void TokenList::printInstrTable(char choice, const string & fileName)
{
	string writeInstrTable = fileName;
	ofstream myOutput;
	char choiceInstrTbl = choice;	//The choice changed
	//std::cout << "Would you like to make an instruction table?" << endl;
	//cin >> choiceInstrTbl;

	if (choiceInstrTbl == 'y')
	{
		
		//std::cin >> writeInstrTable;
		writeInstrTable.append(".itbl");
		myOutput.open(writeInstrTable, std::ofstream::out);
		//Write to a text file.
		//Column 1
		myOutput << "Instr_Address";
		myOutput << setw(20);
		//myOutput << "\t";
		//Column 2
		myOutput << "Operation";
		myOutput << setw(20);
		//myOutput << "\t";
		//Column 3
		myOutput << "Operand";
		myOutput << setw(20);
		//myOutput << "\t";
		myOutput << endl;
		//Print the tokens.
		for (unsigned int i = 0; i < instrTable.size(); i++)
		{
			//Column 1
			myOutput << instrTable[i].getInstLoc();

			myOutput << setw(20);
			//myOutput << "\t";
			//Column 2
			myOutput << instrTable[i].getInstruction();
			myOutput << setw(20);
			//myOutput << "\t";
			//Column 3
			myOutput << instrTable[i].getOprnd();
			myOutput << setw(20);
			//myOutput << "\t";
			myOutput << endl;
		}

		//Write to a text file.
		//Column 1
		std::cout << "Instr_Address";
		std::cout << setw(20);
		std::cout << "\t";
		//Column 2
		std::cout << "Operation";
		std::cout << setw(20);
		std::cout << "\t";
		//Column 3
		std::cout << "Operand";
		std::cout << setw(20);
		std::cout << "\t";
		std::cout << endl;
		//Print the tokens.
		for (unsigned int i = 0; i < instrTable.size(); i++)
		{
			//Column 1
			std::cout << i + 1 << endl;

			std::cout << setw(20);
			std::cout << "\t";
			//Column 2
			std::cout << instrTable[i].getInstruction();
			std::cout << setw(20);
			std::cout << "\t";
			//Column 3
			std::cout << instrTable[i].getOprnd();
			std::cout << setw(20);
			std::cout << "\t";
			std::cout << endl;
		}
		
	}
	myOutput.close();
}
