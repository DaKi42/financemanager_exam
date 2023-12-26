#include "FinManager.h"
#include "Date.h"
#include <iostream>
#include <fstream>
using namespace std;

FinManager::FinManager() {
}

FinManager::FinManager(string number, string type, string option, double balance)
{
	for (int i = 0; i < 50; i++) {
		if (cards[i].number.empty()) {
			cards[i] = { number, type, option , balance };
			return;
		} 
		else {
			break;
		}
	}

}

void FinManager::print() const
{
	bool findedAccounts = false;

	cout << "------ | Your Accounts | ------" << endl;

	for (int i = 0; i < 50; i++) {
		if (cards[i].number != "") {
			cout << "\nFinManager: " << cards[i].number << endl;
			cout << "Type: " << cards[i].type << endl;
			cout << "Option: " << cards[i].option << endl;
			cout << "Balance: " << cards[i].balance << " USD" << endl;
			findedAccounts = true;
			continue;
		}
		else {
			break;
		}
	}

	if (findedAccounts == false) cout << "\nYou doesn't have FinManagers." << "\n\n";
}

void FinManager::addAccount(string number, string type, string option, double balance)
{
	for (int i = 0; i < 50; i++) {

		if (cards[i].number.empty()) {
			cards[i] = { number, type, option , balance };
			break;
		}
		else {
			continue;
		}
	}

}

int FinManager::addExpense(string n, int dd, int dm, int dy, double cost, string c)
{
	cout << "\n------ | Making Payment | ------" << endl;

	if (cost > this->cards->balance) {
		cout << "[Error] Insufficient funds to make the payment." << endl;
		cout << "You want to spend " << cost << " USD, but you have only " << this->cards->balance << " USD" << endl;
		return 0;
	}

	for (int i = 0; i < 500; i++) {
		if (costs[i].accountNumber.empty()) {

			Date costDate(dd, dm, dy);
			costs[i] = { n, costDate, c, cost };

			this->cards->balance -= cost;
			cout << "#" << i + 1 << " - You spend " << cost << " USD on " << c << " by using account " << n << endl;
			cout << "Account balance: " << this->cards->balance << " USD" << endl;
			return 0;
		}
		else {
			continue;
		}
	}
}

int FinManager::deposit(string n, int c)
{
	bool numberFinded = false;

	if (c > 0) {
		for (int i = 0; i < 50; i++) {
			if (cards[i].number == n) {
				cards[i].balance += c;
				cout << "\n------ | Deposit Money | ------" << endl;
				cout << "Succesfully deposited " << c << " USD to account " << cards[i].number << endl;
				cout << "Account balance: " << cards[i].balance << " USD" << endl;
				numberFinded = true;
				return true;
			}
			else {
				continue;
			}
		}

		if (numberFinded == false) {
			cout << "[Error] Account number not found." << endl;
		}

	}
	else {
		cout << "[Error] Invalid sum deposit." << endl;
		return false;
	}

}

void FinManager::showCosts()
{
	bool findedCosts = false;
	cout << "------ | Your Costs | ------" << endl;
	for (int i = 0; i < 500; i++) {
		if (costs[i].accountNumber != "") {

			cout << "Cost No." << i << endl;
			cout << "Account: " << costs[i].accountNumber << endl;
			cout << "Date: " << costs[i].date.getStringDate() << endl;
			cout << "Category: " << costs[i].category << endl;
			cout << "Cost of sum: " << costs[i].sumOfCost << " USD" << endl;

			findedCosts = true;
			return;
		}
		else {
			break;
		}
	}

	if (findedCosts == false) cout << "[Error] You don't making operations on this period." << endl;
}

void FinManager::report(string option) {
	double totalAmount = 0;
	int countCosts = 0;

	bool finded = false;

	string categories[50];
	double categoryExpenses[50] = { 0 };

	Date todayDate;
	todayDate.getDate("today");

	Date startDate;
	cout << endl;
	if (option == "today") {
		cout << "------ | Report Today | ------" << endl;
		startDate = todayDate;
	}
	else if (option == "week") {
		cout << "------ | Report Week | ------" << endl;
		startDate.getDate("week");
	}
	else if (option == "month") {
		cout << "------ | Report Month | ------" << endl;
		startDate.getDate("month");
	}

	for (int i = 0; i < 500; i++) {
		if (costs[i].accountNumber != "") {
			if (startDate.compareDates(costs[i].date, startDate) <= 0 && todayDate.compareDates(costs[i].date, todayDate) >= 0) {

				finded = true;

				cout << "Cost #" << i << endl;
				cout << "Account: " << costs[i].accountNumber << endl;
				cout << "Date: " << costs[i].date.getStringDate() << endl;
				cout << "Category: " << costs[i].category << endl;
				cout << "Cost sum: " << costs[i].sumOfCost << " USD" << endl;
				cout << endl;

				for (int j = 0; j < 100; j++) {
					if (categories[j] == costs[i].category) {
						categoryExpenses[j] += costs[i].sumOfCost;
						break;
					}
					else if (categories[j].empty()) {
						categories[j] = costs[i].category;
						categoryExpenses[j] = costs[i].sumOfCost;
						break;
					}
				}

				totalAmount += costs[i].sumOfCost;
				countCosts++;
			}
		}
	}

	if (finded == true) {
		cout << "-------------------------------" << endl;
		cout << "Total spent: " << totalAmount << " USD" << endl;
		cout << "Count of costs: " << countCosts << endl;
		cout << "\nCategories:" << endl;
		for (int j = 0; j < 50; j++) {
			if (!categories[j].empty()) {
				cout << categories[j] << ": " << categoryExpenses[j] << " USD" << endl;
			}
		}
	}
	else {
		cout << "[Error] You don't making operations on this period." << endl;
	}
}

