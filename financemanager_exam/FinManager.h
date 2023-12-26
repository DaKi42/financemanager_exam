#pragma once
#include <string>
#include <iostream>
#include "Date.h"
using namespace std;

struct Card {
    string number;
    string type;
    string option;
    double balance;
};

struct Cost {
    string accountNumber;
    Date date;
    string category;
    double sumOfCost; 
};

class FinManager
{
    Card cards[10];
    Cost costs[100];

public:
    FinManager();
    FinManager(string number, string type, string option, double balance);

    void print() const;
    void addAccount(string number, string type, string option, double balance);
    int addExpense(string n, int dd, int dm, int dy, double cost, string c);
    int deposit(string n, int c);
    void showCosts();

    void report(string option);
    void rating(string option);

    void saveReport(string option);
    void saveRating(string option);

    int menu();
};
