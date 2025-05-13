#include <iostream>
#include <fstream>

#include "Account.h"
#include "Savings.h"
#include "Checkings.h"

using namespace std;

int main() {
	try {
		// variables to hold user input and account details
		int choice;
		string username;
		string password;

		// create an account object
		Account* account = new Account();

		do {
			// display the main menu
			account->loginAndSignup();

			// get user choice
			cout << "Enter choice: ";
			cin >> choice;

			// check if choice is valid
			switch (choice) {
				// display the menu
			case 1: {
				cout << "***********LOGIN***********\n";

				// grab username and password
				cout << "Enter username: ";
				cin >> username;

				cout << "Enter password: ";
				cin >> password;

				// bool returning function checks if user exists
				if (account->login(username, password)) {
					// call the handleLoggedInMenu function
					account->handleLoggedInMenu(username);
				}
				else {
					// if login fails, display error message
					cout << "Login failed. Please try again." << endl;
				}
				break;
			}
			case 2: {
				cout << "***********SIGNUP***********\n";
				// grab username and password
				cout << "Enter username: ";
				cin >> username;

				cout << "Enter password: ";
				cin >> password;

				// bool returning function checks if user exists
				if (account->signup(username, password)) {
					// call the handleLoggedInMenu function
					account->handleLoggedInMenu(username);
				}
				else {
					// if signup fails, display error message
					throw runtime_error("Signup failed. Please try again.");
				}
				break;
			}
			default:
				// if the choice is invalid, display error message
				throw runtime_error("Invalid choice. Please try again.");
		
			}
		} while (choice != 6);
		// exit the program and cleanup
		delete account;

		return 0;
	}
	catch (const exception& e) {
		// catch any exceptions and display the error message
		cout << "An error occurred: " << e.what() << endl;
	}
	catch (...) {
		// catch any unknown exceptions
		cout << "An unknown error occurred." << endl;
	}
}
