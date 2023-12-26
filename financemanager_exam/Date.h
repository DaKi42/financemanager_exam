#pragma once
#include <string>
using namespace std;

class Date
{
	int day;
	int month;
	int year;
public: 
	Date();
	Date(int d, int m, int y);
	Date getDate(string option);

	int compareDates(Date date1, Date date2);
	int getDaysInMonth(int month, int year);
	int getDay();
	int getMonth();
	int getYear();

	string getStringDate();
};
