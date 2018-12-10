// Complier Final Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <map>

using namespace std;
void Nospace(ifstream& input, ofstream& output);
bool CheckAccepted(ifstream& input);
void ConvertToCPP(ifstream& input, ofstream& output);

int main()
{
	ifstream currentopenfile;
	ofstream writefilehere;
	currentopenfile.open("finalp1.txt");
	writefilehere.open("finalp2.txt");
	if (currentopenfile.fail())
	{
		cout << "Input file could not be opened or found. \n";
		return 0;
	}

	Nospace(currentopenfile, writefilehere);

	//if (CheckAccepted(currentopenfile)) {
	//	writefilehere.close();
	//	ifstream acceptedopenfile;
	//	ofstream acceptedwritefile;
	//	acceptedopenfile.open("finalp2.cpp");
	//	acceptedwritefile.open("finalp3.txt");

	//	if (acceptedopenfile.fail())
	//	{
	//		cout << "Input file could not be opened or found. \n";
	//		return 0;
	//	}

	//	ConvertToCPP(acceptedopenfile, acceptedwritefile);
	//}
	//else {
	//	writefilehere.close();
	//}
	writefilehere.close();
	ifstream acceptedopenfile;
	ofstream acceptedwritefile;
	acceptedopenfile.open("finalp2.txt");
	acceptedwritefile.open("finalp3.txt");
	ConvertToCPP(acceptedopenfile, acceptedwritefile);
	currentopenfile.close();
	cout << "done" << endl;
	system("PAUSE");
	return 0;
}


enum Symbols
{
	//terminal symbols:
	COMMA = 1,	// ,
	COLON,		// :
	SEMICOLON,	// ;
	L_PARENS,	// (
	R_PARENS,	// )
	PLUS,		// +
	MINUS,		// -
	MULT,		// *
	DIV,		// /
	EQUAL,		// =
	ZERO,		// 0
	ONE,		// 1
	TWO,		// 2
	THREE,		// 3
	FOUR,		// 4
	FIVE,		// 5
	SIX,		// 6
	SEVEN,		// 7
	EIGHT,		// 8
	NINE,		// 9
	ALPHA,		// a
	BRAVO,		// b
	CHARLIE,	// c
	DELTA,		// d
	ECHO,		// e
	PROGRAM,	// program
	VAR,		// var
	BEGIN,		// begin
	END,		// end
	INTEGER,	// integer
	SHOW,		// show
	START,
	CASH,
	// non terminal symbols
	A,			// write
	B,			// 
	C,			//
	D,			// dec-list
	E,			// 
	F,			//
	G,			//
	H,			// prog
	I,			// id
	J,			//
	K,			// number
	L,			// letter
	M,			// factor
	N,			// term
	O,			// 
	P,			//
	Q,			//
	R,			// sign
	S,			// stat
	T,			// type
	U,			// digit
	V,			// stat-list
	W,			// 
	X,			// expr
	Y,			// dec
	Z,			// assign

	INVALID,	// invalid token
};

// convert a valid token to a terminal symbol
Symbols Equivalent(char c)
{
	switch (c)
	{
	case ',': return COMMA;
	case ':': return COLON;
	case ';': return SEMICOLON;
	case '*': return MULT;
	case '/': return DIV;
	case '(': return L_PARENS;
	case ')': return R_PARENS;
	case '+': return PLUS;
	case '-': return MINUS;
	case '=': return EQUAL;
	case '1': return ONE;
	case '2': return TWO;
	case '3': return THREE;
	case '4': return FOUR;
	case '5': return FIVE;
	case '6': return SIX;
	case '7': return SEVEN;
	case '8': return EIGHT;
	case '9': return NINE;
	case '0': return ZERO;
	case 'a': return ALPHA;
	case 'b': return BRAVO;
	case 'c': return CHARLIE;
	case 'd': return DELTA;
	case 'e': return ECHO;
	case 'p': return PROGRAM;
	case 'v': return VAR;
	case 'g': return BEGIN;
	case 'n': return END;
	case 'i': return INTEGER;
	case 's': return SHOW;
	case '$': return CASH;
	case 't': return START;
	default: return INVALID;
	}
};

