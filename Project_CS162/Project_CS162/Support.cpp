#include "header.h"
#include "Support.h"
#include "Data.h"
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

bool checkAvailClass(string s, string year)
{
	int tmp1 = 0, tmp2 = 0; int i = -1;
	while (tmp1 < 100 && tmp2 < 100) {
		++i;
		tmp1 *= 10; tmp2 *= 10;
		tmp1 += (int)s[i]; tmp2 += (int)year[i + 2];
	}

	if (tmp1 == tmp2) return true;
	else return false;
}

bool checkConflictSession(session ses1, session ses2)
{
	if (ses1.date == ses2.date && ses1.time == ses2.time) return true;
	else return false;
}
void changeacctostu(account* acc, schoolyear* scy, student*& stu)
{
	Class* c = scy->list_class;
	while (c)
	{
		student* cur = c->student_list;
		while (cur)
		{
			if (acc->username == cur->id)
			{
				stu = cur;
				return;
			}
			cur = cur->pNext;
		}
		c = c->nextClass;
	}
}

bool alreadyEnrolled(string id, enrolledCourse* c)
{
	if (!c) return false;
	enrolledCourse* tmp = c;
	while (tmp) {
		if (tmp->id_course == id) return true;
		tmp = tmp->next;
	}
	return false;
}

int currentSemester()
{
	date d = getCurrentDate();
	if (9 <= d.month && d.month <= 12) return 1;
	else if (1 <= d.month && d.month <= 4) return 2;
	else if (5 <= d.month && d.month <= 8) return 3;
	else return 0;
}

bool checkEnrollTime(semester* s) {
	date sta = s->start_regist;
	date end = s->end_regist;
	if (check_date(sta, end)) return true;
	else return false;
}

bool isEmpty(ifstream& pFile)
{
	return pFile.peek() == ifstream::traits_type::eof();
}

bool conflictSessionEnroll(enrolledCourse* ec, course* c) {
	while (ec) {
		if (checkConflictSession(ec->ses1, c->ses1) || checkConflictSession(ec->ses2, c->ses2) || checkConflictSession(ec->ses1, c->ses2) || checkConflictSession(ec->ses2, c->ses1))
			return true;
		ec = ec->next;
	}
	return false;
}
bool checkSem(date d, int sem) {
	if (sem == 1 && 9 <= d.month && d.month <= 12) {
		return true;
	}
	else if (sem == 2 && 1 <= d.month && d.month <= 4) {
		return true;
	}
	else if (sem == 3 && 5 <= d.month && d.month <= 8) {
		return true;
	}
	else {
		return false;
	}
}
int findYear(string id)
{
	schoolyear* head = nullptr;
	readSchoolyear(head);
	string time;
	while (head) {
		if (checkCurrentSchoolyear(head)) {
			time = head->time;
			break;
		}
		else
			head = head->next_schyear;
	}
	int year = time[3] + time[2] * 10;
	int ID = id[1] + id[0] * 10;
	return (year - ID);
}