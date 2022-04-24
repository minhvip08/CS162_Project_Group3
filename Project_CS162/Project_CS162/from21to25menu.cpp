#include "header.h"
#include "Support.h"
#include "Data.h"
#include "Input.h"
#include "Menu.h"
#include "Scoreboard.h"
bool checkdata(schoolyear* scy)
{
	if (!scy || !scy->sem || !scy->list_class)
		return false;
	return true;
}
void menu_staff2()
{
	//system("cls");
	while (1) {
		int n; cout << "WELCOME" << endl;
		cout << "1. Create new schoolyear" << endl;
		cout << "2. Create new semester to current schoolyear" << endl;
		cout << "3. Add course to semester" << endl;
		cout << "4. Add class to this schoolyear " << endl;
		cout << "5. Export a list of students in a course to a CSV file" << endl;
		cout << "6. Import the scoreboard of a course" << endl;
		cout << "7. View the scoreboard of a course" << endl;
		cout << "8. Update a student result" << endl;
		cout << "9. View the scoreboard of a class" << endl;
		cout << "0. Exit" << endl;
		cout << "Choose your choice: "; cin >> n;
		schoolyear* sy = NULL;
		if (n == 0) break;
		else {
			switch (n) {
			case 1:
				create_schoolyear(sy);
				break;
			case 2:
				create_semester(sy);
				break;
			case 3:
				create_course(sy);
				break;
			case 4:
				create_class(sy);
				break;
			case 5:
				exportstulist_menu(sy);
				break;
			case 6:
				importscoreboard_menu(sy);
				break;
			case 7:
				viewscoboardofc_menu(sy);
				break;
			case 8:
				updatestures_menu(sy);
				break;
			case 9:

				break;
			}
		}
	}
	system("cls");
	menu_view();
	Delete_schoolyear(sy);
}
void printlistclass(Class* c, int x)
{
	if (!c)
		return;
	printlistclass(c->nextClass, x + 1);
	cout << "\n" << x << ". " << c->class_name;
}
void exportstulist_menu(schoolyear* scy)
{
	if (!checkdata(scy))
	{
		cout << "Data is empty!";
		system("pause");
		menu_staff2();
	}

	int i = 0;
	cout << "List of classes:" << endl;
	string str;
	printlistclass(scy->list_class, 1);
	cout << "\n0. Exit" << endl;
	cout << "Enter name of the class you want to export list of students: ";
	c = scy->list_class;
	cin >> str;
	if (stoi(str) == 0)
		return;
	while (c)
	{
		if (str == c->class_name)
		{
			exportlistofstudent(c);
			//system("pause");
			menu_staff2();
			continue;
		}
	}
	cout << "Invalid input" << endl;
	cout << "Enter 1 to try again. Else to exit: ";
	string input;
	cin >> input;
	if (stoi(input) == 1)
	{
		//system("cls")
		exportstulist_menu(scy);
	}
	else
		menu_staff2();
}
void printcourse(course* c, int x)
{
	if (!c)
		return;
	printcourse(c->next, x + 1);
	cout << x << ". " << c->ID_course << " - " << c->course_name << endl;
}

void viewscoboardofcourse(schoolyear* scy)
{
	//system("cls");
	if (!checkdata(scy))
	{
		cout << "Data is empty!";
		system("pause");
		return;
	}
	course* c = scy->sem->course_list;
	cout << "List of courses:" << endl;
	printcourse(scy->sem->course_list, 1);
	cout << "\n0. Exit " << endl;
	cout << "Enter ID of course: ";
	string str;
	cin >> str;
	if (stoi(str) == 0)
	{
		menu_staff2();
	}
	else {
		while (c)
		{
			if (c->ID_course == str)
				viewscoreboardcourse(c);
			c = c->next;
		}
		if (!c)
		{
			cout << "Invalid input!" << endl;
			cout << "Press 1 to try again. 0 to exit";
			string s;
			if (stoi(s) == 1)
				viewscoboardofcourse(scy);
			else
				menu_staff2();
		}
	}
}
void importscoreboard_menu(schoolyear* scy)
{
	//system("cls");
	if (!checkdata(scy))
	{
		cout << "Data is empty!";
		system("pause");
		return;
	}
	course* c = scy->sem->course_list;
	cout << "List of courses:" << endl;
	printcourse(scy->sem->course_list, 1);
	cout << "\n0. Exit " << endl;
	cout << "Enter ID of course: ";
	string str;
	cin >> str;
	if (stoi(str) == 0)
	{
		menu_staff2();
	}
	else {
		while (c)
		{
			if (c->ID_course == str)
				importscoretoCourse(c);
			c = c->next;
		}
		if (!c)
		{
			cout << "Invalid input!" << endl;
			cout << "Press 1 to try again. 0 to exit";
			string s;
			if (stoi(s) == 1)
				importscoreboard_menu(scy);
			else
				menu_staff2();
		}
	}
}
void updatestures_menu(schoolyear* sy)
{
	if (!checkdata(sy))
	{
		cout << "Data is empty!";
		system("pause");
		menu_staff2();
	}
	printcourse(sy->sem->course_list, 1);
	cout << "Enter ID of the course you want to update student result: ";
	string courseid;
	cin >> courseid;
	course* c = sy->sem->course_list;
	while (c)
	{
		if (c->ID_course == courseid)
			break;
		c = c->next;
	}
	cout << "Enter the ID of the student you want to update result: ";
	string id;
	cin >> id;
	updateastudentscore(c, id);

}
void viewscoboardofc_menu(schoolyear* sy)
{
	printcourse(sy->sem->course_list, 1);
	cout << "Enter ID of course you want to view score board: ";
	string id;
	cin >> id;
	course* cur = sy->sem->course_list;
	while (cur)
	{
		if (id == cur->ID_course)
		{
			viewscoreboardcourse(cur);
			system("pause");
			menu_staff2();
			continue;
		}
		cur = cur->next;
	}
	cout << "Invalid input!" << endl;
	cout << "Enter 1 to try again, else to exit: ";
	string choose;
	cin >> choose;
	if (stoi(choose) == 1)
	{
		viewscoboardofc_menu(sy);
	}
	else
		menu_staff2();

}
//void viewscoallcour_menu(schoolyear* sy)
//{
//	if (!checkdata(sy))
//	{
//		cout << "Data is empty!";
//		system("pause");
//		return;
//	}
//	course* c = sy->sem->course_list;
//	while (c)
//	{
//		viewscoreboardcourse(c);
//		c = c->next;
//	}
//}