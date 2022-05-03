#include "header.h"
#include "Login.h"
#include "Support.h"
void loadAccountFile(ifstream& fin, account*& head) {
	account* cur = new account; head = cur; 
	
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
		fout << endl;
		fout << head->type << ',';
		fout << head->username << ',';
		fout << head->password << ',';
		fout << head->prf.lastname << ',';
		fout << head->prf.firstname << ',';
		fout << head->prf.DOB << ',';
		fout << head->prf.gender << ',';
		fout << head->prf.social_id;
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

void collectOneClassAccount(int& n, string class_name,account*&head) {
	ifstream fin; account* cur_acc = new account; head = cur_acc;
	account* keep = new account; int i = -2;
	fin.open(class_name + ".csv");
	if (!fin.is_open()) {
		cout << class_name << " file has not been imported" << endl;
		return;
	}
	else {
		string a1; getline(fin, a1, '\n');
		while (!fin.eof()) {
			++i;
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
			if (i == 0) keep = cur_acc;
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
	n = i + 1;
	fin.close();
	ofstream fout;
	fout.open("Student_acc.txt", ios::app);
	saveAccountFile(fout, head);
	ofstream fout1;
	fout1.open(class_name + ".txt");
	saveStudent1Class(fout1, class_name, head);
	fout.close();
}
void saveStudent1Class(ofstream& fout, string name, account* head)
{
	if (!head) return;
	int n = 0;
	account* tmp = head;
	while (tmp) {
		++n;
		tmp = tmp->pNext;
	}
	fout << n << endl;
	account* cur = head;
	for (int i = 0; i < n; i++) {
		fout << cur->type << endl;
		fout << cur->username << endl;
		fout << cur->password << endl;
		fout << cur->prf.lastname << endl;
		fout << cur->prf.firstname << endl;
		fout << cur->prf.DOB << endl;
		fout << cur->prf.gender << endl;
		fout << cur->prf.social_id << endl;
		cur = cur->pNext;
	}
}

void readStudent1Class(string name, Class*& cl) {
	ifstream fin;
	fin.open(name + ".txt");
	if (isEmpty(fin)) {
		cl = nullptr;
		cout << "Invalid Class" << endl; return;
	}
	int n; fin >> n;
	account* acc = new account;
	student* tmp = new student; cl->student_list = tmp;
	for (int i = 0; i < n; i++) {
		fin >> acc->type; fin.get();
		getline(fin, acc->username, '\n');
		getline(fin, acc->password, '\n');
		getline(fin, acc->prf.lastname, '\n');
		getline(fin, acc->prf.firstname, '\n');
		getline(fin, acc->prf.DOB, '\n');
		getline(fin, acc->prf.gender, '\n');
		getline(fin, acc->prf.social_id, '\n');
		tmp->id = acc->username;
		tmp->prf = acc->prf;
		if (i == n - 1) {
			acc->pNext = nullptr;
			tmp->pNext = nullptr;
		}
		else {
			acc->pNext = new account;
			tmp->pNext = new student;
			acc = acc->pNext;
			tmp = tmp->pNext;
		}
	}
}