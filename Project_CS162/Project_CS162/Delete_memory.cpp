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

void Delete_enrolled_course( student*& pS) {
	
	enrolledCourse* pECCrs = pS->list_enrolled, *pECCrsTemp = nullptr;

	system("cls");
	if (pECCrs != nullptr) {
		cout << "You haven't enrolled any courses yet!";
		cout << "\n Press any key to back.... ";
		char a = _getch();
		return;
	}

	cout << "Please choose one of the course you want to delete";
	show_enrolled_course(pECCrs);
	cout << "\nExit PRESS 0.";
	string choose;
	cin >> choose;

	if (choose == "0")
		return;

	while (choose != pECCrs->id_course ) {
		pECCrsTemp = pECCrs;
		pECCrs = pECCrs->next;
	}

	if (pECCrs == nullptr) {
		cout << "Don't exist course.";
		return;
	}

	pECCrsTemp->next = pECCrs->next;
	delete pECCrs;
	pS->countEnroll--;
}

void Delete_course_staff(course*& c) {
	if (!c) {
		cout << "Empty course list" << endl;
		return;
	}
	show_ID_course(c);
	string tmp; cout << "Enter ID of course you want to delete: "; getline(cin, tmp, '\n');
	course* tmpc = c;
	while (tmpc) {
		if (tmpc->next->ID_course == tmp) break;
		tmpc = tmpc->next;
	}
	course* del = tmpc->next;
	if (!tmpc) {
		cout << "Invalid course" << endl << "Your action can't be done" << endl;
		return;
	}

	cout << "Course information: " << endl;
	cout << "ID: " << del->ID_course << endl;
	cout << "Name: " << del->course_name << endl;
	cout << "Teacher: " << del->teacher_name << endl;
	cout << "Credits: " << del->credits << endl;
	cout << "Current students: " << tmpc->next->cur_student << endl;

	cout << "Are you sure you want to delete: \n"; int n;
	cout << "1. Yes" << endl << "2. No" << endl;
	cin >> n;
	if (n == 2) return;
	else if (n == 1) {
		course* after = tmpc->next->next;
		tmpc->next = after;
		delete del;
	}
	cout << "Course deleted successfully" << endl;
}