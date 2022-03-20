#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <string>
#include <Windows.h>
using namespace std;

#define MAX 50

/*schoolyear: add head; 
semester: add head; // use recursion to output
student list: add head; // use recursion to output
course: add head;
class: add head; */ 

struct date {
	int day, month, year;
};

struct profile{
	string lastname; 
	string firstname;
	date DOB; 
	string gender;
	string social_id; 
};

struct account{
	string username;
	string password;
	int type; // 0 = student, 1 = staff.
	profile prf;
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
};

struct Class {
	string class_name;
	int total_student;  // input <= 50 (opt 1. input, 2.default)
	date start_date; 
	date end_day; 
	student* student_list; 
	Class* nextClass; 
};

struct course{ // thieu student list
	int ID_course; 
	string course_name; 
	string teacher_name;
	unsigned int credits;  
	int cur_student; 
	session *sess;
	student* student_list; 
	//studentScore* list_score; 
	course* next; 
	//int num_sessions; 
};

struct semester { 
	date start_day;
	date end_day;
	int num_course = 0;
	int num_class = 0; 
	course* course_list;
//	Class* list_class; 
	semester* next; 
};

struct schoolyear {
	string time;
	int num_sem = 0;
	semester* sem;
	Class* list_class; 
	schoolyear* next_schyear;
};

struct student 
{
	int No; 
	string id; 
	profile prf;
	double gpa;
	account acc; 
//	course* listCourse;
	enrolledCourse* list_enrolled; 
	finalGPA* list_gpa; 
	student* pNext;
};

struct enrolledCourse {
	int id_course; 
	string name; 
	session *sess;
	studentScore* list_score; 
	enrolledCourse* next; 
	/*int semester; 
	int year;*/
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

struct finalGPA {
	float gpa; 
	finalGPA* next; 
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