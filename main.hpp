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

class Account {
private:
	long accNum;
	double bal;
public:
	Account(long accNum, double bal);
	virtual void deposit(double amount);
	virtual void transfer();
	virtual void printBalance();
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
	vector<Account> accounts;
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
	Account getAccount(long accNum);
};

class Bank {
private:
	vector<Customer *> customers;
	Customer * currentCustomer;
public:
	Bank();
	void loadCustomers();
	void createCustomer(string name, long ufid, int pin);
	void deleteCutomer();
	bool signIn(long ufid, int pin);
	void signOut();
	Customer getCurrentCustomer();
};

void Bank::loadCustomers() {
	//file path
	//for(int i = 0; file path.exist.next) {
	//    customers.push_back(new Customer(fileLine0, fileLine1, fileLine2));
	//}
}

Customer::Customer(string name, long ufid, int pin) {
	this->name = name;
	this->ufid = ufid;
	this->pin = pin;
}

string Customer::getName() {
	return name;
}

Bank::Bank() {
	currentCustomer = NULL;
	loadCustomers();
	
	cout << customers[0]->getName() << endl;
	
	//loadCustomers();
}


#endif /* main_hpp */
