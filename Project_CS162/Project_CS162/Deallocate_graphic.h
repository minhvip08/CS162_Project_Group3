#pragma once
#include "header.h"
void Delete_schoolyear(schoolyear*& head);
void Delete_semester(semester*& head);
void Delete_course(course*& head);
void Delete_class(Class*& head);
void Delete_stdScore(studentScore*& head);
void Delete_student(student*& head);
void Delete_enrollCourse(enrolledCourse*& head);
void Delete_finalGPA(finalGPA*& head);

void SetBGColor(WORD color);
void clrscr(void);
void gotoxy(short x, short y);
void SetColor(WORD color);