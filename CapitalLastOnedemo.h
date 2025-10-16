#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <map>
void demo();
bool login(std::string& username);
void showMenu();
void checkBalance(const struct Account& acc);
void addIncome(struct Account& acc);
void addExpense(struct Account& acc);
void withdraw(struct Account& acc);
void calculateLoan();
void showSummary(const struct Account& acc);
void saveData(const std::string& username, const struct Account& acc);
void loadData(const std::string& username, struct Account& acc);
struct Account {
	double balance = 0.0;
	double totalIncome = 0.0;
	double totalExpenses = 0.0;
	std::map<std::string, double> expenseCategories = {
		{"Food", 0.0},
		{"Rent", 0.0},
		{"Utilities", 0.0},
		{"Entertainment", 0.0},
		{"Other", 0.0}
	};
};