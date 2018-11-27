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
			else if (Currentline[k - 1] == '\t')// get rid of tab
			{
				k -= 1;
			}
			else if (Currentline[0] == 'e' && Currentline[1]== 'n' && Currentline[2]== 'd')
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
					for (int a = 0; a < 100; a++)
						Currentline[a] = NULL;
					k = 0;
					z = 0;
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