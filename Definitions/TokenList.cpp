#include"TokenList.h"

//Constructor
TokenList::TokenList() {
	initialize();
}
void TokenList::initialize() {
	//Setup Real Int Finite State Machines
	tableRealInt[0][0] = 1;
	tableRealInt[0][1] = 4;
	tableRealInt[0][2] = 5;

	tableRealInt[1][0] = 1;
	tableRealInt[1][1] = 2;
	tableRealInt[1][2] = 5;

	tableRealInt[2][0] = 3;
	tableRealInt[2][1] = 4;
	tableRealInt[2][2] = 5;

	tableRealInt[3][0] = 3;
	tableRealInt[3][1] = 4;
	tableRealInt[3][2] = 5;

	tableRealInt[4][0] = 4;
	tableRealInt[4][1] = 4;
	tableRealInt[4][2] = 5;

	tableRealInt[5][0] = 5;
	tableRealInt[5][1] = 5;
	tableRealInt[5][2] = 5;

	//Setup Words Finite State Machines
	tableIdFSM[0][0] = 1;
	tableIdFSM[0][1] = 6;
	tableIdFSM[0][2] = 6;
	tableIdFSM[0][3] = 7;

	tableIdFSM[1][0] = 2;
	tableIdFSM[1][1] = 3;
	tableIdFSM[1][2] = 4;
	tableIdFSM[1][3] = 7;

	tableIdFSM[2][0] = 2;
	tableIdFSM[2][1] = 5;
	tableIdFSM[2][2] = 4;
	tableIdFSM[2][3] = 7;

	tableIdFSM[3][0] = 2;
	tableIdFSM[3][1] = 5;
	tableIdFSM[3][2] = 4;
	tableIdFSM[3][3] = 7;

	tableIdFSM[4][0] = 2;
	tableIdFSM[4][1] = 5;
	tableIdFSM[4][2] = 4;
	tableIdFSM[4][3] = 7;

	tableIdFSM[5][0] = 2;
	tableIdFSM[5][1] = 5;
	tableIdFSM[5][2] = 4;
	tableIdFSM[5][3] = 7;

	tableIdFSM[6][0] = 6;
	tableIdFSM[6][1] = 6;
	tableIdFSM[6][2] = 6;
	tableIdFSM[6][3] = 7;

	tableIdFSM[7][0] = 7;
	tableIdFSM[7][1] = 7;
	tableIdFSM[7][2] = 7;
	tableIdFSM[7][3] = 7;

	//Keywords
	keywords.push_back("if");
	keywords.push_back("else");
	keywords.push_back("endif");
	keywords.push_back("then");
	keywords.push_back("for");
	keywords.push_back("while");
	keywords.push_back("this");
	keywords.push_back("return");
	keywords.push_back("read");
	keywords.push_back("function");
	keywords.push_back("print");
	keywords.push_back("integer");
	keywords.push_back("real");
	keywords.push_back("boolean");
	keywords.push_back("function");
	keywords.push_back("true");
	keywords.push_back("false");

	Memory_address = 6000;
	Instruct_location = 1;

}
//Overloaded Constructor
TokenList::TokenList(const string & myTextLocation)
{
	initialize();
	textLocation = myTextLocation;
}
//Adding a token
void TokenList::addToken(const string & myTokenType, const string & myLexeme, int myLineNumber) {
	Token myToken;
	myToken.setLexeme(myLexeme);
	myToken.setTokenType(myTokenType);
	myToken.setLineNumber(myLineNumber);
	vecTokens.push_back(myToken);
}
//My list
void TokenList::FSM()
{
	bool flagID = false;
	string line;
	ifstream myFile(textLocation);
	int currentState = 0;
	if (myFile.is_open())
	{
		int lineCounter = 1;	//This is to remember the line number.
		while (getline(myFile, line))
		{
			//line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
			replace(line.begin(), line.end(), '\t', ' ');
			line.push_back(' ');
			for (unsigned int cp = 0; cp < line.length(); cp++)
			{
				//Check the character

				char currentCharacter = line[cp];

				int currentChoice;
				if (currentCharacter != ' ')
					currentChoice = FSMdecider(currentCharacter);
				else
					currentChoice = 3;

				if (currentChoice == 2)
				{
					realIntFSM(line, cp, flagID, lineCounter);
					cp--;	//Since this will double increment.
					flagID = true;
				}
				else if (currentChoice == 1)
				{
					identifierFSM(line, cp, lineCounter);
					cp--;	//Since this will double increment.
					flagID = false;
				}
			}
			currentState = 0;
			lineCounter++;
		}
	}


}
//Printing a token
void TokenList::print() {
	cout << "Lexeme" << "\t" << "Token" << endl;
	for (unsigned int i = 0; i < vecTokens.size(); i++)
	{
		vecTokens[i].printToken();
	}
}
//Identifier FSM
void TokenList::identifierFSM(string myLine, unsigned int & index, int lineCounter) {
	//Make sure that there is a space at the end to prevent overbleed.


	//Need to keep a previous state
	int previousState = 0;
	int currentState = 0;
	char currentChar;
	bool flag = false;
	bool flagEnd = false;
	//Place to hold the string
	string temp;
	int fState[4] = { 1, 2, 5, 7 }; //Finishing States

									//Current State
									//If unknown and the previous statement was at a finish state then okay.
	for (index; index < myLine.size() && !flagEnd; index++)
	{
		currentChar = myLine[index];
		previousState = currentState;
		currentState = transitionStateIdFSM(currentState, currentChar);
		temp.push_back(currentChar);
		if (endOfSymbols(myLine, index))
		{
			//This is an identifier or keyword.
			if (previousState == fState[0] || previousState == fState[1] || previousState == fState[2])
			{
				temp.pop_back();
				if (identifierKeywords(temp))
					addToken("keyword", temp, lineCounter);
				else
					addToken("identifier", temp, lineCounter);
				temp.clear();
				currentState = 0;
				previousState = 0;
				if (myLine[index] != ' ')
					index--;
				flagEnd = true;
			}
			//Check to see if the item is an operator.
			else if (identifierSymbols(myLine, index, temp) > 0 && currentState == fState[3])
			{
				if (myLine[index] == ' ')
					temp.pop_back();
				addToken("Operators", temp, lineCounter);
				temp.clear();
				currentState = 0;
				previousState = 0;
				//I know this is an operator, so I can proceed.
				flagEnd = true;
			}
			//If it is a separator.
			else if (identifierSeparators(myLine, index, temp) >0 && currentState == fState[3])
			{
				if (myLine[index] == ' ')
					temp.pop_back();
				addToken("Separators", temp, lineCounter);
				temp.clear();
				//Return all items back to a previous state
				currentState = 0;
				previousState = 0;
				//I know this is a separator so I can proceed.
				flagEnd = true;
			}
			else if (previousState == fState[3] || (previousState == 4 && currentState == fState[3]))
			{
				temp.pop_back();
				addToken("Unknown", temp, lineCounter);
				temp.clear();
				//Return all items back to a previous state
				currentState = 0;
				previousState = 0;
				if (myLine[index] = ' ')
					index--;
				flagEnd = true;
			}
		}
	}
}
//Transition State for ID FSM
int TokenList::transitionStateIdFSM(int currentState, char letter) {
	int transitionState = convertFSMIdToCol(letter);
	transitionState = tableIdFSM[currentState][transitionState];
	return transitionState;
}
//ConvertsLetterToCol for ID FSM
int TokenList::convertFSMIdToCol(char letter)
{
	int transitionColumn;
	bool found = false;
	for (unsigned int i = 0; i < lowerLetter.size() && !found; i++)
	{
		if (letter == lowerLetter[i])
		{
			transitionColumn = 0;
			found = true;
		}

	}
	for (unsigned int i = 0; i < upperLetter.size() && !found; i++)
	{
		if (letter == upperLetter[i])
		{
			transitionColumn = 0;
			found = true;
		}
	}
	for (unsigned int i = 0; i < digits.size(); i++)
	{
		if (letter == digits[i] && !found)
		{
			transitionColumn = 1;
			found = true;
		}
	}
	if (letter == '_')
	{
		transitionColumn = 2;
		found = true;
	}
	if (!found)
	{
		transitionColumn = 3;
	}
	return transitionColumn;
}
//Real Int FSM
void TokenList::realIntFSM(const string& myLine, unsigned int & index, bool & idFlag, int lineCounter) {
	int currentState = 0;
	int previousState = 0;
	string temp;

	bool stateFound = false;
	bool flagSwitchFSM = false;
	bool symbolFSMFlag = false;
	//Finishing States
	int integerState = 1;
	int realState = 3;
	int unknownState = 5;



	for (index; index < myLine.size() && !stateFound; index++)
	{
		char currentCharacter = myLine[index];
		previousState = currentState;
		currentState = transitionStateRealId(currentState, myLine[index]);
		temp.push_back(currentCharacter);
		//Could be an identifier.
		if (previousState == 0 && currentState == 5)
		{
			//Immediately switch to identifier FSM.
			stateFound = true;
			idFlag = true;
			flagSwitchFSM = true;
			index--;
		}
		else if (endOfSymbols(myLine, index)) //Symbol spotted, check it it is a real 
		{
			//For integers.
			if (previousState == integerState)
			{
				temp.pop_back();
				addToken("Integer", temp, lineCounter);
				temp.clear();
				currentState = 0;
				previousState = 0;
				stateFound = true;
				if (myLine[index] != ' ')
					index--;
			}
			else if (previousState == realState)
			{
				temp.pop_back();
				addToken("Real", temp, lineCounter);
				temp.clear();
				currentState = 0;
				previousState = 0;
				stateFound = true;
				if (myLine[index] != ' ')
					index--;
			}
			else if (previousState == unknownState)
			{
				temp.pop_back();
				addToken("Unknown", temp, lineCounter);
				temp.clear();
				currentState = 0;
				previousState = 0;
				stateFound = true;
				if (myLine[index] != ' ')
					index--;
			}
		}
	}
}
int TokenList::transitionStateRealId(int currentState, char letter) {
	int transitionState = convertIntFSMIntRealCol(letter);
	transitionState = tableRealInt[currentState][transitionState];
	return transitionState;
}
int TokenList::convertIntFSMIntRealCol(char letter)
{
	int transitionColumn;
	bool found = false;
	for (unsigned int i = 0; i < digits.size(); i++)
	{
		if (letter == digits[i] && !found)
		{
			transitionColumn = 0;
			found = true;
		}
	}
	if (letter == '.')
	{
		transitionColumn = 1;
		found = true;
	}
	if (!found)
	{
		transitionColumn = 2;
	}
	return transitionColumn;
}
//Identifier Symbols
int TokenList::identifierSymbols(const string& myLine, unsigned int & index, string & temp) {
	char myCurrentChar = myLine[index];
	bool found = false;
	int status = 0;
	//temp.clear();
	for (unsigned int i = 0; 2 * i < operatorsTwo.size() - 1 && !found; i++)
	{
		if (myLine[index] == operatorsTwo[2 * i] || myLine[index + 1] == operatorsTwo[2 * i + 1] && !found)
		{
			status = -1;
		}
		if (myLine[index] == operatorsTwo[2 * i] && myLine[index + 1] == operatorsTwo[2 * i + 1])
		{
			string strLexeme;
			strLexeme.push_back(myLine[index]);
			strLexeme.push_back(myLine[index + 1]);
			temp = strLexeme;
			found = true;
			status = 2;
			index++; //Changed from one in case 2 indexes need to be moved.
		}
	}
	if (!found)
	{
		for (unsigned int j = 0; j < operatorsOne.size() && !found; j++)
		{
			if (myLine[index] == operatorsOne[j])
			{
				string strLexeme;
				strLexeme.push_back(myLine[index]);
				temp = strLexeme;
				found = true;
				status = 1;
			}
		}
	}
	return status;
}
//Indentifier Keywords
bool TokenList::identifierKeywords(const string& myIdentifier) {
	bool flag = false;

	string curMyWord = myIdentifier;
	if (curMyWord[curMyWord.length() - 1] == ' ')
		curMyWord.pop_back();

	for (unsigned int i = 0; i < keywords.size(); i++)
	{
		//Debug
		string curKeywords = keywords[i];


		if (curMyWord == keywords[i])
		{
			flag = true;
		}
	}
	return flag;
}
//Indentifier Separators
int TokenList::identifierSeparators(const string & myLine, unsigned int & index, string &temp) {
	char myCurrentChar = myLine[index];

	bool found = false;

	int status = 0; //None = 0, Seperator one = 1, Seperator two = 2, Only one part of the $$ is found -1.
	for (unsigned int i = 0; i < separatorOne.size() && !found; i++)
	{
		if (myLine[index] == separatorOne[i])
		{
			string strLexeme;
			strLexeme.push_back(myLine[index]);
			temp = strLexeme;
			found = true;
			status = 1;
		}
	}
	if (index < myLine.size() - 1)
	{
		char myCurrentCharNxt = myLine[index + 1];
		if (myLine[index] == '$' && myLine[index + 1] == '$')
		{
			string strLexeme;
			strLexeme.push_back(myLine[index]);
			strLexeme.push_back(myLine[index + 1]);
			temp = strLexeme;
			found = true;
			index++;
			status = 2;
		}
		else if (myLine[index] == '$' && myLine[index + 1] != '$')
		{
			string strLexeme;
			strLexeme.push_back(myLine[index]);
			temp = strLexeme;
			status = -1;
		}
	}
	return status;
}
//Check if done
bool TokenList::endOfSymbols(const string & myLine, unsigned int & index)
{
	bool found = false;
	string symbols = "+-*/<>=!:(){}[]$,;: ";
	char currentChar = myLine[index];
	for (unsigned int i = 0; !found && i < symbols.size(); i++)
	{
		if (myLine[index] == symbols[i])
		{
			found = true;
		}
	}
	return found;
}
//Chcek which FSM to use.
int TokenList::FSMdecider(char firstLetter)
{
	int caseFSM = 1;
	for (unsigned int i = 0; i < upperLetter.size(); i++)
	{
		if (firstLetter == upperLetter[i] || firstLetter == lowerLetter[i])
			caseFSM = 1;

	}
	for (unsigned int i = 0; i < digits.size(); i++)
	{
		if (firstLetter == digits[i])
			caseFSM = 2;
	}
	return caseFSM;
}
void TokenList::writeToken()
{
	string writeFileName;
	string writeSymTblName;
	string fileName;
	ofstream output;
	ofstream symbolTblOutput;
	string choice;
	char choiceSyntax;
	char choiceSymbol;
	char choiceTableOutput;
	char choiceInstrTbl;
	while (choice != "n" && choice != "y")
	{
		cout << "Would you like to analyze this file? (y for yes, n for no)\n";
		cin >> choice;
		if (choice == "y")
		{
			cout << "Would you like to display production rules? (y for yes, n for no)\n";
			cin >> choiceSyntax;
			cout << "Would you like to print the symbol table rules? (y for yes, n for no)\n";
			cin >> choiceSymbol;
			cout << "Would you like to print the instruction table? (y for yes, n for no)\n";
			cin >> choiceInstrTbl;
		}
		if (choice == "y")
		{
			//Print out the symbol table.
			cout << "What is the name for your output file?" << endl;
			cout << "(Note the .Lex extension will be added automatically)" << endl;
			cin >> writeFileName;
			writeFileName.append(".Lex");
			//Print out the lexical items.
			if (choiceSymbol== 'y')
			{
				cout << "What is the name for your symbol table output file?" << endl;
				cout << "(Note the .stb extension will be added automatically)" << endl;
				cin >> writeSymTblName;
				if (choiceInstrTbl == 'y')
				{
					cout << "What is the name for your instruction table?" << endl;
					cout << "The .itlb extension will be added automatically" << endl;
					cin >> fileName;
				}
	

				writeSymTblName.append(".stb");	//stb for symbol table.
				symbolTblOutput.open(writeSymTblName, std::ofstream::out);
				this->printSymbolTable(symbolTblOutput);
				symbolTblOutput.close();
			}

			//Output for the syntatical analyzer.
			output.open(writeFileName, std::ofstream::out);
			if (choiceSyntax == 'y')
			{
				int index = 0;
				this->rat16(true, index, output);
				printInstrTable(choiceSyntax, fileName);
			}
			else if (choiceSyntax == 'n')
			{
				
				for (unsigned int i = 0; i < vecTokens.size(); i++)
				{
					cout << "Token Item #" << i + 1 << endl <<
						"Lexeme is " << vecTokens[i].getLexeme() << " \nToken is " << vecTokens[i].getTokenType() <<
						" \nLine Number is " << vecTokens[i].getLineNumber() << endl;
					output << "Token Item #" << i + 1 << endl <<
						"Lexeme is " << vecTokens[i].getLexeme() << " \nToken is " << vecTokens[i].getTokenType() <<
						" \nLine Number is " << vecTokens[i].getLineNumber() << endl;
					
				}
				
			}
		}
		else if (choice == "n")
		{
			cout << "Thank you for using the Thomas Rat 16 Analyzer" << endl;
		}
		else
		{
			cerr << "This is an incorrect choice please choose either y/n" << endl;
		}
	}
	//cout << 
}

TokenList::~TokenList() {

}
