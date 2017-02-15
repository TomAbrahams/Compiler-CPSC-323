/*
Abrahams, Thomas
December 9, 2016
CPSC 323-01 Compilers
Instructor Dr. Choi
*/

#include<iostream>
#include<string>
#include"TokenList.h"

using namespace std;


int main() {
	string filename;
	string choice;
	do
	{
		choice = "";
		cout << "Note: Please put the text file in the same directory as this executable." << endl;
		cout << endl;
		cout << "What is the name of your text file?" << endl;
		cin >> filename;
		cout << "Checking for file..." << endl;
		TokenList myTokenList;
		myTokenList.setTextFile(filename);
		//Make a Token List
		myTokenList.FSM();
		//Make a Symbol Table
		myTokenList.makeSymbolTable();
		if (myTokenList.getListSize() == 0)
			cerr << "No file found" << endl;		
		else
		{
			//myTokenList.print();
			myTokenList.writeToken();
		}
		//The symbol table.
		//Generate symbol table to text file.

		
		//check to see if they want to check another file.
		while (choice != "y" && choice != "n")
		{
			cout << "Would you like to check another file? (y is for yes, n is for no)" << endl;
			cin >> choice;
			if (choice != "y" && choice != "n")
				cerr << "This is not a valid choice." << endl;
		}
		system("CLS");
		/*
		if (choice == "n")
		{
			cout << "Thank you for using Tom's Lexical Analyzer" << endl;

			cout << "Time to test the syntatical analyzer" << endl;
			int index = 0;
			bool flag = true;
			myTokenList.rat16(flag, index);
		}
		*/
	} while (choice == "y");
	
	system("pause");

	return 0;
}
