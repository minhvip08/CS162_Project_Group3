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
// ViewscoreboardStaff
bool findstuID(student* stu, studentScore*& ss, course* c);
double GPAofCourse(studentScore*& stu);
void scoreboardofclass(student* cur_stu, semester* cur_semester, course* c);
void CaloverallGPA(student*& s);

// Create functions (Input data)
void create_schoolyear(schoolyear*& head);
void create_semester(schoolyear*& head);
void create_course(schoolyear*& head);
void input_session(session& s);
void create_class(schoolyear*& head);
void input_date(date& p);
void createCourseEnrolledTime(semester*& s);
void uppdateCourseInfor(schoolyear*& sy, semester*& pHeadSem);
void update1InforCourse(course* pCourse, int opt);
// Quy dinh luon la student trong enroll delete va view
void enrollCourse(schoolyear*& sy, string time, int sem, student*& stu);
void addEnrolledCourseToStudent(course*& pList, student*& pStudent, string ID_course);
void copyCourse(enrolledCourse*& pEC, course* pC);


//Login and register
void registerView(account* &head);
void loginView(account* &head, int type);
void Menu();
void loadAccountFile(ifstream& fin, account*& head);
void saveAccountFile(ofstream& fout, account* head);
bool checkAccountModel(account* acc, account* head, int type, bool isReg);
bool isEmpty(ifstream& pFile);
void Menu2(account* acc, account*& head, int type);
void viewProfile(account* acc, account*& head);
void enterProfile(account*& acc, int type);
void changePassword(account* acc, account*& head);
void collectOneClassAccount(string class_name, account*& head);

// Output to console
void show_schoolyear(schoolyear* head);
void show_semester(schoolyear*& head, semester*& s);
void show_course(course* c, int i);
void show_session(session head);
void show_class(Class* head, int i);
void show_date(date s);
void menu_staff();
void menu_student(schoolyear*& sy, int semester, student*& stu);
void show_ID_course(course* c);
void showListEnrolledCourse(student* pS);
void show_enrolled_course(enrolledCourse*);
//function 18
void showStudentsInClass(Class* pC);
//function 20
void showStudentsInCourse(course* pC);

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
void Delete_enrolled_course(string time, student*& pS, int sem);

// support function
date getCurrentDate();
bool check_date(date d1, date d2);
bool checkValidSchoolyear(schoolyear* sy);
void showCurrentSchoolyear(schoolyear* head);
bool checkExistSchoolyear(schoolyear* head, string s);
bool checkCurrentSchoolyear(schoolyear* sy);
bool checkValidDate(date d);
bool leap(int n);

// graphic cs161
void SetBGColor(WORD color);
void clrscr(void);
void gotoxy(short x, short y);
void SetColor(WORD color);

void saveSchoolyear(schoolyear* sy);
void saveListOfClass(schoolyear* sy);
void saveListOfSemester(schoolyear* sy);
void saveListOfCourse(schoolyear* sy, course* c, string time, int semester);

// Read data from file txt
void readSchoolyear(schoolyear*& sy);
void readListOfClass(Class*& cl, string time);
void readListOfCourse(string time, course*& c, int semester);
void readSemester(semester*& s, string time);
void read_date(ifstream& fin, date& d, bool check);
void menu_view(); 

bool checkAvailClass(string s, string year);
bool checkConflictSession(session ses1, session ses2);
void Delete_course_staff(schoolyear*& sy, course*& c, string time, int semester);
void save_enrollcourse_stu(string time, student* s, int semester);
bool alreadyEnrolled(string id, enrolledCourse* c);
int currentSemeser();
void readListEnrolled(student*& s, int semester);
