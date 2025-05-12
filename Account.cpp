
#include "Account.h"
#include "Savings.h"
#include "Checkings.h"

//============ findUser =============
// Checks if the provided username and password match an entry in Users.txt
//
// input: string user, string password
// output: bool (true if match found, false otherwise)
// =====================================
bool Account::findUser(string user, string password) {
    try {
		// Open the file in read mode
        ifstream file("Users.txt");

		// Check if the file opened successfully
        if (!file.is_open()) {
            throw runtime_error("Error opening file.");
        }

		// line variable to hold each line read from the file
        string line;

		// Read the file until the end
        while (!file.eof()) {

			// Read the line into the line variable
			// delimiter is space
            getline(file, line, ' ');
            
			// Check if the line matches the username
            if (line == user) {
				// Read the next line into the line variable
                getline(file, line);
				// Check if the line matches the password
                return (line == password);
            }
            else {
				// If the username does not match, skip to the next line
                getline(file, line); // skip to next line
            }
        }
        return false;
    }
    catch (exception& e) {
        cout << e.what() << endl;
        return false;
	}
    catch (...) {
        cout << "An unknown error occurred." << endl;
        return false;
    }
}

//============ userExists =============
// Checks if a given username already exists in Users.txt
//
// input: string user
// output: bool (true if user exists, false otherwise)
// =====================================
bool Account::userExists(string user) {
    try {
		// Open the file in read mode
        ifstream file("Users.txt");

		// Check if the file opened successfully
        if (!file.is_open()) {
            throw runtime_error("Error opening file.");
        }

		// line variable to hold each line read from the file
        string line;

		// read the file line by line
        while (getline(file, line)) {
			// iss istringstream to parse the line
			// e.g "username password" = "username" "password"
            istringstream iss(line);

			// Read the username and password from the line
            string fileUser, filePass;

			// extract the username and password from the line
            iss >> fileUser >> filePass;
            
			// check if the username matches the file username
            if (fileUser == user) {
				// If the username matches, print a message and return true
                cout << "Duplicate username found: " << fileUser << endl;

                return true;
            }
        }
        return false;
    }
    catch (exception& e) {
        cout << e.what() << endl;
        return false;
    }
    catch (...) {
        cout << "An unknown error occurred." << endl;
        return false;
    }
}

//============ signup =================
// Adds a new user to Users.txt if the username is not already taken
//
// input: string user, string password
// output: bool (true if signup successful, false if duplicate or error)
// =====================================
bool Account::signup(string user, string password) {
    try {

		// Check if the username already exists
        if (userExists(user)) {
            cout << "Username already taken." << endl;
            return false;
        }
		else { // username is available

			// Open the file in append mode
            ofstream outFile("Users.txt");
            
            if (!outFile.is_open()) {
                throw runtime_error("Error opening Users.txt for writing.");
            }

            outFile << user << " " << password << endl;
            outFile.close();
            onSignup(user, password);

            cout << "Signup successful!" << endl;
            return true;
        }
    }
    catch (exception& e) {
        cout << e.what() << endl;
        return false;
    }
}

//============ onSignup =============
// Initializes a new user's savings and checkings in LoggedIn.txt
//
// input: string user, string password
// output: bool (true if write successful, false otherwise)
// =====================================
bool Account::onSignup(string user, string password) {
    try {
        ofstream outFile("LoggedIn.txt", ios::app);
        if (!outFile.is_open()) {
            throw runtime_error("Error opening LoggedIn.txt for writing.");
        }

        outFile << user << " " << checkingsBalance << " " << savingsBalance << endl;
        outFile.close();

        return true;
    }
    catch (exception& e) {
        cout << e.what() << endl;
        return false;
    }
    catch (...) {
        cout << "An unknown error occurred." << endl;
        return false;
    }
}

//============ onLogin =============
// Appends user balances to LoggedIn.txt on successful login
//
// input: string user, string password
// output: bool (true if write successful, false otherwise)
// =====================================
bool Account::onLogin(string user, string password) {
    try {
        ofstream outFile("LoggedIn.txt", ios::app);
        if (!outFile.is_open()) {
            throw runtime_error("Error opening LoggedIn.txt for writing.");
        }

        outFile << user << " " << checkingsBalance << " " << savingsBalance << endl;
        outFile.close();

        return true;
    }
    catch (exception& e) {
        cout << e.what() << endl;
        return false;
    }
    catch (...) {
        cout << "An unknown error occurred." << endl;
        return false;
    }
}

