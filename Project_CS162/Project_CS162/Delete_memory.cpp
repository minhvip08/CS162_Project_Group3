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
	
	enrolledCourse* pECCrs = pS->list_enrolled, *pECCrsTemp;

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

	while (pECCrs->id_course != choose) {
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