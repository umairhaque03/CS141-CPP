// CS 141
// Spring 2023
// Program 4 - Contacts App
// Author: Umair Haque
// System: macOS Ventura 13.0.1

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "Contact.h"
#include "ContactList.h"

using namespace std;

// Searches name for contact
vector<int> searchName(ContactList &list)
{
  string searchTerm;
  string subMenu;
  string specific_contact_index;
  char subMenuOption = 'R';
  char confirm = 'M';
  vector<int> numbered;
  int first_index;
  int total_indexes;
  cout << "Enter a search term" << endl;
  cout << endl;
  cin >> searchTerm;
  numbered = list.findContactsByName(searchTerm);
  return numbered;
}

// Displays Menu
void displayMenu()
{
  cout << "********************************************" << endl;
  cout << "Main Menu" << endl;
  cout << endl;
  cout << "Enter the letter for the desired menu option:" << endl;
  cout << "  C - Get count " << endl;
  cout << "  L - Load contacts from file " << endl;
  cout << "  S - Search contacts " << endl;
  cout << "  P - Print contacts " << endl;
  cout << "  X - Exit" << endl;
}

int main()
{
  ContactList contactlist;

  // Initialize Variables
  char input;
  char option;
  char edit_contact;
  int list_nums;
  input = ' ';

  // Initialize while loop that runs until the user inputs X.
  while (toupper(input) != 'X')
  {
    // Displays menu options
    displayMenu();
    cin >> input;
    input = toupper(input);

    // Will run cases depending on the input from user
    switch (input)
    {

    // When user inputs "L", this case is activated which will load contact
    // from a file
    case 'L':
    {
      string filename;
      cout << "Enter a filename" << endl;
      cin >> filename;
      cout << contactlist.loadContactsFromFile(filename) << endl;
      cout << endl
           << endl;
      break;
    }

    // When user inputs "C", this case is activated which will show the count
    // of contacts loaded
    case 'C':
    {
      cout << "There are " << contactlist.getCount() << " contacts" << endl
           << endl;
    }
    break;

    // Searches for contacts that matches terms given, and then prompts the user what they want to do with that contact
    case 'S':
    {
      vector<int> results = searchName(contactlist); // stores the result from search in vector

      // Output different words based on size of vector
      string word = (results.size() > 1) ? " results" : " result";

      // If there are no contacts that match the search
      if (results.empty())
      {
        cout << "No matching contacts found for the search term." << endl;
      }
      else
      {
        // Outputs contacts by lastname, firstname
        cout << "Found " << results.size() << word << endl;
        for (int i = 0; i < results.size(); i++)
        {
          Contact *contact = contactlist.getContact(results[i]);
          cout << (i + 1) << ". " << contact->getLastName() << ", "
               << contact->getFirstName() << endl;
        }

        // Prompts users with options on what to do with given contacts
        cout << endl;
        cout << "  Enter an option:" << endl;
        cout << "  P - Print contacts" << endl;
        cout << "  or a Contact number to view/edit" << endl;
        cout << "  R - Return to main menu" << endl;

        // Initialize optionString to take input from given menu
        string optionString;
        cin >> optionString;

        if (optionString == "R")
        {
          continue; // returns to main menu
        }
        else if (optionString == "P")
        {
          contactlist.printContacts(results); // Prints contacts
          continue;
        }
        else
        {
          int contactNum;
          stringstream s(optionString);

          // IF number given is in range, it will prompt user on what to do with contacy
          if (s >> contactNum && contactNum <= results.size() && contactNum >= 1)
          {
            int index = contactNum - 1;
            Contact *currContact = contactlist.getContact(results[index]);
            cout << currContact->getAsString() << endl;

            // Options menu for the contact selected
            cout << "Enter an option for contact: " << endl;

            cout << "  A - Edit address" << endl;
            cout << "  B - Edit date of birth" << endl;
            cout << "  E - Edit email address" << endl;
            cout << "  N - Edit name" << endl;
            cout << "  P - Edit phone numbers" << endl;
            cout << "  R - Return to main menu" << endl;
            cout << "  D - Delete" << endl;

            cin >> edit_contact;
            edit_contact = toupper(edit_contact);

            // Initialize a switch case to excecute user options
            switch (edit_contact)
            {
            // Edits address of contact
            case 'A':
              break;

            // Edits date of birth of contact
            case 'B':
              break;

            // Edits email address of contact
            case 'E':
            {
              string email_edit = " ";
              cout << "Current email:" << endl;
              cout << currContact->getEmail() << endl; // <- will prompt email of current contact
              cout << "Enter new email or C to cancel:" << endl;
              cin >> email_edit;

              // Checks if user wants to cancel or edit email
              if (email_edit == "C" || email_edit == "c")
              {
                continue;
              }
              else
              {
                currContact->setEmail(email_edit);
                cout << "Email updated:" << endl
                     << currContact->getEmail() << endl;
              }
              cout << endl;
              continue;
            }
            break;

            // Edits the name of the contact
            case 'N':
              break;

            // Edits the phone number of the selected contact
            case 'P':
            {
              // Initialize vector to store the phone number of selected contact
              vector<string> phoneNum = currContact->getPhoneNumbers();

              // Initialize numWord for proper grammar
              string numWord = (phoneNum.size() == 1) ? " number" : " numbers";

              cout << "Found " << phoneNum.size() << " phone" << numWord
                   << endl;

              // Outputs phone number for contact selected
              for (int i = 0; i < phoneNum.size(); i++)
              {
                cout << (i + 1) << ". " << phoneNum[i] << endl;
              }

              // Prompts user with options
              cout << "Enter an option:" << endl;
              cout << "  A - Add a phone number" << endl;
              cout << "  R - Return to main menu" << endl;
              cout << "  or list number to delete" << endl;

              // Store the input in variable subOption
              string subOption;
              cin >> subOption;

              // Makes subOption capital so it is not case sensetive
              for (int i = 0; i < subOption.length(); i++)
              {
                subOption[i] = toupper(subOption[i]);
              }

              // If user inputs "R", it will return to main menu
              if (subOption == "R")
              {
                continue;
                break;
              }

              // Adds phone number to the contact
              else if (subOption == "A")
              {
                // Initialize phoneType and prompt user on which type of phone to add
                char phoneType;
                cout << "Enter the letter for the phone number type:" << endl;
                cout << "C(ell), W(ork) or H(ome)" << endl;

                cin >> phoneType;
                phoneType = toupper(phoneType);

                // Initialize string number, which will store the phone number
                string number;
                cout << "Enter the phone number: " << endl;
                cin >> number;

                // Initialize string add, which will add the phone number to contacts
                string add = currContact->addPhone(phoneType, number);
                cout << add << endl
                     << endl;
                continue;
              }

              else
              {
                // Deletes the number the user selects
                char deleteConfirm;
                int numDelete;

                stringstream ss(subOption);

                if (ss >> numDelete && numDelete >= 1 && numDelete <= results.size())
                {

                  int numIndex = numDelete - 1;

                  // Prompts user for confirmation to delete phone
                  cout << "Are you sure you want to delete phone: "
                       << phoneNum[numIndex] << "?" << endl;
                  cout << "Enter 'Y' to confirm. " << endl;
                  cin >> deleteConfirm;
                  deleteConfirm = toupper(deleteConfirm);

                  // If user inputs 'Y', delete the selected phone number.
                  if (deleteConfirm == 'Y')
                  {
                    cout << currContact->deletePhone(numIndex) << endl;
                  }
                  else
                  {
                    cout << "Invalid input." << endl;
                  }
                }
                continue;
                break;
              }
            }

            // Will intiliaze when user inputs "D" which will prompt to deleting contact steps
            case 'D':
            {
              char confirmDelete;
              cout << "Are you sure you want to delete contact " << currContact->getName() << "?" << endl
                   << "Enter 'Y' to confirm." << endl;
              cin >> confirmDelete;
              confirmDelete = toupper(confirmDelete);

              if (confirmDelete == 'Y')
              {
                cout << contactlist.deleteContact(results[index]); // <- Deletes contact
              }
              cout << endl;
              cout << endl;
              cout << endl;
              continue;
            }

            break;

            // Returns to main menu when user inputs 'R'.
            case 'R':
            {
              continue;
            }
            break;
            }
          }
        }
      }
    }

    // When user inputs "X", it exits the program
    case 'X':
    {
      exit(0);
      break;
    }

    // When user input is invalid
    default:
      cout << "Invalid choice" << endl;
      break;
    }
  }

  return 0;
}