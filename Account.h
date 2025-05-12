#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>	

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;

using std::runtime_error;
using std::exception;

using std::ifstream;
using std::ofstream;
using std::ios;
using std::istringstream;

using std::string;
using std::vector;

// forward declarations to use checkings and savings within Account class
class Checkings; 
class Savings;

// struct to hold user data
struct UserData {
	string username;
	double checkings;
	double savings;

	void printStruct() const {
		cout << "Username: " << username << endl;
		cout << "Checkings: " << checkings << endl;
		cout << "Savings: " << savings << endl;
	}

};

class Account {
protected:
	// data members
	double checkingsBalance = 0.0;
	double savingsBalance = 0.0;
	int withdrawLimit = 5;

	// vector to hold user data
	vector<UserData> loadUserData();
	
	// saves updated user data to file
	void saveUserData(const vector<UserData>&);
	

public:
	Account() : checkingsBalance(100.00), savingsBalance(100.00) {}

	// virtual functions to be overridden in derived classes
	virtual void deposit(double, string);
	virtual void withdraw(double, string);
	virtual void display();

	// functions to handle user login and signup
	bool findUser(string, string);
	bool userExists(string);

	// functions to handle login and signup
	bool login(string, string);
	bool onLogin(string, string);

	// functions to handle signup
	bool onSignup(string, string);
	bool signup(string, string);

	// functions to handle menu display
	void handleLoggedInMenu(const string&);
	void showMenu() const;
	void loginAndSignup() const;

	virtual ~Account() {}
};
#endif // ACCOUNT_H