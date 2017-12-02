#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <dirent.h>
#include <time.h>
#include <iomanip>
#include <sstream>
using namespace std;

class AccountNode
{
public:
  string accountNum;
  double balance;
  AccountNode* next;
  AccountNode();
};

//Implement constructor for AccountNode class
AccountNode::AccountNode()
{
  accountNum = "NA";
  balance = 0;
  next = NULL;
}

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

//Implement constructor for HistoryNode class
HistoryNode::HistoryNode()
{
  accountNum = "NA";
  balance = 0;
  time = "NA";
  action = "NA";
  next = NULL;
}

class AccountList
{
public:
  AccountNode* head;
  AccountList();
  int countAccount();
  bool ifExist(string tempNum);
  void appendAccount(string tempNum, double bal);
};

//Implement constructor for AccountList class
AccountList::AccountList()
{
  head = NULL;
}

//Implement countAccount function to total up number of accounts
int AccountList::countAccount()
{
  if(!head)
    return 0;
  else
  {
    AccountNode* temp = head;
    int i = 0;
    while(temp)
    {
      i++;
      temp = temp->next;
    }
    return i;
  }
}

//Implement ifExist function to check if a certain account exists; returns a boolean
bool AccountList::ifExist(string tempNum)
{
  if(!head)
    return false;
  else
  {
    AccountNode* temp = head;
    while(temp)
    {
      if(temp->accountNum == tempNum)
	return true;

      temp = temp->next;
    }

    return false;
  }
}

//Implement appendAccount function
void AccountList::appendAccount(string tempNum, double bal)
{
  if(!head)
  {
    AccountNode* temp = new AccountNode();
    temp->accountNum = tempNum;
    temp->balance = bal;
    head = temp;
  } 
  else
  {
    AccountNode* current = head;
    while(current->next)
      current = current->next;

    AccountNode* temp = new AccountNode();
    temp->accountNum = tempNum;
    temp->balance = bal;
    current->next = temp;
  }
}

class History
{
public:
  HistoryNode* head;
  History();
  void pushHistory(string account, double bal, string t, string act);
  void appendHistory(string account, double bal, string t, string act);
};

//Implement constructor for History class
History::History()
{
  head = NULL;
}

//Implement pushHistory function to make current info history
void History::pushHistory(string account, double bal, string t, string act)
{
  HistoryNode* temp = new HistoryNode();
  temp->accountNum = account;
  temp->balance = bal;
  temp->time = t;
  temp->action = act;
  temp->next = head;
  head = temp;
}

//Implement appendHistory function to add a transaction to history
void History::appendHistory(string account, double bal, string t, string act)
{
  if(!head)
    pushHistory(account, bal, t, act);
  else
  {
    HistoryNode* current = head;
    while(current->next)
      current = current->next;

    HistoryNode* temp = new HistoryNode();
    temp->accountNum = account;
    temp->balance = bal;
    temp->time = t;
    temp->action = act;
    current->next = temp;
  }
}

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

//Implement constructor for Customer class
Customer::Customer()
{
  ufid = "";
  pin = "NA";
  name = "NA";
  address = "NA";
  email = "NA";
  phone = "NA";
}

//Implement getUfid function for Customer
string Customer::getUfid()
{
  return ufid;
}

//Implement calculateInterest function for Customer to account for interest
void Customer::calculateInterest(string currentTime, string tempNum)
{
  HistoryNode* tempHistory = history.head;
  while(tempHistory)
  {
    if(tempHistory->accountNum == tempNum)
      break;
    tempHistory = tempHistory->next;
  }

  AccountNode* tempAccount = saving.head;
  while(tempAccount)
  {
    if(tempAccount->accountNum == tempNum)
      break;
    tempAccount = tempAccount->next;
  }

  int days = timeDifference(tempHistory->time, currentTime);
  double base = tempAccount->balance;
  double interest = 0;
  while(days > 0)
  {
    double tempInterest = 0;
    if(days < 365)
      tempInterest = base * 0.05 / 365 * days;
    else
      tempInterest = base * 0.05;

    base += tempInterest;
    interest = tempInterest;
    days = days - 365;  
  }

  tempAccount->balance = base;
  stringstream stream;
  stream << fixed << setprecision(2) << interest;
  string action = stream.str();
  action = "Interest $" + action + " is added.";
  history.pushHistory(tempAccount->accountNum, tempAccount->balance, currentTime, action);
}

//Implement countLeapYears function to account for leap years in interest
int Customer::countLeapYears(int year, int month)
{
  if(month <= 2)
    year--;

  return year / 4 - year / 100 + year / 400;
}

