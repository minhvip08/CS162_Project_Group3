#pragma once
#include "header.h"
void create_schoolyear(schoolyear*& head);
void create_semester(schoolyear*& head);
void create_course(schoolyear*& head);
void input_session(session& s);
void create_class(schoolyear*& head);
void createCourseEnrolledTime(semester*& s);
void input_date(date& p);
void uppdateCourseInfor(schoolyear*& sy, semester*& sem);
void update1InforCourse(course*& pCourse, int opt);
void enrollCourse(schoolyear*& sy, string time, int sem, student*& stu);
void addEnrolledCourseToStudent(course* c, student*& stu);
void copyCourse(enrolledCourse*& pEC, course* pC);
void Delete_enrolled_course(string time, student*& pS, int sem);
void Delete_course_staff(schoolyear*& sy, course*& c, string time, int semester);