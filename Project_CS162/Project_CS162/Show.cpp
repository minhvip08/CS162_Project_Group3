#include "header.h"
#include "OutputConsole.h"
#include "Data.h"
#include "Input.h"
#include "Support.h"
#include "Deallocate_graphic.h"
#include "Menu.h"
#include "Login.h"
#include "Scoreboard.h"

void show_course(schoolyear* head)
{
	readSchoolyear(head);
	if (!head) {
		cout << "You haven't added a new schoolyear" << endl;
		return;
	}

	schoolyear* tmp = head; cout << "List of schoolyear: " << endl; int i = 0;
	while (tmp) {
		++i;
		cout << i << ". " << tmp->time << '\t';
		tmp = tmp->next_schyear;
	} cout << endl;

	cout << "Which schoolyear you want to view semester? "; int x; cin >> x;
	while (x > i) {
		cout << "You input a wrong number. PLease input again: "; cin >> x;
	}
	schoolyear* check = head;
	if (x > 1) {
		int j = 1;
		while (j < x) {
			check = check->next_schyear;
			++j;
		}
	}
	if (check->num_sem == 0) {
		cout << "There is no semester added in this schoolyear\n";
		return;
	}
	else
		readSemester(check->sem, check->time);
	semester* s_tmp = check->sem;
	cout << "There are currently " << check->num_sem << " semesters in this schoolyear" << endl;
	cout << "Which semester you want to view it's information: "; cin >> x;
	if (x != check->num_sem) {
		int h = x; while (h < check->num_sem) { s_tmp = s_tmp->next; ++h; }
	}
	if (s_tmp->num_course == 0) {
		cout << "There is no course added in this semester\n";
		return;
	}
	else
		readListOfCourse(check->time, s_tmp->course_list, x);
	cout << "LIST OF COURSES: \n";
	course* c = s_tmp->course_list; int e = 0; 
	while (c) {
		++e; 
		cout << "********** COURSE NUMBER: " << e << " **********" << endl;
		cout << "\t* Course ID: " << c->ID_course << endl;
		cout << "\t* Course name: " << c->course_name << endl;
		cout << "\t* Teacher name: " << c->teacher_name << endl;
		cout << "\t* Number of credits: " << c->credits << endl;
		cout << "\t* Current student(s): " << c->cur_student << endl;
		cout << "\t* Session 1: \n\t\t"; show_session(c->ses1);
		cout << "\t* Session 2: \n\t\t"; show_session(c->ses2);
		c = c->next;
		if(!c) cout << "********************************************\n";
	}
}

void show_session(session s) 
{
	cout << "Day: " << s.date << '\t';
	cout << "Time: " << s.time << endl;
}

void show_class(schoolyear* head)
{
	readSchoolyear(head);
	if (!head) {
		cout << "You haven't create new schoolyear" << endl;
		return;
	}

	schoolyear* tmp = head; cout << "List of schoolyear: " << endl; int i = 1;
	while (tmp) {
		cout << i << ". " << tmp->time << '\t'; ++i;
		tmp = tmp->next_schyear;
	} cout << endl;
	cout << "Which schoolyear you want to view class? "; int x; cin >> x;
	schoolyear* check = head;
	if (x > 1) {
		int j = 1; while (j < x) { check = check->next_schyear; ++j; }
	}
	readListOfClass(check->list_class, check->time);
	Class* cl = check->list_class;
	i = 0;
	while (cl) {
		++i;
		cout << "Class number: " << i << endl;
		cout << "Class name: " << cl->class_name << endl;
		cout << "Number of students: " << cl->total_student << endl;
		cl = cl->nextClass;
	}
}

void show_date(date s) 
{
	cout << "Date: " << setfill('0') << setw(2) << s.day;
	cout << '/' << setfill('0') << setw(2) << s.month << '/' << s.year << endl;
}

void showListEnrolledCourse(student* pS) {
	// choose schoolyear
	schoolyear* sy = new schoolyear;
	readSchoolyear(sy);
	int i = 0; schoolyear* tmpsch = sy; cout << "List of schoolyear: " << endl;
	while (tmpsch) {
		++i;
		cout << i << '.' << tmpsch->time << endl;
		tmpsch = tmpsch->next_schyear;
	}
	cout << "Which schoolyear you want to view your courses: "; int x; cin >> x;
	while (x > i) {
		cout << "invalid schoolyear" << endl << "input again" << endl;
		cin >> x;
	}

	schoolyear* check = sy;
	if (x > 1) {
		int j = 1; while (j < x) { check = check->next_schyear; ++j; }
	}

	// choose semester
	cout << "There are " << check->num_sem << " semesters in this schoolyear" << endl;
	cout << "Which semester you want to view your courses: ";
	int xx; cin >> xx; semester* s_tmp = new semester;
	while (xx > check->num_sem) {
		cout << "Invalid number!!" << endl << "Please input again: "; cin >> xx;
	}

	readListEnrolled(check->time, pS, xx);

	enrolledCourse* cur = pS->list_enrolled;
	if (cur == nullptr) {
		cout << "\nPress any key to continue....";
		char a = _getch();
		return;
	}

	int j = 0;
	while (cur != nullptr) {
		++j;
		cout << "******COURSE NUMBER: " << j << "******\n";
		cout << "  * ID: " << cur->id_course << endl;
		cout << "  * Course name: " << cur->id_course << endl;
		cout << "  * Teacher's name: " << cur->name_teacher << endl;
		cout << "  * Credits: " << cur->credits << endl;
		cout << "  * Session 1: " << cur->ses1.date << '\t' << cur->ses1.time << endl;
		cout << "  * Session 2: " << cur->ses2.date << '\t' << cur->ses2.time << endl;
		cur = cur->next;
	}
}

