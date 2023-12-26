#pragma warning(disable:4996)
#include "Date.h"
#include <iostream>

Date::Date()
{
	day = 1; 
	month = 1;
	year = 1970;
}

Date::Date(int d, int m, int y) :day(d), month(m), year(y)
{
}

int Date::compareDates(Date date1, Date date2)
{
	if (date1.year < date2.year) {
		return -1;
	}
	else if (date1.year > date2.year) {
		return 1;
	}
	else {
		if (date1.month < date2.month) {
			return -1;
		}
		else if (date1.month > date2.month) {
			return 1;
		}
		else {
			if (date1.day < date2.day) {
				return -1;
			}
			else if (date1.day > date2.day) {
				return 1;
			}
			else {
				return 0;
			}
		}
	}
}

int Date::getDaysInMonth(int month, int year)
{
	if (month == 2) {
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
			return 29;
		}
		return 28;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		return 30;
	}
	return 31;
}

Date Date::getDate(string option)
{
	time_t currentTime = time(nullptr);
	tm* localTime = localtime(&currentTime);

	int year = localTime->tm_year + 1900;
	int month = localTime->tm_mon + 1;
	int day = localTime->tm_mday;
	int hour = localTime->tm_hour;
	int minute = localTime->tm_min;
	int second = localTime->tm_sec;

	this->day = day;
	this->month = month;
	this->year = year;

	if (option == "today") {
		return *this;
	}
	else if (option == "week") {
		day += 7;

		int daysInMonth = getDaysInMonth(month, year);
		if (day > daysInMonth) {
			day -= daysInMonth;
			month++;

			if (month > 12) {
				month = 1;
				year++;
			}
		}

		this->day = day;
		this->month = month;
		this->year = year;
		return *this;
	}
	else if (option == "month") {
		month++;
		if (month > 12) {
			month = 1;
			year++;
		}

		this->day = day;
		this->month = month;
		this->year = year;
		return *this;
	}

	return *this;
}

int Date::getDay()
{
	return day;
}

int Date::getMonth()
{
	return month;
}

int Date::getYear()
{
	return year;
}

string Date::getStringDate()
{
	return to_string(day) + "." + to_string(month) + "." + to_string(year);
}