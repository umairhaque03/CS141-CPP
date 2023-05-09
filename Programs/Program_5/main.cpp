/**------------------------------------------
  Program 5: The Scrambler
  Course: CS 141, Spring 2023
  System: macOs Ventura 13.0.1
  Author: Umair Haque, starter code provided by George Maratos and David Hayes
---------------------------------------------**/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <time.h>
using namespace std;

//Scrambler class, functions are public members and variables/mambers are private data members.
class Scrambler
{
	public:
	Scrambler(const string &path, const int size);
	string str() const;
	void JumbleBoard();
	void try_move(const string &cmd);
	bool is_over() const;
	string display_solution();
	vector<string> get_words() const;
	void moveUp(int index);
	void moveDown(int index);
	void moveRight(int index);
	void moveLeft(int index);

	private:
	int size;
	string file;
	vector<string> words;
	vector<vector < char>> board;
	vector<string> boardWords;
	vector<vector < char>> boardCopy;
	vector<string> solCmd;
	string initial_board;
};

//Constructor for Scrambler
//Retrieves words from file and jumbles them randomly on the board
Scrambler::Scrambler(const string &path, const int size)
{
	// Storing values as private data members of the class
	this->file = path;
	this->size = size;

	//Opens file
	ifstream file;
	file.open(path);

	//Adds word from file into a vector
	for (string line; getline(file, line);)
	{
		words.push_back(line);
	}

	//Adds spaces in 2D vector
	for (int i = 0; i < size; i++)
	{
		vector<char> vecRows;
		for (int a = 0; a < size; a++)
		{
			vecRows.push_back(' ');
		}

		board.push_back(vecRows);
	}

	for (int i = 0; i < size; i++)
	{
		int extraSpace = board.at(i).size();
		int charIndex = 0;
		int spaceLeft;

		while (extraSpace > 2) //<- Will excecute when space is more than 2
		{

			int randomPos = rand() % words.size();	//<- Retrives random index
			string randWord = words[randomPos];	//<- Stores word at that random index
			spaceLeft = extraSpace - randWord.size();	//<- Calculates open space after word is stored

			if (randWord.size() <= extraSpace && spaceLeft != 3)
			{
				boardWords.push_back(randWord);

				// Initialize a for loop for each character in a specific random word.
				for (char c: randWord)
				{
					board.at(i).at(charIndex) = c;
					charIndex++;
					extraSpace--;
				}

				charIndex++;
				extraSpace--;
			}
		}
	}

	JumbleBoard();	//Intiialize jumble board to jumble the board
	initial_board = str();	//initializes the board
	boardCopy = board;	//makes a copy of the initialized board
}

//Returns the entire board as a string
string
Scrambler::str() const
{
	int count = 1;
	string boardStr;
	string lines;

	//Add whitespace
	for (int i = 1; i <= size; ++i)
	{
		if (i == 1)
		{
			boardStr += " ";
		}

		if (!(i == size + 1))
		{
			boardStr += "   " + to_string(i);
		}
	}

	boardStr += "\n";

	//Adding lines
	for (int i = 0; i < 4 * size; ++i)
	{
		lines += "-";
	}

	int i = 0;

	//Interate over the 2D vector and adding it to the string to represent the board
	for (vector<char> vecRows: board)
	{
		boardStr += "   " + lines + "\n";
		boardStr += to_string(count) + " | ";
		string replaceStr;
		int i;
		for (i = 0; i < vecRows.size() - 1; i++)
		{
			replaceStr = vecRows.at(i);
			boardStr += replaceStr + " | ";
		}

		replaceStr = vecRows.at(i);
		boardStr += replaceStr + " |";
		boardStr += "\n";
		count += 1;
	}

	boardStr += "   " + lines;
	return boardStr;
}

// randomly jumbles all the characters on the board, so that they do not represent words anymore
void Scrambler::JumbleBoard()
{
	int temp = rand() % 8;
	int numMoves = temp + 3;

	for (int i = 1; i <= numMoves; i++)
	{
		int count = rand() % size;	//<- generates random selection of row/column so it can be shuffled

		if (i % 2 == 0)
		{
			int direction = rand() % 2;
			if (direction == 0)
			{
				char d = 'u';
				string cmd = "c" + to_string(count) + "d";
				solCmd.insert(solCmd.begin(), cmd);	//<- Storing moves in vector so it can be outputted
				moveUp(count);
			}
			else
			{
				char d = 'd';
				string cmd = "c" + to_string(count) + "u";
				solCmd.insert(solCmd.begin(), cmd);
				moveDown(count);
			}
		}
		else
		{
			int direction = rand() % 2;	//<- Random direction for left or right shifting
			if (direction == 0)
			{
				char d = 'r';
				string cmd = "r" + to_string(count) + "l";
				solCmd.insert(solCmd.begin(), cmd);
				moveRight(count);
			}
			else
			{
				char d = 'l';
				string cmd = "r" + to_string(count) + "r";
				solCmd.insert(solCmd.begin(), cmd);
				moveLeft(count);
			}
		}
	}
}