//Implement timeDifference function 
long int Customer::timeDifference(string pastTime, string currentTime)
{
  int pastYear = (pastTime[0] - '0') * 1000 + (pastTime[1] - '0') * 100 + (pastTime[2] - '0') * 10 + (pastTime[3] - '0');
  int currentYear = (currentTime[0] - '0') * 1000 + (currentTime[1] - '0') * 100 + (currentTime[2] - '0') * 10 +(currentTime[3] - '0');
  
  int pastMonth = (pastTime[5] - '0') * 10 + (pastTime[6] - '0');
  int currentMonth = (currentTime[5] - '0') * 10 + (currentTime[6] - '0');

  int pastDay = (pastTime[8] - '0') * 10 + (pastTime[9] - '0');
  int currentDay = (currentTime[8] - '0') * 10 + (currentTime[9] - '0');

  int pastHour = (pastTime[11] - '0') * 10 + (pastTime[12] - '0');
  int currentHour = (currentTime[11] - '0') * 10 + (currentTime[12] - '0');

  int pastMinute = (pastTime[14] - '0') * 10 + (pastTime[15] - '0');
  int currentMinute = (currentTime[14] - '0') * 10 + (currentTime[15] - '0');

  int pastSecond = (pastTime[17] - '0') * 10 + (pastTime[18] - '0');
  int currentSecond = (currentTime[17] - '0') * 10 + (currentTime[18] - '0');


  const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  long int daysOfPast = pastYear * 365 + pastDay;
  for(int i = 0; i < pastMonth - 1; i++)
    daysOfPast += monthDays[i];
  daysOfPast += countLeapYears(pastYear, pastMonth);

  long int daysOfCurrent = currentYear * 365 + currentDay;
  for(int i = 0; i < currentMonth - 1; i++)
    daysOfCurrent += monthDays[i];
  daysOfCurrent += countLeapYears(currentYear, currentMonth);

  long int daysDifference = daysOfCurrent - daysOfPast;
  long int hoursDifference = daysDifference * 24 + (currentHour - pastHour);
  long int minutesDifference = hoursDifference * 60 + (currentMinute - pastMinute);
  long int secondsDifference = minutesDifference * 60 + (currentSecond - pastSecond);

  return (secondsDifference - 60);
}

//Implement ifAllAccountZero function to check balance of all accounts
bool Customer::ifAllAccountZero()
{
  AccountNode* temp = checking.head;
  while(temp)
  {
    if(temp->balance != 0)
      return false;
    
    temp = temp->next;
  }

  temp = saving.head;
  while(temp)
  {
    if(temp->balance != 0)
      return false;
    
    temp = temp->next;
  }

  return true;
}

//Implement deleteCheckingAccount function to delete a customer checking account
void Customer::deleteCheckingAccount()
{
  if(!checking.head)
    cout << endl << "There are no checking accounts to delete!" << endl;
  else if(checking.countAccount() + saving.countAccount() == 1)
    cout << endl << "This action cannot be completed!" << endl
	 << "This is your only account. You must cancel your membership in order to cancel your last account." << endl;
  else
  {
    cout << "Please enter the account# to be cancelled: ";
    string tempNum;
    cin >> tempNum;

    if(!checking.ifExist(tempNum))
    {
      cout << "No such account exists or invalid input!" << endl
	   << "Return to the previous menu" << endl;
      return;
    }
    else
    {
      if(checking.head->accountNum == tempNum)
      {
	if(checking.head->balance != 0)
	{
	  cout << "The current account cannot be deleted: the balance is not 0!" << endl
	       << "Return to the previous menu" << endl;
	}
	else
        {
	  AccountNode* temp = checking.head;
	  checking.head = checking.head->next;
	  string action = "Account is deleted";
	  history.pushHistory(tempNum, 0, currentDateTime(), action);
	  delete temp;
	  cout << "Account# " << tempNum << " is deleted successfully!" << endl;
	}	
      }
      else
      {
	AccountNode* current = checking.head;
	while(current->next)
        {
	  if(current->next->accountNum == tempNum)
	  {
	    if(current->next->balance != 0)
	      cout << "The current account cannot be deleted: the balance is not 0!" << endl;
	    else
	    {
	      AccountNode* temp = current->next;
	      current->next = current->next->next;
	      string action = "Account is deleted";
	      history.pushHistory(tempNum, 0, currentDateTime(), action);
	      delete temp;
	      cout << "Account# " << tempNum << " is deleted successfully!" << endl;
	      return;
	    }
	  }
	  current = current->next;
	}
      }
    }
  }
}

