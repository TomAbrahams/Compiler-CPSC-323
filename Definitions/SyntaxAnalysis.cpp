#include "TokenList.h"

void TokenList::TokenList::rat16(bool showFlag, int & index, ofstream & output)	//Rat16F
{
	//Print the new token.
	synPrintToken(index,output);
	if (showFlag)
	{
		cout << endl << "<Rat16> --> $$<Opt Function Definitions>$$<Opt Declaration List><Statement List>$$" << endl;
		output << endl  << "<Rat16> --> $$<Opt Function Definitions>$$<Opt Declaration List><Statement List>$$" << endl;

	}
	
	matchLex(index, "$$", output);
	//Print the new token.
	synPrintToken(index,output);

	optFunctionDef(showFlag, index, output);
	matchLex(index, "$$", output);
	//Print the new token.
	synPrintToken(index,output);

	optDeclList(showFlag, index, output);
	statementList(showFlag, index, output);
	matchLex(index, "$$", output);
	//Print the new token.
	//synPrintToken(index,output);
	cout << "The File has been accepted" << endl;
	output << "The File has been Accepted" << endl;
	system("pause");
}
void TokenList::optFunctionDef(bool showFlag, int & index, ofstream & output)	//Opt Function Definitions
{
	if (showFlag)
	{
		cout << endl << "<Opt Function Definitions> --> <Function Definitions> | <Empty>" << endl;
		output << endl << "<Opt Function Definitions> --> <Function Definitions> | <Empty>" << endl;
	}
	

	if (vecTokens[index].getLexeme() == "function")
	{
		functionDef(showFlag, index, output);
	}
	else
		return;
}
void TokenList::optDeclList(bool showFlag, int & index, ofstream & output)
{
	//This is it
	if (showFlag)
	{
		cout << endl << "Opt Declaration List -> Declaration | Empty" << endl;
		output << endl << "Opt Declaration List -> Declaration | Empty" << endl;
	}
	if (checkLex(index, "integer") || checkLex(index, "boolean") || checkLex(index, "real"))
	{
		declarList(showFlag, index, output);
	}
	else
		return;

}
void TokenList::statementList(bool showFlag, int & index, ofstream & output)
{
	if (showFlag)
	{
		cout << endl << "<Statement List> --> <Statement><Statement List Prime>" << endl;
		output << endl << "<Statement List> --> <Statement><Statement List Prime>" << endl;
	}
	statement(showFlag, index, output);
	statementListPrime(showFlag, index, output);

}
void TokenList::statementListPrime(bool showFlag, int & index, ofstream & output)
{
	if (showFlag)
	{
		cout << endl << "<Statement List Prime> --> <Empty> | <Statement List>" << endl;
		output << endl << "<Statement List Prime> --> <Empty> | <Statement List>" << endl;
	}
	if (vecTokens[index].getLexeme() == "{")
		statementList(showFlag, index, output);
	else if (vecTokens[index].getTokenType() == "identifier")
		statementList(showFlag, index, output);
	else if (vecTokens[index].getLexeme() == "if")
		statementList(showFlag, index, output);
	else if (vecTokens[index].getLexeme() == "return")
		statementList(showFlag, index, output);
	else if (vecTokens[index].getLexeme() == "print")
		statementList(showFlag, index, output);
	else if (vecTokens[index].getLexeme() == "read")
		statementList(showFlag, index, output);
	else if (vecTokens[index].getLexeme() == "while")
		statementList(showFlag, index, output);
	else
		return;

}
void TokenList::functionDef(bool showFlag, int & index, ofstream & output)
{
	if (showFlag)
		cout << "<Function Definitions> --> <Function><fDefPrime>" << endl;
	output << "<Function Definitions> --> <Function><fDefPrime>" << endl;
	functionKey(showFlag, index, output);
	fDefPrime(showFlag, index, output);
}
void TokenList::fDefPrime(bool showFlag, int & index, ofstream & output)
{
	if (showFlag)
	{
		cout << endl << "<fDefPrime> --> <Function Definitions> | empty" << endl;
		output << endl << "<fDefPrime> --> <Function Definitions> | empty" << endl;
	}
	if (vecTokens[index].getLexeme() == "function")
	{
		functionDef(showFlag, index, output);
	}
	else
		return;
}
void TokenList::functionKey(bool showFlag, int & index, ofstream & output)
{
	if (showFlag){
		cout << endl << "<function> --> function<id>[<Opt Parameter List>]<Opt Declaration List>" << endl;
		output << endl << "<function> --> function<id>[<Opt Parameter List>]<Opt Declaration List>" << endl;
	}
	matchLex(index, "function", output);
	//Print the new token.
	synPrintToken(index,output);

	matchTok(index, "identifier", output);
	//Print the new token.
	synPrintToken(index,output);

	matchLex(index, "[", output);
	//Print the new token.
	synPrintToken(index,output);

	optParamList(showFlag, index, output);
	matchLex(index, "]", output);
	//Print the new token.
	synPrintToken(index,output);

	optDeclList(showFlag, index, output);
	body(showFlag, index, output);

}
void TokenList::optParamList(bool showFlag, int & index, ofstream & output)	//Opt Parameter List
{
	if (showFlag) {
		cout << endl << "<Opt Paramter List> --> <Parameter List> | empty" << endl;
		output << endl << "<Opt Paramter List> --> <Parameter List> | empty" << endl;
	}
	if (checkTok(index, "identifier"))
	{
		paramList(showFlag, index, output);
	}
	else
		return;
}
void TokenList::paramList(bool showFlag, int & index, ofstream & output)
{
	//We don't know what the next is. But we can find out.
	if (showFlag)
	{
		cout << endl << "<Parameter List>--><Parameter> <Parameter List Prime> " << endl;
		output << endl << "<Parameter List>--><Parameter> <Parameter List Prime> " << endl;
	}
	param(showFlag, index, output);
	primeParamList(showFlag, index, output);
}
void TokenList::primeParamList(bool showFlag, int & index, ofstream & output)
{
	if (showFlag)
	{
		cout << endl << "<Parameter List Prime> --> empty | ,<Parameter List> " << endl;
		output << endl << "<Parameter List Prime> --> empty | ,<Parameter List> " << endl;
	}
	if (checkLex(index, ","))
	{
		index++;
		synPrintToken(index,output);
		paramList(showFlag, index, output);
	}
	else
		return;

}

