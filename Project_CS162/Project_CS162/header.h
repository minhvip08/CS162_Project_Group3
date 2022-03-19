#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <string>
#include <Windows.h>
using namespace std;

#define MAX 50

struct date {
	int day, month, year;
};

struct profile{
	string lastname; 
	string firstname;
	date DOB; 
	string gender;
	string phone;
	string email;
	string social_id; 
};

struct account{
	string username;
	string password;
	//profile prf;
	account* pNext;
};

struct session_date {
	const string MON = "MON";
	const string TUE = "TUE";
	const string WED = "WED";
	const string THU = "THU";
	const string FRI = "FRI";
	const string SAT = "SAT";
};

struct session_time {
	const string S1 = "S1(7:30)";
	const string S2 = "S2(09:30)";
	const string S3 = "S3(13:30)";
	const string S4 = "S4(15:30)";
};

struct session{
	string date; 
	string time; 
	session* pNext; 
};

struct Class {
	string class_name;
	int max_student = MAX; 
	int cur_student; 
	date start_date; 
	date end_day; 
	Class* nextClass; 
};

struct course{ 
	int ID_course; 
	string course_name; 
	string teacher_name;
	unsigned int credits;  
	int cur_student; 
	session* sess;
	course* next; 
	//int num_sessions; 
};

struct semester { 
	date start_day;
	date end_day;
	int num_course;
	int num_class; 
	course* course_list;
	Class* list_class; 
	semester* next; 
};

struct schoolyear {
	string time;
	int num_sem = 0;
	semester* sem;
	//Class* list_class; 
	schoolyear* next_schyear;
};

struct teacher
{
	account acc;
	teacher* pNext;
};

struct student
{
	int id; 
	profile prf;
	double gpa;
	account acc; 
	course* listCourse;
	student* pNext;
};

struct studentScore {
	string name;
	string id;
	double total;
	double final;
	double mid;
	double other;
	studentScore* pNext;
};


// Create functions (Input data)
void input_schoolyear(schoolyear*& head);
void input_semester(semester*& head);
void input_course(course*& head);
void input_session(session*& head);
void input_class(Class*& head);
void input_date(date& p);

// Output to console
void show_schoolyear(schoolyear* head);
void show_semester(semester* s);
void show_course(course* c);
void show_session(session* head);
void show_class(Class* head);
void show_date(date s);

// Delete Memory
void Delete_schoolyear(schoolyear*& head);
void Delete_semester(semester*& head);
void Delete_course(course*& head);
void Delete_session(session*& head);
void Delete_class(Class*& head);