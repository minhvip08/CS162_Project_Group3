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
bool checkCurrentSchoolyear(schoolyear* sy) {
	date d = getCurrentDate();
	int cnt1 = 0, cnt2 = 0;
	for (int i = 0; i < 4; i++) {
		cnt1 *= 10; cnt1 += ((int)sy->time[i] - 48);
	}
	for (int i = 5; i < 9; i++) {
		cnt2 *= 10; cnt2 += ((int)sy->time[i] - 48);
	}
	int month = d.month;
	if (month < 9 && cnt2 == d.year) return true;
	else if (month > 9 && cnt1 == d.year) return true;
	else return false;
}

bool checkExistSchoolyear(schoolyear* head, string s)
{
	if (!head) return true;
	schoolyear* tmp = head;
	while (tmp) {
		if (s == tmp->time) return false;
		tmp = tmp->next_schyear;
	}
	return true;
}

void showCurrentSchoolyear(schoolyear* head)
{
	if (!head) return;
	schoolyear* tmp = head;
	while (tmp) {
		if (checkCurrentSchoolyear(tmp) == true) {
			cout << "The current schoolyear is: " << tmp->time << endl;
			break;
		}
		tmp = tmp->next_schyear;
	}
}
bool checkValidSchoolyear(schoolyear* sy)
{
	string check = sy->time; 
	int cnt1 = 0, cnt2 = 0; 
	for (int i = 0; i < 4; i++) {
		cnt1 *= 10; cnt1 += (int)check[i]; 
	} 
	for (int i = 0; i < 4; i++) {
		cnt2 *= 10; cnt2 += (int)check[i];
	}
	if (cnt2 - cnt1 == 1) return true; 
}