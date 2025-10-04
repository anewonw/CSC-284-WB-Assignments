#include "BankAccount.h"

using namespace std;

// Initialize static members
int BankAccount::ms_totalAccounts{ 0 };
int BankAccount::ms_nextAccountNumber{ 10001 };

BankAccount::BankAccount()
	: BankAccount::BankAccount("Unknown", 0.0)
{}

BankAccount::BankAccount(string_view name, double balance)
	: m_accountHolder{ name }
	, m_balance{ balance }
	, m_accountNumber{ ms_nextAccountNumber }
{
	ms_totalAccounts++;
	ms_nextAccountNumber++;
}

BankAccount::~BankAccount()
{
	cout << "Account #" << m_accountNumber << " destroyed.\n";
	ms_totalAccounts--;
}

const string& BankAccount::getAccountHolder() const
{
	return m_accountHolder;
}

int BankAccount::getAccountNumber() const
{
	return m_accountNumber;
}

double BankAccount::getBalance() const
{
	return m_balance;
}

void BankAccount::deposit(double amount)
{
	if (amount > 0) {
		m_balance += amount;
		cout << m_accountHolder << " deposits $" << fixed << setprecision(2)
			<< amount << endl;
	}
	else
		cout << "Error: Deposit amount must be positive.\n";
}

void BankAccount::withdraw(double amount)
{
	if (isValidWithdrawal(amount)) {
		m_balance -= amount;
		cout << m_accountHolder << " withdraws $" << fixed << setprecision(2)
			<< amount << endl;
	}
	else
		cout << "Error: " << m_accountHolder << " has insufficient funds in account.\n";
}

void BankAccount::printAccountInfo() const
{
	cout
		<< "Account Holder: " << m_accountHolder << endl
		<< "Account Number: " << m_accountNumber << endl
		<< "Balance: $" << fixed << setprecision(2) << m_balance << endl;
}

// Transfer funds between accounts, check amount is positive and sender has enough funds
void BankAccount::transfer(BankAccount& toAccount, double amount)
{
	if (amount <= 0)
	{
		cout << "Transaction failed: transfer amount must be positive.\n";
	}
	else if (isValidWithdrawal(amount))
	{
		m_balance -= amount;
		toAccount.m_balance += amount;
		cout << m_accountHolder << " transferred $" << fixed << setprecision(2) << amount << " to "
			<< toAccount.m_accountHolder << ".\n";
	}
	else
		cout << "Transaction failed: Insufficient funds in sender's account.\n";
}

// Check there are sufficient funds to withdraw amount
bool BankAccount::isValidWithdrawal(double amount) const
{
	return (m_balance - amount) >= 0;
}

int BankAccount::getTotalAccounts()
{
	return ms_totalAccounts;
}
