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
	string teacher_
};

struct schoolYear{ 
	
};

struct Teacher{ 
	int 
};
int main() {
	cout << "hello";
}