void FinManager::rating(string option)
{
	if (option == "week" || option == "month") {
		cout << "\n------ | " << (option == "week" ? "Week" : "Month") << " Costs Rating | ------" << endl;

		Date todayDate;
		todayDate.getDate("today");
		Date startDate;

		bool finded = false;

		if (option == "week") startDate.getDate("week");
		else if (option == "month") startDate.getDate("month");

		Cost top3Costs[3];
		double top3Sums[3] = { 0.0 };

		for (int i = 0; i < 500; i++) {
			if (costs[i].accountNumber.empty()) continue;

			if (startDate.compareDates(costs[i].date, startDate) <= 0 && startDate.compareDates(costs[i].date, todayDate) >= 0) {
				double sumOfCost = costs[i].sumOfCost;
				finded = true;

				for (int j = 0; j < 3; j++) {
					if (sumOfCost > top3Sums[j]) {

						for (int k = 2; k > j; k--) {
							top3Costs[k] = top3Costs[k - 1];
							top3Sums[k] = top3Sums[k - 1];
						}

						top3Costs[j] = costs[i];
						top3Sums[j] = sumOfCost;
						break;
					}
				}
			}
		}

		if (finded == true) {
			for (int i = 0; i < 3; i++) {
				cout << "\tTop Cost No." << i + 1 << endl;
				cout << "Account: " << top3Costs[i].accountNumber << endl;
				cout << "Date: " << top3Costs[i].date.getStringDate() << endl;
				cout << "Category: " << top3Costs[i].category << endl;
				cout << "Cost sum: " << top3Costs[i].sumOfCost << " USD" << endl;
				cout << endl;
			}
		}
		else {
			cout << "[Error] You don't making operations on this period." << endl;
		}

	}
}

void FinManager::saveReport(string option) {
	double totalAmount = 0;
	int countCosts = 0;

	bool finded = false;

	string categories[50];
	double categoryExpenses[50] = { 0 };

	Date todayDate;
	todayDate.getDate("today");

	Date startDate;
	cout << endl;
	if (option == "today") {
		cout << "------ Report Today ------" << endl;
		startDate = todayDate;
	}
	else if (option == "week") {
		cout << "------ Report Week ------" << endl;
		startDate.getDate("week");
	}
	else if (option == "month") {
		cout << "------ Report Month ------" << endl;
		startDate.getDate("month");
	}

	string filename = "finmanager_report-" + option + "-" + todayDate.getStringDate() + "-" + startDate.getStringDate() + ".txt";
	ofstream outputFile(filename);

	if (outputFile.is_open()) {
		for (int i = 0; i < 500; i++) {
			if (costs[i].accountNumber != "") {
				if (startDate.compareDates(costs[i].date, startDate) <= 0 && todayDate.compareDates(costs[i].date, todayDate) >= 0) {

					finded == true;

					outputFile << "Cost No." << i << endl;
					outputFile << "FinManager: " << costs[i].accountNumber << endl;
					outputFile << "Date: " << costs[i].date.getStringDate() << endl;
					outputFile << "Category: " << costs[i].category << endl;
					outputFile << "Cost sum: " << costs[i].sumOfCost << " USD" << endl;
					outputFile << endl;

					for (int j = 0; j < 50; j++) {
						if (categories[j] == costs[i].category) {
							categoryExpenses[j] += costs[i].sumOfCost;
							break;
						}
						else if (categories[j].empty()) {
							categories[j] = costs[i].category;
							categoryExpenses[j] = costs[i].sumOfCost;
							break;
						}
					}

					totalAmount += costs[i].sumOfCost;
					countCosts++;
				}
			}
		}

		if (finded == true) {
			outputFile << "-------------------------------" << endl;
			outputFile << "Total spent: " << totalAmount << " USD" << endl;
			outputFile << "Count of costs: " << countCosts << endl;
			outputFile << "\nCategories:" << endl;
			for (int j = 0; j < 50; j++) {
				if (!categories[j].empty()) {
					outputFile << categories[j] << ": " << categoryExpenses[j] << " USD" << endl;
				}
			}
			outputFile.close();
			cout << "[Report] saved to " << filename << endl;
		}
		else {
			cout << "[Error] You don't making operations on this period." << endl;
		}
	}
	else {
		cout << "[Error] Failed to open the file for writing." << endl;
	}
}