void TokenList::param(bool showFlag, int & index, ofstream & output)
{
	if (showFlag)
	{
		cout << endl << "<Parameter>--><IDs>:<Qualifier>" << endl;
		output << endl << "<Parameter>--><IDs>:<Qualifier>" << endl;
	}
	IDs(showFlag, index, output);
	matchLex(index, ":", output);
	//Print the new token.
	synPrintToken(index,output);
	qualifier(showFlag, index, output);
}
void TokenList::qualifier(bool showFlag, int & index, ofstream & output)
{
	if (showFlag)
	{
		cout << endl << "<qualifier> --> integer | boolean | real" << endl;
		output << endl << "<qualifier> --> integer | boolean | real" << endl;
	}
	if (vecTokens[index].getLexeme() == "integer" || vecTokens[index].getLexeme() == "boolean" || vecTokens[index].getLexeme() == "real")
	{
		index++;
		//Print the new token.
		synPrintToken(index,output);
	}
	else
	{
		string message = "Expected a lexeme of integer | boolean | real ";
		syntaxError(index, output, message, 0);
		//int & index, ofstream & output, const string & message, int code
	}
}
void TokenList::body(bool showFlag, int & index, ofstream & output)
{
	if (showFlag)
	{
		cout << endl << "<Body> --> { <Statement List> }" << endl;
		output << endl << "<Body> --> { Statement List }" << endl;
	}
	matchLex(index, "{", output);
	//Print the new token.
	synPrintToken(index,output);

	statementList(showFlag, index, output);
	matchLex(index, "}", output);
	//Print the new token.
	synPrintToken(index,output);

}
void TokenList::declarList(bool showFlag, int & index, ofstream & output)
{
	//Changed
	if (showFlag)
	{
		cout << endl << "<Declaration List> --> <Declaration>;<Declaration List Prime>" << endl;
		output << endl << "<Declaration List> --> <Declaration>;<Declaration List Prime>" << endl;
	}
	declaration(showFlag, index, output);
	if (checkLex(index, ";"))
	{
		matchLex(index, ";", output);
		//Print the new token.
		synPrintToken(index,output);

		declarListPrime(showFlag, index, output);
	}
	else
		return;
}
void TokenList::declarListPrime(bool showFlag, int &index, ofstream & output)
{
	if (showFlag)
	{
		cout << endl << "<Declaration List Prime> --> <Declaration List> | Empty" << endl;
		output << endl << "<Declaration List Prime> --> <Declaration List> | Empty" << endl;
	}
	//Declare list prime
	/*
	if (checkLex(index, ";"))
		declarList(showFlag, index, output);
	else
		return;
		*/
	if (vecTokens[index].getLexeme() == "integer" || vecTokens[index].getLexeme() == "boolean" || vecTokens[index].getLexeme() == "real")
		declarList(showFlag, index, output);
	else
		return;
		//Print the new token.
		
	
}
void TokenList::declaration(bool showFlag, int & index, ofstream & output)
{
	if (showFlag)
	{
		cout << endl << "<Declaration> --> <Qualifier> <IDs>" << endl;
		output << endl << "<Declaration> --> <Qualifier> <IDs>" << endl;
	}
	qualifier(showFlag, index, output);
	IDs(showFlag, index, output);

}
void TokenList::IDs(bool showFlag, int & index, ofstream & output)
{
	if (showFlag)
	{
		cout << endl << "<IDs> --> <Identifier><IDs Prime>" << endl;
		output << endl << "<IDs> --> <Identifier><IDs Prime>" << endl;
	}
	matchTok(index, "identifier", output);

	synPrintToken(index,output);
	IDsPrime(showFlag, index, output);
}
void TokenList::IDsPrime(bool showFlag, int & index, ofstream & output)
{
	if (showFlag)
	{
		cout << endl << "<IDs Prime> -->,<IDs> | <Empty>" << endl;
		output << endl <<  "<IDs Prime> -->,<IDs> | <Empty>" << endl;
	}

	if (vecTokens[index].getLexeme() == ",")
	{
		index++;
		//Print the new token.
		synPrintToken(index, output);
		IDs(showFlag, index, output);
	}
	else
		return;
}

