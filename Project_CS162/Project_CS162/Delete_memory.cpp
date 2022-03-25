#include "Header.h"

void Delete_schoolyear(schoolyear*& head)
{
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
	while (head) {
		semester* tmp = head->next;
		Delete_course(tmp->course_list);
		delete head;
		head = tmp;
	}
}

void Delete_course(course*& head)
{
	while (head) {
		course* tmp = head->next;
		Delete_stdScore(head->list_score);
		delete head;
		head = tmp;
	}
}

void Delete_class(Class*& head)
{
	while (head) {
		Class* tmp = head->nextClass;
		delete head;
		head = tmp;
	}
}

void Delete_stdScore(studentScore*& head)
{
	while (head) {
		studentScore* tmp = head->pNext;
		delete head;
		head = tmp;
	}
}

void Delete_student(student*& head)
{
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
	while (head) {
		Delete_stdScore(head->list_score);
		enrolledCourse* tmp = head->next;
		delete head;
		head = tmp;
	}
}

void Delete_finalGPA(finalGPA*& head)
{
	while (head) {
		finalGPA* tmp = head->next;
		delete head;
		head = tmp;
	}
}