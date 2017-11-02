//
//  main.hpp
//  
//
//  Created by Nicholas Ionata on 10/31/17.
//
//

#ifndef main_hpp
#define main_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

//
//	Object definitions
//

class Account {
private:
	long accNum;
	double bal;
public:
	Account(long accNum, double bal);
	virtual void deposit(double amount);
	virtual void transfer();
	virtual void printBalance();
	virtual double getBal();
};

class SavingsAccount: public Account {
	
};

class CheckingAccount: public Account {
public:
	void withdraw(double value);
	void printTransaction();
};

class Customer {
private:
	vector<Account *> accounts;
	string name;
	long ufid;
	int pin;
public:
	Customer(string name, long ufid, int pin);
	void loadAccounts();
	void createAccount(int type);
	void deleteAccount(long accNum);
	void setName(string name);
	void setUfid(long ufid);
	void setPin(int pin);
	string getName();
	long getUfid();
	int getPin();
	Account* getAccount(long accNum);
};

class Bank {
private:
	vector<Customer *> customers;
	Customer* currentCustomer;
public:
	Bank();
	void loadCustomers();
	void createCustomer(string name, long ufid, int pin);
	void deleteCurrentCustomer();
	bool signIn(long ufid, int pin);
	void signOut();
	Customer* getCurrentCustomer();
};

//
//  Bank Function Declarations
//

Bank::Bank() {
	currentCustomer = NULL;
	loadCustomers();
	
	cout << customers[0]->getName() << endl;
	
	//loadCustomers();
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
	//Get file path
	//create a new file with the give values
	//Reload customers
}

void Bank::deleteCurrentCustomer() {
	//Get file path
	//Delete current custsomer file
	//Reload customers
}

bool Bank::signIn(long ufid, int pin) {
	for(int i = 0; i < customers.size(); i++) {
		if(customers[i]->getUfid() == ufid and customers[i]->getPin() == pin) {
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


#endif /* main_hpp */
