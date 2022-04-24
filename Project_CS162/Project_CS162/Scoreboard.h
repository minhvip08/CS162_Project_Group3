#pragma once
#include "header.h"
bool findstuID(student* stu, studentScore*& ss, course* c);
double GPAofCourse(studentScore*& stu);
void scoreboardofclass(student* cur_stu, semester* cur_semester, course* c);
void CaloverallGPA(student*& s);
void viewstudentscore(studentScore* sco);
void updateastudentscore(course*& c, string id);
void viewscoreboardcourse(course* c);
void viewstudentscore(studentScore* sco);