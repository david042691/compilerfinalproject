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
	bool beencheckedcorrectly = true;
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
	currentopenfile.open("finalp2.txt");
	CheckAccepted(currentopenfile);
	if (CheckAccepted == false)
	{
		return 0;
	}
	currentopenfile.close();

	ifstream acceptedopenfile("finalp2.txt");
	ofstream acceptedwritefile("finalp3.cpp");

	if (acceptedopenfile.fail())
	{
		std::cout << "input file could not be opened or found. \n";
		return 0;
	}

	
	ConvertToCPP(acceptedopenfile, acceptedwritefile);

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


	table[A][SHOW] = 1;					// 1=show(I); 2= UC	3=LC 4=Y:T; 5= UE 6=,YF 7=+NG 8= -NG 9=LC
	table[A][SHOW] = 1;					// 10=*MJ	11=/MJ	12= RE	13= (X)	14=K	15=I	16=MJ	17=+ 18=-
	table[C][ZERO] = 2;					// 19= Z 20=A	21=integer 22=SV	23=S	24=IF	25=NG	26= I=X;
	table[C][ONE] = 2;					// 100=lambda 200= Program I; var D begin V end
	table[C][TWO] = 2;					// 200= a 201=b	202=c	203=d 204=e
	table[C][THREE] = 2;				// 300=0	301=1 302=2	303=3 304=4	305=5	306=6 307=7 308=8	309=9
	table[C][FOUR] = 2;
	table[C][FIVE] = 2;
	table[C][SIX] = 2;
	table[C][SEVEN] = 2;
	table[C][EIGHT] = 2;
	table[C][NINE] = 2;
	table[C][ALPHA] = 3;
	table[C][BRAVO] = 3;
	table[C][CHARLIE] = 3;
	table[C][DELTA] = 3;
	table[C][ECHO] = 3;
	table[C][SEMICOLON] = 100; // LAMBDA
	table[C][COMMA] = 100;
	table[C][COLON] = 100;
	table[C][L_PARENS] = 100;
	table[C][R_PARENS] = 100;
	table[C][PLUS] = 100;
	table[C][MINUS] = 100;
	table[C][DIV] = 100;
	table[C][MULT] = 100;
	table[C][EQUAL] = 100;
	table[D][ALPHA] = 4; // Y:T;
	table[D][BRAVO] = 4;
	table[D][CHARLIE] = 4;
	table[D][DELTA] = 4;
	table[D][ECHO] = 4;
	table[E][COMMA] = 100;
	table[E][COLON] = 100;
	table[E][SEMICOLON] = 100;
	table[E][L_PARENS] = 100;
	table[E][R_PARENS] = 100;
	table[E][PLUS] = 100;
	table[E][MINUS] = 100;
	table[E][MULT] = 100;
	table[E][DIV] = 100;
	table[E][EQUAL] = 100;
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
	table[E][ALPHA] = 100;
	table[E][BRAVO] = 100;
	table[E][CHARLIE] = 100;
	table[E][DELTA] = 100;
	table[E][ECHO] = 100;
	table[E][VAR] = 100;
	table[E][BEGIN] = 100;
	table[E][END] = 100;
	table[E][INTEGER] = 100;
	table[E][SHOW] = 100;
	table[F][COMMA] = 6;
	table[F][COLON] = 100;
	table[G][SEMICOLON] = 100;
	table[G][R_PARENS] = 100;
	table[G][PLUS] = 7;
	table[G][MINUS] = 8;
	table[H][PROGRAM] = 500;
	table[I][ALPHA] = 9;
	table[I][BRAVO] = 9;
	table[I][CHARLIE] = 9;
	table[I][DELTA] = 9;
	table[I][ECHO] = 9;
	table[J][SEMICOLON] = 100;
	table[J][R_PARENS] = 100;
	table[J][PLUS] = 100;
	table[J][MINUS] = 100;
	table[J][MULT] = 10;
	table[J][DIV] = 11; // /MJ
	table[J][ZERO] = 100;
	table[J][ONE] = 100;
	table[J][TWO] = 100;
	table[J][THREE] = 100;
	table[J][FOUR] = 100;
	table[J][FIVE] = 100;
	table[J][SIX] = 100;
	table[J][SEVEN] = 100;
	table[J][EIGHT] = 100;
	table[J][NINE] = 100;
	table[J][ALPHA] = 100; // I
	table[J][BRAVO] = 100;
	table[J][CHARLIE] = 100;
	table[J][DELTA] = 100;
	table[J][ECHO] = 100;
	table[K][PLUS] = 12; // RE
	table[K][MINUS] = 12;
	table[K][ZERO] = 12; // RE
	table[K][ONE] = 12;
	table[K][TWO] = 12; // RE
	table[K][THREE] = 12;
	table[K][FOUR] = 12; // RE
	table[K][FIVE] = 12;
	table[K][SIX] = 12; // RE
	table[K][SEVEN] = 12;
	table[K][EIGHT] = 12; // RE
	table[K][NINE] = 12;
	table[L][ALPHA] = 200; //a
	table[L][BRAVO] = 201; //b
	table[L][CHARLIE] = 202; //c
	table[L][DELTA] = 203; //d
	table[L][ECHO] = 204; //e
	table[M][L_PARENS] = 13; // (X)
	table[M][PLUS] = 14; // K
	table[M][MINUS] = 14;
	table[M][ZERO] = 14;
	table[M][ONE] = 14;
	table[M][TWO] = 14;
	table[M][THREE] = 14;
	table[M][FOUR] = 14;
	table[M][FIVE] = 14;
	table[M][SIX] = 14;
	table[M][SEVEN] = 14;
	table[M][EIGHT] = 14;
	table[M][NINE] = 14;
	table[M][ALPHA] = 15; // I
	table[M][BRAVO] = 15;
	table[M][CHARLIE] = 15;
	table[M][DELTA] = 15;
	table[M][ECHO] = 15;
	table[N][PLUS] = 16; // MJ
	table[N][MINUS] = 16;
	table[N][MULT] = 16;
	table[N][DIV] = 16;
	table[N][EQUAL] = 16;
	table[N][ZERO] = 16;
	table[N][ONE] = 16;
	table[N][TWO] = 16;
	table[N][THREE] = 16;
	table[N][FOUR] = 16;
	table[N][FIVE] = 16;
	table[N][SIX] = 16;
	table[N][SEVEN] = 16;
	table[N][EIGHT] = 16;
	table[N][NINE] = 16;
	table[N][ALPHA] = 16;
	table[N][BRAVO] = 16;
	table[N][CHARLIE] = 16;
	table[N][DELTA] = 16;
	table[N][ECHO] = 16;
	table[R][PLUS] = 17; // +
	table[R][MINUS] = 18; // -

	table[R][ZERO] = 100; // LAMBDA
	table[R][ONE] = 100;
	table[R][TWO] = 100;
	table[R][THREE] = 100;
	table[R][FOUR] = 100;
	table[R][FIVE] = 100;
	table[R][SIX] = 100;
	table[R][SEVEN] = 100;
	table[R][EIGHT] = 100;
	table[R][NINE] = 100;
	table[S][ALPHA] = 19; // Z
	table[S][BRAVO] = 19;
	table[S][CHARLIE] = 19;
	table[S][DELTA] = 19;
	table[S][ECHO] = 19;
	table[S][SHOW] = 20; // A
	table[T][INTEGER] = 21; // integer
	table[U][ZERO] = 300; // 0
	table[U][ONE] = 301; // 1
	table[U][TWO] = 302; // 2
	table[U][THREE] = 303; // 3
	table[U][FOUR] = 304; // 4
	table[U][FIVE] = 305; // 5
	table[U][SIX] = 306; // 6
	table[U][SEVEN] = 307; // 7
	table[U][EIGHT] = 308; // 8
	table[U][NINE] = 309; // 9
	table[V][ALPHA] = 22; // SV
	table[V][BRAVO] = 22;
	table[V][CHARLIE] = 22;
	table[V][DELTA] = 22;
	table[V][ECHO] = 22;
	table[V][SHOW] = 22;
	table[V][END] = 100;
	table[X][L_PARENS] = 25; // NG
	table[X][MULT] = 25;
	table[X][DIV] = 25;
	table[X][ALPHA] = 25;
	table[X][BRAVO] = 25;
	table[X][CHARLIE] = 25;
	table[X][DELTA] = 25;
	table[X][ECHO] = 25;
	table[X][ZERO] = 25; // NG
	table[X][ONE] = 25;
	table[X][TWO] = 25;
	table[X][THREE] = 25;
	table[X][FOUR] = 25;
	table[X][FIVE] = 25;
	table[X][SIX] = 25;
	table[X][SEVEN] = 25;
	table[X][EIGHT] = 25;
	table[X][NINE] = 25;
	table[Y][ALPHA] = 24; // IF
	table[Y][BRAVO] = 24;
	table[Y][CHARLIE] = 24;
	table[Y][DELTA] = 24;
	table[Y][ECHO] = 24;
	table[Z][ALPHA] = 26; // I=X;
	table[Z][BRAVO] = 26;
	table[Z][CHARLIE] = 26;
	table[Z][DELTA] = 26;
	table[Z][ECHO] = 26;


	// initialize the stack
	SStack.push(CASH);
	SStack.push(H);
	string Currentstring;
	getline(input, Currentstring);
	int walker = 0;
	bool reservedword = false;
	int count = Currentstring.length();
	Symbols WordInput;
	bool spellprogram = false;
	bool spellvar = false;
	bool spellbegin = false;
	bool spellend = false;
	bool spellinteger = false;
	bool spellshow = false;
	while (SStack.size() > 0)
	{
		if (walker >= count)
		{
			if (SStack.top() == END && WordInput == END)
			{
				cout << "No Error" << endl;
				return true;
			}
			getline(input, Currentstring);
			walker = 0;
			count = Currentstring.length();
			WordInput = Equivalent(Currentstring[walker]);
		}
		if (Currentstring.substr(walker, 7) == "program")
		{
			reservedword = true;
			walker += 7;
			spellprogram = true;
			WordInput = PROGRAM;
		}
		else if (Currentstring.substr(walker, 3) == "var")
		{
			reservedword = true;
			walker += 3;
			spellvar = true;
			WordInput = VAR;
		}
		else if (Currentstring.substr(walker, 5) == "begin")
		{
			reservedword = true;
			walker += 4;
			spellbegin = true;
			WordInput = BEGIN;
		}
		else if (Currentstring.substr(walker, 3) == "end")
		{
			reservedword = true;
			walker += 3;
			spellend = true;
			WordInput = END;
		}
		else if (Currentstring.substr(walker, 7) == "integer")
		{
			reservedword = true;
			walker += 6;
			spellinteger = true;
			WordInput = INTEGER;
		}
		else if (Currentstring.substr(walker, 4) == "show")
		{
			reservedword = true;
			walker += 3;
			spellshow = true;
			WordInput = SHOW;
		}

		if (WordInput == INVALID && !(walker >= count))
		{
			walker++;
			WordInput = Equivalent(Currentstring[walker]);
		}

		else if (reservedword == true && SStack.top() == WordInput)
		{
			SStack.pop();
			walker++;
			reservedword = false;
			if (walker <= count)
				WordInput = Equivalent(Currentstring[walker]);


		}

		else if (SStack.top() == WordInput && reservedword == false)
		{
			walker++;
			SStack.pop();
			WordInput = Equivalent(Currentstring[walker]);
		}
		else //switch table
		{
			switch (table[SStack.top()][WordInput])
			{

			case 1:
				SStack.pop();
				SStack.push(SEMICOLON);
				SStack.push(R_PARENS);
				SStack.push(I);
				SStack.push(L_PARENS);
				SStack.push(SHOW);
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
				SStack.push(SEMICOLON);
				SStack.push(T);
				SStack.push(COLON);
				SStack.push(Y);
				break;
			case 5:
				SStack.pop();
				SStack.push(E);
				SStack.push(U);
				break;
			case 6:
				SStack.pop();
				SStack.push(F);
				SStack.push(Y);
				SStack.push(COMMA);
				break;
			case 7:
				SStack.pop();
				SStack.push(G);
				SStack.push(N);
				SStack.push(PLUS);
				break;
			case 8:
				SStack.pop();
				SStack.push(G);
				SStack.push(N);
				SStack.push(MINUS);
				break;
			case 9:
				SStack.pop();
				SStack.push(C);
				SStack.push(L);
				break;
			case 10:
				SStack.pop();
				SStack.push(J);
				SStack.push(M);
				SStack.push(MULT);
				break;
			case 11:
				SStack.pop();
				SStack.push(J);
				SStack.push(M);
				SStack.push(DIV);
				break;
			case 12:
				SStack.pop();
				SStack.push(E);
				SStack.push(R);
				break;
			case 13:
				SStack.pop();
				SStack.push(R_PARENS);
				SStack.push(X);
				SStack.push(L_PARENS);
				break;
			case 14:
				SStack.pop();
				SStack.push(K);
				break;
			case 15:
				SStack.pop();
				SStack.push(I);
				break;
			case 16:
				SStack.pop();
				SStack.push(J);
				SStack.push(M);
				break;
			case 17:
				SStack.pop();
				SStack.push(PLUS);
				break;
			case 18:
				SStack.pop();
				SStack.push(MINUS);
				break;
			case 19:
				SStack.pop();
				SStack.push(Z);
				break;
			case 20:
				SStack.pop();
				SStack.push(A);
				break;
			case 21:
				SStack.pop();
				SStack.push(INTEGER);
				break;
			case 22:
				SStack.pop();
				SStack.push(V);
				SStack.push(S);
				break;
			case 23:
				SStack.pop();
				SStack.push(S);
				break;
			case 24:
				SStack.pop();
				SStack.push(F);
				SStack.push(I);
				break;
			case 25:
				SStack.pop();
				SStack.push(G);
				SStack.push(N);
				break;
			case 26:
				SStack.pop();
				SStack.push(SEMICOLON);
				SStack.push(X);
				SStack.push(EQUAL);
				SStack.push(I);
				break;
			case 100:
				SStack.pop();
				break;
			case 500:
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
			case 200:
				SStack.pop();
				SStack.push(ALPHA);
				break;
			case 201:
				SStack.pop();
				SStack.push(BRAVO);
				break;
			case 202:
				SStack.pop();
				SStack.push(CHARLIE);
				break;
			case 203:
				SStack.pop();
				SStack.push(DELTA);
				break;
			case 204:
				SStack.pop();
				SStack.push(ECHO);
				break;
			case 300:
				SStack.pop();
				SStack.push(ZERO);
				break;
			case 301:
				SStack.pop();
				SStack.push(ONE);
				break;
			case 302:
				SStack.pop();
				SStack.push(TWO);
				break;
			case 303:
				SStack.pop();
				SStack.push(THREE);
				break;
			case 304:
				SStack.pop();
				SStack.push(FOUR);
				break;
			case 305:
				SStack.pop();
				SStack.push(FIVE);
				break;
			case 306:
				SStack.pop();
				SStack.push(SIX);
				break;
			case 307:
				SStack.pop();
				SStack.push(SEVEN);
				break;
			case 308:
				SStack.pop();
				SStack.push(EIGHT);
				break;
			case 309:
				SStack.pop();
				SStack.push(NINE);
				break;
			default:
				if (spellprogram == true)
					cout << " is expected" << endl;
				else cout << " is spelled wrong or does not exist in file" << endl;

				if (spellvar == true)
					cout << " is expected" << endl;
				else cout << " is spelled wrong or does not exist in file" << endl;

				if (spellbegin == true)
					cout << " is expected" << endl;
				else cout << " is spelled wrong or does not exist in file" << endl;

				if (spellend == true)
					cout << " is expected" << endl;
				else cout << " is spelled wrong or does not exist in file" << endl;

				if (spellinteger == true)
					cout << " is expected" << endl;
				else cout << " is spelled wrong or does not exist in file" << endl;

				if (spellshow == true)
					cout << " is expected" << endl;
				else cout << " is spelled wrong or does not exist in file" << endl;

				cout << "Illegal Expression";
				return false;
				// 1=show(I); 2= UC	3=LC 4=Y:T; 5= UE 6=,YF 7=+NG 8= -NG 9=LC
							// 10=*MJ	11=/MJ	12= RE	13= (X)	14=K	15=I	16=MJ	17=+ 18=-
							// 19= Z 20=A	21=integer 22=SV	23=S	24=IF	25=NG	26= I=X;
							// 100=lambda 200= Program I; var D begin V end
							// 200= a 201=b	202=c	203=d 204=e
							// 300=0	301=1 302=2	303=3 304=4	305=5	306=6 307=7 308=8	309=9
			}
		}


	}


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
				output << "int";
				i += 7;
				continue;
				}
				if (Currentline[i] == ';')
				{
				output << ";\n";
				Variablenext = false;
				break;
				}
				output << Currentline[i];
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
}