void TokenList::statement(bool showFlag, int & index, ofstream & output)
{
	//Compound what is the first terminal symbol? {
	//Assign, what is the first terminal symbol? TokenType = Identifier.
	//if, what is the first terminal symbol? if is.
	//return, what is the first terminal symbol? return is
	//write, what is the first terminal symbol? write is
	//read, read is the first terminal symbol
	//while, while is the first terminal symbol
	if (showFlag)
	{
		cout << endl << "<Statement> --> <Compound> | <Assign> | <If> | <Return> | <Write>| <Read> | <While>" << endl;
		output << endl << "<Statement> --> <Compound> | <Assign> | <If> | <Return> | <Write>| <Read> | <While>" << endl;
	}
	if (vecTokens[index].getLexeme() == "{")
		compound(showFlag, index, output);
	else if (vecTokens[index].getLexeme() == "if")
		ifSt(showFlag, index, output);
	else if (vecTokens[index].getLexeme() == "return")
		returnSt(showFlag, index, output);
	else if (vecTokens[index].getLexeme() == "print")
		writeSt(showFlag, index, output);
	else if (vecTokens[index].getLexeme() == "read")
		readSt(showFlag, index, output);
	else if (vecTokens[index].getLexeme() == "while")
		whileSt(showFlag, index, output);
	else if (vecTokens[index].getTokenType() == "identifier")
		assign(showFlag, index, output);
}
void TokenList::compound(bool showFlag, int & index, ofstream & output)
{
	if (showFlag)
	{
		cout << endl << "<Compound> --> { <Statement List> }" << endl;
		output << endl << "Compound> --> { <Statement List> }" << endl;
	}
	matchLex(index, "{", output);
	//Print the new token.
	synPrintToken(index,output);

	statementList(showFlag, index, output);
	matchLex(index, "}", output);
	//Print the new token.
	synPrintToken(index,output);

}
void TokenList::assign(bool showFlag, int & index, ofstream & output)	//Assign
{
	if (showFlag)
	{
		cout << endl << "<Assign> --> identifier:=<Expression>;" << endl;
		output << endl << "<Assign> --> identifier:=<Expression>;" << endl;
	}
	int myIdx;
	if (checkTok(index, "identifier"))
	{
		myIdx = index;
	}
	matchTok(index, "identifier", output);
	//Print the new token.
	synPrintToken(index,output);

	matchLex(index, ":=", output);
	//Address the get address save... We advanced one so index - 1
	//Identifier is index - 2, where the address is.

	//Print the new token.
	synPrintToken(index,output);
	express(showFlag, index, output);
	gen_instr("POPM", get_address(vecTokens[myIdx]));	//Added for the Assembly Instructions.

	matchLex(index, ";", output);
	synPrintToken(index,output);
	//express(showFlag, index, output);
}
void TokenList::ifSt(bool showFlag, int & index, ofstream & output)
{
	if (showFlag)
	{
		cout << endl << "<If> --> if(<Condition>) <Statement> endif | if(<Condition>) <Statement> else <Statement> endif" << endl;
		output << endl << "<If> --> if(<Condition>) <Statement> endif | if(<Condition>) <Statement> else <Statement> endif" << endl;
	}
	matchLex(index, "if", output);
	//int address = Instruct_location;
	synPrintToken(index, output);
	matchLex(index, "(", output);
	synPrintToken(index, output);
	condition(showFlag, index, output);
	matchLex(index, ")", output);
	//Print the new token.
	synPrintToken(index, output);
	statement(showFlag, index, output);
	//We are done store this address.
	int address = Instruct_location;	//
	//Store the address
	//Need jump.

	back_patch(address);
	if (checkLex(index, "else"))
	{

		push_jumpstack(address);	//This is for the else
		int myStuffbeforeJump = Instruct_location;
		gen_instr("JUMP", "nil");
		//Added for randomness, for some reason this works...
		push_jumpstack(myStuffbeforeJump);	//else_Address
		back_patch(Instruct_location);
		//Added
		synPrintToken(index, output);
		index++;
		statement(showFlag, index, output);
		back_patch(Instruct_location);

		if (vecTokens[index].getLexeme() == "endif")
		{
			synPrintToken(index, output);
			matchLex(index, "endif", output);
		}
	}
	else if (vecTokens[index].getLexeme() == "endif")
	{
		synPrintToken(index, output);
		matchLex(index, "endif", output);
	}
	else
	{
		matchLex(index, "endif", output);
	}
}

