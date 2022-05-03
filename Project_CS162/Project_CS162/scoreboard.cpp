#include "header.h"
#include "Scoreboard.h"
#include "Data.h"
#include "Support.h"
#include"Login.h"
int conditionGPA(float m)
{
	if (m >= 8.5 && m <= 10) return 4;
	else if (m < 8.5 && m >= 6.5) return 3;
	else if (m < 6.5 && m >= 4) return 2;
	else return 1;
}

void gpaOfClass(schoolyear* head)
{
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
	readStudent1Class(ctmp->class_name, ctmp);
	if (!read) {
		cout << "Please choose another class to view";
		return;
	}
	else {
		student* stu = ctmp->student_list;
		int sem = currentSemester();
		int z = 0;
		while (stu) {
			++z;
			cout << "***********STUDENT NUMBER: " << z << "**********\n";
			cout << "\t* Name: " << stu->prf.lastname + ' ' + stu->prf.firstname << endl;
			cout << "\t* Course enrolled: \n"; int b = 1;
			readListEnrolled(check->time, stu, sem);
			enrolledCourse* ec = stu->list_enrolled;
			float gpa = 0; float cred = 0;
			while (ec) {
				cout << "\t\t* Course number: " << b << endl;
				cout << "\t\t* Course name: " << ec->course_name << endl;
				cout << "\t\t* Course ID: " << ec->id_course << endl;
				cout << "\t\t\tOther\tMid\tFinal\tTotal:\n";
				cout << "\t\t\t" << ec->ecscore.other << '\t' << ec->ecscore.mid << '\t' << ec->ecscore.final << '\t' << ec->ecscore.total << endl;
				gpa += conditionGPA(ec->ecscore.total) * ec->credits;
				cred += ec->credits;
				++b;
				ec = ec->next;
			}
			float end = gpa / cred;
			cout << "\t* Total GPA in semester " << sem << ": " << end << endl;
			float gpaf = 0; float credf = 0;
			for (int i = 1; i <= 3; i++) {
				readListEnrolled(check->time, stu, i);
				enrolledCourse* ecf = stu->list_enrolled;
				while (ecf) {
					gpaf += conditionGPA(ecf->ecscore.total) * ecf->credits;
					credf += ecf->credits;
					ecf = ecf->next;
				}
			}
			float endf = gpaf / credf;
			cout << "\t* Total GPA of schoolyear: " << endf << endl;
			stu = stu->pNext;
		}
	}
}

void view_scoreboard_sem(student* stu)
{
	schoolyear* head = nullptr;
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
	cout << "Which schoolyear you want to view information? "; int x; cin >> x;
	while (x > i) {
		cout << "You input wrong number. PLease input again: "; cin >> x;
	}
	schoolyear* check = head;
	if (x > 1) {
		int j = 1; while (j < x) { check = check->next_schyear; ++j; }
	}
	readSemester(check->sem, check->time);
	if (!check->sem) {
		cout << "You haven't add a semester for this schoolyear" << endl;
		return;
	}

	cout << "There are currently " << check->num_sem << " semesters in this schoolyear." << endl;
	cout << "Which semester you want to add course? "; int k; cin >> k;
	while (k > check->num_sem) {
		cout << "Invalid number, please input again: "; cin >> k;
	}
	semester* s_check = check->sem;
	if (k != check->num_sem) {
		int h = 1; while (h < k) { s_check = s_check->next; ++h; }
	}
	readListEnrolled(check->time, stu, k);
	cout << "*********Semester " << k << "********\n";
	cout << "\t* Courses: \n";
	enrolledCourse* ec = stu->list_enrolled;
	float gpa = 0; float cred = 0; int b = 0;
	while (ec) {
		++b;
		cout << "\t\t* Course number: " << b << endl;
		cout << "\t\t* Name: " << ec->course_name << endl;
		cout << "\t\t* ID: " << ec->id_course << endl;
		cout << "\t\t* Teacher: " << ec->name_teacher << endl;
		cout << "\t\t* Credits: " << ec->credits << endl;
		cout << "\t\t* Mark: \n";
		cout << "\t\t\tOther\tMid\tFinal\tTotal\n";
		cout << "\t\t\t" << ec->ecscore.other << '\t' << ec->ecscore.mid << '\t' << ec->ecscore.final << '\t' << ec->ecscore.total << '\n';
		gpa += conditionGPA(ec->ecscore.total) * ec->credits;
		cred += ec->credits;
		ec = ec->next;
	}
	float end = gpa / cred;
	cout << "\t* Total GPA in semester " << k << ": " << end << endl;

	float gpaf = 0; float credf = 0;
	for (int i = 1; i <= 3; i++) {
		readListEnrolled(check->time, stu, i);
		enrolledCourse* ecf = stu->list_enrolled;
		while (ecf) {
			gpaf += conditionGPA(ecf->ecscore.total) * ecf->credits;
			credf += ecf->credits;
			ecf = ecf->next;
		}
	}
	float endf = gpaf / credf;
	cout << "\t* Total GPA of schoolyear: " << endf << endl;
}

void Scoreboard_staff(schoolyear* head)
{
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
	cout << "Which schoolyear you want to view information? "; int x; cin >> x;
	while (x > i) {
		cout << "You input wrong number. PLease input again: "; cin >> x;
	}
	schoolyear* check = head;
	if (x > 1) {
		int j = 1; while (j < x) { check = check->next_schyear; ++j; }
	}
	readSemester(check->sem, check->time);
	if (!check->sem) {
		cout << "You haven't add a semester for this schoolyear" << endl;
		return;
	}

	cout << "There are currently " << check->num_sem << " semesters in this schoolyear." << endl;
	cout << "Which semester you want to view course? "; int k; cin >> k;
	while (k > check->num_sem) {
		cout << "Invalid number, please input again: "; cin >> k;
	}
	semester* s_check = check->sem;
	if (k != check->num_sem) {
		int h = k; while (h < check->num_sem) { s_check = s_check->next; ++h; }
	}
	readListOfCourse(check->time, s_check->course_list, s_check->mark);
	course* c = s_check->course_list;
	while (c) {
		importscoreboardcourse(c);
		print(c);
		c = c->next;
	}
}