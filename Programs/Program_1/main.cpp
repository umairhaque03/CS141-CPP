/**------------------------------------------
    Program 1: ASCII Flowers
    Prompt for the number of flower layers and display
    Course: CS 141, Spring 2023
    System: Linux_x86_64 and G++
    Author: Umair Haque, starter code provided by George Maratos and David Hayes
 ---------------------------------------------**/

#include <iomanip>
#include <iostream>

using namespace std;

int main() {
  // display the prompt to the user
  cout << "Program 1: ASCII Flowers\n"
       << "Choose from the following options:\n"
       << "   1. Display the HELLO graphic\n"
       << "   2. Display The Flower\n"
       << "   3. Exit the program\n"
       << "Your choice -> ";

  // read in the user's choice
  int menu_option;
  cin >> menu_option;

  // handle option to quit
  if (menu_option == 3) {
    exit(0);
  }

  // handle the HELLO graphic choice
  if (menu_option == 1) {
    char frame;
    cout << "Enter your frame character: ";
    cin >> frame;
    // top border
    cout << endl;
    for (int i = 0; i < 2; i++) {
      cout << setfill(frame) << setw(36) << ' ' << endl;
    }
    // message
    cout << setfill(frame) << setw(3) << right << " "
         << "** ** ***** **    **    *****" << setfill(frame) << setw(3) << left
         << " " << endl
         << setfill(frame) << setw(3) << right << " "
         << "** ** ***** **    **    *****" << setfill(frame) << setw(3) << left
         << " " << endl
         << setfill(frame) << setw(3) << right << " "
         << "** ** **    **    **    ** **" << setfill(frame) << setw(3) << left
         << " " << endl
         << setfill(frame) << setw(3) << right << " "
         << "***** ***** **    **    ** **" << setfill(frame) << setw(3) << left
         << " " << endl
         << setfill(frame) << setw(3) << right << " "
         << "***** ***** **    **    ** **" << setfill(frame) << setw(3) << left
         << " " << endl
         << setfill(frame) << setw(3) << right << " "
         << "** ** **    **    **    ** **" << setfill(frame) << setw(3) << left
         << " " << endl
         << setfill(frame) << setw(3) << right << " "
         << "** ** ***** ***** ***** *****" << setfill(frame) << setw(3) << left
         << " " << endl
         << setfill(frame) << setw(3) << right << " "
         << "** ** ***** ***** ***** *****" << setfill(frame) << setw(3) << left
         << " " << endl
         << right;
    // bottom border
    for (int i = 0; i < 2; i++) {
      cout << setfill(frame) << setw(36) << " " << endl;
    }
  }
  // handle the floral pattern TODO for students
  if (menu_option == 2) {

    // Initialize integer "numSection" which stores the amount of flower heads
    // the user inputs
    int numSection;
    cout << "Enter the number of sections: ";
    cin >> numSection;

    // this loop outputs each individual flower head
    for (int i = 1; i <= numSection; i++) {
      cout << setw(numSection) << setfill(' ') << ""
           << "---" << endl;

      // This loop outputs the top half of the flower head
      for (int j = 1; j < i; j++) {
        cout << setw(numSection - j) << setfill(' ') << ""
             << "{" << setw(2 * j + 1) << setfill(':') << ""
             << "}" << endl;
      }

      // Outputs the middle of the head which includes the "@"
      cout << setw(numSection - i) << setfill(' ') << ""
           << "{" << setw(i) << setfill(':') << ""
           << "@" << setw(i) << setfill(':') << ""
           << "}" << endl;

      // This loop outputs the bottom half of the flower head
      for (int j = i - 1; j > 0; j--) {
        cout << setw(numSection - j) << setfill(' ') << ""
             << "{" << setw(2 * j + 1) << setfill(':') << ""
             << "}" << endl;
      }
    }

    // Places bottom border on final flower head
    cout << setw(numSection) << setfill(' ') << ""
         << "---" << endl;

    int alternate = 1; // Initialize integer "alternate" which keeps the index
                       // of each alternating flower head

    int numStem = numSection * 2; // Initialize integer "numStem" which determines the
                                  // amount of stems of the flower head

    // This loop outputs the stem of the flower
    for (int k = 1; k <= numStem; k++) {
      if (k % 2 == 1) {
        if (alternate % 2 == 1) {
          cout << setw(numSection + 1) << setfill(' ') << ""
               << "|/" << endl;
        } else {
          cout << setw(numSection - 1) << setfill(' ') << ""
               << " \\|" << endl;
        }
        alternate += 1;
      } else {
        cout << setw(numSection + 1) << setfill(' ') << ""
             << "|" << endl;
      }
    }
  }
  return 0;
}