void FinManager::saveRating(string option)
{
	if (option == "week" || option == "month") {
		cout << "\n==== " << (option == "week" ? "Week" : "Month") << " Costs Rating ====" << endl;

		Date todayDate;
		todayDate.getDate("today");
		Date startDate;

		bool finded = false;

		if (option == "week") {
			startDate.getDate("week");
		}
		else if (option == "month") {
			startDate.getDate("month");
		}

		Cost top3Costs[3];
		double top3Sums[3] = { 0.0 };

		for (int i = 0; i < 500; i++) {
			if (costs[i].accountNumber.empty()) continue;

			if (startDate.compareDates(costs[i].date, startDate) <= 0 && startDate.compareDates(costs[i].date, todayDate) >= 0) {
				double sumOfCost = costs[i].sumOfCost;
				finded = true;

				for (int j = 0; j < 3; j++) {
					if (sumOfCost > top3Sums[j]) {

						for (int k = 2; k > j; k--) {
							top3Costs[k] = top3Costs[k - 1];
							top3Sums[k] = top3Sums[k - 1];
						}

						top3Costs[j] = costs[i];
						top3Sums[j] = sumOfCost;
						break;
					}
				}
			}
		}

		if (finded == true) {
			string filename = "finmanager_rating-" + option + "-" + todayDate.getStringDate() + "-" + startDate.getStringDate() + ".txt";
			ofstream outputFile(filename);

			for (int i = 0; i < 3; i++) {
				outputFile << "\tTop Cost No." << i + 1 << endl;
				outputFile << "FinManager: " << top3Costs[i].accountNumber << endl;
				outputFile << "Date: " << top3Costs[i].date.getStringDate() << endl;
				outputFile << "Category: " << top3Costs[i].category << endl;
				outputFile << "Cost sum: " << top3Costs[i].sumOfCost << " USD" << endl;
				outputFile << endl;
			}

			outputFile.close();
			cout << "[Report] saved to " << filename << endl;
		}
		else {
			cout << "[Error] You don't making operations on this period." << endl;
		}
	}
	else {
		cout << "[Error] Failed to open the file for writing." << endl;
	}
}

int FinManager::menu()
{
	int choice;

	string wnumber, type, option, category;
	double amount;
	int dd, dm, dy;

	while (true) {
		option = "";
		amount = 0;

		cout << "\n------ | FinManager v1.2 Final |------" << endl;
		cout << "|1| Add New Account" << endl;
		cout << "|2| Add Cost" << endl;
		cout << "|3| Deposit money" << endl;
		cout << "|4| Show Costs" << endl;
		cout << "|5| Show Accounts" << endl;
		cout << "|6| Generate Report" << endl;
		cout << "|7| Generate Costs Rating" << endl;
		cout << "|8| Save Report" << endl;
		cout << "|9| Save Costs Rating" << endl;
		cout << "|0| Exit" << endl;

		cout << "\nEnter your choice: ";
		cin >> choice;

		cout << endl;

		switch (choice) {
		case 1:
			cout << "Enter account number: ";
			cin >> wnumber;

			cout << "Enter account type (Visa, Mastercard, Payoneer and other): ";
			cin >> type;

			while (option != "Credit" && option != "Debit" && option != "Other") {
				cout << "Enter account option (Credit, Debit or Other): ";
				cin >> option;
			}

			while (amount <= 0) {
				cout << "Enter card balance: ";
				cin >> amount;
			}
			FinManager::addAccount(wnumber, type, option, amount);
			break;
		case 2:
			cout << "Enter account number: ";
			cin >> wnumber;

			cout << "Enter day, month, and year of the expense (e.g., 04 01 2024): ";
			cin >> dd >> dm >> dy;

			while (amount <= 0) {
				cout << "Enter expense amount: ";
				cin >> amount;
			}

			cout << "Enter expense category: ";
			cin >> category;

			FinManager::addExpense(wnumber, dd, dm, dy, amount, category);
			break;
		case 3:
			cout << "Enter account number: ";
			cin >> wnumber;

			while (amount <= 0) {
				cout << "Enter deposit amount: ";
				cin >> amount;
			}
			FinManager::deposit(wnumber, amount);
			break;
		case 4:
			FinManager::showCosts();
			break;
		case 5:
			FinManager::print();
			break;
		case 6:
			while (option != "week" && option != "month" && option != "today") {
				cout << "Enter report option (today, week, month): ";
				cin >> option;
			}
			FinManager::report(option);
			break;
		case 7:
			while (option != "week" && option != "month") {
				cout << "Enter rating option (week, month): ";
				cin >> option;
			}
			FinManager::report(option);
			break;
		case 8:
			while (option != "week" && option != "month" && option != "today") {
				cout << "Enter report option (today, week, month): ";
				cin >> option;
			}
			FinManager::saveReport(option);
			break;
		case 9:
			while (option != "week" && option != "month") {
				cout << "Enter rating option (week, month): ";
				cin >> option;
			}
			FinManager::saveRating(option);
			break;
		case 0:
			cout << "Good luck!" << endl;
			return 0;
		}
	}
}
