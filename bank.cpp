#include <iostream>
#include <vector>

using namespace std;

class Account {
private:
    int accountNumber;
    string accountHolder;
    double balance;

public:
    Account(int number, string holder, double initialBalance)
        : accountNumber(number), accountHolder(holder), balance(initialBalance) {}

    int getAccountNumber() const {
        return accountNumber;
    }

    string getAccountHolder() const {
        return accountHolder;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: " << amount << endl;
        } else {
            cout << "Invalid amount for deposit." << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: " << amount << endl;
        } else {
            cout << "Insufficient funds or invalid amount for withdrawal." << endl;
        }
    }
};

class Bank {
private:
    vector<Account> accounts;
    int nextAccountNumber;

public:
    Bank() : nextAccountNumber(1001) {}

    void createAccount(string holder, double initialBalance) {
        Account newAccount(nextAccountNumber, holder, initialBalance);
        accounts.push_back(newAccount);
        cout << "Account created. Account number: " << nextAccountNumber << endl;
        nextAccountNumber++;
    }

    Account* findAccount(int accountNumber) {
        for (auto& account : accounts) {
            if (account.getAccountNumber() == accountNumber) {
                return &account;
            }
        }
        return nullptr;
    }

    const vector<Account>& getAccounts() const {
        return accounts;
    }
};

int main() {
    Bank bank;

    while (true) {
        cout << "1. Create Account" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Check Balance" << endl;
        cout << "5. Display All Accounts" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string holder;
                double initialBalance;
                cout << "Enter account holder's name: ";
                cin.ignore(); // Clear the newline character from the buffer
                getline(cin, holder);
                cout << "Enter initial balance: ";
                cin >> initialBalance;
                bank.createAccount(holder, initialBalance);
                break;
            }
            case 2: {
                int accountNumber;
                double amount;
                cout << "Enter account number: ";
                cin >> accountNumber;
                Account* account = bank.findAccount(accountNumber);
                if (account) {
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    account->deposit(amount);
                } else {
                    cout << "Account not found." << endl;
                }
                break;
            }
            case 3: {
                int accountNumber;
                double amount;
                cout << "Enter account number: ";
                cin >> accountNumber;
                Account* account = bank.findAccount(accountNumber);
                if (account) {
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    account->withdraw(amount);
                } else {
                    cout << "Account not found." << endl;
                }
                break;
            }
            case 4: {
                int accountNumber;
                cout << "Enter account number: ";
                cin >> accountNumber;
                Account* account = bank.findAccount(accountNumber);
                if (account) {
                    cout << "Account Holder: " << account->getAccountHolder() << endl;
                    cout << "Account Balance: " << account->getBalance() << endl;
                } else {
                    cout << "Account not found." << endl;
                }
                break;
            }
            case 5:
                cout << "All Accounts:" << endl;
                for (const Account& account : bank.getAccounts()) {
                    cout << "Account Number: " << account.getAccountNumber() << endl;
                    cout << "Account Holder: " << account.getAccountHolder() << endl;
                    cout << "Account Balance: " << account.getBalance() << endl;
                    cout << "----------------------------" << endl;
                }
                break;
            case 6:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice." << endl;
        }
    }

    return 0;
}