//============ login =============
// Validates user credentials and logs user in if valid
//
// input: string user, string password
// output: bool (true if login successful, false otherwise)
// =====================================
bool Account::login(string user, string password) {
    if (findUser(user, password)) {
        onLogin(user, password);
        return true;
    }
    else {
        cout << "Login failed." << endl;
        return false;
    }
}

//============ withdraw =============
// Placeholder function for base class withdrawal
//
// input: double amount, string user
// output: void
// =====================================
void Account::withdraw(double amount, string) {
    cout << "Pass" << endl;
}

//============ deposit =============
// Placeholder function for base class deposit
//
// input: double amount, string user
// output: void
// =====================================
void Account::deposit(double amount, string user) {
    cout << "Pass" << endl;
}

//============ display =============
// Placeholder function for displaying account info
//
// input: none
// output: void
// =====================================
void Account::display() {
    cout << "Pass" << endl;
}

//============ handleLoggedInMenu =============
// Displays post-login banking menu and handles user choices
//
// input: const string& username
// output: void
// =====================================
void Account::handleLoggedInMenu(const string& username) {
    Checkings* checkings = new Checkings();
    Savings* savings = new Savings();

    int menuChoice;
    double amount;

    do {
        showMenu();

        cout << "Enter choice";
        cin >> menuChoice;

        switch (menuChoice) {
        case 1:
            cout << "Enter amount to deposit into savings: ";
            cin >> amount;
            savings->deposit(amount, username);
            break;
        case 2:
            cout << "Enter amount to deposit into checkings: ";
            cin >> amount;
            checkings->deposit(amount, username);
            break;
        case 3:
            cout << "Enter amount to withdraw from savings: ";
            cin >> amount;
            savings->withdraw(amount, username);
            break;
        case 4:
            cout << "Enter amount to withdraw from checkings: ";
            cin >> amount;
            checkings->withdraw(amount, username);
            break;
        case 5:
            checkings->display();
            savings->display();
            break;
        case 6:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

    } while (menuChoice != 6);

    delete checkings;
    delete savings;
}

//============ showMenu =============
// Displays the in-session banking options menu
//
// input: none
// output: void
// =====================================
void Account::showMenu() const {
    cout << "\n***********BANK ACCOUNT MENU***********\n";
    cout << "1. Deposit to Savings Account\n";
    cout << "2. Deposit to Checkings Account\n";
    cout << "3. Withdraw from Savings Account\n";
    cout << "4. Withdraw from Checkings Account\n";
    cout << "5. Display Account Balances\n";
    cout << "6. Exit\n";
    cout << "\n********************************\n";
}

//============ loginAndSignup =============
// Displays the login and signup options menu
//
// input: none
// output: void
// =====================================
void Account::loginAndSignup() const {
    cout << "***********BANK ACCOUNT MENU***********\n";
    cout << "1. Login\n";
    cout << "2. Signup\n";
}

//============ loadUserData =============
// Loads all user data (username, checkings, savings) from LoggedIn.txt
//
// input: none
// output: vector<UserData> containing all users and balances
// =====================================
vector<UserData> Account::loadUserData() {
    vector<UserData> users;
    ifstream inFile("LoggedIn.txt");
    string username;
    double checkings, savings;

    while (inFile >> username >> checkings >> savings) {
        UserData data;
        data.username = username;
        data.checkings = checkings;
        data.savings = savings;
        users.push_back(data);
    }
    return users;
}

//============ saveUserData =============
// Writes all user data back to LoggedIn.txt
//
// input: vector<UserData> users
// output: void
// =====================================
void Account::saveUserData(const vector<UserData>& users) {
    ofstream outFile("LoggedIn.txt");
    for (int i = 0; i < users.size(); ++i) {
        outFile << users[i].username << " " << users[i].checkings << " " << users[i].savings << endl;
    }
}


