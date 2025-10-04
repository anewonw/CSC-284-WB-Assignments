// CSC 284
// Unit 4 Assignment 1: Bank Account Management
// Andrew Dasch

#include "BankAccount.h"
#include <iostream>
#include <memory>
#include <vector>
#include <string_view>

using namespace std;

// Create account objects and add to vector
void createAccount(vector<unique_ptr<BankAccount>>& acctList, string_view name, double balance);
void createAccount(vector<unique_ptr<BankAccount>>& acctList);
void printAll(vector<unique_ptr<BankAccount>>& acctList);

int main() {
	// Vector of BankAccount objects
	vector<unique_ptr<BankAccount>> accountList;

	// Create accounts
	cout <<"Creating accounts...\n";
	createAccount(accountList, "Scottie Rawlingson", 14'500.34);
	createAccount(accountList, "Gloria Glorgenthal", 54'398.89);
	createAccount(accountList);
	createAccount(accountList, "Bailey McTanner", 87.50);

	// Display initial account info
	cout << "\nInitial account info:\n";
	printAll(accountList);

	// Process transactions
	accountList[0]->deposit(34.56);
	accountList[0]->deposit(-90);
	accountList[1]->deposit(1003.32);
	accountList[2]->withdraw(97.0);
	accountList[3]->withdraw(87.49);
	
	// Print updated info and number of accounts
	cout << "\nUpdated account info:\n";
	printAll(accountList);
	cout << "Total accounts: " << BankAccount::getTotalAccounts() << endl;

	// Add account in block scope
	{
		cout << "\nEntering block scope...\n";
		BankAccount tempAccount{};
		cout << "Total accounts: " << BankAccount::getTotalAccounts() << endl;
		cout << "Leaving block scope...\n";
	}
	cout << "\nTotal accounts after block: " << BankAccount::getTotalAccounts() << "\n\n";

	// Process transfers
	accountList[2]->transfer(*accountList[1], 25.0);
	accountList[1]->transfer(*accountList[2], .35);
	accountList[0]->transfer(*accountList[2], 500.67);

	// Print final account info and exit
	cout << "\nFinal account info:\n";
	printAll(accountList);

	cout << "Exiting program...\n";
	return 0;
}

void createAccount(vector<unique_ptr<BankAccount>>& acctList, string_view name, double balance)
{
	acctList.push_back({ make_unique<BankAccount>(name, balance) });
}

void createAccount(vector<unique_ptr<BankAccount>>& acctList)
{
	acctList.push_back({ make_unique<BankAccount>() });
}

void printAll(vector<unique_ptr<BankAccount>>& acctList)
{
	for (auto& acct : acctList) {
		acct->printAccountInfo();
		cout << endl;
	}
}