void TokenList::returnSt(bool showFlag, int & index, ofstream & output)
{
	if (showFlag)
	{
		cout << endl << "<Return> --> return <Return Prime>" << endl;
		output << endl << "<Return> --> return <Return Prime>" << endl;
	}
	matchLex(index, "return", output);
	returnPrime(showFlag, index, output);

}
void TokenList::returnPrime(bool showFlag, int & index, ofstream & output)
{
	if (showFlag)
	{
		cout << endl << "<Return Prime> --> ; | <Expression>;" << endl;
		output << endl << "<Return Prime> --> ; | <Expression>;" << endl;
	}
	if (vecTokens[index].getLexeme() == ";")
		matchLex(index, ";", output);
	else
	{
		express(showFlag, index, output);
		matchLex(index, ";", output);
	}
}
void TokenList::condition(bool showFlag, int & index, ofstream & output)
{
	if (showFlag)
	{
		cout << endl << "<Condition> --> <Expression><Relop><Expression>" << endl;
		output << endl << "<Condition> --> <Expression><Relop><Expression>" << endl;
	}
	express(showFlag, index, output);
	int op = index;

	//DO NOT USE RELOP.
	relop(showFlag, index, output);
	express(showFlag, index, output);
	if (checkLex(op, "=") || checkLex(op, "/=") || checkLex(op, ">") || checkLex(op, "<") || checkLex(op, "=>") ||
		checkLex(op, "<="))
	{
		if (checkLex(op, "<"))
		{
			gen_instr("LES", "nil");
			push_jumpstack(Instruct_location);
			gen_instr("JUMPZ", "nil");
		}
		else if (checkLex(op, "="))
		{
			gen_instr("EQU", "nil");
			push_jumpstack(Instruct_location);
			gen_instr("JUMPZ", "nil");
		}
		else if (checkLex(op, "/="))
		{
			gen_instr("NEQ", "nil");
			push_jumpstack(Instruct_location);
			gen_instr("JUMPZ", "nil");
		}
		else if(checkLex(op, ">"))
		{
			gen_instr("GRT", "nil");
			push_jumpstack(Instruct_location);
			gen_instr("JUMPZ", "nil");
		}
		else if (checkLex(op, "=>"))
		{
			gen_instr("GEQ", "nil");
			push_jumpstack(Instruct_location);
			gen_instr("JUMPZ", "nil");
		}
		else if (checkLex(op,"<="))
		{
			gen_instr("LEQ", "nil");
			push_jumpstack(Instruct_location);
			gen_instr("JUMPZ", "nil");
		}
	}
}
void TokenList::relop(bool showFlag, int & index, ofstream & output) //wrk
{
	int address;
	if (showFlag)
	{
		cout << endl << "<Relop> --> = | /= | > | < | => | <= " << endl;
		output << endl << "<Relop> --> = | /= | > | < | => | <= " << endl;
	}
	if (checkLex(index, "="))
	{
		matchLex(index, "=", output);
		//Added for Assembly

		//Print the new token.
		synPrintToken(index, output);

	}
	else if (checkLex(index, "/="))
	{
		matchLex(index, "/=", output);
		//Added for Assembly
		
		//Print the new token.
		//gen_inst("")
		synPrintToken(index, output);
	}
	else if (checkLex(index, ">"))
	{
		//Added for Assembly
		
		matchLex(index, ">", output);
		//Print the new token.
		synPrintToken(index, output);

	}
	else if (checkLex(index, "<"))
	{
		//Added for Assembly
		matchLex(index, "<", output);
		//int findNext = get_address(vecTokens[index]);
		//gen_instr("PUSHM", findNext);	//Gets the next variable.
		//Print the new token.
		synPrintToken(index, output);
	}
	else if (checkLex(index, "=>"))
	{
		//Added for Assembly
		matchLex(index, "=>", output);
		//Print the new token.
		synPrintToken(index, output);
	}
	else if (checkLex(index, "<="))
	{
		//Added for Assembly
		matchLex(index, "<=", output);
		//Print the new token.
		synPrintToken(index, output);
	}
	else
	{
		string message = "Expected a lexeme of = | /= | > | < | => | <= ";
		syntaxError(index, output, message, 0);
	}

}
void TokenList::writeSt(bool showFlag, int & index, ofstream & output)
{
	if (showFlag)
	{
		cout << endl << "<Write> --> print (<Expression>);" << endl;
		output << endl << "<Write> --> print (<Expression>);" << endl;
	}
	matchLex(index, "print", output);
	//Print the new token.
	synPrintToken(index,output);

	matchLex(index, "(", output);
	//Print the new token.
	synPrintToken(index,output);

	express(showFlag, index, output);
	matchLex(index, ")", output);
	//Print the new token.
	synPrintToken(index,output);
	matchLex(index, ";", output);
	gen_instr("STDOUT", "nil");
	synPrintToken(index,output);
}
void TokenList::readSt(bool showFlag, int & index, ofstream & output)		//Read Assembly
{
	if (showFlag)
	{
		cout << endl << "<Read> --> read (<IDs>);" << endl;
		output << endl << "<Read> --> read (<IDs>);" << endl;
	}
	if (checkLex(index, "read"))
	{
		matchLex(index, "read", output);
		//Print the new token.
		synPrintToken(index,output);
		matchLex(index, "(", output);
		synPrintToken(index,output);
		int temp_address = index;
		IDs(showFlag, index, output);	//IDs
		
		matchLex(index, ")", output);
		synPrintToken(index,output);
		matchLex(index, ";", output);
		synPrintToken(index,output);
		gen_instr("STDIN", "nil");
		gen_instr("POPM", get_address(vecTokens[temp_address]));	//Get address
	}
}
void TokenList::whileSt(bool showFlag, int & index, ofstream & output)	//While Statement Assembly
{
	if (showFlag)
	{
		cout << endl << "<While> --> while ( <Condition> ) <Statement>" << endl;
		output << endl << "<While> --> while ( <Condition> ) <Statement>" << endl;
	}
	matchLex(index, "while", output);
	int address = Instruct_location;
	//Print the new token.
	synPrintToken(index,output);
	gen_instr("LABEL", "nil");		//Assembly

	matchLex(index, "(", output);
	//Print the new token.
	synPrintToken(index,output);

	condition(showFlag, index, output);
	matchLex(index, ")", output);
	//Print the new token.
	synPrintToken(index,output);

	statement(showFlag, index, output);
	gen_instr("JUMP", address);	//Assembly
	back_patch(Instruct_location);	//Not any more. This is broken.

}

