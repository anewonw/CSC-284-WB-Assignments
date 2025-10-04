#pragma once

#include <string>
#include <string_view>
#include <iostream>
#include <iomanip>

class BankAccount
{
public:
	// Constructors
	BankAccount();
	BankAccount(std::string_view name, double balance);

	// Destructor
	~BankAccount();

	// Accessors
	const std::string& getAccountHolder() const;
	int getAccountNumber() const;
	double getBalance() const;

	// Member functions
	void deposit(double amount);
	void withdraw(double amount);
	void printAccountInfo() const;
	void transfer(BankAccount& toAccount, double amount);
	bool isValidWithdrawal(double amount) const;

	// Static function
	static int getTotalAccounts();

private:
	std::string m_accountHolder;
	int m_accountNumber;
	double m_balance;

	static int ms_totalAccounts;
	static int ms_nextAccountNumber;
};