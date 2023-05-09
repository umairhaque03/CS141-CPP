/**------------------------------------------
    Program 3: Typing Tutor

    Will give users the option to spell commonly misspelled words, display some
    words from one of the data sets, practice typing random words from a
    dictionary, or to search for a word in the dictionary.

    Course: CS 141, Spring 2023
    System: Linux_x86_64 and G++ Author: Umair Haque, starter code provided by
 George Maratos and David Hayes
 ---------------------------------------------**/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int NMISP = 5;
const int RNG_RANGE = 100;

void display_header(const int ndict, const int nmiss) {
  cout << "*** Typing Tutor" << endl;
  cout << "There are " << ndict << " words in the dictionary." << endl;
  cout << "There are " << nmiss << " commonly misspelled words." << endl;
}

void display_menu_options() {
  /* This function prints out all the menu options, it is
  given to you as part of the starter code. If you change
  it,  you run the  risk of failing  an early test of the
  autograder.*/

  cout << endl
       << "*** Select a menu option:" << endl
       << "1. Spell commonly misspelled words" << endl
       << "2. Type random words from the full dictionary" << endl
       << "3. Display some words from one of the lists" << endl
       << "4. Use binary search to lookup a word in the dictionary" << endl
       << "5. Exit the program." << endl
       << "Your choice: ";
}

//Creates and returns a vector that has n random numbers drawn from 0 to the value of the parameter max.
vector<int> randn(const int n, const int max) {

  //Initialize vector and pushes random numbers in those vectors
  vector<int> result;
  for (int i = 0; i < n; i++) {
    int rNum = rand() % (max + 1);
    result.push_back(rNum);
  }

  return result;
}

ifstream open(const string &src_file) {
  ifstream src{src_file};
  if (!src.is_open()) {
    cout << "Could not find file " << src_file << "." << endl;
    exit(1);
  }
  return src;
}

//Reads the data from the file src_file, and store each line in the vector dst.
void extract_dict(vector<string> &dst, const string &src_file) {
  ifstream file = open(src_file);
  string count;
  while (getline(file, count)) {
    dst.push_back(count);
  }

  file.close();
}
//Extract the word pairs (misspelled, correct) from the file and stores them in their vectors.
void extract_misspelled(vector<string> &misspelled, vector<string> &correct,const string &src_file) {

  //Ifsream named "file" which stores the source file
  ifstream file = open(src_file);
  string count;

  //While loop that adds misspelled word and correct words to their vectors from a file
  while (getline(file, count)) {
    stringstream ss(count);
    string misspelledWord;
    string correctWord;
    ss >> misspelledWord >> correctWord;
    misspelled.push_back(misspelledWord);
    correct.push_back(correctWord);
  }
  file.close();
}

//print out the elements in the vector src with a space between each of the elements.
void display_elems(const vector<string> &src, const vector<int> &positions) {

  for (int i = 0; i < positions.size(); i++) {
    cout << src[positions[i]];
    if (i < positions.size()) {
      cout << " ";
    }
  }
}

//Copy the elements at the indices, in the positions vector, from the correct vector, into the vector dst.
void extract_spelling_answers(vector<string> &dst, const vector<string> &correct, const vector<int> positions) {

  for (int index : positions) {
    dst.push_back(correct[index]);
  }
}

//This function will find spelling mistakes and store it in the dst vector
void extract_spelling_mistakes(vector<string> &dst, const string &to_grade, const vector<string> &correct) {

  stringstream ss(to_grade);
  for (int i = 0; i < correct.size(); i++) {
    string wordIndex;
    ss >> wordIndex;
    if (wordIndex != correct[i]) {
      dst.push_back(wordIndex + " -> " + correct[i]);

    }
  }
}

//Will prompt user with mistakes that they made 
void report_misspell_mistakes(const vector<string> &mistakes,const int num_words) {

  //Will determing if user made mistakes or not
  if (mistakes.size() == 0) {
    cout << "No misspelled words!" << endl;
  }
   else {
    cout << "Misspelled words:\n";

    for (int i = 0; i < mistakes.size(); i++) {
      cout << "    " << mistakes[i] << endl;
    }
  }
  
  //Initialize variables to calculate user score
  int score = (num_words - mistakes.size()) * 3;
  int penalty = mistakes.size() * 6;
  int finalScore = score - penalty;

//Output user scores
  cout << score << " points: " << num_words - mistakes.size() << " spelled correctly x 3 points for each.\n";

  cout << penalty << " point penalty: " << mistakes.size() << " spelled incorrectly x -6 points for each.\n";

  cout << "Score: " << finalScore << endl;
}

