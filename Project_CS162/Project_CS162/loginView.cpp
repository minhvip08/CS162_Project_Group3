#include "header.h"
#include "Support.h"
#include "Login.h"
#include "Menu.h"
#include"design.h"
#include<chrono>
#include <tchar.h>
#include <thread>
void loginDraw(short opt, int type) {
	short opt_ = opt;
	SetColor(4);
	gotoxy(47, 7);
	string str;
	if (type == 0) {
		str = " STAFF";
	}
	else if (type == 1) {
		str = " STUDENT";
	}
	cout << "WELCOME " << str;
	setColorBGTextXY(50, 8, 15, ((opt_ == 1) ? 2 : 0), "  LOGIN  ");
	if (type == 0) {
		setColorBGTextXY(50, 9, 15, ((opt_ == 2) ? 3 : 0), " SIGN UP ");
	}
	setColorBGTextXY(50, 10-type, 15, ((opt_ == 3-type) ? 4 : 0), "  EXIT   ");
	SetBGColor(16);
}
void menuDraw(short opt) {
	short opt_ = opt;
	setColorBGTextXY(50, 8, 15, ((opt_ == 1) ? 2 : 0), "  STAFF  ");
	setColorBGTextXY(50, 9, 15, ((opt_ == 2) ? 3 : 0), " STUDENT ");
	setColorBGTextXY(50, 10, 15, ((opt_ == 3) ? 4 : 0), "  EXIT   ");
	SetBGColor(16);
}
string headline() {
	string hl;
	return hl = R"(  
   ___     _____                       ___           _    __           __  _             ____        __          
  / _ |   / ___/__  __ ____________   / _ \___ ___ _(_)__/ /________ _/ /_(_)__  ___    / __/_ _____/ /____ __ _ 
 / __ |  / /__/ _ \/ // / __(_-< -_) / , _/ -_) _ `/ (_-< __/ __/ _ `/ __/ / _ \/ _ \  _\ \/ // (_-< __/ -_)  ' \
/_/ |_|  \___/\___/\_,_/_/ /___|__/ /_/|_|\__/\_, /_/___|__/_/  \_,_/\__/_/\___/_//_/ /___/\_, /___|__/\__/_/_/_/
                                             /___/                                        /___/                    
    )";
}
void loginMenu(account*& head, int type) {
	int opt = 1;
	int y = 7;
	int row = 0;
	while (true) {
		ifstream fin;
		if (type == 0) {
			row = 3;
			fin.open("Staff_acc.txt");
		}
		else if (type == 1) {
			row = 2;
			fin.open("Student_acc.txt");
		}
		bool flag = isEmpty(fin);
		if (!flag) {
			loadAccountFile(fin, head);
		}
		fin.close();

		char keyBoard = {};
		string art = headline();
		//while(true) {
			//clrscr();
			system("cls");
			SetColor(rand() % 14 + 1);
			cout << art << endl;

			SetColor(15);
			loginDraw(opt, type);
			do {
				ShowConsoleCursor(false);
				keyBoard = _getch();
				switch (keyBoard) {
				case KEY_DOWN:
					if (opt == row) {
						opt = 1;
						loginDraw(opt, type);
						y = 7;
					}
					else {
						opt++;
						y++;
						loginDraw(opt, type);
					}
					break;

				case KEY_UP:
					if (opt == 1) {
						opt = row;
						y = 10;
						loginDraw(opt, type);
					}
					else {
						opt--;
						y--;
						loginDraw(opt, type);
					}
					break;
				default:
					break;
				}
			} while (keyBoard != '\r');

			switch (opt) {
			case 1:
				if (flag) {
					if (type == 1) {
						cout << "\nThere is no available account. PLease wait for staff to create" << endl;
					}
					else if (type == 0) {
						cout << "\nThere is no available account. PLease create a new account" << endl;
					}
				}
				else
					loginView(head, type);
				break;
			case 2:
				if (type == 1) {
					return;
				}
				else {
					registerView(head);
					break;
				}
			case 3:
				head = NULL;
				return;
			}
			cout << endl;
			system("pause");
		//}
	}
}
void Intro() {
	account* head = NULL;
	srand((unsigned int)time(NULL));
	int opt = 1;
	int y = 7;
	char keyBoard = {};
	SetColor(15);
	string art = headline();

	clrscr();
	for (int i = 0; i < art.length(); i++) {
		cout << art[i];
		if (art[i] != ' ') {
			chrono::microseconds wait(10);
			this_thread::sleep_for(wait);
		}
	}
	do {
		clrscr();
		//system("cls");
		SetColor(rand() % 14 + 1);
		cout << art << endl;
		SetColor(15);
		menuDraw(opt);
		do {
			ShowConsoleCursor(false);
			keyBoard = _getch();
			switch (keyBoard) {
			case KEY_DOWN:
				if (opt == 3) {
					opt = 1;
					menuDraw(opt);
					y = 7;
				}
				else {
					opt++;
					y++;
					menuDraw(opt);
				}
				break;

			case KEY_UP:
				if (opt == 1) {
					opt = 3;
					y = 10;
					menuDraw(opt);
				}
				else {
					opt--;
					y--;
					menuDraw(opt);
				}
				break;
			default:
				break;
			}
		} while (keyBoard != '\r');
		switch (opt) {
		case 1:
			loginMenu(head, 0);
			break;
		case 2:
			loginMenu(head, 1);
			break;
		case 3:
			for (int i = 3; i > 0; i--) {
				ShowConsoleCursor(false);
				gotoxy(31, 14);
				cout << "Good bye! The program will exit in " << i << " seconds.\r";
				chrono::seconds duration(1);
				this_thread::sleep_for(duration);
			}
			gotoxy(31, 14);
			std::cout << "Good bye! The program will exit in 0 seconds.\n";
			ShowConsoleCursor(true);
			return;
		}
	} while (opt != 3);
}
//void moveChoice() {
//
//}

