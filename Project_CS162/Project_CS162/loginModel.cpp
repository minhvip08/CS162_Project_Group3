#include "header.h"
void loadAccountFile(ifstream& fin, account*& head) {
	if (!head) {
		head = new account;
	}
	account* cur = head; string a; getline(fin, a, '\n');
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
	fout << "Type,Username,Password,Last name,First name,DOB,Gender,Social ID";
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

bool isEmpty(ifstream& pFile)
{
	return pFile.peek() == ifstream::traits_type::eof();
}
void printStudentsAccount(Class*& cl, account*& head) {
	while (cl) {
		ifstream fin;
		fin.open(cl->class_name + ".txt");
		if (!fin.is_open()) {
			cout << "No class yet";
			break;
		}
		string a;
		getline(fin, a, '\n');
		while (!fin.eof()) {
			account* cur_acc = new account;
			cur_acc->type = 1;
			string a; getline(fin, a, ',');
			getline(fin, cur_acc->username, ',');
			cur_acc->password = "12345678";
			getline(fin, cur_acc->prf.lastname, ',');
			getline(fin, cur_acc->prf.firstname, ',');
			getline(fin, cur_acc->prf.DOB, ',');
			getline(fin, cur_acc->prf.gender, ',');
			getline(fin, cur_acc->prf.social_id, '\n');

			if (!head) {
				head = cur_acc;
				head->pNext = NULL;
			}
			else {
				cur_acc->pNext = head;
				head = cur_acc;
			}
		}
		fin.close();
		cl = cl->nextClass;
	}
	ofstream fout;
	fout.open("Student_acc.txt");
	saveAccountFile(fout, head);
}
void collectStudentsAccount(account*&head) {
	schoolyear*sy=NULL;
	Class* cl = NULL;
	Class* temp = NULL;
	readSchoolyear(sy);
	if(!sy) {
		return;
	}
	while (sy) {
		//cout << "No23123"<<endl;
		readListOfClass(cl, sy->time);
		printStudentsAccount(cl, head);
		sy = sy->next_schyear;
	}
	/*if (!cl) {
		return;
	}*/

}