#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;

#define MAX 50


struct Profile {
	string name;
	string date;
	string gender;
	string phone;
	string email;
};

struct Accounts {
	string username;
	string password;
	Profile profile;
	Accounts* pNext_Acc;
};
struct StudentInfor{ 
	int ID_student; 
	string FirstName; 
	string LastName; 
	string Gender; 
	string birthday; 
	string Social_ID; 
};

struct Date{ 
	int day, month, year; 
};

struct Courses{ 
	int ID_course; 
	string course_name; 
	string teacher_name; 
	unsigned int credits; 
	//int max_student = MAX; 
	int cur_student; 
	session_date session_date; 
	session_time session_time;
	int num_sessions; 
};

struct schoolYear{ 
	string time; 
	int courses; 
};

struct Teacher{
};

struct session_date{ 
	const string MON = "MON"; 
	const string TUE = "TUE"; 
	const string WED = "WED"; 
	const string THU = "THU"; 
	const string FRI = "FRI"; 
	const string SAT = "SAT"; 
};

struct session_time{
	const string S1 = "S1(7:30)"; 
	const string S2 = "S2(09:30"; 
	const string S3 = "S3(13:30)";
	const string S4 = "S4(15:30)"; 
};


