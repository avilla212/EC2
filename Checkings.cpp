#include "Checkings.h"

// ====== deposit ==================
// This function deposits a specified amount into the user's checkings account.
//
// input: amount - the amount to deposit
//        user - the username of the user
//
// output: none
//  =====================================
void Checkings::deposit(double amount, string user) {
    std::vector<UserData> users = loadUserData();

    for (int i = 0; i < users.size(); ++i) {
        if (users[i].username == user) {
            users[i].checkings += amount;
            checkingsBalance = users[i].checkings;
            break;
        }
    }

    saveUserData(users);
}
// end of deposit function

// ====== withdraw ==================
// This function withdraws a specified amount from the user's checkings account.
//
// input: total - the amount to withdraw
//        user - the username of the user
//
// output: none
//  =====================================

void Checkings::withdraw(double total, string user) {
    std::vector<UserData> users = loadUserData();

    for (int i = 0; i < users.size(); ++i) {
        if (users[i].username == user) {
            if (total > users[i].checkings) {
                cout << "Cannot withdraw that much. Try again" << endl;
                return;
            }
            
			// if withdrawLimit is greater than 0, allow withdrawal without fee
            if (withdrawLimit > 0) {
				users[i].checkings -= total; // subtract the amount from checkings
                checkingsBalance = users[i].checkings; // update the checkings balance 
				withdrawLimit--;  // decrement the withdraw limit
                break;
            }
            else {
				cout << "You have withdrawn 5 times, you will incur a fee of $5.00" << endl;
				// incur a fee of $5.00
				// we dont need to check if they have enough money
				// it will just go negative
				users[i].checkings -= total + 5.00;
				checkingsBalance = users[i].checkings;
				withdrawLimit = 5; // set back to 5 after incurring fee
                break;
            }
        }
    }

	// Save the updated user data back to the file
    saveUserData(users);
}
// end of withdraw function

// ===== display ==================
// This function displays the user's checkings account balance.
//
// input: none
// output: none
//  =====================================
  
void Checkings::display() {
    cout << "Checkings balance: $" << checkingsBalance << endl;
}
// end of display function