void showStudentsInClass(schoolyear* head) {
	readSchoolyear(head);
	if (!head) {
		cout << "You haven't create new schoolyear" << endl;
		return;
	}

	schoolyear* tmp = head; cout << "List of schoolyear: " << endl; int i = 1;
	while (tmp) {
		cout << i << ". " << tmp->time << '\t'; ++i;
		tmp = tmp->next_schyear;
	} cout << endl;
	cout << "Which schoolyear you want to view class? "; int x; cin >> x;
	schoolyear* check = head;
	if (x > 1) {
		int j = 1; while (j < x) { check = check->next_schyear; ++j; }
	}
	readListOfClass(check->list_class, check->time);
	cout << "List of class: " << endl;
	Class* cl = check->list_class; int a = 1;
	while (cl) {
		cout << a << ". " << cl->class_name << endl; ++a;
		cl = cl->nextClass;
	}
	cout << "Which class you want to view information: "; int t; cin >> t;
	Class* ctmp = check->list_class;
	if (t > 1) {
		int j = 1; while (j < t) { ctmp = ctmp->nextClass; ++j; }
	}
	Class* read = new Class;
	readStudent1Class(ctmp->class_name, read);
	if (!read) {
		cout << "Please choose another class to view"<<endl;
		return;
	}
	else {
		student* pStudentHead = read->student_list; int b = 1;

		cout << "No\tID\t\tName\t\t\t\tBirthday\tGender\t\tSocial ID\n";
		while (pStudentHead) {
			cout << b << '\t';
			string fullname = pStudentHead->prf.lastname + ' ' + pStudentHead->prf.firstname;
			cout << pStudentHead->id << '\t' << fullname << '\t' << ((fullname.length() < 16) ? '\t' : ' ') << '\t' << pStudentHead->prf.DOB << "\t\t" << pStudentHead->prf.gender << "\t" << pStudentHead->prf.social_id << "\n";
			++b;
			pStudentHead = pStudentHead->pNext;
		}
	}
}

void showStudentsInCourse(schoolyear* head) {
	readSchoolyear(head);
	if (!head) {
		cout << "You haven't input a schoolyear" << endl;
		return;
	}

	schoolyear* tmp = head; cout << "List of schoolyear: " << endl; int i = 1;
	while (tmp) {
		cout << i << ". " << tmp->time << '\t'; ++i;
		tmp = tmp->next_schyear;
	} cout << endl;
	cout << "Which schoolyear you want to view semester? "; int x; cin >> x;
	schoolyear* check = head;
	if (x > 1) {
		int j = 1; while (j < x) { check = check->next_schyear; ++j; }
	}
	if (check->num_sem == 0) {
		cout << "You haven't add a semester for this schoolyear" << endl;
		return;
	}
	else
		readSemester(check->sem, check->time);

	cout << "There are currently " << check->num_sem << " semesters in this schoolyear." << endl;
	cout << "Which semester you want to view course? "; int k; cin >> k;
	semester* s_check = check->sem;
	if (k != check->num_sem) {
		int h = k; while (h < check->num_sem) { s_check = s_check->next; ++h; }
	}
	if (s_check->num_course == 0) {
		cout << "There is no course added in this semester\n";
		return;
	}
	else
		readListOfCourse(check->time, s_check->course_list, k);
	course* ctmp = s_check->course_list; i = 0;
	cout << "List of course: \n";
	while (ctmp) {
		++i;
		cout << i << ".ID: " << ctmp->ID_course << '\t' << "Course name: " << ctmp->course_name << endl;
		ctmp = ctmp->next;
	}
	cout << "0. Exit" << endl;
	cout << "Please choose the number represented the course (1,2,3, ... ): "; cin >> x;
	while (x > i) {
		cout << "Invalid number!!" << endl << "Please input again: "; cin >> x;
	}
	if (x == 0) return;
	course* cur = s_check->course_list;
	if (x > 1) {
		int h = 1; while (h < x) {
			cur = cur->next; ++h;
		}
	}
	readStudentOfCourse(cur);
	studentScore* pStuCrs = cur->list_score;
	if (!pStuCrs) {
		cout << "No student enrolled in this course\n";
		return;
	}
	else
		cout << "No\tID\t\tName\n";
	int b = 0;
	while (pStuCrs != nullptr) {
		++b;
		cout << b << "\t";
		cout << pStuCrs->id << "\t";
		cout << pStuCrs->name << "\n";
		pStuCrs = pStuCrs->pNext;
	}
}

