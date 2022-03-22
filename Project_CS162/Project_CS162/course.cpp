#include "header.h"


/*Course*/
void createSemester(schoolyear* pHead) {
	int semesterNow(0);
	date dateTmp;
	semester* pTemp = pHead->sem;
	while (pTemp != nullptr) {
		semesterNow++;
		pTemp = pTemp->next;
	}

	semesterNow++;
	pTemp = new semester;
	cout << "Now is semester" << semesterNow << ".";
	cout << endl << "Please enter the start of the semester";
	cout << endl << "Day: ";
	cin >> dateTmp.day;
	cout << "Month: ";
	cin >> dateTmp.month;
	cout << "Year: ";
	cin >> dateTmp.year;

	pTemp->start_date = dateTmp;

	cout << endl << "Please enter the end of the semester";
	cout << endl << "Day: ";
	cin >> dateTmp.day;
	cout << "Month: ";
	cin >> dateTmp.month;
	cout << "Year: ";
	cin >> dateTmp.year;

	pTemp->end_date = dateTmp;

	createCourseEnrolledTime(pTemp);

	pTemp->next = nullptr;
	pHead->num_sem = semesterNow;
	pTemp->course_list = nullptr;
		
}

void createCourseEnrolledTime(semester*& pTemp) {
	date dateTmp;
	cout << "Create a course registration session! ";
	cout << endl << "Please enter the start of the semester";
	cout << endl << "Day: ";
	cin >> dateTmp.day;
	cout << "Month: ";
	cin >> dateTmp.month;
	cout << "Year: ";
	cin >> dateTmp.year;

	pTemp->start_regist = dateTmp;

	cout << endl << "Please enter the end of the semester";
	cout << endl << "Day: ";
	cin >> dateTmp.day;
	cout << "Month: ";
	cin >> dateTmp.month;
	cout << "Year: ";
	cin >> dateTmp.year;
	pTemp->end_regist = dateTmp;
}