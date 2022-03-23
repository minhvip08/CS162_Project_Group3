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

void addCourseToSemester(course* crs) {
	course* tempCrs = new course;
	cout << "Please enter ID of course:";
	cin >> tempCrs->ID_course;
	
	course* pCurCrs = crs;
	while (pCurCrs != nullptr) {
		if (pCurCrs->ID_course == tempCrs->ID_course) {
			cout << "Sorry, You just enter the exist course!";
			cout << "\nIf you want to enter again, enter id_course, if not press 0.";
			cin >> tempCrs->ID_course;
			if (tempCrs->ID_course == "0")
				return;
			pCurCrs = crs;
			continue;
		}

		pCurCrs = pCurCrs->next;

	}

	cout << endl << "Enter Name of course";
	cin.ignore(100, '\n');
	getline(cin, tempCrs->course_name, '\n');
	cout << endl << "Enter Teacher's Name of course";
	cin.ignore(100, '\n');
	getline(cin, tempCrs->teacher_name, '\n');
	cout << endl << "Enter number of credits of course";
	cin >> tempCrs->credits;
	cout << endl << "Enter  max students of the course of course";
	cin >> tempCrs->cur_student;
	
	while (tempCrs->cur_student > 50) {
		cout << endl << "Sorry, max students of the course is over the default (>50), please enter again.";
		cin >> tempCrs->cur_student;
	}

	int choose;
	system("cls");
	cout << endl << "Enter the session 1 you want to choose:";
	cout << endl << "There are six day of week to choose, please press from 1 to 6 to choose:";
	cout << endl << "1. Monday.";
	cout << endl << "2. Tuesday.";
	cout << endl << "3. Wednesday.";
	cout << endl << "4. Thursday.";
	cout << endl << "5. Friday.";
	cout << endl << "6. Saturday.";

	cin >> choose;
	switch (choose) {
	case 1: {
		tempCrs->sess[0].date == "MON";
		break;
	}
	case 2: {
		tempCrs->sess[0].date == "TUE";
		break;
	}
	case 3: {
		tempCrs->sess[0].date == "WED";
		break;
	}
	case 4: {
		tempCrs->sess[0].date == "THU";
		break;
	}
	case 5: {
		tempCrs->sess[0].date == "FRI";
		break;
	}
	case 6: {
		tempCrs->sess[0].date == "SAT";
		break;
	}
	}

	system("cls");

	session_time SS;

	cout << endl << "There are four session of week to choose, please press from 1 to 4 to choose:";
	cout << endl << "S1(7:30)";
	cout << endl << "S2(09:30)";
	cout << endl << "S3(13:30)";
	cout << endl << "S4(15:30)";
	cin >> choose;
	switch (choose) {
	case 1: {
		tempCrs->sess[0].time = SS.S1;
		break;
	}
	case 2: {
		tempCrs->sess[0].time = SS.S2;
		break;
	}
	case 3: {
		tempCrs->sess[0].time = SS.S3;
		break;
	}
	case 4: {
		tempCrs->sess[0].time = SS.S4;
		break;
	}
	}

	system("cls");

	int choose;
	system("cls");
	cout << endl << "Enter the session 2 you want to choose:";
	cout << endl << "There are six day of week to choose, please press from 1 to 6 to choose:";
	cout << endl << "1. Monday.";
	cout << endl << "2. Tuesday.";
	cout << endl << "3. Wednesday.";
	cout << endl << "4. Thursday.";
	cout << endl << "5. Friday.";
	cout << endl << "6. Saturday.";

	cin >> choose;
	switch (choose) {
	case 1: {
		tempCrs->sess[1].date == "MON";
		break;
	}
	case 2: {
		tempCrs->sess[1].date == "TUE";
		break;
	}
	case 3: {
		tempCrs->sess[1].date == "WED";
		break;
	}
	case 4: {
		tempCrs->sess[1].date == "THU";
		break;
	}
	case 5: {
		tempCrs->sess[1].date == "FRI";
		break;
	}
	case 6: {
		tempCrs->sess[1].date == "SAT";
		break;
	}
	}

	system("cls");

	session_time SS;

	cout << endl << "There are four session of week to choose, please press from 1 to 4 to choose:";
	cout << endl << "S1(7:30)";
	cout << endl << "S2(09:30)";
	cout << endl << "S3(13:30)";
	cout << endl << "S4(15:30)";
	cin >> choose;
	switch (choose) {
	case 1: {
		tempCrs->sess[1].time = SS.S1;
		break;
	}
	case 2: {
		tempCrs->sess[1].time = SS.S2;
		break;
	}
	case 3: {
		tempCrs->sess[1].time = SS.S3;
		break;
	}
	case 4: {
		tempCrs->sess[1].time = SS.S4;
		break;
	}
	}
	
	if (crs == nullptr) {
		crs = tempCrs;
		crs->NO = 1;
		return;
	}

	pCurCrs = crs;
	int No = 2;
	while (pCurCrs->next != nullptr) {
		No++;
		pCurCrs = pCurCrs->next;
	}

	tempCrs->NO = No;
	pCurCrs->next = tempCrs;
	pCurCrs = pCurCrs->next;
	pCurCrs->next = nullptr;
		
	return;
}