//Implement deleteSavingAccount function to delete a customer saving account
void Customer::deleteSavingAccount()
{
  if(!saving.head)
    cout << endl << "Nothing to delete!" << endl;
  else if(checking.countAccount() + saving.countAccount() == 1)
    cout << endl << "This action cannot be completed!" << endl
	 << "This is your only account. You must cancel your membership in order to cancel your last account." << endl;
  else
  {
    cout << "Please enter the account# to be cancelled: ";
    string tempNum;
    cin >> tempNum;

    if(!saving.ifExist(tempNum))
    {
      cout << "No such account exists or invalid input!" << endl
	   << "Return to the previous menu" << endl;
      return;
    }
    else
    {
      if(saving.head->accountNum == tempNum)
      {
	if(saving.head->balance != 0)
	{
	  cout << "The current account cannot be deleted: the balance is not 0!" << endl
	       << "Return to the previous menu" << endl;
	}
	else
        {
	  AccountNode* temp = saving.head;
	  saving.head = saving.head->next;
	  string action = "Account is deleted";
	  history.pushHistory(tempNum, 0, currentDateTime(), action);
	  delete temp;
	  cout << "Account# " << tempNum << " is deleted successfully!" << endl;
	}	
      }
      else
      {
	AccountNode* current = saving.head;
	while(current->next)
        {
	  if(current->next->accountNum == tempNum)
	  {
	    if(current->next->balance != 0)
	      cout << "The current account cannot be deleted since the balance is not 0!" << endl;
	    else
	    {
	      AccountNode* temp = current->next;
	      current->next = current->next->next;
	      string action = "Account is deleted";
	      history.pushHistory(tempNum, 0, currentDateTime(), action);
	      delete temp;
	      cout << "Account# " << tempNum << " is deleted successfully!" << endl;
	      return;
	    }
	  }
	  current = current->next;
	}
      }
    }
  }
}

//Implement addCheckingAccount function to add a new customer checking account
void Customer::addCheckingAccount(string tempNum, double tempBal)
{
  if(checking.countAccount() > 9)
  {
    cout << endl << "Action cannot be completed! You have reached the maximum number of checking accounts."
	 << endl << "Return to Previous Menu" << endl;
    return;
  }
    
  AccountNode* temp = new AccountNode();
  temp->accountNum = tempNum;
  temp->balance = tempBal;
  if(!checking.head || checking.head->accountNum[9] != temp->accountNum[9])
  {
    temp->next = checking.head;
    checking.head = temp;
    string action = "Account is created!";
    history.pushHistory(temp->accountNum, tempBal, currentDateTime(), action);
  }
  else
  {
    temp->accountNum[9]++;
    AccountNode* current = checking.head;
    while(current->next)
    {
      if(current->next->accountNum[9] != temp->accountNum[9])
      {
	temp->next = current->next;
	current->next = temp;
	string action = "Account is created!";
	history.pushHistory(temp->accountNum, tempBal, currentDateTime(), action);
	return;
      }
      temp->accountNum[9]++;
      current = current->next;
    }

    current->next = temp;
    string action = "Account is created!";
    history.pushHistory(temp->accountNum, tempBal, currentDateTime(), action);
  }
}

//Implement addSavingAccount function to add a new customer savings account
void Customer::addSavingAccount(string tempNum, double tempBal)
{
  if(saving.countAccount() > 9)
  {
    cout << endl << "Action cannot be completed! You have reached the maximum number of savings accounts."
	 << endl << "Return to Previous Menu" << endl;
    return;
  }
    
  AccountNode* temp = new AccountNode();
  temp->accountNum = tempNum;
  temp->balance = tempBal;
  if(!saving.head || saving.head->accountNum[9] != temp->accountNum[9])
  {
    temp->next = saving.head;
    saving.head = temp;
    string action = "Account is created!";
    history.pushHistory(temp->accountNum, tempBal, currentDateTime(), action);
  }
  else
  {
    temp->accountNum[9]++;
    AccountNode* current = saving.head;
    while(current->next)
    {
      if(current->next->accountNum[9] != temp->accountNum[9])
      {
	temp->next = current->next;
	current->next = temp;
	string action = "Account is created!";
	history.pushHistory(temp->accountNum, tempBal, currentDateTime(), action);
	return;
      }
      temp->accountNum[9]++;
      current = current->next;
    }

    current->next = temp;
    string action = "Account is created!";
    history.pushHistory(temp->accountNum, tempBal, currentDateTime(), action);
  }
}

//Implement newCustomer function to create a new customer and credentials in the bank
void Customer::newCustomer()
{
  bool control = true;
  while(control)
  {
    cout << endl;
    cout << "Please enter your UFID (8 digits): ";
    string ufid1;
    cin >> ufid1;
    cout << "Please confirm your UFID: ";
    string ufid2;
    cin >> ufid2;
    if(ufid1 != ufid2)
      cout << "The UFID you confirmed does not match!" << endl;
    else
    {
      ufid = ufid1;
      string path = "./customers/" + ufid + ".txt";
      ifstream customerFile;
      customerFile.open(path);
      if(customerFile)
      {
	cout << "This ID is already taken! Please enter another UFID!" << endl;
	customerFile.close();
	continue;
      }
      else if(!isDigits(ufid) || ufid.length() != 8)
	cout << "Please enter a valid UFID!" << endl;
      else
	control = false;
    }
  }
  
  setPin();

  control = true;
  while(control)
  {
    cout << endl;
     cin.ignore();
      cin.clear();
    cout << "Please enter your full name and press enter: ";
    string name1;
     getline(cin,name1,'\n');
  
      name = name1;
      control = false;
 cin.clear();
  }

  setAddress();
  setEmail();
  setPhone();

  AccountNode* temp = new AccountNode();
  temp->accountNum = "0" + ufid + "0";
  checking.head = temp;

  string action = "Account is created!"; 
  history.pushHistory(temp->accountNum, 0, currentDateTime(), action);
}