void registerView(account*& head) {
	system("cls");
	cout << headline() << endl;
	ShowConsoleCursor(true);
	bool flag = true;
	account* acc = new account;
	string repassword;
	/*SetColor(rand() % 14+1);
	gotoxy(40, 8);*/
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
	check = checkAccountModel(acc, head, 0, true);
	if (check) {
		cout << "Username exist" << endl;
		//	system("pause");
		return;
	}
	else {
		cout << "Username approved" << endl;
		enterProfile(acc, 0);

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
		fout.open("Staff_acc.txt");
		saveAccountFile(fout, head);
		fout.close();
	}
}
void loginView(account* &head, int type) 
{
	system("cls");
	cout << headline() << endl;
	ShowConsoleCursor(true);
	account* acc = new account;
	cout << "Enter username: "; cin >> acc->username;
	cout << "Enter your password: "; cin >> acc->password;

	if (checkAccountModel(acc, head, type, false)) {
		cout << "Login successful!" << endl;
		system("pause");
		Menu2(acc,head,type);
	}
	else {
		cout << "Username or password is incorrect" << endl;
		return;
	}
}

void enterProfile(account*& acc, int type)
{
	int gender = 0;
	acc->type=type;
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
	system("cls");
	account* cur = head;

	while (acc->username != cur->username) {
		cur = cur->pNext;
	}
	int choose = 100;
	SetColor(3);
	gotoxy(0,7);
	while (choose != 1 && choose != 0) {
		cout << "-----Profile-----" << endl;
		cout << "Last name : " << cur->prf.lastname << endl;
		cout << "First name: " << cur->prf.firstname << endl;
		cout << "Day of birth: " << cur->prf.DOB << endl;
		cout << "Gender: " << cur->prf.gender << endl;
		cout << "SocialID: " << cur->prf.social_id << endl;
		cout << "----------------" << endl;
		cout << "1. Change Profile." << endl;
		cout << "0. Back to menu" << endl;

		cin >> choose;
	}
	if (choose == 1)
	{
		enterProfile(cur,cur->type);
		cout << "Change Profile successfull !" << endl;
		system("pause");
		ofstream fout;
		if (cur->type == 1) {
			fout.open("Student_acc.txt");
		}
		else if(cur->type == 0) {
			fout.open("Staff_acc.txt");
		}
		saveAccountFile(fout, head);
		fout.close();
		viewProfile(acc,cur);
	}
	else if (choose==0) {
		Menu2(cur, head,cur->type);
	}
}
void changePassword(account* acc, account*& head)
{
	system("cls");
	SetColor(4);
	gotoxy(0,7);
	string pwd;
	cout << "Enter old password : ";
	cin >> pwd;
	while (pwd != acc->password)
	{
		cout << "Incorrect password! Try again!" << endl;
		cout << "Enter old password : ";
		cin >> pwd;
	}
	cout << "Enter new password: ";
	cin >> pwd;
	account* cur = head;
	while (cur != NULL)
	{
		if (acc->username==cur->username)
		{
			cur->password = pwd;
			break;
		}
		cur = cur->pNext;
	}
	cout << "Change password successfully!"<<endl;
	ofstream fout;
	if (cur->type == 1) {
		fout.open("Student_acc.txt");
	}
	else {
		fout.open("Staff_acc.txt");
	}
	
	saveAccountFile(fout, head);
	fout.close();
}
void moveChoice(int row, int y, int&opt) {
	char keyBoard = {};
	do
	{
		keyBoard = _getch();
		switch (keyBoard)
		{
		case KEY_DOWN:
			if (y + 1 != row+7)
			{
				y++;
				opt++;
				gotoxy(7, y + 1);
			}
			else
			{
				y -= (row-1);
				opt =1;
				gotoxy(7, y + 1);
			}
			break;
		case KEY_UP:
			if (y - 1 != 6)
			{
				y--;
				opt--;
				gotoxy(7, y + 1);
			}
			else
			{
				y += (row - 1);
				opt =row;
				gotoxy(7, y + 1);
			}
			break;
		default:
			break;
		}
	} while (keyBoard != '\r');
}
void Menu2(account*cur, account*&head, int type) {
	system("cls");
	int opt = 1;
	int row = 4;//rows of menu lines
	int y = 7;
	ShowConsoleCursor(true);
	SetColor(rand()%14+1);

	gotoxy(7, y+1);
	cout << "View Profile" << endl;
	SetColor(rand() % 14 + 1);
	gotoxy(7, y+2);
	cout << "Change Password" << endl;
	SetColor(rand() % 14 + 1);
	gotoxy(7, y+3);
	if (type == 0) {
		cout << "MENU_STAFF" << endl;
	}
	else if(type==1) {
		cout << "MENU_STUDENT" << endl;
	}
	SetColor(rand() % 14 + 1);
	gotoxy(7, y+4);
	cout << "Log Out" << endl;
	gotoxy(7, y + 1);
	moveChoice(row, y, opt);

	switch (opt) {
	case 1:
		viewProfile(cur,head);
		break;
	case 2:
		changePassword(cur,head);
		break;
	case 3:
		if (type == 0) {
			menu_staff();
		}
		else if (type == 1) {
			cout << "STU" << endl;
			//menu_student();
		}
		break;
	case 4:
		//Menu();
		break;
	}
}