void Nospace(ifstream& input, ofstream& output)
{
	string CurrentWord;
	int i = 0;
	char Currentline[100];
	int k = 0;
	int z = 0;
	int marktheendofline = 0;
	bool nonewlineneeded = false;
	bool starcomment = false;
	while (input.good())
	{
		i = 0;
		// get each string from input
		getline(input, CurrentWord, ' ');
		//loop through current string until it ends
		while (CurrentWord[i] != '\0')
		{

			Currentline[k] = CurrentWord[i];
			i++;
			k++;

			if (Currentline[0] == '\n')	// if you begin a new line with another \n then don't add it to the output
			{
				k = 0;
				Currentline[0] = '\0';
			}
			else if (Currentline[1] == '\n')	// if you begin a new line with another \n then don't add it to the output
			{
				k = 1;
				Currentline[1] = '\0';
			}
			else if (Currentline[2] == '\n')	// if you begin a new line with another \n then don't add it to the output
			{
				k = 2;
				Currentline[2] = '\0';
			}
			else if (Currentline[k - 1] == '\t')// get rid of tab
			{
				k -= 1;
			}
			else if (Currentline[0] == 'e' && Currentline[1] == 'n' && Currentline[2] == 'd')
			{
				output << "end";
				break;
			}
			else if (CurrentWord[i] == '\n')	// if run into \n process the current line first before moving on to the next line
			{

				while (z != k)
				{

					if (Currentline[z] == '/' && Currentline[z + 1] == '*')
					{
						starcomment = true;
						break;
					}
					else if (Currentline[z] == ';' && Currentline[z + 1] == '/' && Currentline[z + 2] == '/')
					{
						//nonewlineneeded = true;
						output << Currentline[z];
						break;
					}
					else if (Currentline[z] == '/' && Currentline[z + 1] == '/')
					{
						nonewlineneeded = true;
						break;
					}
					else
					{
						output << Currentline[z];
						z++;
					}
				}

				if (nonewlineneeded == false && starcomment == false)
				{
					output << '\n';
					z = 0;
					k = 0;
					for (int a = 0; a < 100; a++)
						Currentline[a] = '\0';
				}

				else if (nonewlineneeded == true)
				{
					z = 0;
					k = 0;
					nonewlineneeded = false;
					for (int a = 0; a < 100; a++)
						Currentline[a] = '\0';
				}

				if (starcomment == true)
				{
					bool checkEnd = false;
					while (!checkEnd) {
						for (int a = 0; a < 100; a++) {
							if (Currentline[a] == '*' && Currentline[a + 1] == '/') {
								checkEnd = true;
							}
							Currentline[a] = NULL;
						}
						if (!checkEnd) {
							int a = 0;
							input.get(Currentline[a]);
							while (Currentline[a] != '\n'){
								a++;
								input.get(Currentline[a]);
							}
						}
					}
					k = 0;
					z = 1;
					starcomment = false;
				}
			}
		}

		if (Currentline[k - 1] == ')' || Currentline[k - 1] == '(' || Currentline[k - 1] == ';' || Currentline[k - 1] == '/')
		{
			k = k;
		}
		else
		{
			Currentline[k] = ' ';
			k++;
		}
	}
}

bool CheckAccepted(ifstream& input) {
	// parser table, map <non-terminal, terminal>
	map<Symbols, map<Symbols, int>> table;
	stack<Symbols> SStack;
	int walker = 0;
	string CurrentWord;
	string check;
	Symbols inputTerminal;

	//checks for required reserved words : program, var, begin, end
	bool expectedErrors[4] = { false, false, false, false };

	table[A][SHOW] = 1;
	table[C][ZERO] = 2;
	table[C][ONE] = 2;



	// initialize the stack
	SStack.push(CASH);
	SStack.push(H);
	getline(input, CurrentWord);

	while (input.good() && SStack.size() > 0) {

		if (CurrentWord.substr(walker, walker + 7) == "program") {
			inputTerminal = PROGRAM;
		}

		switch (table[SStack.top()][inputTerminal]) {
		case 1:
			break;
		case 2:
			break;
		}

	}
	if (SStack.size() > 0) {
		std::cout << "Error, program did not compile.";
		return false;
	}

	std::cout << "Program Compiled Successfully.";
	return true;



}

void ConvertToCPP(ifstream& input, ofstream& output) {
	string Currentline;
	bool Variablenext = false;
	while (input.good())
	{
		int i = 0;
		getline(input, Currentline, '\n');

		if (!Currentline.find("program"))
		{
			output << "#include";
			output << '"';
			output << "stdafx.h";
			output << '"';
			output << "\n";
			output << "#include <iostream>\n";
			output << "using namespace std;\n";
			continue;
		}

		if (!Currentline.find("var"))
		{
			Variablenext = true;
			continue;
		}

		if (Currentline[i] == 's' &&Currentline[i + 1] == 'h' &&Currentline[i + 2] == 'o' &&Currentline[i + 3] == 'w')
		{
			output << "cout <<";
			i += 4;
			for (i; i < Currentline.length(); i++)
			{
				output << Currentline[i];
			}
			output << "\n";
			continue;
		}
		if (!Currentline.find("end"))
		{
			output << "}\n";
			continue;
		}

		else if (!Currentline.find("begin"))
		{
			output << "int main()\n{\n";
			continue;
		}

		if (Variablenext == true) {
			output << "int ";
			while (Variablenext == true)
			{
				/*if (Currentline[i] == 'i' && Currentline[i + 1] == 'n' && Currentline[i + 2] == 't')			// Use this code here to make cpp file similar to what he have on the prompt
				{
					writefilehere << "int";
					i += 7;
					continue;
				}
				if (Currentline[i] == ';')
				{
					writefilehere << ";\n";
					Variablenext = false;
					break;
				}
				writefilehere << Currentline[i];
				i++;*/

				output << Currentline[i];
				i++;
				if (Currentline[i] == ':')
				{
					output << ";\n";
					Variablenext = false;
				}

			}
		}
		else
		{
			output << Currentline;
			output << "\n";
		}
	}
	input.close();
	output.close();
	cout << "done" << endl;
	system("pause");
}