//Implement loadCustomer function to load up a signed in customer’s file
void Customer::loadCustomer(string path)
{
  fstream customerFile;
  customerFile.open(path);
  string line;
  getline(customerFile,line);
  pin = line;
  getline(customerFile,line);
  ufid = line;
  getline(customerFile,line);
  name = line;
  getline(customerFile,line);
  address = line;
  getline(customerFile,line);
  email = line;
  getline(customerFile,line);
  phone = line;
  
  getline(customerFile,line);
  getline(customerFile,line);
  while(line != "History: ")
  {
    string accountNum = line;
    getline(customerFile,line);
    double balance = stod(line);
    if(accountNum[0] == '0')
      checking.appendAccount(accountNum, balance);
    else if(accountNum[0] == '1')
      saving.appendAccount(accountNum, balance);

    getline(customerFile, line);
  }

  while(getline(customerFile, line))
  {
    string accountNum = line;
    getline(customerFile,line);
    double balance = stod(line);
    getline(customerFile,line);
    string time = line;
    getline(customerFile,line);
    string action = line;
    history.appendHistory(accountNum, balance, time, action);
  }

  customerFile.close();
  customerFile.clear();
}

//Implement setPin function that allows a customer to create a pin number
void Customer::setPin()
{
  bool control = true;
  while(control)
  {
    cout << endl;
    cout << "Please enter your pin(4 to 8 digits): ";
    string pin1;
    cin >> pin1;
    cout << "Please confirm your pin: ";
    string pin2;
    cin >> pin2;
    if(pin1 != pin2)
      cout << "The pin you confirmed does not match!" << endl;
    else
    {
      pin = pin1;
      if(!isDigits(pin))
	cout << "Please enter digits only!" << endl;
      else if(pin.length() < 4)
	cout << "The pin you entered is too short!" << endl;
      else if(pin.length() > 8)
	cout << "The pin you entered is too long!" << endl;
      else
	control = false;
    }
  }    
}

//Implement setAddress function that allows customers to save their address to the bank 
void Customer::setAddress()
{

  bool control = true;
  while(control)
  {
    cout << endl;
    string address1;
    cout << "Please enter your address: "<< endl;
  
    getline(cin,address1,'\n');
    //cout<< address1<<endl;
      address = address1;
      control = false;
  }
  //cin.clear();
}

//Implement setEmail function that allows customers to save their e-mail address to the bank 
void Customer::setEmail()
{
  bool control = true;
  while(control)
  {
    cout << endl;
    cout << "Please enter your UF email (case sensitive): ";
    string email1;
    cin >> email1;
      cin.ignore();
    cin.clear();
    cout << "Please confirm your UF email: ";
    string email2;
    cin >> email2;
    
    if((email1) != (email2))
      cout << "The email you confirmed does not match!" << endl;
    else
    {
      email = email1;
      if(email.length() < 8)
	cout << "The email you entered is not a valid UF email!" << endl;
      else if(email.substr(email.length()-8) != "@ufl.edu")
	cout << "The email you entered is not a valid UF email!" << endl;
      else
	control = false;
 
    }
  }
}

//Implement setPhone function that allows customers to save their phone number to the bank 
void Customer::setPhone()
{
  bool control = true;
  while(control)
  {
    cout << endl;
    cout << "Please enter your phone number(format: XXX-XXX-XXXX): ";
    string phone1;
    cin >> phone1;
    cout << "Please confirm your phone number: ";
    string phone2;
    cin >> phone2;
    if(phone1 != phone2)
      cout << "The phone number you confirmed does not match!" << endl;
    else
    {
      phone = phone1;
      if(phone.length() != 12)
	cout << "Invalid input!" << endl;
      else
      {
	string str1 = phone.substr(0,3);
	string str2 = phone.substr(4,3);
	string str3 = phone.substr(8,4);
	if(!isDigits(str1) || !isDigits(str2) || !isDigits(str3) || phone[3] != '-' || phone[7] != '-')
	  cout << "Please enter only digits in the form of: XXX-XXX-XXXX" << endl;
	else
	  control = false;
      }	  
    }
  
  }
}

/*Implement printInformation function that outputs all the customer’s information saved in the bank */
void Customer::printInformation()
{
  cout << endl;
  cout << "Name:      " << name << endl;
  cout << "Address:   " << address << endl;
  cout << "Email:     " << email << endl;
  cout << "Phone:     " << phone << endl;
}
//Implement printCheckingAccount function that outputs checking account number and balance
void Customer::printCheckingAccount()
{
  if(!checking.head)
    cout << "No existing checking accounts!" << endl;
  else
  {
    AccountNode* temp = checking.head;
    while(temp)
    {
      cout << "Account#:  " << temp->accountNum << endl;
      cout << "Balance:   " << setprecision(2) << fixed << temp->balance << endl;
      temp = temp->next;
    }
  } 
}

