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

// csv file
void createlistofstu(Class*& head, const string str);
void copystudentinfor(student*& stu1, student*& stu2);
void exportonestu(ofstream& fout, student* stu);
void exportlistofstudent(Class* c, course* cour);
void import1studentscore(ifstream& fin, studentScore* stusc);
void importscoretoCourse(course*& c);
void copyliststu(Class*& c1, Class* c2);
void collectOneClassAccount(string class_name, account*& head);