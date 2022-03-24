
#include "header.h"
void registerView(account& acc, account*&head) {
	bool flag = false;
	string repassword;
	cout << "Enter your username: ";
	cin >> acc.username;
	do
	{
		flag = true;
		cout << "Enter password: ";
		cin >> acc.password;
		cout << "Enter password again: ";
		cin >> repassword;
		if (acc.password != repassword) {
			cout << "Not alike" << endl;
			flag = false;
		}
	} while (!flag);

	if (checkAccountModel(acc, head)) {
		cout << "Username or password exist" << endl;
		registerView(acc, head);
	}
	else {
		registerModel(acc, head);
		cout << "Username and password approved" << endl;
		cout << "Register Successful !";
		ofstream fout;
		fout.open("AccountFile.txt");
		if (!fout.is_open())
		{
			cout << "Can not open file" << endl;
		}
		else
		{
			saveAccountFile(fout, head);
		}
		fout.close();
	}

}
void loginView(account& acc, account* head) {
	cout << "Enter your username: ";
	cin >> acc.username;
	cout << "Enter your password: ";
	cin >> acc.password;

	if (checkAccountModel(acc, head)) {
		cout << "Register successful!";
	}
	else {
		int choose = 0;
		while (choose != 1 && choose != 2) {
			cout << "Wrong username or password" << endl;
			cout << "1.Login again" << endl;
			cout << "2.Register" << endl;
			cin >> choose;
		}
		if (choose == 1)
		{
			loginView(acc, head);
		}
		else if (choose == 2) {
			registerView(acc, head);
		}
	}
}

void Menu() {
	int type = 0;
	account acc;
	account* head =NULL;
	while (type != 1 && type != 2) {
		cout << "Staff or Student?" << endl;
		cout << "1.Staff" << endl;
		cout << "2.Student" << endl;
		cin >> type;
	}
	if (type == 1) {
		//acc.type="Staff";
		cout << "Staff" << endl;
	}
	else if (type == 2) {
		//acc.type="Student";
		cout << "Student" << endl;
	}
	type = 0;
	while (type != 1 && type != 2) {
		cout << "1.Login" << endl;
		cout << "2.Register" << endl;
		cin >> type;
	}
	ifstream fin;
	fin.open("AccountFile.txt");
	if (!fin.is_open())
	{
		cout << "Can not open file" << endl;
	}
	else
	{
		loadAccountFile(fin, head);
	}
	fin.close();
	if (type == 1) {
		loginView(acc, head);
	}
	else if (type == 2) {
		registerView(acc, head);
	}
}