//Implement printSavingAccount function that outputs saving account number and balance
void Customer::printSavingAccount()
{
  if(!saving.head)
    cout << "No existing saving accounts!" << endl;
  else
  {
    AccountNode* temp = saving.head;
    while(temp)
    {
      cout << "Account#:  " << temp->accountNum << endl;
      cout << "Balance:   " << setprecision(2) << fixed << temp->balance << endl;
      temp = temp->next;
    }
  } 
}

//Implement printHistory function that outputs transaction history of a customer’s account
void Customer::printHistory()
{
  if(!history.head)
    return;

  HistoryNode* temp = history.head;
  int i = 1;
  while(temp)
  {
    cout << endl << i << ". " << endl
	 << "Account#:  " << temp->accountNum << endl
	 << "Balance:   " << setprecision(2) << fixed << temp->balance << endl
	 << "Time:      " << temp->time << endl
	 << "Action:    " << temp->action << endl;
    temp = temp->next;
    i++;
  }
}

//Implement outputTxt function writes customer information into a new file
void Customer::outputTxt()
{
  string path = "./customers/" + ufid + ".txt";
  ofstream newFile;
  newFile.open(path);
 
  if(!newFile)
    return;

  newFile << pin << endl<< ufid << endl<< name << endl << address << endl
  << email << endl << phone << endl;
  
  newFile << "Account: " << endl;
  if(checking.head)
  {
    AccountNode* temp = checking.head;
    while(temp)
    {
      newFile << temp->accountNum << endl;
      newFile << temp->balance << endl;
      temp = temp->next;
    }
  }
  
  if(saving.head)
  {
    AccountNode* temp = saving.head;
    while(temp)
    {
      newFile << temp->accountNum << endl;
      newFile << temp->balance << endl;
      temp = temp->next;
    }
  }

  newFile << "History: " << endl;
  if(history.head)
  {
    HistoryNode* temp = history.head;
    while(temp)
    {
      newFile << temp->accountNum << endl;
      newFile << temp->balance << endl;
      newFile << temp->time << endl;
      newFile << temp->action << endl;
      temp = temp->next;
    }
  }

  newFile.close();
  newFile.clear();
}

/*Implement checkingDeposit function that allows a customer to deposit money into their checking accounts*/
void Customer::checkingDeposit()
{
  if(!checking.head)
  {
    cout << "No existing checking accounts!" << endl;
    return;
  }

  cout << endl << "Please enter the checking account number: ";
  string tempNum;
  cin >> tempNum;
  AccountNode* temp = checking.head;
  while(temp)
  {
    if(temp->accountNum == tempNum)
    {
      double tempAmount;
      string selection = "N";
      while(selection != "Y")
      {
	     cout << "Please enter the deposit amount: ";
	     cin >> tempAmount;
	     while(cin.fail())
	       {
	           cout << "Please enter a valid amount: ";
	           cin >> tempAmount;
	       }
	     tempAmount = ((int)(tempAmount*100)) / 100;
	     cout << "Do you mean " << setprecision(2) << fixed << tempAmount << "?"  << endl << "Enter Y/N (capital letters only): ";
	     cin >> selection;
      }
	
      temp->balance += tempAmount;
      stringstream stream;
      stream << fixed << setprecision(2) << tempAmount;
      string action = stream.str();
      action = "Deposit $" + action;
      history.pushHistory(temp->accountNum, temp->balance, currentDateTime(), action);
      return;
    }
    temp = temp->next;
  }

  cout << "Invalid input or the account does not exist!" << endl;
}

/*Implement savingDeposit function that allows a customer to deposit money into their savings accounts*/
void Customer::savingDeposit()
{
  if(!saving.head)
  {
   // cout << "No existing saving accounts!" << endl;
    return;
  }

  cout << endl << "Please enter the saving account number: ";
  string tempNum;
  cin >> tempNum;
  AccountNode* temp = saving.head;
  while(temp)
  {
    if(temp->accountNum == tempNum)
    {
      double tempAmount;
      string selection = "N";
      while(selection != "Y")
      {
	cout << "Please enter the deposit amount: ";
	cin >> tempAmount;
	while(cin.fail())
	{
	  cout << "Please enter a valid amount: ";
	  cin >> tempAmount;
	}
	tempAmount = ((int)(tempAmount*100)) / 100;
	cout << "Do you mean " << setprecision(2) << fixed << tempAmount << "?"
	   << endl << "Enter Y/N (Capital letters only): ";
	cin >> selection;
      }

      string currentTime = currentDateTime();
      calculateInterest(currentTime, temp->accountNum);
      temp->balance += tempAmount;
      stringstream stream;
      stream << fixed << setprecision(2) << tempAmount;
      string action = stream.str();
      action = "Deposit $" + action;
      history.pushHistory(temp->accountNum, temp->balance, currentTime, action);
      return;
    }
    temp = temp->next;
  }

  cout << "Invalid input or the account does not exist!" << endl;
}

