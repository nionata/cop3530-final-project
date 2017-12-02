//
//  gatorBank.h
//  
//
//  Created by an AMAZING team:
//  Yingwen Huang
//  Olia Zayshlaya
//  Unmi Park
//  James Dika
//  Carlos Henriquez
//  Nick Ionata
//  Vitaliy Kurishko
//

#include <stdio.h>
#include <string>

using namespace std;

#ifndef gatorBank_h
#define gatorBank_h

class AccountNode
{
public:
	string accountNum;
	double balance;
	AccountNode* next;
	AccountNode();
};

class HistoryNode
{
public:
	string accountNum;
	double balance;
	string time;
	string action;
	HistoryNode* next;
	HistoryNode();
};

class AccountList
{
public:
	AccountNode* head;
	AccountList();
	int countAccount();
	bool ifExist(string tempNum);
	void appendAccount(string tempNum, double bal);
};

class History
{
public:
	HistoryNode* head;
	History();
	void pushHistory(string account, double bal, string t, string act);
	void appendHistory(string account, double bal, string t, string act);
};

class Customer
{
public:
	Customer();
	void newCustomer();
	void loadCustomer(string path);
	void setPin();
	void setAddress();
	void setEmail();
	void setPhone();
	void printInformation();
	void printCheckingAccount();
	void printSavingAccount();
	void printHistory();
	void addCheckingAccount(string tempNum, double tempBal);
	void addSavingAccount(string tempNum, double tempBal);
	void deleteCheckingAccount();
	void deleteSavingAccount();
	void outputTxt();
	void checkingDeposit();
	void savingDeposit();
	void checkingWithdraw();
	void transfer();
	void calculateInterest(string currentTime, string tempNum);
	bool ifAllAccountZero();
	bool isDigits(string str);
	string getName();
	string getUfid();
	string currentDateTime();
	int countLeapYears(int year, int month);
	long int timeDifference(string pastTime, string currentTime);
	
private:
	string ufid;
	string pin;
	string name;
	string address;
	string email;
	string phone;
	AccountList checking;
	AccountList saving;
	History history;
};

class Bank
{
public:
	Bank();
	void mainMenu();
	void signInMenu();
	void informationMenu();
	void generalAccountsMenu();
	void createMembershipMenu();
	void checkingAccountMenu();
	void savingAccountMenu();
	void trySignIn();
	void cancelMembership();
	bool ifSignIn(string ufid, string pin);
	
private:
	Customer* currentCustomer;
};

#endif /* gatorBank_h */
