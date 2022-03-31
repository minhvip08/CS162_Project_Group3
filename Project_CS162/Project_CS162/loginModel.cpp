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

bool checkAccountModel(account* acc, account* head, int type)
{
	if (!head) return false;
	else {
		account* cur = head;
		while (cur) {
			if (cur->type == type) {
				if (cur->username == acc->username && cur->password == acc->password) {
					return true;
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