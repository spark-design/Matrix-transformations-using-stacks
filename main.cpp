
/*Student Name: Connor Sparkman
Student NetID: cps260
Compiler Used: Visual Studio
Program Description: Program takes in input from user like transform, rotate, and translate, to apply translations or rotations to a 3d point using a matrix.
*/
// Add our class header files
#include "Tokenizer.h"
#include "Stack.h"

#include <fstream>

using std::ifstream;
using std::cin;
using std::cout;
using std::endl;


// Interactive Shell Function
bool processText(istream& is, Stack stk, bool interactive)
{
	string line;
	string command;

	// Command argument variables
	double doubleArg1, doubleArg2, doubleArg3;
	int intArg1;
	string strArg1;

	// Initialize our classes as objects
	Tokenizer tkn;

	while (true)
	{
		// Begin interactive tokenizer shell
		if (!interactive)
		{
			if (is.eof()) return true;
		}
		else { cout << ">> "; }

		// Read in a line from the user
		getline(is, line);

		// Set tokenizer line from user input
		tkn.setString(line);

		// Read the command string
		// Begin long chain of if statement
		command == "";
		
		tkn.readString(command);

		// Exit command. Just exits the interactive shell and
		// and end the program
		if (command == "exit")
		{
			cout << "Exiting ...." << endl;
			return false;
		}

		// Load file command
		if (command == "load")
		{
			// load expects a filename (string arg), so error if 
			// no filename is provided
			if (!tkn.readString(strArg1)) {
				cout << "Missing file name" << endl;
				continue; // skip back to the top of the read loop
			}
			ifstream fin;
			bool status = true;

			// Attempts to open filename
			fin.open(strArg1);

			// Process file if able to open
			if (fin.is_open())
				status = processText(fin, stk, false);
			// Error out if file cannot be opened
			else
				cout << "Failed to open the file" << endl;

			// Close file
			fin.close();
			if (!status) return false;
		}


		// Help Command
		if (command == "help")
		{
			// Help Menu Formatting Color Codes
			string commandColorCode = "\x1b[36m";
			string parameterColorCode = "\x1b[35m";
			string defaultColorCode = "\x1b[39m";

			// Lists all possible shell commands
			cout << "Commands" << endl
				<< "############" << endl
				<< commandColorCode << "exit\t\t" << defaultColorCode << "Exits the interactive shell" << endl
				<< commandColorCode << "load " << parameterColorCode << "String\t" << defaultColorCode << "Loads a file to execute a list of commands" << endl
				<< commandColorCode << "help\t\t" << defaultColorCode << "Lists all possible commands and their parameters" << endl
				<< commandColorCode << "push " << parameterColorCode << "Int\t" << defaultColorCode << "Adds a Node containing an Integer to the stack" << endl
				<< commandColorCode << "pop\t\t" << defaultColorCode << "Removes the top node of the stack" << endl
				<< commandColorCode << "peek " << parameterColorCode << "Int\t" << defaultColorCode << "Looks at the top Node of the stack" << endl
				<< commandColorCode << "display\t\t" << defaultColorCode << "Prints the stack" << endl
				<< "############" << endl;
		}

		if (command == "display")
		{
			stk.display();
		}

		if (command == "translate")
		{
			if (tkn.readDouble(doubleArg1))
			{
				if (tkn.readDouble(doubleArg2))
				{
					if (tkn.readDouble(doubleArg3))
					{
						stk.translate(doubleArg1, doubleArg2, doubleArg3);
						cout << "Added node containing a transition matrix to top of stack." << endl;
					}
					else
					{
						cout << "Expected a Double." << endl;
					}
				}
				else
				{
					cout << "Expected a Double." << endl;
				}
			}
			else
			{
				cout << "Expected a Double." << endl;
			}
		}

		if (command == "transformVertex")
		{
			if (tkn.readDouble(doubleArg1))
			{
				if (tkn.readDouble(doubleArg2))
				{
					if (tkn.readDouble(doubleArg3))
					{
						stk.transformVertex(doubleArg1, doubleArg2, doubleArg3);
					}
					else
					{
						cout << "Expected a Double." << endl;
					}
				}
				else
				{
					cout << "Expected a Double." << endl;
				}
			}
			else
			{
				cout << "Expected a Double." << endl;
			}
		}

		if (command == "undo")
		{
			stk.pop();
			cout << "Removed top node from stack." << endl;
		}
		
		if (command == "rotateZ") // Uses roll
		{
			if (tkn.readDouble(doubleArg1))
			{
				stk.roll(doubleArg1);
				cout << "Added node containing a roll matrix to the top of the stack." << endl;
			}
			else
			{
				cout << "Expected a double." << endl;
			}
		}

		if (command == "rotateY") // Uses Yaw
		{
			if (tkn.readDouble(doubleArg1))
			{
				stk.yaw(doubleArg1);
				cout << "Added node containing a yaw matrix to the top of the stack." << endl;
			}
			else
			{
				cout << "Expected a double." << endl;
			}
		}

		if (command == "rotateX") // Uses pitch
		{
			if (tkn.readDouble(doubleArg1))
			{
				stk.pitch(doubleArg1);
				cout << "Added node containing a pitch matrix to the top of the stack." << endl;
			}
			else
			{
				cout << "Expected a double." << endl;
			}
		}
	}
}


int main()
{
	Stack stk;
	//Matrix* tmp = new Matrix();
	// Passes cin to the function
	// This is needed to create an interacive shell

	processText(cin, stk, true);
	return 0;
}