void TokenList::express(bool showFlag, int & index, ofstream & output)	//Expression Assembly
{
	if (showFlag)
	{
		cout << endl << "<Expression> --> <Term><Expression Prime>" << endl;
		output << endl << "<Expression> --> <Term><Expression Prime>" << endl;
	}
	term(showFlag, index, output);
	expressPrime(showFlag, index, output);

}
void TokenList::expressPrime(bool showFlag, int & index, ofstream & output)	//Express Prime Assembly
{
	if (showFlag)
	{
		cout << endl << "<Expression Prime> --> +<Term><Expression Prime> | -<Term><Expression Prime> | Empty" << endl;
		output << endl << "<Expression Prime> --> +<Term><Expression Prime> | -<Term><Expression Prime> | Empty" << endl;
	}

	if (vecTokens[index].getLexeme() == "+")
	{
		matchLex(index, "+", output);
		//Print the new token.
		synPrintToken(index,output);

		term(showFlag, index, output);
		//Need to add gen_instr(ADD, 0)
		gen_instr("ADD", "nil");		//Done for assembly.
		expressPrime(showFlag, index, output);
	}
	else if (vecTokens[index].getLexeme() == "-")
	{
		matchLex(index, "-", output);
		//Print the new token.
		synPrintToken(index,output);
		gen_instr("SUB", "nil");		//Done for assembly.
		term(showFlag, index, output);
		expressPrime(showFlag, index, output);
	}
	else
		return;
}
void TokenList::term(bool showFlag, int & index, ofstream & output)
{
	if (showFlag)
	{
		cout << endl << "<Term> --> <Factor><Term Prime>" << endl;
		output << endl << "<Term> --> <Factor><Term Prime>" << endl;
	}
	factor(showFlag, index, output);		//1
	termPrime(showFlag, index, output);
}
void TokenList::termPrime(bool showFlag, int & index, ofstream & output)	//Term Prime Assembly
{
	if (showFlag)
	{
		cout << endl << "<Term Prime> --> *<Factor><Term Prime> | /<Factor><Term Prime> | Empty " << endl;
		output << endl << "<Term Prime> --> *<Factor><Term Prime> | /<Factor><Term Prime> | Empty " << endl;
	}
	if (checkLex(index, "*"))
	{
		matchLex(index, "*", output);
		//Print the new token.
		synPrintToken(index,output);

		factor(showFlag, index, output);
		//Gen instruction
		gen_instr("MUL", "nil");
		termPrime(showFlag, index, output);

	}
	else if (checkLex(index, "/"))
	{
		matchLex(index, "/", output);
		//Print the new token.
		synPrintToken(index,output);
		gen_instr("DIV", "nil");
		factor(showFlag, index, output);
		termPrime(showFlag, index, output);
	}
	else
		return;
}
void TokenList::factor(bool showFlag, int & index, ofstream & output)
{
	if (showFlag)
	{
		cout << endl << "<Factor> --> = -<Primary> | <Primary>" << endl;
		output << endl << "<Factor> --> = -<Primary> | <Primary>" << endl;
	}
	
	if (checkTok(index, "identifier"))
	{
		int address = get_address(vecTokens[index]);
		gen_instr("PUSHM", address);		//There is a problem This generated the wrong instruction.
		index++;
	}
	
	
	if (checkLex(index, "-"))
	{
		matchLex(index, "-", output);
		//Print the new token.
		synPrintToken(index,output);
		
		primary(showFlag, index, output);
		//Primary has the items needed for assembly
	}
	else
		primary(showFlag, index, output);
}
void TokenList::primary(bool showFlag, int & index, ofstream & output)	//From Factor Assembly
{
	if (showFlag)
	{
		cout << endl << "<Primary> --> <identifier>|<Integer>| <identifier>[<IDs>] | (<Expression>) |<Real> | true | false" << endl;
		output << endl << "<Primary> --> <identifier>|<Integer>| <identifier>[<IDs>] | (<Expression>) |<Real> | true | false" << endl;
	}
	if (checkTok(index, "identifier"))
	{
		int theIndex = index;
		matchTok(index, "identifier", output);
		//Need to add the address. Token for identifier has to be shifted back by 1 to get the identifier
		//identifier - 1
	
		//gen_instr("PUSHM", get_address(vecTokens[theIndex]));
		
		//Print the new token.
		synPrintToken(index,output);
		
		if (checkLex(index, "["))
		{
			matchLex(index, "[", output);
			//Print the new token.
			
			gen_instr("PUSHM", get_address(vecTokens[index]));
			synPrintToken(index,output);
			IDs(showFlag, index, output);
			matchLex(index, "]", output);
			//Print the new token.
			synPrintToken(index,output);
		}
		else
			return;
	}
	else if (checkTok(index, "Integer"))
	{
		int integer_address = atoi(vecTokens[index].getLexeme().c_str());	//Have symbol table address
		gen_instr("PUSHI", integer_address);
		matchTok(index, "Integer", output);
		//Print the new token.
		synPrintToken(index,output);
	}
	else if (checkLex(index, "("))
	{
		matchLex(index, "(", output);
		//Print the new token.
		express(showFlag, index, output);
		synPrintToken(index,output);
		matchLex(index, ")", output);
		synPrintToken(index,output);
	}
	else if (checkTok(index, "Real"))
	{
		matchTok(index, "Real", output);
		//Print the new token.
		synPrintToken(index,output);
	}
	else if (checkLex(index, "true"))
	{
		int temp_addr = index;
		matchLex(index, "true", output);
		gen_instr("PUSHI", 1);
		//Print the new token.
		synPrintToken(index,output);
	}
	else if (checkLex(index, "false"))
	{
		int temp_addr = index;
		matchLex(index, "false", output);
		gen_instr("PUSHI", 0);
		//Print the new token.
		synPrintToken(index,output);
	}	
	else if (checkLex(index, "["))
	{
		matchLex(index, "[", output);
		//Print the new token.

		gen_instr("PUSHM", get_address(vecTokens[index]));
		synPrintToken(index, output);
		IDs(showFlag, index, output);
		matchLex(index, "]", output);
		//Print the new token.
		synPrintToken(index, output);
	}
}