/*Implement checkingWithdraw function that allows a customer to take out money from their checking accounts*/
void Customer::checkingWithdraw()
{
  cout << endl << "Please enter the account number: ";
  string tempNum;
  cin >> tempNum;
  AccountNode* temp = checking.head;
  
  if(!temp)
  {
    cout << "No existing accounts!" << endl;
    return;
  }
  
  while(temp)
  {
    if(temp->accountNum == tempNum)
    {
      double tempAmount;
      string selection = "N";
      while(selection != "Y")
      {
	cout << "Please enter the withdraw amount: ";
	cin >> tempAmount;
	while(cin.fail())
	{
	  cout << "Please enter a valid amount: ";
	  cin >> tempAmount;
	}
	tempAmount = ((int)(tempAmount*100)) / 100;
	cout << "Do you mean " << setprecision(2) << fixed << tempAmount << "?"
	   << endl << "Enter Y/N (Capital letters only): ";
	cin >> selection;
      }
      
      if(temp->balance - tempAmount < 0)
	cout << "There is not enough balance in this account!" << endl;
      else
      {
	temp->balance -= tempAmount;
	stringstream stream;
	stream << fixed << setprecision(2) << tempAmount;
	string action = stream.str();
	action = "Withdraw $" + action;
	history.pushHistory(temp->accountNum, temp->balance, currentDateTime(), action);
      }
      return;
    }
    temp = temp->next;
  }

  cout << "Invalid input or the account does not exist!" << endl;
}

//Implement transfer function that allows a customer to transfer funds between their accounts
void Customer::transfer()
{
  if(!checking.head)
    cout << endl << "Warning! No existing checking accounts!" << endl;
  if(!saving.head)
    cout << endl <<"Warning! No existing saving accounts!" << endl;

  cout << endl << "Please enter the account# you are transferring funds from: ";
  string accountNum1;
  cin >> accountNum1;
  AccountNode* temp1 = checking.head;
  while(temp1)
  {
    if(temp1->accountNum == accountNum1)
      break;
    temp1 = temp1->next;
  }
  if(!temp1)
  {
    temp1 = saving.head;
    while(temp1)
    {
      if(temp1->accountNum == accountNum1)
	break;
      temp1 = temp1->next;
    }
  }
  if(!temp1)
  {
    cout << "Invalid input or the account does not exist!" << endl
	 << "Return to Previous Menu" << endl;
    return;
  }

  cout << endl << "Please enter the account# you are transferring funds to: ";
  string accountNum2;
  cin >> accountNum2;
  AccountNode* temp2 = checking.head;
  while(temp2)
  {
    if(temp2->accountNum == accountNum2)
      break;
    temp2 = temp2->next;
  }
  if(!temp2)
  {
    temp2 = saving.head;
    while(temp2)
    {
      if(temp2->accountNum == accountNum2)
	break;
      temp2 = temp2->next;
    }
  }
  if(!temp2)
  {
    cout << "Invalid input or the account does not exist!" << endl
	 << "Return to Previous Menu" << endl;
    return;
  }

  double tempAmount;
  string selection = "N";
  while(selection != "Y")
  {
    cout << "Please enter the transfer amount: ";
    cin >> tempAmount;
    while(cin.fail())
    {
      cout << "Please enter a valid amount: ";
      cin >> tempAmount;
    }
    tempAmount = ((int)(tempAmount*100)) / 100;
    cout << "Do you mean " << setprecision(2) << fixed << tempAmount << "?"
	 << endl << "Enter Y/N (Capital letters only): ";
    cin >> selection;
  }
  
  if(temp1->balance - tempAmount < 0)
    cout << "There is not enough balance in this account!" << endl;
  else
  {
    string currentTime = currentDateTime();
    if(temp1->accountNum[0] == '1')
      calculateInterest(currentTime, temp1->accountNum);
    if(temp2->accountNum[0] == '1')
      calculateInterest(currentTime, temp2->accountNum);
    
    temp1->balance -= tempAmount;
    stringstream stream1;
    stream1 << fixed << setprecision(2) << tempAmount;
    string action = stream1.str();
    action = "Transfer out $" + action;
    history.pushHistory(temp1->accountNum, temp1->balance, currentTime, action);
    temp2->balance += tempAmount;
    stringstream stream2;
    stream2 << fixed << setprecision(2) << tempAmount;
    action = stream2.str();
    action = "Transfer in $" + action;
    history.pushHistory(temp1->accountNum, temp1->balance, currentTime, action);
  }
}

//Implement isDigits function that confirms a string consists of numbers only
bool Customer::isDigits(string str)
{
  int i = 0;
  while(i < str.length())
  {
    if(isdigit(str[0])==false)
      return false;
    i++;
  }
  return true;
}

//Implement getName function for customer
string Customer::getName()
{
  return name;
}

//Implement currentDateTime function that fetches the time and date
string Customer::currentDateTime()
{
  time_t now = time(0);
  struct tm  tstruct;
  char       buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
  return buf;
}

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

//Implements constructor for Bank class
Bank::Bank()
{
  currentCustomer = NULL;
}

