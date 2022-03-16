#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

#define MAX 50


struct profile{
	string name;
	string date;
	string gender;
	string phone;
	string email;
};

struct account{
	string username;
	string password;
	profile prf;
	account* pnext;
};
struct studentinfor{ 
	int id; 
	string firstname; 
	string lastname; 
	string gender; 
	string birthday; 
	string social_id;
};

struct date{ 
	int day, month, year; 
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
	/*session_date day;
	session_time time;*/
	
	string date; 
	string time; 
	session* next; 
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
	string start_day;
	string end_day;
	int num_course;
	int num_class; 
	course* course_list;
	Class* list_class; 
};

struct schoolyear {
	string time;
	semester* semseter = new semester[3];
	//Class* list_class; 
	schoolyear* next_schyear;
};

struct teacher{
	profile prf;
	course* cours;
	teacher* next;
};

struct student
{
	profile prf;
	course* cours;
	student* next;
};
