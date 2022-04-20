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
	if (head->type == 0) {
		fout << "Type,Username,Password,Last name,First name,DOB,Gender,Social ID";
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
			cout << cl->class_name<< " has not been created"<<endl;
		}
		else {
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
		}
		fin.close();
		cl = cl->nextClass;
	}
	ofstream fout;
	fout.open("Student_acc.txt");
	saveAccountFile(fout, head);
}
void collectStudentsAccount(account*&head) {
	schoolyear* sy = NULL;
	Class* check = NULL;
	readSchoolyear(sy);
	if(!sy) {
		system("cls");
		cout << "No school year has been created yet" << endl;
		return;
	}
	while (sy) {
		Class* cl = NULL;
		readListOfClass(cl, sy->time);
		if (cl) {
			printStudentsAccount(cl, head);
		}
		else {
			system("cls");
			cout << "List of classes in " << sy->time << " is empty" << endl;
		}
		sy = sy->next_schyear;
	}

}
void collectOneClassAccount(string class_name,account*&head) {
	ifstream fin;
	fin.open(class_name + ".txt");
	if (!fin.is_open()) {
		cout << class_name << " has not been created" << endl;
	}
	else {
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
	}
	fin.close();
	bool check = false;
	ifstream fin2;
	fin2.open("Student_acc.txt");
	if (!fin2.is_open()) {
		check = true;
	}	
	fin2.close();

	ofstream fout;
	fout.open("Student_acc.txt", ios::app);
	if (check) {
		fout << "Type,Username,Password,Last name,First name,DOB,Gender,Social ID";
	}
	saveAccountFile(fout, head);
	fout.close();
}