//Implement ifSignIn function to see if a customer is signed in
bool Bank::ifSignIn(string ufid, string pin)
{
  string path = "./customers/" + ufid + ".txt";
  ifstream customerFile;
  customerFile.open(path);
	
  if(!customerFile)
    return false;

  string potPin = "";
  getline(customerFile, potPin);

  customerFile.close();

  if(potPin == pin)
    return true;
  else 
    return false;
}

/*Implement cancelMembership function that allows a customer to get rid of their membership, including all accounts, from the bank */
void Bank::cancelMembership()
{
  cout << endl << "Are you sure that you want to cancel the membership?"
       << endl << "Enter Y/N: ";
  string selection;
  cin >> selection;
  
  if(selection == "y"|| selection=="Y")
  {
    if(currentCustomer->ifAllAccountZero())
    {
      string path = "./customers/" + currentCustomer->getUfid() + ".txt";
      remove(path.c_str());
      cout << endl << "We are sorry to see you go! Have a great day!" << endl;
      delete currentCustomer;
      currentCustomer = NULL;

    }
    else
    {
      cout << endl << "The membership cannot be cancelled!" << endl
	   << "The balance is not 0 in all accounts!" << endl
	   << "Return to Previous Menu" << endl;
      return;
    }
  }
  else if(selection == "N"|| selection=="n")
  {
    return;
  }
  else
  {
    cout << "Invalid input!" << endl;
  }
}

//Implement trySignIn function that allows a customer to log into their membership
void Bank::trySignIn()
{
  cout << endl << "Please enter your UFID: ";
  string ufid;
  cin >> ufid;
  cout << "Please enter your pin#: ";
  string pin;
  cin >> pin;

  bool control = ifSignIn(ufid, pin);
  if(!control){

    cout << "Invalid UFID or pin#!" << endl;
    mainMenu();
  }

  currentCustomer = new Customer();
  string path = "./customers/" + ufid + ".txt";
  currentCustomer->loadCustomer(path);
}

/*Implement informationMenu function that outputs and performs the options of the information bank menu */
void Bank::informationMenu()
{
  string selection = "NA";
 
  while(selection != "4")
  {
    currentCustomer->printInformation();

    cout << endl << "**************************"
	 << endl
	 << "Information Menu"
	 << endl
	 << "1. Edit my address"
	 << endl
	 << "2. Edit my email"
	 << endl
	 << "3. Edit my phone"
	 << endl
	 << "4. Return to Sign In Menu"
	 << endl
	 << "**************************"
	 << endl << endl;

    cout << "Selection - ";
    cin >> selection;

    while(selection != "4" && selection != "3" && selection != "2" && selection != "1")
    {
      cout << "Invalid selection!" << endl << endl;
      cout << "Selection - ";
      cin >> selection;
    }

    if(selection == "1"){
      cin.ignore();
      cin.clear();
       currentCustomer->setAddress();
     }
    else if(selection == "2")
      currentCustomer->setEmail();
    else if(selection == "3")
      currentCustomer->setPhone();
    else
      return;

    cout << "Information change was saved successfully!" << endl;
  }
}

/*Implement checkingAccountMenu function that outputs and performs the options of the checking accounts bank menu */
void Bank::checkingAccountMenu()
{
  string selection = "NA";
 
  while(selection != "6")
  {
    cout << endl;
    currentCustomer->printCheckingAccount();
    
    cout << endl << "**************************"
	 << endl
	 << "Checking Account Menu"
	 << endl
	 << "1. Deposit"
	 << endl
	 << "2. Withdraw"
	 << endl
	 << "3. Transfer"
	 << endl
	 << "4. Add checking account"
	 << endl
	 << "5. Delete checking account"
	 << endl
	 << "6. Return to General Account Menu"
	 << endl
	 << "**************************"
	 << endl << endl;

    cout << "Selection - ";
    cin >> selection;

    while(selection != "6" && selection != "5" && selection != "4" && selection != "3" && selection != "2" && selection != "1")
    {
      cout << "Invalid selection!" << endl << endl;
      cout << "Selection - ";
      cin >> selection;
    }

    if(selection == "1")
      currentCustomer->checkingDeposit();
    else if(selection == "2")
      currentCustomer->checkingWithdraw();
    else if(selection == "3")
      currentCustomer->transfer();
    else if(selection == "4")
      currentCustomer->addCheckingAccount("0"+currentCustomer->getUfid()+"0", 0);
    else if(selection == "5")
      currentCustomer->deleteCheckingAccount();
    else
      return;
  }
}

