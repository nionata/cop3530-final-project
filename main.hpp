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
	string ufid;
	string pin;
public:
	Customer(string name, string ufid, string pin);
	void loadAccounts();
	void createAccount(int type);
	void deleteAccount(long accNum);
	void setName(string name);
	void setUfid(string ufid);
	void setPin(string pin);
	string getName();
	string getUfid();
	string getPin();
	Account* getAccount(long accNum);
};

class Bank {
private:
	Customer* currentCustomer;
public:
	Bank();
	void createCustomer(string name, string ufid, string pin);
	void deleteCurrentCustomer();
	bool signIn(string ufid, string pin);
	void signOut();
	Customer* getCurrentCustomer();
};



#endif /* main_hpp */
