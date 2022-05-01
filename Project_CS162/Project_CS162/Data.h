#pragma once
#include "header.h"
void saveSchoolyear(schoolyear* sy);
void saveListOfClass(schoolyear* sy);
void saveListOfSemester(schoolyear* sy);
void saveListOfCourse(schoolyear* sy, course* c, string time, int semester);
void save_enrollcourse_stu(string time, student* s, int semester);
void readSchoolyear(schoolyear*& sy);
void readListOfClass(Class*& cl, string time);
void readListOfCourse(string time, course*& c, int semester);
void readSemester(semester*& s, string time);
void readListEnrolled(string time, student*& s, int semester);
void readStudentOfCourse(course*& c);
void saveStudentOfCourse(course* c);
void readStudent1Class(string name, Class*& cl);
// csv file
void collectOneClassAccount(int& n,string class_name, account*& head); 