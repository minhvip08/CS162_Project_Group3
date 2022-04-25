#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <string>
#include <ctime>
#include <Windows.h>
#include<chrono>
#include <tchar.h>
#include <thread>
using namespace std;

/*schoolyear: add head;
semester: add head; // use recursion to output
student list: add head; // use recursion to output
course: add head;
class: add head; */

struct date {
	int day, month, year;
};

struct profile {
	string lastname;
	string firstname;
	string DOB;
	string gender;
	string social_id;
};
struct account {
	string username;
	string password;
	int type; // 0 = staff, 1 = student
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

struct session {
	string date;
	string time;
};
struct score {
	double total;
	double final;
	double mid;
	double other;
};

struct studentScore { // course
	int no;
	string id;
	string name; 
	score stscore; 
	studentScore* pNext;
};

struct enrolledCourse { // student (class)
	string id_course;
	string course_name; // name of course
	string name_teacher; // them ten giao vien
	int credits; // them so luong tin chi
	session ses1; 
	session ses2; 
	studentScore* list_score;
	score ecscore;
	//studentScore* list_score;
	score ecscore; 
	enrolledCourse* next;
	/*int semester;
	int year;*/
};

struct finalGPA { // class
	float gpa;
	finalGPA* next;
};

struct student  // Class
{
	int No;
	string id;
	profile prf;
	double gpa;
	account acc;
	//	course* listCourse;
	int countEnroll = 0; 
	enrolledCourse* list_enrolled;
	finalGPA* list_gpa;
	student* pNext;
};

struct Class {
	string class_name;
	int total_student;  // input <= 50 (opt 1. input, 2.default)
	date start_date;
	date end_day;
	student* student_list;
	Class* nextClass;
};

struct course { 
	string ID_course;
	string course_name;
	string teacher_name;
	int credits; 
	int max_student; // tong so hoc sinh max cua mot lop
	int cur_student; // so hoc sinh hien tai cua lop
	session ses1;
	session ses2;
	studentScore* list_score;
	course* next;
};

struct semester {
	int mark; 
	date start_date;
	date end_date;
	date start_regist; 
	date end_regist; 
	int num_course = 0;
	course* course_list;
	//	Class* list_class; 
	semester* next;
};

struct schoolyear {
	string time;
	int num_sem = 0;
	int num_class = 0;
	bool cur = false; 
	semester* sem;
	Class* list_class;
	schoolyear* next_schyear;
};