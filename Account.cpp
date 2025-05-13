
#include "Account.h"
#include "Savings.h"
#include "Checkings.h"

//============ findAccount =============
// Checks if the provided username, passowrd and ID an entry in Users.txt
//
// input: string user, string password
// output: bool (true if match found, false otherwise)
// =====================================
bool Account::findAccount(string user, string password, unsigned int id) {
    try {
		// Open the file in read mode
        ifstream inFile("Users.txt");

		// Check if the file opened successfully
        if (!inFile.is_open()) {
            throw runtime_error("Error opening file.");
        }

        string fileUser;
        string filePass;
        unsigned int fileId;

		// Read the file
        // skip the whitespace and read one token at a time
        while (inFile >> fileUser >> filePass >> fileId) {
            // check if username, password and id match
			if (fileUser == user && filePass == password && fileId == id) {
				// If a match is found, print a message and return true
				cout << "Login successful for user: " << fileUser << endl;
				inFile.close();
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

//============ isDuplicateUser =============
// Checks if a given username already exists in Users.txt
//
// input: string user
// output: bool (true if user exists, false otherwise)
// =====================================
bool Account::isDuplicateUser(string user) {
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
        if (isDuplicateUser(user)) {
            cout << "Username already taken." << endl;
            return false;
        }
		else { // username is available

            // new id 
			unsigned int newId = generateUserId();

			// Open the file in append mode
            ofstream outFile("Users.txt", ios::app);
            
			// Check if the file opened successfully
            if (!outFile.is_open()) {
                throw runtime_error("Error opening Users.txt for writing.");
            }

			// write the new user and password to the file
            outFile << user << " " << password << " " << newId << endl;
            outFile.close();

			// call onSignup to initialize the user's savings and checkings
            onSignup(user, password, newId);

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
// Initializes a new user's savings, checkings and id.
// Id will be incre
//
// input: string user, string password
// output: bool (true if write successful, false otherwise)
// =====================================
bool Account::onSignup(string user, string password, unsigned int id) {
    try {
		// Open the file in append mode
        ofstream outFile("LoggedIn.txt", ios::app);

		// Check if the file opened successfully
        if (!outFile.is_open()) {
            throw runtime_error("Error opening LoggedIn.txt for writing.");
        }

		// write the new user and initial balances to the file
        outFile << user << " " << id << "  " << checkingsBalance << " " << savingsBalance << " " << endl;
        
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

		// get the user id
        unsigned int id = getUserId(user);

		// Open the file in read mode
        ifstream inFile("LoggedIn.txt");
        
		// Check if the file opened successfully
        if (!inFile.is_open()) {
            throw runtime_error("Error opening LoggedIn.txt for reading.");
        }

		// variables to hold the data read from the file
        string username;
        unsigned int fileId;
        double checkings, savings;

        // Check if this ID already exists in the file
        while (inFile >> username >> fileId >> checkings >> savings) {
            if (fileId == id) {
                cout << "User already logged in (file).\n";
                inFile.close();
                return true;
            }
        }
        inFile.close();

        // If not found, append the user
        ofstream outFile("LoggedIn.txt", ios::app);
        if (!outFile.is_open()) {
            throw runtime_error("Error opening LoggedIn.txt for writing.");
        }

        outFile << user << " " << id << " " << checkingsBalance << " " << savingsBalance << endl;
        outFile.close();

        return true;
    }
    catch (exception& e) {
        cout << e.what() << endl;
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

	// grab the user id to be passed into findAccount
    unsigned int id = getUserId(user);

	// check if the user exists in Users.txt
    if (findAccount(user, password, id)) {

        // Check in-memory active session
        for (int i = 0; i < activeSessions.size(); ++i) {
            if (activeSessions[i].id == id) {
                cout << "User already logged in (in memory).\n";
                return true;
            }
        }

        // If not logged in, log and write to file
        onLogin(user, password);

        // Add UserData to vector
        UserData session;

        session.username = user;
        session.id = id;
        session.checkings = checkingsBalance;
        session.savings = savingsBalance;
        activeSessions.push_back(session);

        return true;
    }

    cout << "Login failed.\n";
    return false;
}


//============ loadUserData =============
// Loads all user data (username, checkings, savings) from LoggedIn.txt
//
// input: none
// output: vector<UserData> containing all users and balances
// =====================================
vector<UserData> Account::loadUserData() {
	// vector to hold user data
    vector<UserData> users;

	// open the file in read mode
    ifstream inFile("LoggedIn.txt");

	// Check if the file opened successfully
    string username;
    unsigned int id;
    double checkings, savings;

	// read the file line by line extracting each token
    while (inFile >> username >> id >> checkings >> savings) {
		// create struct to be pushed into the vector
        UserData data;

		// assign the values to the struct
        data.username = username;
        data.id = id;
        data.checkings = checkings;
        data.savings = savings;

		// push the struct into the vector
        users.push_back(data);
    }

	// check if the file opened successfully
    inFile.close();

    return users;
}




//============ saveUserData =============
// Writes all user data back to LoggedIn.txt
//
// input: vector<UserData> users
// output: void
// =====================================
void Account::saveUserData(const vector<UserData>& users) {

	// open the file in write mode
    ofstream outFile("LoggedIn.txt");

	// assign user data to the file
    for (int i = 0; i < users.size(); ++i) {
        outFile << users[i].username  << " "
                << users[i].id        << " "
                << users[i].checkings << " "
                << users[i].savings   << endl;
                
    }

}

//============ withdraw =============
// Placeholder function for base class withdrawal
//
// input: double amount, string user
// output: void
// =====================================
void Account::withdraw(double amount, string) {
    // Placeholder since i had issues with pure virtual functions and i forgot to fix them ...
    cout << "Pass" << endl;
}

//============ deposit =============
// Placeholder function for base class deposit
//
// input: double amount, string user
// output: void
// =====================================
void Account::deposit(double amount, string user) {
    // Placeholder since i had issues with pure virtual functions and i forgot to fix them ...
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
    // create instances of Checkings and Savings
    Checkings* checkings = new Checkings();
    Savings* savings = new Savings();

    // load user data
    int menuChoice;
    double amount;

    do {
        // display the menu
        showMenu();

        //  prompt user for choice
        cout << "Enter choice: ";
        cin >> menuChoice;

        // check if the choice is valid
        switch (menuChoice) {
        case 1: // Deposit to Savings
            cout << "Enter amount to deposit into savings: ";
            cin >> amount;
            savings->deposit(amount, username);
            break;
        case 2: // Deposit to Checkings
            cout << "Enter amount to deposit into checkings: ";
            cin >> amount;
            checkings->deposit(amount, username);
            break;
        case 3: // Withdraw from Savings
            cout << "Enter amount to withdraw from savings: ";
            cin >> amount;
            savings->withdraw(amount, username);
            break;
        case 4: // Withdraw from Checkings
            cout << "Enter amount to withdraw from checkings: ";
            cin >> amount;
            checkings->withdraw(amount, username);
            break;
        case 5: // Display Account Balances
            checkings->display();
            savings->display();
            break;
        case 6: // Exit
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

    } while (menuChoice != 6);

    // clean up
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

// ============ generateUserId =============
// Generates a unique user ID by incrementing the last ID in the file
//
// input: none
//
// output: unsigned int (new user ID)
// ====================================

unsigned int Account::generateUserId() {
    try {
        // id to be created and returned
        unsigned int id = 0;
        
        // keep track of the id
        ifstream inFile("id_counter.txt");

		// Check if the file opened successfully
        if (!inFile.is_open()) {
			throw runtime_error("Error opening id_counter.txt");
        }
        else {
            inFile >> id;
            inFile.close();
        }

        // 
        ++id;

		// open the file in write mode to write the new id
		ofstream outFile("id_counter.txt", ios::trunc);

		// Check if the file opened successfully
        if (!outFile.is_open()) {
            throw runtime_error("Error opening id_counter.txt");
        }

		// write the new id to the file
        outFile << id;

		outFile.close();

        return id;  
    } catch (exception& e) {
        cout << e.what() << endl;
	    return 0;
    }
    catch (...) {
		cout << "Unknown error occurred while generating user ID." << endl;
		return 0;
    }
}

// =========== isLoggedIn =============
// Checks if a user is already logged in by checking LoggedIn.txt
//
// input: unsigned int idToCheck
//
// output: bool (true if logged in, false otherwise)
// ====================================
bool Account::isLoggedIn(unsigned int idToCheck) {
    try {
		
		return false;
    }
    catch (exception& e) {
        cout << e.what() << endl;
        return false;
    }
    catch (...) {
		cout << "Unkwown error occurred." << endl;
        return false;
    }
}

// ============ getUserId =============
// Retrieves the user ID for a given username from Users.txt
//
// input: const string& user
//
//  output: unsigned int (user ID)
// ====================================
unsigned int Account::getUserId(const string& user) {
    ifstream inFile("Users.txt");
    string username;
	string password;
    unsigned int id;

    while (inFile >> username >> password >> id) {
        if (username == user) {
            return id;
        }
    }

    return 0; // return 0 for not found or invalid ID
}

// ============ printLoggedInUsers =============
// Displays all logged in users from LoggedIn.txt by passing in our active sessions vector
//
// input: vector<UserData>& vec
//
// output: void
// ====================================
void Account::printLoggedInUsers(const vector<UserData>& vec){
    cout << "Logged in Users " << endl;
   
    vector<UserData>::iterator it;
    for (it = activeSessions.begin(); it != activeSessions.end(); ++it) {
        cout << "Username: " << it->username << ", ID: " << it->id << endl;
    }
}