/*Implement savingAccountMenu function that outputs and performs the options of the savings accounts bank menu */
void Bank::savingAccountMenu()
{
  string selection = "NA";
 
  while(selection != "5")
  {
    cout << endl;
    currentCustomer->printSavingAccount();
    
    cout << endl << "**************************"
	 << endl
	 << "Saving Account Menu"
	 << endl
	 << "1. Deposit"
	 << endl
	 << "2. Transfer"
	 << endl
	 << "3. Add saving account"
	 << endl
	 << "4. Delete saving account"
	 << endl
	 << "5. Return to General Account Menu"
	 << endl
	 << "**************************"
	 << endl << endl;

    cout << "Selection - ";
    cin >> selection;

    while(selection != "5" && selection != "4" && selection != "3" && selection != "2" && selection != "1")
    {
      cout << "Invalid selection!" << endl << endl;
      cout << "Selection - ";
      cin >> selection;
    }

    if(selection == "1")
      currentCustomer->savingDeposit();
    else if(selection == "2")
      currentCustomer->transfer();
    else if(selection == "3")
      currentCustomer->addSavingAccount("1"+currentCustomer->getUfid()+"0", 0);
    else if(selection == "4")
      currentCustomer->deleteSavingAccount();
    else
      return;
  }
}
 
/*Implement generalAccountsMenu function that outputs and performs the options of the general accounts bank menu */
void Bank::generalAccountsMenu()
{
  string selection = "NA";
 
  while(selection != "3")
  {
    cout << endl << "**************************"
	 << endl
	 << "General Account Menu"
	 << endl
	 << "1. View my checking account"
	 << endl
	 << "2. View my saving account"
	 << endl
	 << "3. Return to Sign In Menu"
	 << endl
	 << "**************************"
	 << endl << endl;

    cout << "Selection - ";
    cin >> selection;

    while(selection != "3" && selection != "2" && selection != "1")
    {
      cout << "Invalid selection!" << endl << endl;
      cout << "Selection - ";
      cin >> selection;
    }

    if(selection == "1")
      checkingAccountMenu();
    else if(selection == "2")
      savingAccountMenu();
    else
      return;
  }
}

/*Implement signInMenu function that outputs and performs the options of the sign in menu */
void Bank::signInMenu()
{
  DIR* dir = opendir("customers");
  int i = 0;
  while(readdir(dir))
    i++;
  closedir(dir);
  if(i == 2)
  {
    cout << endl <<"Gator Bank has no customers yet!" << endl
	 << "Please create a membership!" << endl;
    return;
  }
  
  trySignIn();
  cout << endl << "Logged in successfully!" << endl;
  
  string selection = "NA";
 
  while(selection != "6")
  {
    cout << endl <<"**************************"
       << endl
       << "Welcome back! " << currentCustomer->getName()
       << endl << endl
       << "Sign In Menu"
       << endl
       << "1. View Personal Information"
       << endl
       << "2. View Accounts"
       << endl
       << "3. View History"
       << endl
       << "4. Change Pin"
       << endl
       << "5. Cancel Membership"
       << endl
       << "6. Sign Out"
       << endl
       << "**************************"
       << endl << endl;

    cout << "Selection - ";
    cin >> selection;

    while(selection != "6" && selection != "5" && selection != "4" && selection != "3" && selection != "2" && selection != "1")
    {
      cout << "Invalid selection!" << endl << endl;
      cout << "Selection - ";
      cin >> selection;
    }

    if(selection == "1")
      informationMenu();
    else if(selection == "2")
      generalAccountsMenu();
    else if(selection == "3")
      currentCustomer->printHistory();
    else if(selection == "4")
      currentCustomer->setPin();
    else if(selection == "5"){
      cancelMembership();
      return;
    }
    else
    {
      cout << endl << "Signed out successully!"
	   << endl << "Return to Main Menu!" << endl;
      currentCustomer->outputTxt();
      delete currentCustomer;
      currentCustomer = NULL;
      return;
    }
  }
}
  
/*Implement createMembershipMenu function that outputs and performs the options of the create membership bank menu */
void Bank::createMembershipMenu()
{
  currentCustomer = new Customer();
  currentCustomer->newCustomer();
  cout << endl << "Membership was created successfully! " << endl;
  currentCustomer->outputTxt();
  delete currentCustomer;
  currentCustomer = NULL;
}

//Implement mainMenu function that outputs and performs the options of the main bank menu 
void Bank::mainMenu()
{
  string selection = "NA";
  while(selection != "3")
  {
    cout << endl <<"**************************"
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
       << endl << endl;
  
    cout << "Selection - ";
    cin >> selection;

    while(selection != "3" && selection != "2" && selection != "1")
    {
      cout << "Invalid selection!" << endl << endl;
      cout << "Selection - ";
      cin >> selection;
    }
    
    if(selection == "1")
      signInMenu();
    else if(selection == "2")
      createMembershipMenu();
    else if(selection == "3")
    {
      cout << endl <<"Thank you for choosing Gator Bank!"
	   << endl << "Have a nice day!" << endl << endl;
      exit(0);
    }
  }
}

//Implement the main function
int main()
{
  DIR* dir = opendir("customers");
  if(!dir)
    system("mkdir ./customers");
  else
    closedir(dir);

  Bank* ourBank = new Bank();
  cout << endl <<"Welcome to the Gator Bank!" << endl;

  ourBank->mainMenu();
  
  return 0;
}

