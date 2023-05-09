/**------------------------------------------
    Program 2: Great 13
    Course: CS 141, Spring 2023.
    System: Linux x86_64 and G++
    Author: Umair Haque, starter code provided by George Maratos and David Hayes
 ---------------------------------------------**/
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

/* Everything below this comment is starter code, and you are not
allowed to modify */

using namespace std;

// Function that displays the instructions to the user

void display_instructions() {
  cout << "Class: CS 141" << endl
       << "Program 2: Great 13" << endl
       << endl
       << "Make a series of jumps until there is a single piece left" << endl
       << "anywhere on board. On each move you must jump an adjacent" << endl
       << "piece   into   an  empty  square,  jumping  horizontally," << endl
       << "vertically, or diagonally." << endl
       << endl
       << "Input of 'R' resets the board back to the beginning, and " << endl
       << "'X' exits the game." << endl;
}

// The internal representation of the board as an array. Do not modify directly.

char board[13]{};

/* These two functions are how you will get and set elements on the board. Only
use these two when changing, or reading the board. */

char get_element(char position) {
  if ((position < 'A') || (position > 'M')) {
    cout << "Failed to get element at position " << position << endl
         << "Make sure the given position is an uppercase letter " << endl
         << "between A-M." << endl;
    exit(1);
  }
  return board[position - 'A'];
}

void set_element(char position, char value) {
  if ((position < 'A') || (position > 'M')) {
    cout << "Failed to set element at postion " << position << endl
         << "Make sure the given position is an uppercase letter " << endl
         << "between A-M." << endl;
    exit(1);
  }
  board[position - 'A'] = value;
}

// print out the board with the legend on the right

void display_board() {
  cout << endl;
  cout << setw(7) << "Board" << setw(12) << "Position" << endl;
  cout << setw(5) << board[0] << setw(11) << 'A' << endl
       << setw(3) << board[1] << ' ' << board[2] << ' ' << board[3] << setw(11)
       << "B C D" << endl
       << board[4] << ' ' << board[5] << ' ' << board[6] << ' ' << board[7]
       << ' ' << board[8] << ' ' << " E F G H I" << endl
       << setw(3) << board[9] << ' ' << board[10] << ' ' << board[11]
       << setw(11) << "J K L" << endl
       << setw(5) << board[12] << setw(11) << 'M' << endl;
  cout << endl;
}

/* This is the end of the starter code, and below is where you can
add your own code. Feel free to add helper functions or variables.
*/

/* forward declarations for the functions you will write later. This
is so the order of the function definitions, in this file,  does not
matter. */

void make_move();
void initialize_board();
bool game_over();

//Runs all functions nessecary for game to work
int main() {

  initialize_board();
  display_instructions();

  do {
    display_board();
    make_move();
    
  } while (!game_over() == false && !cin.eof());

  return 0;
}

//Will prompt user to enter move, check the move, and update the board
void make_move() {

  // Ask user for information and store it in string "input"
  string input;
  cout << "Enter positions from, jump, and to (e.g. EFG): ";
  cin >> input;

  // Converts input to uppercase
  for (int i = 0; i < input.length(); i++) {
    input[i] = toupper(input[i]);
  }

  // If input = X, stop the program
  if (input == "X") {
    cout << "Exiting." << endl;
    exit(0);
  }

  // If input = R, restart the game
  if (input == "R") {
    cout << "Restarting game." << endl;
    initialize_board();
    display_board();
    make_move();
  }

  // If input length is not equal to 3, print error and allow the user to retry
  if (input.length() != 3) {
    cout << "*** Invalid sequence. Please retry." << endl;
    display_board();
    make_move();
  }
  
  // Check if input includes valid moves
  if (input == "ADI" || input == "BGL" || input == "EJM" || input == "ABE" ||
      input == "DGJ" || input == "ILM" || input == "IDA" || input == "LGB" ||
      input == "MJE" || input == "EBA" || input == "JGD" || input == "MLI" ||
      input == "ACG" || input == "CGK" || input == "GKM" || input == "BFJ" ||
      input == "DHL" || input == "GCA" || input == "KGC" || input == "MKG" ||
      input == "JFB" || input == "LHD" || input == "BDC" || input == "DCB" ||
      input == "EFG" || input == "GFE" || input == "FGH" || input == "HGF" ||
      input == "GHI" || input == "IHG" || input == "JKL" || input == "LKG") {

    // Set from,jump,to from input
    char from = input.at(0);
    char jump = input.at(1);
    char to = input.at(2);

    // create variables that stores the element from the variables: from,jump,to
    char from_element = get_element(from);
    char jump_element = get_element(jump);
    char to_element = get_element(to);

    // Check if position is a piece
    if (from_element == '.') {
      cout << "*** Source needs a piece. Please retry." << endl;
      display_board();
      make_move();
    }

    // Check if peice is being jumped over
    if (jump_element == '.') {
      cout << "*** Must jump a piece. Please retry." << endl;
      display_board();
      make_move();
    }

    // Check if destination is empty
    if (to_element == '#') {
      cout << "*** Destination must be empty. Please retry." << endl;
      display_board();
      make_move();
    }

    // Updates the board once input passes all checks
    set_element(from, '.');
    set_element(jump, '.');
    set_element(to, '#');

    //Do while loop to check if game is over
    do {

      game_over();
      display_board();
      make_move();

    } while (!game_over() == false && !cin.eof());

  } 
  else {
    //If the input does not equal the a valid move, display error and allow the user to retry
    cout << "*** Move is invalid. Please retry." << endl;
    display_board();
    make_move();
  }
}

//Returns false if game is not over
bool game_over() {

  // Initialize count to 0 to count '.' on the board
  int count = 0;
  
  // Initialize for loop to iterate through the board
  for (int i = 0; i < 13; i++) {
    
    // If the element of the board is '.', add one to the count
    if (board[i] == '.') {
      count++;
      
    }
  }
  
  // If there are 12 '.', print congrats message and exit program
  if (count == 12) {
    cout << "Congrats you win!" << endl;
    exit(0);
  }
  
  // return false if game is not over
  return false;
  
}

//Displays Initial board
void initialize_board() {
  
  // For Loop that displays board
  for (int i = 0; i < 13; i++) {
    if (i == 6) {
      set_element('A' + i, '.');
    } 
    else {
      set_element('A' + i, '#');
    }
  }
}
