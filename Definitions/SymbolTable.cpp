#include "TokenList.h"
#include <iomanip>

void TokenList::makeSymbolTable()
{
	//Check all items in the vec tokens list
	for (unsigned int i = 0; i < vecTokens.size(); i++)
	{
		//Found an identifier.
		if (vecTokens[i].getTokenType() == "identifier")
		{
			bool found = false;
			//Is the identifier already on the list?
			for (unsigned int j = 0; j < symbolTable.size() && !found; j++)
			{
				if (vecTokens[i].getLexeme() == symbolTable[j].getLexeme())
					found = true;
			}
			//Was not found in the table, so push the unique identifier back.
			bool checkInt = vecTokens[i - 1].getLexeme() == "integer";
			bool checkComma = (vecTokens[i - 1].getLexeme() == ",");
			if (!found && (checkInt || checkComma))
			{
				//Push the memory address in
				vecTokens[i].setAddress(Memory_address);
				//Push the token in the identifier
				symbolTable.push_back(vecTokens[i]);
				//Increment the memory address
				Memory_address++;
				//Do I do it after or during?
			}
			else if (!found)
			{
				cerr << "Unidentified identifier. Will not generate symbol table or assembly table.\n";
				system("pause");
				exit(-1);
			}
		}
	}
}
bool TokenList::checkDuplicate(const string & varName)
{
	bool found = false;
	for (unsigned int i = 0; i < symbolTable.size() && !found; i++)
	{
		if (symbolTable[i].getLexeme() == varName)
			found = true;
	}
	return found;
}
void TokenList::printSymbolTable(ofstream & myOutput)
{
	//Write to a text file.
	//Column 1
	myOutput << "Identifier";
	myOutput << setw(20);
	myOutput << "\t";
	//Column 2
	myOutput << "Memory Location";
	myOutput << setw(20);
	myOutput << "\t";
	//Column 3
	myOutput << "Type";
	myOutput << setw(20);
	myOutput << "\t";
	myOutput << endl;
	//Print the tokens.
	for (unsigned int i = 0; i < symbolTable.size(); i++)
	{
		//Column 1
		myOutput << symbolTable[i].getLexeme();
			
		myOutput << setw(20);
		myOutput << "\t";
		//Column 2
		myOutput << symbolTable[i].getAddress();
		myOutput << setw(20);
		myOutput << "\t";
		//Column 3
		myOutput << symbolTable[i].getTokenType();
		myOutput << setw(20);
		myOutput << "\t";
		myOutput << endl;
	}

	//Write to a text file.
	//Column 1
	cout << "Identifier";
	cout << setw(20);
	cout << "\t";
	//Column 2
	cout << "Memory Location";
	cout << setw(20);
	cout << "\t";
	//Column 3
	cout << "Type";
	cout << setw(20);
	cout << "\t";
	cout << endl;
	//Print the tokens.
	for (unsigned int i = 0; i < symbolTable.size(); i++)
	{
		//Column 1
		cout << symbolTable[i].getLexeme();

		cout << setw(20);
		cout << "\t";
		//Column 2
		cout << symbolTable[i].getAddress();
		cout << setw(20);
		cout << "\t";
		//Column 3
		cout << symbolTable[i].getTokenType();
		cout << setw(20);
		cout << "\t";
		cout << endl;
	}
}
