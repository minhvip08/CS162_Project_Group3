#include <iostream>
#include<fstream>
#include<string.h>
#include "header.h"
#include "loginModel.cpp"
using namespace std;
void Menu() {
	int type = 0;
	account acc;
	while (type != 1 && type != 2) {
		cout << "Staff or Student?" << endl;
		cout << "1.Staff"<<endl;
		cout << "2.Student"<<endl;
		cin >> type;
		if (type == 1) {
			//open file for staff
		}
		else if (type == 2) {
			//open file for student
		}
	}
	type = 0;
	while (type!=1&&type!=2) {
		cout << "1.Login" << endl;
		cout << "2.Register" << endl;
		cin >> type;
		if (type == 1) {
			loginView(acc);
		}
		else if (type == 2) {
			registerView(acc);
		}
	}
}
void loginView(account& login){
	cout << "Enter your username: ";
	cin >> login.username;
	cout << "Enter your password: ";
	cin >> login.password;
	loginModel(login);
}
void registerView(account &reg){
	string check;
	cout << "Enter account name: "<<endl;
	cin >> reg.username;
	do
	{
		cout << "Please enter password: ";
		cin >> reg.password;
		cout << "Please enter password again: ";
		cin >> check;
	} while (check.compare(reg.password) == 1);
	registerModel(reg);
	//cout << "Register successful!";
}

void inputProfileInfo(account*& acc)
{
	int gender = 0;
	cout << "Enter your name: "<<endl;
	getline(cin, acc->prf.name);
	while (gender!=1&&gender!=2&&gender!=3) {
		cout << "Enter your gender: " << endl;
		cout << "1.Male" << endl;
		cout << "2.Female" << endl;
		cout << "3.Other" << endl;
		cin >> gender;
		if (gender == 1) {
			acc->prf.gender = "Male";
		}
		else if (gender == 2) {
			acc->prf.gender = "Female";
		}
		else if(gender==3){
			cin >> acc->prf.gender;
		}
	}
	cout << "Enter date of birth: "<<endl;
	cin >> acc->prf.date;
	//cout << "Day: " << endl;
	//cout << "Month: " << endl;
	//cout << "Year: " << endl;
	cout << "\nEnter your phone number:"<<endl;
	cin >> acc->prf.phone;
	cout << "Enter your e-mail: "<<endl;
	cin >> acc->prf.email;
}