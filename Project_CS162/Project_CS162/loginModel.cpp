
#include "header.h"
void profileRegisterModel(account*& acc)
{
	int gender = 0;
	cout << "Enter name: ";
	cin >> acc->prf.name;
	cout << "Enter date of birth: ";
	cin >> acc->prf.date;
	//cout << "Day: " << endl;
	//cout << "Month: " << endl;
	//cout << "Year: " << endl;
	while (gender != 1 && gender != 2 && gender != 3) {
		cout << "Enter gender: " << endl;
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
		else if (gender == 3) {
			cout << "Enter gender: ";
			cin >> acc->prf.gender;
		}
	}
	cout << "Enter your phone number:";
	cin >> acc->prf.phone;
	cout << "Enter your e-mail: ";
	cin >> acc->prf.email;
}
void loadAccountFile(ifstream& fin, account*& head) {
	head = new account;
	getline(fin, head->username, ',');
	getline(fin, head->password, ',');
	getline(fin, head->prf.name, ',');
	getline(fin, head->prf.date, ',');
	getline(fin, head->prf.gender, ',');
	getline(fin, head->prf.phone, ',');
	getline(fin, head->prf.email);

	account* cur = head;
	while (fin.eof() == false) {
		cur->pNext = new account;
		cur = cur->pNext;
		getline(fin, cur->username, ',');
		getline(fin, cur->password, ',');
		getline(fin, cur->prf.name, ',');
		getline(fin, cur->prf.date, ',');
		getline(fin, cur->prf.gender, ',');
		getline(fin, cur->prf.phone, ',');
		getline(fin, cur->prf.email);
	}
	cur->pNext = NULL;
}

void saveAccountFile(ofstream& fout, account* head)
{
	account* cur = head;
	//fout << "Username,Password,Name,Date of Birth,Gender,Phone,Email" << endl;
	while (cur != NULL) {
		fout << cur->username << ",";
		fout << cur->password << ",";
		fout << cur->prf.name << ",";
		fout << cur->prf.date << ",";
		//fout << cur->prf.date.day << "/"<< cur->prf.date.month << "/"<<cur->prf.date.year << ",";
		fout << cur->prf.gender << ",";
		fout << cur->prf.phone << ",";
		fout << cur->prf.email;
		fout << endl;
		cur = cur->pNext;
	}
}

void registerModel(account &acc, account* head) {
	account* cur = head;
	if (head == NULL) {
		head = new account;
		head->username = acc.username;
		head->password = acc.password;
		cur = head;
	}
	else {
		cur->pNext = new account;
		cur = cur->pNext;
		cur->username = acc.username;
		cur->password = acc.password;
	}
	profileRegisterModel(cur);
	cur->pNext = NULL;
}
bool checkAccountModel(account acc, account* head)
{
	account* cur = head;
	while (cur != NULL)
	{
		if (cur->username == acc.username && cur->password == acc.password){
			return true;
		}
		cur = cur ->pNext;
	}
	return false;
}