//void Menu() {
//	int type = 100;
//	account* head =NULL;
//	while (true) {
//		while (type != 1 && type != 2 && type != 0) {
//			cout << "Staff or Student?" << endl;
//			cout << "1.Staff" << endl;
//			cout << "2.Student" << endl;
//			cout << "0. Exit" << endl;
//			cin >> type;
//		}
//		if (type == 1) {
//			ifstream fin; fin.open("Staff_acc.txt");
//			bool flag = isEmpty(fin);
//			if (!flag) {
//				loadAccountFile(fin, head);
//			}
//			fin.close();
//			while (true) {
//				system("cls");
//				int n; bool login = true;
//				cout << "-------STAFF-------" << endl;
//				cout << "1. Login" << endl;
//				cout << "2. Register" << endl;
//				cout << "0. Go back to main menu" << endl;
//
//				cin >> n;
//				if (n == 0) {
//					head = NULL;
//					type = -1;
//					break;
//				}
//				switch (n) {
//				case 1:
//					if (flag)
//						cout << "There is no available account. PLease create a new account" << endl;
//					else
//						loginView(head, 0);
//					break;
//				case 2:
//					registerView(head, fin);
//					system("pause");
//					login = false;
//					break;
//				}
//				if (!login) break;
//			}
//		}
//		else if (type == 2) {
//			ifstream fin; fin.open("Student_acc.txt");
//			bool flag = isEmpty(fin);
//			if (!flag) {
//				loadAccountFile(fin, head);
//			}
//			fin.close();
//			while (true) {
//				system("cls");
//				int n;
//				cout << "-------STUDENT-------" << endl;
//				cout << "1. Login" << endl;
//				cout << "0. Go back to main menu" << endl;
//				cin >> n;
//				if (n == 0) {
//					head = NULL;
//					type = -1;
//					break;
//				}
//				switch (n) {
//				case 1:
//					if (flag)
//						cout << "There is no available account. PLease wait for staff to create" << endl;
//					else
//						loginView(head, 1);
//					break;
//				}
//			}
//		}
//		else if (type == -1) continue;
//		else if (type == 0) break;
//	}
//}