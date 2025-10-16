//Our program will be a budget and loan calculator.The user will be able to check accounts and get balances.They will be about to get monthly payment amounts on loans and have access to it all in one place.This will be great for those over spenders or those new to budgeting and don’t know where to start.It will give the user an overview of their spending habits while also giving them tools to start saving for future payments.

//Core Features
//•	The user will be able to check their balances
//•	The user will be able to calculate monthly payment amounts
//•	The user will be able to track income and expenses
//•	The user will be able to withdraw money and overdraft
// Technical Approach
//•	We will be using, int, bool, doubles, and var statements
//•	We will use <iostream>, void, string
//•	If, else and break statements will be used
// User Interaction
//Explain how users will interact with your program :
//•	There will be multiple menu options for the user to choose from.
//•	There user will be able to enter in an account and get the balance
//•	The user will be able to go back to the main menu and choose another option
#include "demo.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <map>

using namespace std;

void demo() {}

// ================= LOGIN =================
bool login(string& username) {
    string password, storedUser, storedPass;
    int choice;

    cout << "\n1. Login\n2. Create Account\nChoose option: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        cout << "Enter username: ";
        getline(cin, username);
        cout << "Enter password: ";
        getline(cin, password);

        ifstream file("users.txt");
        bool found = false;

        while (file >> storedUser >> storedPass) {
            if (storedUser == username && storedPass == password) {
                cout << "Login successful!\n";
                found = true;
                break;
            }
        }
        file.close();

        if (!found) {
            cout << "Invalid login. Exiting.\n";
            return false;
        }
    }
    else if (choice == 2) {
        cout << "Create new username: ";
        getline(cin, username);
        cout << "Create password: ";
        getline(cin, password);

        ofstream file("users.txt", ios::app);
        file << username << " " << password << "\n";
        file.close();

        cout << "Account created successfully!\n";
    }
    else {
        cout << "Invalid option.\n";
        return false;
    }

    return true;
}

// ================= MENU =================
void showMenu() {
    cout << "\n===== Main Menu =====\n";
    cout << "1. Check Account Balance\n";
    cout << "2. Add Income\n";
    cout << "3. Add Expense\n";
    cout << "4. Withdraw Money\n";
    cout << "5. Calculate Loan Payment\n";
    cout << "6. View Spending Summary\n";
    cout << "7. Save & Exit\n";
}

// ================= ACCOUNT FUNCTIONS =================
void checkBalance(const Account& acc) {
    cout << fixed << setprecision(2);
    cout << "Current Balance: $" << acc.balance << "\n";
}

void addIncome(Account& acc) {
    double income;
    cout << "Enter income amount: $";
    cin >> income;

    acc.balance += income;
    acc.totalIncome += income;

    cout << "Income added successfully!\n";
}

void addExpense(Account& acc) {
    double expense;
    int categoryChoice;
    string categories[] = { "Food", "Rent", "Utilities", "Entertainment", "Other" };

    cout << "\nSelect Expense Category:\n";
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << categories[i] << "\n";
    }

    cout << "Choice: ";
    cin >> categoryChoice;
    cout << "Enter expense amount: $";
    cin >> expense;

    if (categoryChoice < 1 || categoryChoice > 5) {
        cout << "Invalid category.\n";
        return;
    }

    acc.balance -= expense;
    acc.totalExpenses += expense;
    acc.expenseCategories[categories[categoryChoice - 1]] += expense;

    cout << "Expense recorded under " << categories[categoryChoice - 1] << ".\n";
}

void withdraw(Account& acc) {
    double amount;
    cout << "Enter withdrawal amount: $";
    cin >> amount;

    if (amount > acc.balance) {
        cout << "Overdraft! Insufficient funds.\n";
    }
    else {
        acc.balance -= amount;
        cout << "Withdrawal successful.\n";
    }
}

void calculateLoan() {
    double principal, rate, years;
    cout << "Enter loan amount: $";
    cin >> principal;
    cout << "Enter annual interest rate (%): ";
    cin >> rate;
    cout << "Enter number of years: ";
    cin >> years;

    double monthlyRate = rate / 100 / 12;
    double payments = years * 12;
    double monthlyPayment = (principal * monthlyRate) /
        (1 - pow(1 + monthlyRate, -payments));

    cout << fixed << setprecision(2);
    cout << "Monthly payment: $" << monthlyPayment << "\n";
}

// ================= SUMMARY & FILE I/O =================
void showSummary(const Account& acc) {
    cout << fixed << setprecision(2);
    cout << "\n===== Spending Summary =====\n";
    cout << "Total Income: $" << acc.totalIncome << "\n";
    cout << "Total Expenses: $" << acc.totalExpenses << "\n";
    cout << "Current Balance: $" << acc.balance << "\n\n";

    cout << "Expenses by Category:\n";
    for (const auto& pair : acc.expenseCategories) {
        cout << setw(15) << left << pair.first << " : $" << pair.second << "\n";
    }
}

void saveData(const string& username, const Account& acc) {
    string filename = "data_" + username + ".txt";
    ofstream file(filename);

    file << acc.balance << " " << acc.totalIncome << " " << acc.totalExpenses << "\n";
    for (const auto& pair : acc.expenseCategories) {
        file << pair.first << " " << pair.second << "\n";
    }

    file.close();
}

void loadData(const string& username, Account& acc) {
    string filename = "data_" + username + ".txt";
    ifstream file(filename);

    if (!file) {
        cout << "No existing data for this user. Starting fresh.\n";
        return;
    }

    file >> acc.balance >> acc.totalIncome >> acc.totalExpenses;

    string category;
    double amount;
    while (file >> category >> amount) {
        acc.expenseCategories[category] = amount;
    }

    file.close();
}