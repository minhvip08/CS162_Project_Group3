#include "header.h"
void registerView(account*& head, ifstream& fin) {
	bool flag = true;
	account* acc = new account;
	string repassword;
	cout << "Enter username: "; cin >> acc->username;
	do
	{
		cout << "Enter password: ";
		cin >> acc->password;
		cout << "Enter password again: ";
		cin >> repassword;
		if (acc->password != repassword) {
			cout << "Not alike" << endl;
			flag = false;
		}
		else flag = true; 
	} while (!flag);

	bool check; 
	if (!isEmpty(fin)) {
		check = false;
	}
	else {
		check = checkAccountModel(acc, head, 0);
	}
	if (check) {
		cout << "Username or password exist" << endl;
		//	system("pause");
		return;
	}
	else if (!check) {
		cout << "Username and password approved" << endl;
		//registerModel(head, acc); 

		enterProfile(acc);
		if (!head) {
			head = acc;
			head->pNext = NULL;
		}
		else {
			acc->pNext = head;
			head = acc;
		}

		cout << "Register Successful !" << endl;
		ofstream fout;
		fout.open("AccountFile1.txt");
		saveAccountFile(fout, head);
		fout.close();
	}
}
void loginView(account* &head, int type) 
{
	account* acc = new account;
	cout << "Enter username: "; cin >> acc->username;
	cout << "Enter your password: "; cin >> acc->password;

	if (checkAccountModel(acc, head, type)) {
		cout << "Login successful!" << endl;
		//head = cur;
		Menu2(acc,head);
		//menu_staff();
	}
	else {
		cout << "Username or password is incorrect" << endl;
		return;
	}
}
void enterProfile(account*& acc)
{
	int gender = 0; 
	acc->type = 0;
	cout << "Enter last name: "; cin.get(); getline(cin, acc->prf.lastname);
	cout << "Enter first name: "; getline(cin, acc->prf.firstname);
	cout << "Enter date of birth (dd/mm/yyyy): "; getline(cin, acc->prf.DOB);

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
	cout << "Enter your social ID: "; cin >> acc->prf.social_id;
}
void viewProfile(account*acc, account*& head)
{
	account* cur = head;

	while (acc->username != cur->username || acc->password!=cur->password) {
		cur = cur->pNext;
	}
	int choose = 100;
	while (choose != 1 && choose != 0) {
		cout << "-----Profile-----" << endl;
		cout << "Last name : " << cur->prf.lastname << endl;
		cout << "First name: " << cur->prf.firstname << endl;
		cout << "Day of birth: " << cur->prf.DOB << endl;
		cout << "Gender: " << cur->prf.gender << endl;
		cout << "SocialID: " << cur->prf.social_id << endl;
		cout << "----------------" << endl;
		cout << endl;
		cout << "1. Change Profile." << endl;
		cout << "0. Back to menu" << endl;

		cin >> choose;
	}
	if (choose == 1)
	{
		enterProfile(cur);
		cout << "Change Profile successfull !" << endl;
		ofstream fout;
		fout.open("AccountFile1.txt");
		saveAccountFile(fout, head);
		fout.close();
		viewProfile(acc,cur);
	}
	else if (choose==0) {
		Menu2(cur, head);
	}
}
//void changePassword(account*& head) {
//
//}
void Menu2(account*cur, account*&head) {
	int choose = 100;
	while (choose!=1&&choose!=2&&choose!=3&&choose!=4&&choose!=5) {
		cout << "1. View Profile" << endl;
		cout << "2. Change Password" << endl;
		cout << "3. MENU_STAFF" << endl;
		cout << "4. Log Out" << endl;
		cin >> choose;
	}
	switch (choose) {
	case 1:
		viewProfile(cur,head);
		break;
	case 2:
		//changePassword(head);
		break;
	case 3:
		menu_staff();
		break;
	case 4:
		Menu();
		break;
	}
}
void Menu() {
	int type = 100;
	account* head =NULL;
	while (true) {
		while (type != 1 && type != 2 && type != 0) {
			cout << "Staff or Student?" << endl;
			cout << "1.Staff" << endl;
			cout << "2.Student" << endl;
			cout << "0. Exit" << endl;
			cin >> type;
		}
		ifstream fin;fin.open("AccountFile1.txt");
		bool flag = isEmpty(fin);
		if (!flag) {
			loadAccountFile(fin, head);
		}
		fin.close();
		if (type == 1) {
			while (true) {
				//system("cls");
				int n; bool login = true;
				cout << "-------STAFF-------" << endl;
				cout << "1. Login" << endl;
				cout << "2. Register" << endl;
				cout << "0. Go back to main menu" << endl;

				cin >> n; if (n == 0) {
					type = -1;
					break;
				}
				switch (n) {
				case 1:
					if (flag)
						cout << "There is no available account. PLease create a new account" << endl;
					else
						loginView(head, 0);
					break;
				case 2:
					registerView(head, fin);
					system("pause");
					login = false;
					break;

				}
				if (!login) break;
			}
		}
		else if (type == 2) {
			while (true) {
				//	system("cls");
				int n;
				cout << "-------STUDENT-------" << endl;
				cout << "1. Login" << endl;
				cout << "0. Go back to main menu" << endl;
				cin >> n; if (n == 0) {
					type = -1;
					break;
				}
				switch (n) {
				case 1:
					loginView(head, 1);
					break;
				}
			}
		}
		else if (type == -1) continue;
		else if (type == 0) break;
	}
}