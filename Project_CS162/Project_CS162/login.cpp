#include "header.h"

bool login(account* head, account* &result)
{
	account* result = nullptr;
	account* cur = head;
	if (!head)
	{
		return false;
	}
	cout << "\nEnter username: ";
	cin.ignore(1000, '\n');
	string username, pass;
	getline(cin, username);
	while (true)
	{
		cout << "\033[2J\033[1;1H";
		cout << "Enter username: ";
		getline(cin, username);
		account* cur = head;
		while (cur)
		{
			if (username == head->username)
			{
				pass == head->password;
				break;
			}
			cur = cur->pnext;

		}
		cout << "Wrong username";
		system("pause");
		 // cout << "\033[2J\033[1;1H";
		while (true)
		{
			int x;
			cout << "Type:\n1. Reinput.\n2. Sign up.";
			if (x == 1)
			{
				// getline(cin, username);
				break;
			}
			else if (x == 2) {
				// call sign-up function
				return true;
			}
		}

	}
	while (true)
	{
		int k = 5;
		string password;
		getline(cin, password);
		if (password == cur->password)
		{
			cout << "\nSuccess.";
			result = cur;
			system("pause");
			return true;
		}
		else
		{
			k--;
			cout << "\nWrong password.";
			cout << "\nPlease enter the password again.\nYou have " << k <<" times left";
		}
		if (k == 0)
			return false;


	}


}