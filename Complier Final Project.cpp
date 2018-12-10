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
		std::cout << "Input file could not be opened or found. \n";
		return 0;
	}

	Nospace(currentopenfile, writefilehere);

	writefilehere.close();
	currentopenfile.close();
	ifstream acceptedopenfile;
	ofstream acceptedwritefile;
	acceptedopenfile.open("finalp2.txt");
	acceptedwritefile.open("finalp3.txt");

	if (acceptedopenfile.fail())
	{
		std::cout << "input file could not be opened or found. \n";
		return 0;
	}

	if (CheckAccepted(acceptedopenfile)) {

		ConvertToCPP(acceptedopenfile, acceptedwritefile);

	}

	//writefilehere.close();
	//ifstream acceptedopenfile;
	//ofstream acceptedwritefile;
	//acceptedopenfile.open("finalp2.txt");
	//acceptedwritefile.open("finalp3.txt");
	//ConvertToCPP(acceptedopenfile, acceptedwritefile);
	acceptedopenfile.close();
	acceptedwritefile.close();
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
	LAMBDA,
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
	case 'l': return LAMBDA;
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
							while (Currentline[a] != '\n') {
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

	table[A][SHOW] = 1; // show(I);
	table[C][ZERO] = 2; // UC
	table[C][ONE] = 2;
	table[C][TWO] = 2;
	table[C][THREE] = 2;
	table[C][FOUR] = 2;
	table[C][FIVE] = 2;
	table[C][SIX] = 2;
	table[C][SEVEN] = 2;
	table[C][EIGHT] = 2;
	table[C][NINE] = 2;
	table[C][ALPHA] = 3; // LC
	table[C][BRAVO] = 3;
	table[C][CHARLIE] = 3;
	table[C][DELTA] = 3;
	table[C][ECHO] = 3;
	table[E][COMMA] = 4; // LAMBDA
	table[E][COLON] = 4;
	table[E][SEMICOLON] = 4;
	table[E][L_PARENS] = 4;
	table[E][R_PARENS] = 4;
	table[E][PLUS] = 4;
	table[E][MINUS] = 4;
	table[E][MULT] = 4;
	table[E][DIV] = 4;
	table[E][EQUAL] = 4;
	table[E][ZERO] = 5; // UE
	table[E][ONE] = 5;
	table[E][TWO] = 5;
	table[E][THREE] = 5;
	table[E][FOUR] = 5;
	table[E][FIVE] = 5;
	table[E][SIX] = 5;
	table[E][SEVEN] = 5;
	table[E][EIGHT] = 5;
	table[E][NINE] = 5;
	table[E][ALPHA] = 4; // LAMBDA
	table[E][BRAVO] = 4;
	table[E][CHARLIE] = 4;
	table[E][DELTA] = 4;
	table[E][ECHO] = 4;
	table[E][PROGRAM] = 4;
	table[E][VAR] = 4;
	table[E][BEGIN] = 4;
	table[E][END] = 4;
	table[E][INTEGER] = 4;
	table[E][SHOW] = 4;
	table[F][COMMA] = 6; // ,Y
	table[F][COLON] = 4; // LAMBDA
	table[G][SEMICOLON] = 4;
	table[G][R_PARENS] = 4;
	table[G][PLUS] = 7; // +NG
	table[G][MINUS] = 8; // -NG
	table[H][PROGRAM] = 9; // program I; var D begin V end
	table[I][ALPHA] = 3; // LC
	table[I][BRAVO] = 3;
	table[I][CHARLIE] = 3;
	table[I][DELTA] = 3;
	table[I][ECHO] = 3;
	table[J][SEMICOLON] = 4; // LAMBDA
	table[J][R_PARENS] = 4;
	table[J][PLUS] = 4;
	table[J][MINUS] = 4;
	table[J][MULT] = 10; // *MJ
	table[J][DIV] = 11; // /MJ
	table[K][PLUS] = 12; // RE
	table[K][MINUS] = 12;
	table[J][SEMICOLON] = 4;
	table[L][ALPHA] = 13; //a
	table[L][BRAVO] = 14; //b
	table[L][CHARLIE] = 43; //c
	table[L][DELTA] = 15; //d
	table[L][ECHO] = 16; //e
	table[M][L_PARENS] = 17; // (X)
	table[M][PLUS] = 18; // K
	table[M][MINUS] = 18;
	table[M][ZERO] = 18;
	table[M][ONE] = 18;
	table[M][TWO] = 18;
	table[M][THREE] = 18;
	table[M][FOUR] = 18;
	table[M][FIVE] = 18;
	table[M][SIX] = 18;
	table[M][SEVEN] = 18;
	table[M][EIGHT] = 18;
	table[M][NINE] = 18;
	table[M][ALPHA] = 19; // I
	table[M][BRAVO] = 19;
	table[M][CHARLIE] = 19;
	table[M][DELTA] = 19;
	table[M][ECHO] = 19;
	table[N][PLUS] = 20; // MJ
	table[N][MINUS] = 20;
	table[N][MULT] = 20;
	table[N][DIV] = 20;
	table[N][EQUAL] = 20;
	table[N][ZERO] = 20;
	table[N][ONE] = 20;
	table[N][TWO] = 20;
	table[N][THREE] = 20;
	table[N][FOUR] = 20;
	table[N][FIVE] = 20;
	table[N][SIX] = 20;
	table[N][SEVEN] = 20;
	table[N][EIGHT] = 20;
	table[N][NINE] = 20;
	table[N][ALPHA] = 20;
	table[N][BRAVO] = 20;
	table[N][CHARLIE] = 20;
	table[N][DELTA] = 20;
	table[N][ECHO] = 20;
	table[R][PLUS] = 21; // +
	table[R][MINUS] = 22; // -
	table[D][ALPHA] = 23; // Y:T;
	table[D][BRAVO] = 23;
	table[D][CHARLIE] = 23;
	table[D][DELTA] = 23;
	table[D][ECHO] = 23;
	table[R][ZERO] = 4; // LAMBDA
	table[R][ONE] = 4;
	table[R][TWO] = 4;
	table[R][THREE] = 4;
	table[R][FOUR] = 4;
	table[R][FIVE] = 4;
	table[R][SIX] = 4;
	table[R][SEVEN] = 4;
	table[R][EIGHT] = 4;
	table[R][NINE] = 4;
	table[S][ALPHA] = 24; // Z
	table[S][BRAVO] = 24;
	table[S][CHARLIE] = 24;
	table[S][DELTA] = 24;
	table[S][ECHO] = 24;
	table[S][SHOW] = 25; // A
	table[T][INTEGER] = 26; // integer
	table[S][ALPHA] = 24;
	table[U][ZERO] = 27; // 0
	table[U][ONE] = 28; // 1
	table[U][TWO] = 29; // 2
	table[U][THREE] = 30; // 3
	table[U][FOUR] = 31; // 4
	table[U][FIVE] = 32; // 5
	table[U][SIX] = 33; // 6
	table[U][SEVEN] = 34; // 7
	table[U][EIGHT] = 36; // 8
	table[U][NINE] = 37; // 9
	table[V][ALPHA] = 38; // SV
	table[V][BRAVO] = 38;
	table[V][CHARLIE] = 38;
	table[V][DELTA] = 38;
	table[V][ECHO] = 38;
	table[V][SHOW] = 39; // S
	table[V][SHOW] = 39;
	table[X][L_PARENS] = 40; // NG
	table[X][MULT] = 40;
	table[X][DIV] = 40;
	table[X][ALPHA] = 40;
	table[X][BRAVO] = 40;
	table[X][CHARLIE] = 40;
	table[X][DELTA] = 40;
	table[X][ECHO] = 40;
	table[Y][ALPHA] = 41; // IF
	table[Y][BRAVO] = 41;
	table[Y][CHARLIE] = 41;
	table[Y][DELTA] = 41;
	table[Y][ECHO] = 41;
	table[Z][ALPHA] = 42; // I=X;
	table[Z][BRAVO] = 42;
	table[Z][CHARLIE] = 42;
	table[Z][DELTA] = 42;
	table[Z][ECHO] = 42;
	table[C][SEMICOLON] = 4; // LAMBDA
	table[C][COMMA] = 4;
	table[C][L_PARENS] = 4;
	table[C][EQUAL] = 4;
	table[U][SEMICOLON] = 4;
	table[U][COMMA] = 4;


	bool spaceCheck = false;

	// initialize the stack
	SStack.push(CASH);
	SStack.push(H);
	getline(input, CurrentWord);
	int count = CurrentWord.length();
	if (CurrentWord.substr(walker, 7) == "program")
	{
		inputTerminal = PROGRAM;
		walker += 7;
	}
	while (input.good() && SStack.size() > 0) {

		if (walker >= count)
		{
			getline(input, CurrentWord);
			walker = 0;
			count = CurrentWord.length();
			inputTerminal = Equivalent(CurrentWord[walker]);
		}
		if (CurrentWord.substr(walker, 3) == "var")
		{
			inputTerminal = VAR;
			walker += 3;
		}
		if (CurrentWord.substr(walker, 5) == "begin")
		{
			inputTerminal = BEGIN;
			walker += 5;
		}
		if (CurrentWord.substr(walker, 3) == "end")
		{
			inputTerminal = END;
			walker += 3;
		}
		if (CurrentWord.substr(walker, 7) == "integer")
		{
			inputTerminal = INTEGER;
			walker += 7;
		}
		if (SStack.top() == inputTerminal)
		{
			SStack.pop();
			walker++;
			if (walker >= count)
			{
				continue;
			}
			inputTerminal = Equivalent(CurrentWord[walker]);
		}


		if (!spaceCheck) {
			switch (table[SStack.top()][inputTerminal]) {
			case 1:
				SStack.pop();
				SStack.push(E);
				SStack.push(E);
				SStack.push(I);
				walker = walker + 6;
				break;
			case 2:
				SStack.pop();
				SStack.push(C);
				SStack.push(U);

				break;
			case 3:
				SStack.pop();
				SStack.push(C);
				SStack.push(L);
				break;
			case 4:
				SStack.pop();
				break;
			case 5:
				SStack.pop();
				SStack.push(E);
				SStack.push(U);
				break;
			case 6:
				SStack.pop();
				SStack.push(Y);
				SStack.push(COMMA);
				break;
			case 7:
				SStack.pop();
				SStack.push(R);
				SStack.push(N);
				SStack.push(G);
				break;
			case 8:
				SStack.pop();
				SStack.push(R);
				SStack.push(N);
				SStack.push(G);
				break;
			case 9:
				SStack.pop();
				SStack.push(END);
				SStack.push(V);
				SStack.push(BEGIN);
				SStack.push(D);
				SStack.push(VAR);
				SStack.push(SEMICOLON);
				SStack.push(I);
				SStack.push(PROGRAM);
				break;
			case 10:
				SStack.pop();
				SStack.push(J);
				SStack.push(M);
				SStack.push(E);
				break;
			case 11:
				SStack.pop();
				SStack.push(J);
				SStack.push(M);
				SStack.push(E);
				break;
			case 12:
				SStack.pop();
				SStack.push(E);
				SStack.push(R);
				break;
			case 13:
				SStack.pop();
				SStack.push(ALPHA);
				break;
			case 14:
				SStack.pop();
				SStack.push(BRAVO);
				break;
			case 15:
				SStack.pop();
				SStack.push(DELTA);
				break;
			case 16:
				SStack.pop();
				SStack.push(ECHO);
				break;
			case 43:
				SStack.pop();
				SStack.push(CHARLIE);
				break;
			case 17:
				SStack.pop();
				SStack.push(E);
				SStack.push(X);
				SStack.push(E);
				break;
			case 18:
				SStack.pop();
				SStack.push(K);
				break;
			case 19:
				SStack.pop();
				SStack.push(I);
				break;
			case 20:
				SStack.pop();
				SStack.push(J);
				SStack.push(M);
				break;
			case 21:
				SStack.pop();
				SStack.push(E);
				break;
			case 22:
				SStack.pop();
				SStack.push(E);
				break;
			case 23:
				SStack.pop();
				SStack.push(E);
				SStack.push(T);
				SStack.push(E);
				SStack.push(Y);
				break;
			case 24:
				SStack.pop();
				SStack.push(Z);
				break;
			case 25:
				SStack.pop();
				SStack.push(A);
				break;
			case 26:
				SStack.pop();
				SStack.push(INTEGER);
				break;
			case 27:
				SStack.pop();
				SStack.push(ZERO);
				break;
			case 28:
				SStack.pop();
				SStack.push(ONE);
				break;
			case 29:
				SStack.pop();
				SStack.push(TWO);
				break;
			case 30:
				SStack.pop();
				SStack.push(THREE);
				break;
			case 31:
				SStack.pop();
				SStack.push(FOUR);
				break;
			case 32:
				SStack.pop();
				SStack.push(FIVE);
				break;
			case 33:
				SStack.pop();
				SStack.push(SIX);
				break;
			case 34:
				SStack.pop();
				SStack.push(SEVEN);
				break;
			case 35:
				SStack.pop();
				SStack.push(EIGHT);
				break;
			case 36:
				SStack.pop();
				SStack.push(EIGHT);
				break;
			case 37:
				SStack.pop();
				SStack.push(NINE);
				break;
			case 38:
				SStack.pop();
				SStack.push(V);
				SStack.push(S);
				break;
			case 39:
				SStack.pop();
				SStack.push(S);
				break;
			case 40:
				SStack.pop();
				SStack.push(G);
				SStack.push(N);
				break;
			case 41:
				SStack.pop();
				SStack.push(F);
				SStack.push(I);
				break;
			case 42:
				SStack.pop();
				SStack.push(E);
				SStack.push(X);
				SStack.push(E);
				SStack.push(I);
				break;
			default:
				std::cout << "Illegal Expression.";
				return false;
			}
			//if (inputTerminal != PROGRAM || inputTerminal != VAR || inputTerminal != BEGIN || inputTerminal != END || inputTerminal != INTEGER)
//inputTerminal = Equivalent(CurrentWord[walker]);
			spaceCheck = false;
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