#pragma once
#include "header.h"
bool isEmpty(ifstream& pFile);
date getCurrentDate();
bool check_date(date d1, date d2);
bool leap(int n);
bool checkValidDate(date d);
bool checkCurrentSchoolyear(schoolyear* sy);
bool checkExistSchoolyear(schoolyear* head, string s);
void showCurrentSchoolyear(schoolyear* head);
bool checkValidSchoolyear(string time);
bool checkAvailClass(string s, string year);
bool checkConflictSession(session ses1, session ses2);
bool alreadyEnrolled(string id, enrolledCourse* c);
int currentSemester();
bool checkEnrollTime(semester* s);
bool conflictSessionEnroll(enrolledCourse* ec, course* c);
bool checkSem(date d, int sem);
int findYear(string id);