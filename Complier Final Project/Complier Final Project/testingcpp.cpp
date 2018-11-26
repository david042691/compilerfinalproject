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
	string Stringarray[100];
	while (input.good())
	{
		getline(input, CurrentWord, ' ');
		Stringarray[i] = CurrentWord;
		i++;
	}
}