void evaluate_user_misspells(const vector<string> &src, const vector<int> &positions) {

  vector<string> correct;
  vector<string> mistakes;
  string input;
  getline(cin, input);
  extract_spelling_answers(correct, src, positions);
  extract_spelling_mistakes(mistakes, input, correct);
  report_misspell_mistakes(mistakes, 5);
}

//displays 5 random words from the dictionary and evaluate the user's input
void misspelled(const vector<string> &mspelled, const vector<string> &correct) {

  cout << endl << "*** Using commonly misspelled words.\n";

  //Initialize integer vector named position
  vector<int> positions;
  positions = randn(5, correct.size() - 1);

  //Display words
  display_elems(mspelled, positions);
  cout << endl << "Type the words above with the correct spelling:\n";

  //Will give user feedback based on the words inputted
  evaluate_user_misspells(correct, positions);
}


//display five random words from the full dictionary, then evaluate the user's input. 
void full_dict(const vector<string> &dict) {

  //Print out starting message for menu option 2,
  cout << endl << "*** Using full dictionary." << endl;

  //Initialize integer vector named position
  vector<int> positions;
  positions = randn(5, dict.size() - 1);

  //Display words
  display_elems(dict, positions);
  cout << endl << "Correctly type the words above:" << endl;

  //Will give user feedback based on the words inputted
  evaluate_user_misspells(dict, positions);
}

void display_words_prompt() {
  // This displays the data set choices for menu option 3
  cout << endl
       << "*** Displaying word list entries." << endl
       << "Which words do you want to display?" << endl
       << "A. Dictionary of all words" << endl
       << "B. Commonly misspelled words (wrongly spelled)" << endl
       << "C. Commonly misspelled words (correctly spelled)" << endl
       << "Your choice: ";
}

//Will print words from dictionary between given indices
void print_range(const vector<string> &data) {

  //Prompt user to enter stard and end indices
  cout << "*** Enter the start and end indices between 0 and "
       << data.size() - 1 << ": ";


  int startIndex;
  int endIndex;
  cin >> startIndex >> endIndex;

  //Checks if indices are valid
  if (startIndex < 0 || startIndex > endIndex || startIndex >= data.size() ||
      endIndex >= data.size()) {

    cout << "The end index must come after the start, and the indices must be ""in range." << endl;
  }
  
  //Outputs words
  for (int i = startIndex; i <= endIndex; i++) {
    cout << i << ". " << data[i] << endl;
  }
}

//Will read in the user's choice of dataset, and display the data in range.
void display_in_range(const vector<string> &dict,const vector<string> &mspelled, const vector<string> &correct) {

  //Display initial message
  display_words_prompt();

  //Will take input and will call print_range function depending on what user inputs
  char input;
  cin >> input;
  if (toupper(input) == 'A') {
    print_range(dict);
  } else if (toupper(input) == 'B') {
    print_range(mspelled);
  } else if (toupper(input) == 'C') {
    print_range(correct);
  } else {
    cout << "Invalid" << endl;
  }
}

void bsearch(const vector<string> &data) {

  //Prompt users to enter a word to search
  string findWord;
  cout << "*** Enter word to search: ";
  cin >> findWord;

  //Initialize variables for search
  int index = 1;
  int start = 0;
  int size = data.size();


  //while loop that searches for word in dictionary
  while (start < size) {

    int mid = (start + size) / 2;
    cout << setw(5) << index << ". Comparing to: " << data[mid] << endl;
    index++;

    if (data[mid] == findWord) {
      cout << findWord << " was found." << endl;
      return;
    } 
    else if (data[mid] < findWord) {
      start = mid + 1;
    } 
    else {
      size = mid;
      }
  }
  cout << findWord << " was NOT found." << endl;
}

void extract_all_data(vector<string> &dict, vector<string> &mspelled,vector<string> &correct) {
  extract_dict(dict, "dictionary.txt");
  extract_misspelled(mspelled, correct, "misspelled.txt");
}

int main() {
  srand(1);
  vector<string> dict, mspelled, correct;
  extract_all_data(dict, mspelled, correct);
  display_header(dict.size(), correct.size());
  unsigned int choice;
  do {
    display_menu_options();
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch (choice) {
    case 1:
      misspelled(mspelled, correct);
      break;
    case 2:
      full_dict(dict);
      break;
    case 3:
      display_in_range(dict, mspelled, correct);
      break;
    case 4:
      bsearch(dict);
      break;
    case 5:
      cout << "Exiting." << endl;
      break;
    default:
      cout << "No menu option " << choice << ". " << "Please try again." << endl;
    }
  } while ((choice != 5) && !cin.eof());

  return 0;
}