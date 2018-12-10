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
	ofstream writefilehere("finalp3.cpp");
	currentopenfile.open("finalp2.txt");
	if (currentopenfile.fail())
	{
		cout << "Input file could not be opened or found. \n";
		return 0;
	}

	string Currentline;
	bool Variablenext = false;
	while (currentopenfile.good())
	{
		int i = 0;
		getline(currentopenfile, Currentline, '\n');

		if (!Currentline.find("program"))
		{
			writefilehere << "#include";
			writefilehere << '"';
			writefilehere << "stdafx.h";
			writefilehere << '"';
			writefilehere << "\n";
			writefilehere << "#include <iostream>\n";
			writefilehere << "using namespace std;\n";
			continue;
		}

		if (!Currentline.find("var"))
		{
			Variablenext = true;
			continue;
		}

		if (Currentline[i] == 's' &&Currentline[i + 1] == 'h' &&Currentline[i + 2] == 'o' &&Currentline[i + 3] == 'w')
		{
			writefilehere << "cout <<";
			i += 4;
			for (i; i < Currentline.length(); i++)
			{
				writefilehere << Currentline[i];
			}
			writefilehere << "\n";
			continue;
		}
		if (!Currentline.find("end"))
		{
			writefilehere << "}\n";
			continue;
		}

		else if (!Currentline.find("begin"))
		{
			writefilehere << "int main()\n{\n";
			continue;
		}

		if (Variablenext == true) {
			writefilehere << "int ";
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

				writefilehere << Currentline[i];
				i++;
				if (Currentline[i] == ':')
				{
					writefilehere << ";\n";
					Variablenext = false;
				}

			}
		}
		else
		{
			writefilehere << Currentline;
			writefilehere << "\n";
		}
	}
	currentopenfile.close();
	writefilehere.close();
	system("gcc -o finalp3.cpp");
	cout << "done" << endl;
	system("pause");
	return 0;
}