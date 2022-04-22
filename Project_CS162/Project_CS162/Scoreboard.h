#pragma once
#include "header.h"
bool findstuID(student* stu, studentScore*& ss, course* c);
double GPAofCourse(studentScore*& stu);
void scoreboardofclass(student* cur_stu, semester* cur_semester, course* c);
void CaloverallGPA(student*& s);

void updateastudentscore(course*& c);
void viewscoreboard(course* c);