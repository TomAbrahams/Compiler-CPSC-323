#ifndef TOKENLIST_H
#define TOKENLIST_H
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include<stack>
#include "Assembly.h"
#include"Token.h"

class TokenList {
public:
	TokenList();
	void initialize();
	TokenList(const string & myTextLocation);
	//Adding a token
	void addToken(const string& myTokenType, const string& myLexeme, int myLineNumber);
	//Printing a token
	void print();
	//FSM
	void FSM();
	//Identifier FSM
	void identifierFSM(string myLine, unsigned int & index, int lineCounter);
	int transitionStateIdFSM(int currentState, char letter);
	int convertFSMIdToCol(char letter);
	//Real Int FSM
	void realIntFSM(const string& myLine, unsigned int & index, bool & idFlag, int lineCounter);
	int transitionStateRealId(int currentState, char letter);
	int convertIntFSMIntRealCol(char letter);
	//Identifier Symbols
	int identifierSymbols(const string& myLine, unsigned int & index, string & temp);
	//Indentifier Keywords
	bool identifierKeywords(const string& myIdentifier);
	//Indentifier Separators
	int identifierSeparators(const string & myLine, unsigned int & index, string &temp);
	//Check if done
	bool endOfSymbols(const string & myLine, unsigned int & index);
	void setTextFile(const string & myLocation)
	{
		textLocation = myLocation;
	}
	unsigned int getListSize()
	{
		return vecTokens.size();
	}
	void clearTokenList()
	{
		vecTokens.clear();
	}
	int FSMdecider(char firstLetter);
	void writeToken();
	//Destructor
	~TokenList();

	//Items to include for the Syntatical Analyzer
	void rat16(bool showFlag, int & index, ofstream & output);
	void optFunctionDef(bool showFlag, int & index, ofstream & output);
	void optDeclList(bool showFlag, int & index, ofstream & output);
	void statementList(bool showFlag, int & index, ofstream & output);
	void statementListPrime(bool showFlag, int & index, ofstream & output);
	void functionDef(bool showFlag, int & index, ofstream & output);
	void fDefPrime(bool showFlag, int & index, ofstream & output);
	void functionKey(bool showFlag, int & index, ofstream & output);
	void optParamList(bool showFlag, int & index, ofstream & output);
	void paramList(bool showFlag, int & index, ofstream & output);
	void primeParamList(bool showFlag, int & index, ofstream & output);
	void param(bool showFlag, int & index, ofstream & output);
	void qualifier(bool showFlag, int & index, ofstream & output);
	void body(bool showFlag, int & index, ofstream & output);
	void declarList(bool showFlag, int & index, ofstream & output);
	void declaration(bool showFlag, int & index, ofstream & output);
	void IDs(bool showFlag, int & index, ofstream & output);
	void IDsPrime(bool showFlag, int & index, ofstream & output);
	void statement(bool showFlag, int & index, ofstream & output);
	void compound(bool showFlag, int & index, ofstream & output);
	void assign(bool showFlag, int & index, ofstream & output);
	void ifSt(bool showFlag, int & index, ofstream & output);
	void ifPrime(bool showFlag, int & index, ofstream & output);
	void returnSt(bool showFlag, int & index, ofstream & output);
	void returnPrime(bool showFlag, int & index, ofstream & output);
	void condition(bool showFlag, int & index, ofstream & output);
	void writeSt(bool showFlag, int & index, ofstream & output);
	void readSt(bool showFlag, int & index, ofstream & output);
	void whileSt(bool showFlag, int & index, ofstream & output);
	void relop(bool showFlag, int & index, ofstream & output);
	void express(bool showFlag, int & index, ofstream & output);
	void expressPrime(bool showFlag, int & index, ofstream & output);
	void term(bool showFlag, int & index, ofstream & output);
	void termPrime(bool showFlag, int & index, ofstream & output);
	void factor(bool showFlag, int & index, ofstream & output);
	void primary(bool showFlag, int & index, ofstream & output);
	void declarListPrime(bool showFlag, int & index, ofstream & output);

	//Exit
	void syntaxError(int & index, ofstream & output);	//Tells us whats wrong and when
	void matchLex(int & index, const string & matchStr, ofstream & output);
	void matchTok(int & index, const string & matchStr, ofstream & output);
	bool checkLex(int index, const string & matchStr);
	bool checkTok(int index, const string & matchStr);
	void printToken(int index);
	void synPrintToken(int index, ofstream & output);

	//Overloaded
	void syntaxError(int & index, ofstream & output, const string & message, int code);	//Tells us whats wrong and when


	//Symbol Table
	void makeSymbolTable();
	void printSymbolTable(ofstream & myOutput);
	int get_address(const Token & myToken);
	void gen_instr(const string & command, const string & myOprnd);
	void gen_instr(const string & command, int myOprnd);
	bool checkDuplicate(const string & command);
	//Instruction Table
	/*
	void pushI(int value);	//Pushes the integer value onto the top of the stack.
	void pushM(int memoryLocation);	//Pushes the value stored at the memory location onto the top of the stack.
	void popM(int memoryLocation);	//Pops the value from the top of the stack and stores it at Memory Location.
	void stdOut();	//Pops the value from the top of the stack and outputs it to the standard output.
	void stdIn();	//Get the value from the standard input and place in onto the Top of the Stack.
	void add();		//Pop the frist two items from the stack and push the sum onto the Top of the Stack.
	void sub();		//Pop the two itmes from the stack and push the differences onto the Top of the Stack (Second item - First item)
	void mul();		//Pop the first two items from the stack and push the product onto the Top of the Stack
	void div();		//Pop the first two items from the stack and push the result onto the Top of the Stack.
	void grt();		//Pops two items from stack and push 1 onto the Top of the Stack if the second item is larger than the first otherwise push 0.
	void les();		//Pops two items from stack and push 1 onto the Top of the Stack if the second item is smaller than the first otherwise push 0.
	void jumpz(int instructionLocation);	//Pop the stack and if the value is 0 then jump to instruction location.
	void jump(int instructionLocation);		//Jump unconditionally jump to instruction location.
	void label();	//Empty instruction; Provides the instruction location to jump to.								
	*/
	//Other items.
	void back_patch(const string & jump_address);
	void back_patch(int jump_address);
	void push_jumpstack(const string & instr_address);
	void push_jumpstack(int instr_address);
	void printInstrTable(char choice, const string & fileName);	//Char choice added.
private:
	vector<Token> vecTokens;
	vector<Token> symbolTable;
	vector<Assembly> instrTable;
	stack<string> jumpstack;

	//Finite State Matrix for Identifier
	int tableIdFSM[8][4];
	//Finite State Matrix for Real and Integer
	int tableRealInt[6][3];
	//List
	string textLocation;
	//String Letters
	string lowerLetter = "abcdefghijklmnopqrstuvwxyz";
	string upperLetter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	//Digits
	string digits = "0123456789";
	//Operators
	string operatorsOne = "+-*/<>%=:";
	string operatorsTwo = "/=:=<==>";
	//Separators
	string separatorOne = "(){}[];:,";
	string separatorTwo = "$$";
	//Keywords
	vector<string> keywords;
	int Memory_address;
	int Instruct_location;

};


#endif
