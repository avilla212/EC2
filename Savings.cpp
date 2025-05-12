#include "Savings.h"

// ====== deposit ==================
// This function deposits a specified amount into the user's savings account.
//
// input: amount - the amount to deposit
//        user - the username of the user
//
// output: none
//  =====================================

void Savings::deposit(double amount, string user) {
	// Load user data from the file and store it in a vector
    std::vector<UserData> users = loadUserData();

	// iterate through the vector of users to find the user
    for (int i = 0; i < users.size(); ++i) {
		// if the username matches, deposit the amount into their savings account
        if (users[i].username == user) {
			// deposit the amount into the user's savings account
            users[i].savings += amount;
            // update the savings balance 
            savingsBalance = users[i].savings;
            break;
        }
    }

    // save the updated user data back to the file
    saveUserData(users);
}
// end of deposit function

// ====== withdraw ==================
// This function withdraws a specified amount from the user's savings account.
//
// input: amount - the amount to withdraw
//        user - the username of the user
//
// output: none
//  =====================================

void Savings::withdraw(double amount, string user) {
    std::vector<UserData> users = loadUserData();

    for (int i = 0; i < users.size(); ++i) {
        if (users[i].username == user) {
            if (amount > users[i].savings) {
                cout << "You cannot withdraw that much. Try again." << endl;
                return;
            }

            if (withdrawLimit > 0) {
                users[i].savings -= amount;
				savingsBalance = users[i].savings;
				withdrawLimit--;
				break;
			}
			else {
				cout << "You have withdrawn 5 times, you will incur a fee of $5.00" << endl;
				// incur a fee of $5.00
				// we dont need to check if they have enough money
				// it will just go negative
				users[i].savings -= amount + 5.00;
				savingsBalance = users[i].savings;
				withdrawLimit = 5; // set back to 5 after incurring fee
				break;
            }
        }
    }

	// Save the updated user data back to the file
    saveUserData(users);
}
// end of withdraw function

// ====== display ==================
// This function displays the user's savings account balance.
//
// input: none
// output: none
//  =====================================

void Savings::display() {
    cout << "Savings balance: $" << savingsBalance << endl;
}
// end of display function
