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
//void exportonestu(ofstream& fout, studentScore* stu);
void exportlistofstudent(course* cour);
//void import1studentscore(ifstream& fin, studentScore* stusc);
void importscoretoCourse(string time, course*& c, int sem);
void copyliststu(Class*& c1, Class* c2);
void collectOneClassAccount(string class_name, account*& head); 
void readListOfStu(student*& stu, string class_name);
void saveScoreboardCSV(course* c);
int conditionGPA(float a);

bool checkdata(schoolyear* scy);
void menu_staff2();
void printlistclass(Class* c, int x);
void exportstulist_menu(schoolyear* scy);
void printcourse(course* c, int x);
void viewscoboardofcourse(schoolyear* scy);
void importscoreboard_menu(schoolyear* scy);
void importscoretoCourse(string time, course*& c, int sem);
void updatestures_menu(schoolyear* sy);
void saveScoreboardCSV(course* c);
void viewscoboardofc_menu(schoolyear* sy);
void viewScoreOfClass(schoolyear* sy);
int conditionGPA(float a);