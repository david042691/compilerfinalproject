// Complier Final Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
void Nospace(ifstream& input, ofstream& output);

int main()
{
	ifstream currentopenfile;
	ofstream writefilehere("finalp2.txt");
	currentopenfile.open("finalp1.txt");
	if (currentopenfile.fail())
	{
		cout << "Input file could not be opened or found. \n";
		return 0;
	}

	Nospace(currentopenfile, writefilehere);
	currentopenfile.close();
	writefilehere.close();
	cout << "done" << endl;
	system("pause");
	return 0;
}

void Nospace(ifstream& input, ofstream& output)
{
	string CurrentWord;
	char previouschar = '/0';
	bool commentafterapost = false;
	bool iscomment = false;
	int i = 0;
	bool doubleslash = false;
	bool commentonseparateline = false;
	while (input.good())
	{
		getline(input, CurrentWord, ' ');
		if (CurrentWord != "")
		{
			int z = 0;

			while (CurrentWord[z] != '\0')
			{
				//check for comment
				if (previouschar == ';' && CurrentWord[z] == '/' && CurrentWord[z + 1] == '/')
				{
					commentafterapost = true;
				}
				if (CurrentWord[z] == '/')
				{
					if (CurrentWord[z + 1] == '/')	// check for // comment
					{
						iscomment = true;
						doubleslash = true;
					}
					if (CurrentWord[z + 1] == '*')	// check for beginning of /* comment
						iscomment = true;
				}


				// check for end comment
				if (doubleslash == true && CurrentWord[z] == '\n') // check for end of double // comment
				{
					if (commentafterapost == false)
					{
						z += 2;
						iscomment = false;
						doubleslash = false;
					}
					else if (commentafterapost == true)
					{
						iscomment = false;
						doubleslash = false;
						commentafterapost = false;
					}
				}
				if (CurrentWord[z] == '*')	// check for end of */ type comment
				{
					if (CurrentWord[z + 1] == '/')
					{
						if (CurrentWord[z + 2] == '\n')
						{
							z += 3;
						}
						iscomment = false;
					}
				}
				previouschar = CurrentWord[z];
				if (iscomment == true) // if comment skip over it
				{
					z++;
				}

				// if not commment get rid of space
				else if (CurrentWord[z] == '\t' || CurrentWord[z] == '\v')// check for tabs
				{
					z++;
				}
				else if (CurrentWord[z] == ' ' && CurrentWord[z + 1] == ' ')// check for double spacing
				{
					z++;
				}
				else if (CurrentWord[z] == '\n' && CurrentWord[z + 1] == '\n') // check for double new lines
				{
					z++;
				}
				else
				{
					output << CurrentWord[z];
					z++;
				}


			}
			//output << ' ';

		}
	}
}
