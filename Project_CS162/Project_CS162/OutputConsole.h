#pragma once
#include "header.h"
void show_semester(schoolyear*& head, semester*& s);
void show_course(course* c, int i);
void show_ID_course(course* c);
void show_enrolled_course(enrolledCourse* c);
void show_session(session s);
void show_class(Class* head, int i);
void show_date(date s);
void show_schoolyear(schoolyear* head);
void showListEnrolledCourse(student* pS); // chua viet
void viewscoreboard(course* c);
void showStudentsInClass(Class* pC);
void showStudentsInCourse(course* pC);