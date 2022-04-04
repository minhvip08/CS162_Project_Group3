#include "Header.h"
void show_semester(semester* s, int i)
{
	if (!s) return;
	show_semester(s->next, i - 1);
	cout << "Semester: " << i << endl;
	show_date(s->start_date); show_date(s->end_date);
	cout << "Number of course: " << s->num_course << endl;

	while (1) {
		int n;
		cout << "1. View course list" << endl;
		cout << "0. Go backward" << endl;
		cout << "You choose: "; cin >> n;

		if (n == 0) break;
		switch (n) {
		case 1: show_course(s->course_list, s->num_course); break;
		}
	}
}

void show_course(course* c, int i)
{
	if (!c) return;
	show_course(c->next, i - 1);
	cout << "Course ID: " << c->ID_course << endl;
	cout << "Course name: " << c->course_name << endl;
	cout << "Teacher name: " << c->teacher_name << endl;
	cout << "Number of credits: " << c->credits << endl;
	cout << "Current student(s): " << c->cur_student << endl;
	cout << "Session 1: " << endl; show_session(c->ses1);
	cout << "Session 2: " << endl; show_session(c->ses2);
}

void show_ID_course(course* c) {
	if (!c) return;
	show_ID_course(c->next);
	cout << endl << "Course ID: " << c->ID_course << endl << "Name Course: " << c->course_name << endl;
}

void show_enrolled_course(enrolledCourse* c) {
	if (!c) return;
	show_enrolled_course(c->next);
	cout << endl << "Course ID: " << c->id_course << endl << "Name Course: " << c->course_name << endl;
}


void show_session(session s) // OK 
{
	cout << "Day: " << s.date << endl;
	cout << "Time: " << s.time << endl;
}

void show_class(Class* head, int i) //OK
{
	if (!head) return;
	show_class(head->nextClass, i - 1);
	cout << "Class number: " << i << endl;
	cout << "Class name: " << head->class_name << endl;
	cout << "Number of current students: " << head->total_student << endl;
	cout << "Start day: " << endl; show_date(head->start_date);
	cout << "End day: " << endl; show_date(head->end_day);
}

void show_date(date s) // OK
{
	cout << "Date: " << setfill('0') << setw(2) << s.day;
	cout << '/' << setfill('0') << setw(2) << s.month << '/' << s.year << endl;
}

void show_schoolyear(schoolyear* head)
{
	while (1) {
		schoolyear* tmp = head; cout << "List of schoolyear: " << endl; int i = 1;
		while (tmp) {
			cout << i << ". " << tmp->time << '\t'; ++i;
			tmp = tmp->next_schyear;
		} cout << endl;
		cout << "Go back to main Menu, press 0; else press 1 to continue";
		int k; cin >> k;
		if (k == 0) break;

		cout << "Which schoolyear you want to view information: "; int x; cin >> x;
		schoolyear* check = head;
		if (x > 1) {
			int j = 1; while (j < x) { check = check->next_schyear; ++j; }
		}

		while (1) {
			cout << "1. View list of semesters" << endl;
			cout << "2. View list of classes" << endl;
			cout << "0. Back to School Year Menu" << endl;

			int choice; cout << "You choose: "; cin >> choice;
			if (choice == 0) break;
			switch (choice) {
			case 1: show_semester(check->sem, check->num_sem); break;
			case 2: show_class(check->list_class, check->num_class); break;
				//case 0: break; 
			}
		}
	}



}

void menu_staff()
{
	int n; cout << "WELCOME" << endl;
	cout << "1. Creat new schoolyear" << endl;
	cout << "2. Create new semester to current schoolyear" << endl;
	cout << "3. Add course to semester" << endl;
	cout << "4. Add class to this schoolyear " << endl;
	cout << "0. Exit" << endl;
	cout << "Choose your choice: "; cin >> n;

	schoolyear* sy = NULL;

	while (1) {
		if (n == 0) break;
		else {
			switch (n) {
			case 1: create_schoolyear(sy); break;
			case 2: create_semester(sy); break;
			case 3: create_course(sy); break;
			case 4: create_class(sy); break;
			}
		}
		cout << "Choose your choice: "; cin >> n;
	}

	system("cls");

	while (1) {
		int choice;
		cout << "1. View list schoolyear" << endl;
		cout << "0. Exit" << endl;
		cout << "Choose your choice: "; cin >> choice;

		switch (choice) {
		case 1: show_schoolyear(sy); break;
		case 0: return;
		}
	}
}

void viewListEnrolledCourse(student* pS) {
	enrolledCourse* pECCur = pS->list_enrolled;
	if (pECCur == nullptr) {
		cout << "You haven't enrolled any course yet! ";
		cout << "\nPress any key to continue....";
		char a = _getch();
	}

	cout << "ID Course  " << "Course's Name  " << "Teacher's Name  " << "Credits  " << "Session 1  " << "Session 2  ";

	while (pECCur != nullptr) {
		cout << pECCur->id_course << "  " << pECCur->course_name << "  " << pECCur->name_teacher << "  "
			<< pECCur->credits << "  " << pECCur->ses1.date << "-" << pECCur->ses1.time << "  " << pECCur->ses2.date << "-" << pECCur->ses2.time;
		pECCur = pECCur->next;
	}

}
