#include "header.h"
#include "Login.h"
#include "Support.h"
void loadAccountFile(ifstream& fin, account*& head) {
	if (!head) {
		head = new account;
	}
	account* cur = head;
	
	//string a; getline(fin, a, '\n');
	while (!fin.eof()) {
		fin >> cur->type;
		string a; getline(fin, a, ',');
		getline(fin, cur->username, ',');
		getline(fin, cur->password, ',');
		getline(fin, cur->prf.lastname, ',');
		getline(fin, cur->prf.firstname, ',');
		getline(fin, cur->prf.DOB, ',');
		getline(fin, cur->prf.gender, ',');
		getline(fin, cur->prf.social_id, '\n');

		if (fin.eof()) {
			cur->pNext = NULL;
			break;
		}
		else {
			cur->pNext = new account;
			cur = cur->pNext;
		}
	}
}

void saveAccountFile(ofstream& fout, account* head)
{
	if (!head) {
		cout << "Error" << endl; // kt lai
		return;
	}
	while (head != NULL) {
		//fout << endl; 
		fout << head->type << ',';
		fout << head->username << ',';
		fout << head->password << ',';
		fout << head->prf.lastname << ',';
		fout << head->prf.firstname << ',';
		fout << head->prf.DOB << ',';
		fout << head->prf.gender << ',';
		fout << head->prf.social_id;
		fout << endl;
		head = head->pNext;
		//if (head) fout << endl; 
	}
}

bool checkAccountModel(account* acc, account* head, int type, bool isReg)
{
	if (!head) return false;
	else {
		account* cur = head;
		while (cur) {
			if (cur->type == type) {
				if (cur->username == acc->username) {
					if (isReg) {
						return true;
					}
					if (cur->password == acc->password) {
						return true;
					}
				}
			}
			cur = cur->pNext;
		}
		return false;
	}
}


void collectOneClassAccount(string class_name,account*&head) {
	ifstream fin; account* cur_acc = new account; head = cur_acc; 
	fin.open(class_name + ".csv");
	if (!fin.is_open()) {
		cout << class_name << " file has not been imported" << endl;
		return;
	}
	else {
		while (!fin.eof()) {
			cur_acc->type = 1;
			string a; getline(fin, a, ',');
			getline(fin, cur_acc->username, ',');
			cur_acc->password = "12345678";
			getline(fin, cur_acc->prf.lastname, ',');
			getline(fin, cur_acc->prf.firstname, ',');
			getline(fin, cur_acc->prf.DOB, ',');
			getline(fin, cur_acc->prf.gender, ',');
			getline(fin, cur_acc->prf.social_id, '\n');
			fin.ignore();
			if (fin.eof()) {
				cur_acc->pNext = NULL;
				break;
			}
			else {
				cur_acc->pNext = new account;
				cur_acc = cur_acc->pNext;
			}
		}
			
	}
	fin.close();

	ofstream fout;
	fout.open("Student_acc.txt", ios::app);
	saveAccountFile(fout, head);
	fout.close();
}