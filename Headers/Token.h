#ifndef TOKEN_H
#define TOKEN_H

#include<iostream>
#include<string>
using namespace std;


class Token {
public:

	Token();
	Token(const string & theLexeme, const string & theTokenType, int theLineNumber);
	//Mutator Functions
	void setTokenType(const string & newTokenType);
	void setLexeme(const string & newLexeme);
	void setLineNumber(int lineNumber);
	void setAddress(int myAddress);
	//Getters
	string getLexeme() const;
	string getTokenType() const;
	int getAddress() const;
	int getLineNumber() const;
	//Print
	void printToken() const;
	void printLexeme() const;
	void printTokenType() const;
	void printLineNum() const;
	Token & operator =(const Token & rightToken);
	//Destructor
	~Token();
private:
	//The token value.
	string lexeme;
	//The token type.
	string tokenType;
	int lineNum;
	int address = -1;

};
#endif
