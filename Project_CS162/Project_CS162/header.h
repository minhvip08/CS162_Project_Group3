#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <string>
#include <ctime>
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

struct session {
	string date;
	string time;
};
struct studentScore { // course
	int no;
	string id;
	string name; 
	double total;
	double final;
	double mid;
	double other;
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
	semester* sem;
	Class* list_class;
	schoolyear* next_schyear;
};


// Create functions (Input data)
void create_schoolyear(schoolyear*& head);
void create_semester(schoolyear*& head);
void create_course(schoolyear*& head);
void input_session(session& s);
void create_class(schoolyear*& head);
void input_date(date& p);
void createCourseEnrolledTime(semester*& s);
void uppdateCourseInfor(semester* pHeadSem);
void update1InforCourse(course* pCourse, int opt);
// Quy dinh luon la student trong enroll delete va view
void enrollCourse(course*& pList, student*& pStudent);


//Login and register(missing clearscreen, type and date modification)
void registerView(account* &head, ifstream &fin);
void loginView(account* &head, int type);
void Menu();
void loadAccountFile(ifstream& fin, account*& head);
void saveAccountFile(ofstream& fout, account* head);
bool checkAccountModel(account* acc, account* head, int type);
bool isEmpty(ifstream& pFile);
void Menu2(account* acc, account*& head);
void viewProfile(account* acc, account*& head);
void enterProfile(account*& acc);

// Output to console
void show_schoolyear(schoolyear* head);
void show_semester(semester* s, int i);
void show_course(course* c, int i);
void show_session(session head);
void show_class(Class* head, int i);
void show_date(date s);
void menu_staff();
void show_ID_course(course* c);
void viewListEnrolledCourse(student* pS);
void show_enrolled_course(enrolledCourse*);

//Load students in csv file
void createlistofstu(Class*& head, const string str);
void copystudentinfor(student* &stu1, student* &stu2);
void copyliststu(Class*& c1, Class* c2);
void sortbyID(Class*& c);
void importscoretoCourse(course*& c);
void import1studentscore(ifstream& fin, studentScore* stusc);
void updateastudentscore(course*& c);
void viewscoreboard(course* c);

// delete memory
void Delete_schoolyear(schoolyear*& head);
void Delete_semester(semester*& head);
void Delete_course(course*& head);
void Delete_class(Class*& head);
void Delete_stdScore(studentScore*& head);
void Delete_student(student*& head);
void Delete_enrollCourse(enrolledCourse*& head);
void Delete_finalGPA(finalGPA*& head);
void Delete_enrolled_course( student*& pS);

// support function
date getCurrentDate();
bool check_date(date d1, date d2);


// graphic cs161
void SetBGColor(WORD color);
void clrscr(void);
void gotoxy(short x, short y);
void SetColor(WORD color);