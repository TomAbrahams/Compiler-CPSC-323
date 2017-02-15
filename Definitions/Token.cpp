#include "Token.h"

Token::Token()
{
	lexeme = "Not Generated";
	tokenType = "Not Generated";
	lineNum = -1;
}
Token::Token(const string & theLexeme, const string & theTokenType, int theLineNumber)
{
	lexeme = theLexeme;
	tokenType = theTokenType;
	lineNum = theLineNumber;
}
Token & Token::operator=(const Token & rightToken)
{
	lexeme = rightToken.lexeme;
	tokenType = rightToken.tokenType;
	lineNum = rightToken.lineNum;
	address = rightToken.address;
	return *this;
}
//Mutator Functions
void Token::setTokenType(const string & newTokenType)
{
	tokenType = newTokenType;
}
void Token::setLexeme(const string & newLexeme)
{
	lexeme = newLexeme;
}
void Token::setLineNumber(int lineNumber)
{
	lineNum = lineNumber;
}


//Getters

string Token::getLexeme() const
{
	return lexeme;
}
string Token::getTokenType() const
{
	return tokenType;
}
int Token::getLineNumber() const
{
	return lineNum;
}

//Print
void Token::printToken() const
{
	cout << "lexeme =" << lexeme << ", token =" << tokenType << ", line number =" << lineNum << endl;

}
void Token::printLexeme() const
{
	cout << lexeme << endl;
}
void Token::printTokenType() const
{
	cout << tokenType << endl;
}
void Token::printLineNum() const
{
	cout << lineNum << endl;
}
int Token::getAddress() const
{
	return address;
}
void Token::setAddress(int myAddress)
{
	address = myAddress;
}

Token::~Token()
{

}
