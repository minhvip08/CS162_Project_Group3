#include "header.h"
date getCurrentDate()
{
	date d; 
	time_t tt; 
	time(&tt); 
	tm TM = *localtime(&tt); 

	d.day = TM.tm_mday; 
	d.month = TM.tm_mon + 1; 
	d.year = TM.tm_year + 1900; 

	return d;
}

bool check_date(date d1, date d2)
{
	date check = getCurrentDate();

	if (d1.year != check.year || d2.year != check.year) return false;
	else {
		if (d1.month > check.month || check.month > d2.month) return false;
		else {
			if (check.month == d1.month && check.day < d1.day) return false;
			else if (check.month == d2.month && check.day > d2.day) return false;
			else return true;
		}
	}
}

bool leap(int n)
{
	if (n % 4 == 0 && n % 100 != 0 || n % 400 == 0) return true;
	else return false;
}

bool checkValidDate(date d)
{
	if (d.day < 0 || d.day > 31 || d.month < 0 || d.month > 12 || d.year < 1900 || d.year > 2200) return false;
	else {
		switch (d.month) {
		case 2:
			if (!leap(d.year) && d.day > 28) return false;
			else if (d.day > 29) return false;
			break;
		case 4: case 6: case 9: case 11:
			if (d.day > 30) return false;
			break;
		}
		return true;
	}
}