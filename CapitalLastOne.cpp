#include "demo.h"
int main() {
	std::string username;
	Account acc;
	std::cout << "===== Welcome to the Budget & Loan Calculator =====\n";
	if (!login(username)) return 0;
	loadData(username, acc);
	int choice;
	bool running = true;
}