//Exit
void TokenList::syntaxError(int & index, ofstream & output)	//Tells us whats wrong and when
{
	output << endl << "Syntax Error on Line" << vecTokens[index].getLineNumber() << endl;
	cerr << endl << "Syntax Error on Line" << vecTokens[index].getLineNumber() << endl;
	system("pause");
	exit(1);
}
void::TokenList::matchLex(int & index, const string & matchStr, ofstream & output)
{
	if (vecTokens[index].getLexeme() == matchStr)
	{
		index++;
	}
	else
	{
		string message = "Expecting the Lexeme " + matchStr;
		syntaxError(index, output, message, 0);
	}
}
void::TokenList::matchTok(int & index, const string & matchStr, ofstream & output)
{
	if (vecTokens[index].getTokenType() == matchStr)
	{
		index++;
	}
	else
	{
		string message = "Expecting the Token " + matchStr;
		syntaxError(index, output, message, 1);
	}
}
bool TokenList::checkLex(int index, const string & matchStr)
{
	return (vecTokens[index].getLexeme() == matchStr);
}
bool TokenList::checkTok(int index, const string & matchStr)
{
	return (vecTokens[index].getTokenType() == matchStr);
}
void TokenList::printToken(int index)
{
	vecTokens[index].printToken();
}
void TokenList::synPrintToken(int index, ofstream & output)
{
	//cout << endl;
	cout << "Print Token" << endl;
	cout << "Token is " << vecTokens[index].getTokenType() << "\tLexeme is " << vecTokens[index].getLexeme() <<
		"\tLine Number is " << vecTokens[index].getLineNumber() << endl << endl;

	//output << endl;
	output << "Print Token" << endl;
	output << "Token is " << vecTokens[index].getTokenType() << "\tLexeme is " << vecTokens[index].getLexeme() <<
		"\tLine Number is " << vecTokens[index].getLineNumber() << endl << endl;
}



void TokenList::syntaxError(int & index, ofstream & output, const string & message, int code)
{
	output << endl << "Syntax Error on Line " << vecTokens[index].getLineNumber() << endl;
	output << message << " instead found a ";
	cerr << endl << "Syntax Error on Line " << vecTokens[index].getLineNumber() << endl;
	cerr << endl << message << " instead found a ";
	if (code == 1)
	{
		cerr << vecTokens[index].getTokenType() << endl;
		output << vecTokens[index].getTokenType() << endl;
	}
	else
	{
		cerr << vecTokens[index].getLexeme() << endl;
		output << vecTokens[index].getLexeme() << endl;
	}
	system("pause");
	exit(1);
}
