//
//  main.cpp
//  
//
//  Created by Nicholas Ionata on 10/31/17.
//
//

#include "main.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <typeinfo>

//
//  Bank Function Declarations
//

Bank::Bank() {
	currentCustomer = NULL;
}

void Bank::createCustomer(string name, string ufid, string pin) {
	//Create new file
	string path = "./customers/" + ufid + ".txt";
	cout << path;
	ofstream newFile;
	newFile.open(path);
	
	if(!newFile) {
		return;
	}
	
	newFile << name << "\n" << ufid << "\n" << pin << endl;
	newFile.close();
	
	//Add new customer to the vector
	currentCustomer = new Customer(name, ufid, pin);
	
	return;
}

void Bank::deleteCurrentCustomer() {
	string path = "./customers/" + (currentCustomer->getUfid()) + ".txt";

	if(remove(path.c_str()) !=0 ) {
		//failed to deleted
	} else {
		//success
	}
	
	return;
}

bool Bank::signIn(string ufid, string pin) {
	string path = "./customers/" + ufid + ".txt";
	ifstream customerFile;
	customerFile.open(path);
	
	if(!customerFile) {
		return false;
	}
	
	string potPin = "";
	getline(customerFile, potPin);
	
	if(potPin == pin) {
		currentCustomer = new Customer("", ufid, pin);
		return true;
	} else {
		return false;
	}
	
	return false;
}

void Bank::signOut() {
	currentCustomer = NULL;
}

Customer* Bank::getCurrentCustomer() {
	return currentCustomer;
}

//
//  Customer Function Declarations
//

/* Todo - Debating whether these are needed or not
 void setName(string name);
 void setUfid(long ufid);
 void setPin(int pin);
 */

Customer::Customer(string name, string ufid, string pin) {
	this->name = name;
	this->ufid = ufid;
	this->pin = pin;
}

void Customer::loadAccounts() {
	//Get file path
	//Go into customer file
	//Loop thru file and add account objects to the vector
}

//Before calling this funciton we much check that the type val is either == 1 or == 2
void Customer::createAccount(int type) {
	//Get file path
	if(type == 1) {
		//Create a new savings
		//save to file
	} else {
		//Create a new checkings
		//svae to file
	}
	
	//Reload accounts
}

void deleteAccount(long accNum) {
	//Get file path
	//Delete the given file path
	//Reload the accounts
}

string Customer::getName() {
	return name;
}

string Customer::getUfid() {
	return ufid;
}

string Customer::getPin() {
	return pin;
}

Account* Customer::getAccount(long accNum) {
	return NULL;
}

//
//  Account Function Declarations
//

/* Todo
 Account(long accNum, double bal);
	virtual void deposit(double amount);
	virtual void transfer();
	virtual void printBalance();
 */

Account::Account(long accNum, double bal) {
	this->accNum = accNum;
	this->bal = bal;
}

void Account::deposit(double amount) {
	this->bal = bal + amount;
}

void Account::transfer() {
	
}

void Account::printBalance() {
	
}

double Account::getBal() {
	return bal;
}

void printSignedInMenu() {
	cout << "**************************"
	<< endl
	<< "Signed In Menu"
	<< endl
	<< "1. View Accounts"
	<< endl
	<< "2. Delete Membership"
	<< endl
	<< "3. Sign Out"
	<< endl
	<< "**************************"
	<< endl;
}

void signedInMenu(Bank * bank) {
	int menuSelection = 0;
	
	printSignedInMenu();
	
	cout << "Selection - ";
	cin >> menuSelection;
	
	while(cin.fail()) {
		cout << "Invalid input! Try a new menu option - ";
		cin >> menuSelection;
	}
	
	switch (menuSelection) {
		case 1:
			cout << "This is our accounts boooiiiiiii";
			break;
		case 2:
			bank->deleteCurrentCustomer();
			break;
		case 3:
			//booling = false;
			cout << endl << "Later Gator!" << endl;
			break;
		default:
			cout << "Invalid input! Try a new menu option";
			cin.clear();
			cin.ignore();
			break;
			
	}
	
	return;
}

void signIn(Bank * bank) {
	string ufid = "";
	string pin = "";
	
	cout << "Please enter your:"
		<< endl
		<< "UFID (8 digits w/out a dash) - ";
	cin >> ufid;
	
	cout << "Pin - ";
	cin >> pin;
	
	if(bank->signIn(ufid, pin)) {
		signedInMenu(bank);
	} else {
		cout << "Those credentials did not match or there isn't any membership to our bank!\n";
	}
}

void createMembership(Bank * bank) {
	string ufid = "";
	string pin = "";
	
	cout << "UFID (8 digits w/out a dash) - ";
	cin >> ufid;
	
	cout << "Pin - ";
	cin >> pin;
	
	cout << "Test: " << pin << ufid;
}

void printMainMenu() {
	cout << "**************************"
		<< endl
		<< "Main Menu"
		<< endl
		<< "1. Sign In"
		<< endl
		<< "2. Create Membership"
		<< endl
		<< "3. Exit"
		<< endl
		<< "**************************"
		<< endl;
}

int main() {
	Bank * ourBank = new Bank();
	
	//ourBank->createCustomer("Test", 1231212, 1234);
	
	bool booling = true;
	int menuSelection = 0;
	//int choice = 0;
	
	cout << "Welcome to the Gator Bank!" << endl << endl;
	
	while(booling) {
		printMainMenu();
		
		cout << "Selection - ";
		cin >> menuSelection;
		
		while(cin.fail()) {
			cout << "Invalid input! Try a new menu option - ";
			cin >> menuSelection;
		}
		
		switch (menuSelection) {
			case 1:
				signIn(ourBank);
				break;
			case 2:
				createMembership(ourBank);
				break;
			case 3:
				booling = false;
				cout << endl << "Later Gator!" << endl;
				break;
			default:
				cout << "Invalid input! Try a new menu option";
				cin.clear();
				cin.ignore();
				break;
				
		}
		
		/*switch (menuSelection) {
			case 0:
				cout << "Main Menu\n" << endl << "1. Sign In\n" << "2. Create Membership\n" << "3. Exit\n" << "Selection - ";
				cin >> choice;
				
				switch ()
				
				if(choice == 1) {
					//sign in function
					menuSelection = 1;
				} else if
				
				break;
			case 1:
				
				break;
			case 2:
				break;
			case 3:
				break;
			default:
				booling = false;
				break;
		}*/
		/*if(0) {
			
		} else if(1) {
			
		} else if (2) {
			
		}*/
	}
	
	return 0;
}
