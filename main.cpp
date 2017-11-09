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

//
//  Bank Function Declarations
//

Bank::Bank() {
	currentCustomer = NULL;
	loadCustomers();
	
	//cout << customers[0]->getName() << endl;
}

void Bank::loadCustomers() {
	//Get file path
	//loop thru customer folder
	//push new customer objects to the vector
	
	
	//file path
	//for(int i = 0; file path.exist.next) {
	//    customers.push_back(new Customer(fileLine0, fileLine1, fileLine2));
	//}
}

void Bank::createCustomer(string name, long ufid, int pin) {
	//Create new file
	ofstream newFile;
	newFile.open(to_string(ufid) + ".txt");
	if(!newFile) {
		return;
	}
	newFile << name << "\n" << ufid << "\n" << pin << endl;
	newFile.close();
	
	//Add new customer to the vector
	customers.push_back(new Customer(name, ufid, pin));
	
	return;
}

void Bank::deleteCurrentCustomer() {
	//Get file path
	//Delete current custsomer file
	//Reload customers
}

bool Bank::signIn(long ufid, int pin) {
	for(int i = 0; i < customers.size(); i++) {
		if(customers[i]->getUfid() == ufid && customers[i]->getPin() == pin) {
			currentCustomer = customers[i];
			return true;
		}
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

Customer::Customer(string name, long ufid, int pin) {
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

long Customer::getUfid() {
	return ufid;
}

int Customer::getPin() {
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

void signIn(Bank * bank) {
	long ufid = 0;
	int pin = 0;
	
	cout << "UFID - ";
	cin >> ufid;
	
	cout << "Pin - ";
	cin >> pin;
	
	if(bank->signIn(ufid, pin)) {
		//call signined menu
	} else {
		cout << "Those credentials did not match any membership to our bank!\n";
	}
}

void createMembership(Bank * bank) {
	long ufid = 0;
	int pin = 0;
	
	cout << "UFID - ";
	cin >> ufid;
	
	cout << "Pin - ";
	cin >> pin;
	
	cout << "Test: " << pin << ufid;
}

int main() {
	Bank * ourBank = new Bank();
	
	ourBank->createCustomer("Test", 1231212, 1234);
	
	bool booling = true;
	int menuSelection = 0;
	//int choice = 0;
	
	cout << "Welcome to the Gator Bank!\n";
	
	while(booling) {
		cout << "Main Menu\n" << endl << "1. Sign In\n" << "2. Create Membership\n" << "3. Exit\n" << "Selection - ";
		cin >> menuSelection;
		
		while(!cin.fail()) {
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
