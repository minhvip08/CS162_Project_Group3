#include "Header.h"

void Delete_schoolyear(schoolyear*& head)
{
	if (!head) return; 
	while (head) {
		schoolyear* tmp = head->next_schyear;
		Delete_semester(head->sem);
		Delete_class(head->list_class);
		delete head;
		head = tmp;
	}
}

void Delete_semester(semester*& head)
{
	if (!head) return; 
	while (head) {
		semester* tmp = head->next;
		Delete_course(tmp->course_list);
		delete head;
		head = tmp;
	}
}

void Delete_course(course*& head)
{
	if (!head) return;
	while (head) {
		course* tmp = head->next;
		Delete_stdScore(head->list_score);
		delete head;
		head = tmp;
	}
}

void Delete_class(Class*& head)
{
	if (!head) return;
	while (head) {
		Class* tmp = head->nextClass;
		delete head;
		head = tmp;
	}
}

void Delete_stdScore(studentScore*& head)
{
	if (!head) return;
	while (head) {
		studentScore* tmp = head->pNext;
		delete head;
		head = tmp;
	}
}

void Delete_student(student*& head)
{
	if (!head) return;
	while (head) {
		// del enrolledCourse
		Delete_enrollCourse(head->list_enrolled);
		// del final GPA
		Delete_finalGPA(head->list_gpa);
		student* tmp = head->pNext;
		delete head;
		head = tmp;
	}
}

void Delete_enrollCourse(enrolledCourse*& head)
{
	if (!head) return;
	while (head) {
		Delete_stdScore(head->list_score);
		enrolledCourse* tmp = head->next;
		delete head;
		head = tmp;
	}
}

void Delete_finalGPA(finalGPA*& head)
{
	if (!head) return;
	while (head) {
		finalGPA* tmp = head->next;
		delete head;
		head = tmp;
	}
}

void Delete_enrolled_course(string time, student*& pS, int sem) {
	
	enrolledCourse* pECCrs = pS->list_enrolled, *pECCrsTemp = nullptr;

	//system("cls");
	if (pECCrs != nullptr) {
		cout << "You haven't enrolled any courses yet!";
		cout << "\n Press any key to back.... ";
		char a = _getch();
		return;
	}

	cout << "Please choose one of the course you want to delete\n";
	int i = 0; enrolledCourse* tmp = pS->list_enrolled;
	while (tmp) {
		++i;
		cout << i << ".ID Course: " << tmp->id_course << '\t' << "Course name: " << tmp->course_name << endl;
		tmp = tmp->next;
	} cout << "0. Exit" << endl;
	int x; cin >> x;
	while (x > i) {
		cout << "Invalid number!!" << endl << "Please input again: "; cin >> x;
	}
	if (x == 0) return;
	enrolledCourse* cur = pS->list_enrolled;
	if (x > 1) {
		int h = 1; while (h < x) {
			cur = cur->next; ++h;
		}
	}
	if (cur) {
		cout << "------COURSE INFORMATION------" << endl;
		cout << "ID: " << cur->id_course << endl;
		cout << "Name: " << cur->course_name << endl;
		cout << "Teacher: " << cur->name_teacher << endl;
		cout << "Credits: " << cur->credits << endl;
		cout << "Session 1: " << cur->ses1.date << '\t' << cur->ses1.time << endl;
		cout << "Session 2: " << cur->ses2.date << '\t' << cur->ses2.time << endl;
	}

	cout << "Are you sure you want to delete: \n"; int n;
	cout << "1. Yes" << endl << "2. No" << endl;
	cin >> n;
	if (n == 2) return;
	else if (n == 1) {
		if (cur == pECCrs) {
			enrolledCourse* after = cur->next;
			pECCrs = after;
			delete cur;
		}
		else {
			enrolledCourse* before = pECCrs;
			while (before->next != cur)
				before = before->next;
			enrolledCourse* after = cur->next;
			before->next = after;
			delete cur;
		}
	}
	--pS->countEnroll;
	save_enrollcourse_stu(time, pS, sem);
}

void Delete_course_staff(schoolyear*& sy, course*& c, string time, int sem) {
	if (!c) {
		cout << "Empty course list" << endl;
		return;
	}
	int i = 0; course* tmp = c;
	while (tmp) {
		++i;
		cout << i << '.' << "Course ID: " << tmp->ID_course << '\t' << "Course name: " << tmp->course_name << endl;
		tmp = tmp->next;
	}
	cout << "0. Exit" << endl;
	cout << "Please choose the number represented the course (1,2,3, ... ): "; int x; cin >> x;
	while (x > i) {
		cout << "Invalid number!!" << endl << "Please input again: "; cin >> x;
	}
	if (x == 0) return;
	course* cur = c;
	if (x > 1) {
		int h = 1; while (h < x) {
			cur = cur->next; ++h;
		}
	}
	if (cur) {
		cout << "Course information: " << endl;
		cout << "ID: " << cur->ID_course << endl;
		cout << "Name: " << cur->course_name << endl;
		cout << "Teacher: " << cur->teacher_name << endl;
		cout << "Credits: " << cur->credits << endl;
		cout << "Current students: " << cur->next->cur_student << endl;
	}
	
	cout << "Are you sure you want to delete: \n"; int n;
	cout << "1. Yes" << endl << "2. No" << endl;
	cin >> n;
	if (n == 2) return;
	else if (n == 1) {
		if (cur == c) {
			course* after = cur->next;
			c = after;
			delete cur;
		}
		else {
			course* before = c;
			while (before->next != cur)
				before = before->next;
			course* after = cur->next;
			before->next = after;
			delete cur;
		}
	}

	semester* se = sy->sem;
	while (se && se->mark != sem) se = se->next;
	--se->num_course;
	cout << "Course deleted successfully" << endl;
	saveListOfCourse(sy, c, sy->time, sem);
}