//Excutes user input, if user types in "R", it will reset the board
void
Scrambler::try_move(const string &cmd)
{
	int cmdSize = cmd.size();	//<- Retrieve size of the command

	//If command is the correct size, analyze and excecute given command
	if (cmdSize == 3)
	{
		char pos = tolower(cmd.at(0));
		int idx = stoi(cmd.substr(1, 1));
		idx = idx - 1;
		char d = tolower(cmd.at(2));

		// Will excecute shift functions based on the user input
		if (d == 'u')
		{
			moveUp(idx);
		}
		else if (d == 'd')
		{
			moveDown(idx);
		}
		else if (d == 'l')
		{
			moveLeft(idx);
		}
		else if (d == 'r')
		{
			moveRight(idx);
		}
	}

	//This will reset the board if user types in "R"
	else if (cmdSize == 1)
	{
		board = boardCopy;
	}
}

// checks if the game has ended or needs to keep continuing
bool
Scrambler::is_over() const
{
	int num = 0;

	//Will iterate over the board and will determine if game is over or not
	for (vector<char> vecRows: board)
	{
		string word;
		if (isspace(vecRows.at(0)))
		{
			return false;
		}

		for (int i = 0; i < size; i++)
		{
			if (isalpha(vecRows.at(i)))
			{
				word += vecRows.at(i);
			}
			else
			{
				continue;
				word = "";
			}

			if (find(boardWords.begin(), boardWords.end(), word) != boardWords.end())
			{
				num++;
				word = "";
			}
		}
	}

	//If all words on board are correct, return true. Otherwise return false (keeps game going)
	if (num == boardWords.size())
	{
		return true;
	}
	else
	{
		return false;
	}
}


//outputs all the boards from the jumbled state until the final result
string Scrambler::display_solution()
{
	string final = "";
	final += initial_board + "\n";

	//Iterates and excutes commands
	for (int i = 0; i < solCmd.size(); i++)
	{
		char pos = tolower(solCmd.at(i).at(0));
		int idx = stoi(solCmd.at(i).substr(1, 1));
		char d = tolower(solCmd.at(i).at(2));
		final += "***Move " + to_string(i + 1) + "(" + pos + "," + to_string(idx + 1) + "," + d + ")" + "\n";
		if (d == 'u')
		{
			moveUp(idx);
		}
		else if (d == 'd')
		{
			moveDown(idx);
		}
		else if (d == 'l')
		{
			moveLeft(idx);
		}
		else if (d == 'r')
		{
			moveRight(idx);
		}

		final += str() + "\n";
	}

	return final;	// <- Returns "final" which is the solution as a string
}

//Returns words on the board
vector<string> Scrambler::get_words() const
{
	return boardWords;
}

//Pushes a specific column up, which cause all of the elements to push up and the top elements appear at the bottom.
void Scrambler::moveUp(int index)
{
	char one = board.at(0).at(index);
	for (int i = 0; i < size - 1; i++) 		//<- Iterating through each char in column
	{


		board.at(i).at(index) = board.at(i + 1).at(index);	//<- moves character to position + 1
	}

	board.at(size - 1).at(index) = one;
}

//Pushes a specific column down, which cause all of the elements to push down and the bottom elements appear at the top.
void Scrambler::moveDown(int index)
{
	char one = board.at(size - 1).at(index);
	for (int i = size - 1; i > 0; i--)
	{
		board.at(i).at(index) = board.at(i - 1).at(index);
	}

	board.at(0).at(index) = one;
}

//Moves all the elements in a row to the right, and the rightmost element becomes the leftmost element.
void Scrambler::moveRight(int index)
{
	char one = board.at(index).at(size - 1);
	for (int i = size - 1; i > 0; i--)
	{
		board.at(index).at(i) = board.at(index).at(i - 1);
	}

	board.at(index).at(0) = one;
}

//Moves all the elements in a row to the left, and the leftmost element becomes the rightmost element.
void Scrambler::moveLeft(int index)
{
	char one = board.at(index).at(0);
	for (int i = 0; i < size - 1; i++)
	{
		board.at(index).at(i) = board.at(index).at(i + 1);
	}

	board.at(index).at(size - 1) = one;
}

//Testing the code, autograder will dismiss this
int main()
{
	string file = "dictionary.txt";
	int length = 5;
	Scrambler s(file, length);
	cout << s.display_solution();
	cout << s.str();
	s.is_over();
}