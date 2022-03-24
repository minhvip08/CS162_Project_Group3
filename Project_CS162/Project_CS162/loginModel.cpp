
#include "header.h"
void profileRegisterModel(account*& head)
{
	int gender = 0;
	cout << "Enter last name: ";
	cin >> head->prf.lastname;
	cout << "Enter first name: ";
	cin >> head->prf.firstname;
	cout << "Enter date of birth: ";
	cin >> head->prf.DOB;
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
			head->prf.gender = "Male";
		}
		else if (gender == 2) {
			head->prf.gender = "Female";
		}
		else if (gender == 3) {
			cout << "Enter gender: ";
			cin >> head->prf.gender;
		}
	}
	cout << "Enter your social ID:";
	cin >> head->prf.social_id;
}
void loadAccountFile(ifstream& fin, account*& head) {
	head = new account;
	getline(fin, head->username, ',');
	getline(fin, head->password, ',');
	getline(fin, head->prf.lastname, ',');
	getline(fin, head->prf.firstname, ',');
	getline(fin, head->prf.DOB, ',');
	getline(fin, head->prf.gender, ',');
	getline(fin, head->prf.social_id);

	account* cur = head;
	while (fin.eof() == false) {
		cur->pNext = new account;
		cur = cur->pNext;
		getline(fin, cur->username, ',');
		getline(fin, cur->password, ',');
		getline(fin, cur->prf.lastname, ',');
		getline(fin, cur->prf.firstname, ',');
		getline(fin, cur->prf.DOB, ',');
		getline(fin, cur->prf.gender, ',');
		getline(fin, cur->prf.social_id);
	}
	cur->pNext = NULL;
}

void saveAccountFile(ofstream& fout, account* head)
{
	while (head != NULL) {
		fout << head->username << ",";
		fout << head->password << ",";
		fout << head->prf.lastname << ",";
		fout << head->prf.firstname << ",";
		fout << head->prf.DOB << ",";
		//fout << cur->prf.date.day << "/"<< cur->prf.date.month << "/"<<cur->prf.date.year << ",";
		fout << head->prf.gender << ",";
		fout << head->prf.social_id;
		fout << endl;
		head = head->pNext;
	}
}

void registerModel(account& acc, account*& head) {
	account* cur = new account;
	cur->username = acc.username;
	cur->password = acc.password;
	if (head == nullptr) {
		head = cur;
	}
	else {
		cur->pNext = head;
		head = cur;
	}
	profileRegisterModel(head);
}

bool checkAccountModel(account acc, account* head)
{
	account* cur = head;
	while (cur != NULL)
	{
		if (cur->username == acc.username && cur->password == acc.password) {
			return true;
		}
		cur = cur->pNext;
	}
	return false;
}


