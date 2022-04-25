#include "header.h"
#include "Support.h"
#include "Data.h"
#include "Input.h"
#include "Menu.h"
#include "Scoreboard.h"
#include "Deallocate_graphic.h"
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
	//Delete_schoolyear(sy);
}
void printlistclass(Class* c, int x)
{
	if (!c)
		return;
	printlistclass(c->nextClass, x + 1);
	cout << "\n" << x << ". " << c->class_name;
}
void exportstulist_menu(schoolyear* scy) // chay lai
{
	readSchoolyear(scy); 
	while (scy) {
		if (checkCurrentSchoolyear(scy)) break; 
		scy = scy->next_schyear; 
	}
	if (!scy) return;
	readSemester(scy->sem, scy->time); 
	int sem = currentSemester();
	semester* s = scy->sem; 
	while (s) {
		if (s->mark == sem) break; 
		s = s->next; 
	}
	cout << "List of course:" << endl; readListOfCourse(scy->time, s->course_list, sem);
	int i = 0;  
	course* tmp = s->course_list; 
	while (tmp) {
		++i; 
		cout << i << ". Course ID: " << tmp->ID_course << '\t' << "Course name: " << tmp->course_name << endl; 
		tmp = tmp->next; 
	}	cout << "0. Exit" << endl;
	cout << "Please choose the number represented the course(1, 2, 3, ...) : "; int x; cin >> x;
		while (x > i) {
			cout << "Invalid number!!" << endl << "Please input again: "; cin >> x;
		}
	if (x == 0) return;
	course* cur = s->course_list;
	if (x > 1) {
		int h = 1; while (h < x) {
			cur = cur->next; ++h;
		}
	}
	exportlistofstudent(cur);
	cout << "Export successfully" << endl;
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
	readSchoolyear(scy);
	while (scy) {
		if (checkCurrentSchoolyear(scy)) break;
		scy = scy->next_schyear;
	}
	if (!scy) return;
	readSemester(scy->sem, scy->time);
	int sem = currentSemester();
	semester* s = scy->sem;
	while (s) {
		if (s->mark == sem) break;
		s = s->next;
	}
	cout << "List of course:" << endl; readListOfCourse(scy->time, s->course_list, sem);
	int i = 0;
	course* tmp = s->course_list;
	while (tmp) {
		++i;
		cout << i << ". Course ID: " << tmp->ID_course << '\t' << "Course name: " << tmp->course_name << endl;
		tmp = tmp->next;
	}	cout << "0. Exit" << endl;
	cout << "Please choose the number represented the course(1, 2, 3, ...) : "; int x; cin >> x;
	while (x > i) {
		cout << "Invalid number!!" << endl << "Please input again: "; cin >> x;
	}
	if (x == 0) return;
	course* cur = s->course_list;
	if (x > 1) {
		int h = 1; while (h < x) {
			cur = cur->next; ++h;
		}
	}
	importscoretoCourse(cur);
	cout << "Import successfully" << endl;
}
void updatestures_menu(schoolyear* sy)
{
	readSchoolyear(sy);
	while (sy) {
		if (checkCurrentSchoolyear(sy)) break;
		sy = sy->next_schyear;
	}
	if (!sy) return;
	readSemester(sy->sem, sy->time);
	int sem = currentSemester();
	semester* s = sy->sem;
	while (s) {
		if (s->mark == sem) break;
		s = s->next;
	}
	cout << "List of course:" << endl; readListOfCourse(sy->time, s->course_list, sem);
	int i = 0;
	course* tmp = s->course_list;
	while (tmp) {
		++i;
		cout << i << ". Course ID: " << tmp->ID_course << '\t' << "Course name: " << tmp->course_name << endl;
		tmp = tmp->next;
	}	cout << "0. Exit" << endl;
	cout << "Please choose the number represented the course(1, 2, 3, ...) : "; int x; cin >> x;
	while (x > i) {
		cout << "Invalid number!!" << endl << "Please input again: "; cin >> x;
	}
	if (x == 0) return;
	course* cur = s->course_list;
	if (x > 1) {
		int h = 1; while (h < x) {
			cur = cur->next; ++h;
		}
	}
	viewscoreboardcourse(cur); 
	cout << "Enter student's number you want to update his/her score: "; int x; cin >> x;
	studentScore* stu = cur->list_score; 
	while (stu) {
		if (stu->no == x) break;
		else
			stu = stu->pNext; 
	}
	if (!stu) {
		cout << "Can't find student!!!" << endl;
		return; 
	}
	while (1) {
		cout << "Which score you want to update: " << endl;
		cout << "1. Update other score." << endl;
		cout << "2. Update midterm score." << endl;
		cout << "3. Update final score." << endl;
		cout << "0. Exit." << endl;
		int choice; cout << "Your option: "; cin >> choice;
		if (choice == 0) return;
		else if (choice > 3) {
			cout << "You input wrong number!!!\nPLease input again: "; cin >> choice; 
		}
		switch (choice) {
		case 1: {
			float other; cout << "New other score: "; cin >> other;
			stu->stscore.other = other; 
			break; 
		}
		case 2: {
			float mid; cout << "New midterm score: "; cin >> mid; 
			stu->stscore.mid = mid; 
			break;
		}
		case 3: {
			float final; cout << "New final score: "; cin >> final; 
			stu->stscore.final = final; 
			break;
		}
		}
		float total = stu->stscore.other * 0.3 + stu->stscore.mid * 0.3 + stu->stscore.final * 0.4; 
		cout << "New total score: " << total << endl;
		stu->stscore.total = total; 
	}
	saveScoreboardCSV(cur);
}

void saveScoreboardCSV(course* c) {
	if (!c || !c->list_score) {
		cout << "Empty data\n"; return; 
	}
	studentScore* stu = c->list_score;
	ofstream fout; fout.open(c->ID_course + ".csv"); 
	fout << "No,ID,Name,Other,Mid,Final,Total\n"; 
	while (stu) {
		fout << stu->no << ',';
		fout << stu->id << ',';
		fout << stu->name << ','; 
		fout << stu->stscore.other << ','; 
		fout << stu->stscore.mid << ',';
		fout << stu->stscore.final << ',';
		fout << stu->stscore.total << '\n';
		stu = stu->pNext; 
	}
	fout.close(); 
}

void viewscoboardofc_menu(schoolyear* sy)
{
	readSchoolyear(sy);
	while (sy) {
		if (checkCurrentSchoolyear(sy)) break;
		sy = sy->next_schyear;
	}
	if (!sy) return;
	readSemester(sy->sem, sy->time);
	int sem = currentSemester();
	semester* s = sy->sem;
	while (s) {
		if (s->mark == sem) break;
		s = s->next;
	}
	cout << "List of course:" << endl; readListOfCourse(sy->time, s->course_list, sem);
	int i = 0;
	course* tmp = s->course_list;
	while (tmp) {
		++i;
		cout << i << ". Course ID: " << tmp->ID_course << '\t' << "Course name: " << tmp->course_name << endl;
		tmp = tmp->next;
	}	cout << "0. Exit" << endl;
	cout << "Please choose the number represented the course(1, 2, 3, ...) : "; int x; cin >> x;
	while (x > i) {
		cout << "Invalid number!!" << endl << "Please input again: "; cin >> x;
	}
	if (x == 0) return;
	course* cur = s->course_list;
	if (x > 1) {
		int h = 1; while (h < x) {
			cur = cur->next; ++h;
		}
	}
	viewscoreboardcourse(cur);
}