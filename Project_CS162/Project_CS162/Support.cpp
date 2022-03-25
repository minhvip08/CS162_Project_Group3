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