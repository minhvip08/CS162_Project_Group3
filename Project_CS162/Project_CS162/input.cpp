#include "header.h"
void create_schoolyear(schoolyear* &head)
{
	readSchoolyear(head);
	schoolyear* cur = new schoolyear;
	cin.get();
	cout << "Input time (ex 2021-2022): "; getline(cin, cur->time, '\n');
	cur->sem = NULL;
	cur->list_class = NULL;
	if (!head) {
		head = cur;
		head->next_schyear = NULL;
	}
	else {
		cur->next_schyear = head;
		head = cur;
	}
	saveSchoolyear(head);
}

void create_semester(schoolyear* &head)
{
	if (!head) {
		cout << "You haven't added a new schoolyear" << endl; 
		return;
	}

	schoolyear* tmp = head; cout << "List of schoolyear: " << endl; int i = 1;
	while (tmp) {
		cout << i << ". " << tmp->time << '\t'; ++i;
		tmp = tmp->next_schyear;
	} cout << endl;

	cout << "Which schoolyear you want to add semester? "; int x; cin >> x;
	schoolyear* check = head;
	if (x > 1) {
		int j = 1;
		while (j < x) {
			check = check->next_schyear;
			++j;
		}
	}
	++check->num_sem;
	semester* cur = new semester; cur->course_list = NULL;
	cur->mark = check->num_sem; 
	cout << "Start date: "; input_date(cur->start_date);
	cout << "End day: "; input_date(cur->end_date);
	createCourseEnrolledTime(cur);
	cur->course_list = NULL;
	if (!check->sem) {
		check->sem = cur;
		check->sem->next = NULL;
	}
	else {
		cur->next = check->sem;
		check->sem = cur;
	}
	saveListOfSemester(check); 
}

void create_course(schoolyear* &head) // OK 
{
	if (!head) {
		cout << "You haven't input a schoolyear" << endl;
		return;
	}

	schoolyear* tmp = head; cout << "List of schoolyear: " << endl; int i = 1;
	while (tmp) {
		cout << i << ". " << tmp->time << '\t'; ++i;
		tmp = tmp->next_schyear;
	} cout << endl;
	cout << "Which schoolyear you want to add semester? "; int x; cin >> x;
	schoolyear* check = head;
	if (x > 1) {
		int j = 1; while (j < x) { check = check->next_schyear; ++j; }
	}

	if (!check->sem) {
		cout << "You haven't add a semester for this schoolyear" << endl;
		return;
	}

	cout << "There are currently " << check->num_sem << " semesters in this schoolyear." << endl;
	cout << "Which semester you want to add course? "; int k; cin >> k;
	semester* s_check = check->sem;
	if (k != check->num_sem) {
		int h = k; while (h < check->num_sem) { s_check = s_check->next; ++h; }
	}

	++s_check->num_course;
	course* cur = new course; cur->list_score = nullptr; 
	cin.get();
	cout << "Course ID: "; getline(cin, cur->ID_course, '\n');
	cout << "Course name: "; getline(cin, cur->course_name, '\n');
	cout << "Teacher name: "; getline(cin, cur->teacher_name, '\n');
	cout << "Number of credits: "; cin >> cur->credits;
	cout << "Total student(press 1 for default 50): "; int n; cin >> n; 
	if (n == 1) cur->cur_student = 50;
	else cur->cur_student = n; 

	cout << "Session 1: "; input_session(cur->ses1);
	cout << "Session 2: "; input_session(cur->ses2);

	cur->list_score = NULL;
	if (!s_check->course_list) {
		s_check->course_list = cur;
		s_check->course_list->next = NULL;
	}
	else {
		cur->next = s_check->course_list;
		s_check->course_list = cur;
	}
	saveListOfCourse(check,s_check->course_list, check->time, s_check->mark);
}

void input_session(session &s) // OK
{
	session_date sdate; session_time stime;
	cout << "Day: " << endl;
	cout << "1. MON\t 2. TUE\t 3.WED\t 4.THU\t 5.FRI\t 6.SAT" << endl;
	int n; cin >> n;
	switch (n) {
	case 1: s.date = sdate.MON; break;
	case 2: s.date = sdate.TUE; break;
	case 3: s.date = sdate.WED; break;
	case 4: s.date = sdate.THU; break;
	case 5: s.date = sdate.FRI; break;
	case 6: s.date = sdate.SAT; break;
	}

	cout << "Time: " << endl;
	cout << "1. S1(7:30)\t 2. S2(09:30)\t 3.S3(13:30)\t 4. S4(15:30)" << endl;
	int m; cin >> m;
	switch (m) {
	case 1: s.time = stime.S1; break;
	case 2: s.time = stime.S2; break;
	case 3: s.time = stime.S3; break;
	case 4: s.time = stime.S4; break;
	}
}

void create_class(schoolyear* &head) //OK
{
	if (!head) {
		cout << "You haven't create new schoolyear" << endl;
		return;
	}

	schoolyear* tmp = head; cout << "List of schoolyear: " << endl; int i = 1;
	while (tmp) {
		cout << i << ". " << tmp->time << '\t'; ++i;
		tmp = tmp->next_schyear;
	} cout << endl;
	cout << "Which schoolyear you want to add class? "; int x; cin >> x;
	schoolyear* check = head;
	if (x > 1) {
		int j = 1; while (j < x) { check = check->next_schyear; ++j; }
	}
	++check->num_class;
	Class* cur = new Class;
	cout << "Class name: "; cin.ignore(10000, '\n'); getline(cin, cur->class_name, '\n');
	cout << "Total student (press 1 for default 50): "; int n; cin >> n;
	if (n == 1) cur->total_student = 50;
	else cur->total_student = n;
	cout << "Start date: "; input_date(cur->start_date);
	cout << "End date: "; input_date(cur->end_day);


	cur->student_list = NULL;

	if (!check->list_class) {
		check->list_class = cur;
		cur->nextClass = NULL;
	}
	else {
		cur->nextClass = check->list_class;
		check->list_class = cur;
	}
	saveListOfClass(check);
}

void createCourseEnrolledTime(semester*& s) 
{
	cout << "Create a course registration time! " << endl;
	cout << endl << "Please enter the start of the semester";
	input_date(s->start_regist);

	cout << endl << "Please enter the end of the semester";
	input_date(s->end_regist);
}

void input_date(date &p) // OK
{
	cout << "Day: "; cin >> p.day; 
	cout << "Month: "; cin >> p.month; 
	cout << "Year: "; cin >> p.year; 
}

void uppdateCourseInfor(semester* &pHeadSem) {
	if (pHeadSem == nullptr) {
		cout << endl << "Sorry, This school year is empty, please create a course before updating information.";
		char a = _getch();
		return;
	}

	int opt = 1; string id_course;

	system("cls");
	cout << endl << "These are all courses in this semester, please enter one ID Course!";
	course* tmp = pHeadSem->course_list; 
	show_ID_course(tmp);
	// kiem tra lai
	cin >> id_course;
	
	course* pCurCourse = tmp;
	
	while (pCurCourse != nullptr && pCurCourse->ID_course != id_course)
		pCurCourse = pCurCourse->next;

	if (pCurCourse == nullptr) {
		cout << "Sorry, the id course does not exist, please enter again.";
		return;
	}

	while (opt != 0) {
		system("cls");
		cout << "Which information do you want to change?";
		cout << endl << "1.ID of Course.";
		cout << endl << "2.Name of Course.";
		cout << endl << "3.Teacher's name.";
		cout << endl << "4.Credits.";
		cout << endl << "4.Total student.";
		cout << endl << "5.Session 1 of Course.";
		cout << endl << "6.Session 2 of Course.";
		cout << endl << "0.Exit.";
		cout << endl << "Your option is: ";
		cin >> opt;
		update1InforCourse(pCurCourse, opt);
	}
	return;
}

void update1InforCourse(course* pCourse, int opt) {
	if (opt == 0)
		return;
	switch (opt) {
	case 1: {
		system("cls");
		cout << "\nOld ID of Course: " << pCourse->ID_course;
		cout << "\nPlease enter new ID of Course: ";
		cin >> pCourse->ID_course;
		cout << "ID of course has been changed successfully!!";
		break;
	}
	case 2: {
		system("cls");
		cout << "\nOld Name of Course: " << pCourse->course_name;
		cout << "\nPlease enter Name of Course : ";
		cin >> pCourse->course_name;
		cout << "Name of course has been changed successfully!!";
		break;
	}
	case 3: {
		system("cls");
		cout << "\nOld Teacher's Name of Course: " << pCourse->teacher_name;
		cout << "\nPlease enter new Teacher's Name of Course: ";
		cin >> pCourse->teacher_name;
		cout << "Teacher's Name of course has been changed successfully!!";
		break;
	}
	case 4: {
		system("cls");
		cout << "\nOld Credits of Course: " << pCourse->credits;
		cout << "\nPlease enter new Credits of Course: ";
		cin >> pCourse->credits;
		cout << "Credits of course has been changed successfully!!";
		break;
	}
	case 5: {
		system("cls");
		cout << "\nOld Session 1 is: "; show_session(pCourse->ses1);
		cout << "\nPlease enter new Session 1: ";
		input_session(pCourse->ses1);
		cout << "Session 1 has been changed successfully!!";
		break;
	}
	case 6: {
		system("cls");
		cout << "\nOld Session 2 is: "; show_session(pCourse->ses2);
		cout << "\nPlease enter new Session 1: ";
		input_session(pCourse->ses2);
		cout << "Session 1 has been changed successfully!!";
		break;
	}
	default: {
		cout << endl << "You enter wrong number, please enter again!";
		cout << "\nPress any key to continue....";
		char a = _getch();
		return;
	}
	}
}


void enrollCourse(course*& pList, student*& pStudent) {
	course* pCurCourse = pList;
	string choose(0);
	do {
		system("cls");
		if (pCurCourse == nullptr) {
			cout << "No Course";
		}
		cout << "There is a list of courses, please enter one of them:" << endl;
		show_ID_course(pList);
		cout << endl << "0. EXIT.";
		cin >> choose;

		while (pCurCourse != nullptr && pCurCourse->ID_course != choose)
			pCurCourse = pCurCourse->next;

		if (pCurCourse == nullptr) {
			cout << "Sorry, the id course does not exist, please enter again.";
			continue;
		}

		if (choose == '0') {
			cout << "\nPress any key to continue....";
			char a = _getch();
			return;
		}

		if (pStudent->countEnroll >= 5) {
			cout << "You cannot enroll over 5 course in this semester.";
			cout << "\nPress any key to continue....";
			char a = _getch();
			continue;
		}
		
		addEnrolledCourseToStudent(pCurCourse, pStudent, choose);

	} while (true);


}

void addEnrolledCourseToStudent(course*& pList, student*& pStudent, string ID_course) {
	course* pCurCrs = pList;
	enrolledCourse* pCurECrs = pStudent->list_enrolled;

	while (pCurCrs != nullptr && pCurCrs->ID_course != ID_course)
		pCurCrs = pCurCrs->next;

	if (pCurCrs->cur_student == pCurCrs->total_student) {
		cout << "\This course is full, please choose another course! ";
		cout << "\nPress any key to continue....";
		char a = _getch();
		return;
	}

	while (pCurECrs != nullptr) {
		if (pCurECrs->id_course == pCurCrs->ID_course) {
			cout << "\nThis course is enrolled, please choose another course! ";
			cout << "\nPress any key to continue....";
			char a = _getch();
			return;
		}
		pCurECrs = pCurECrs->next;
	}

	studentScore* pTempStudent = pCurCrs->list_score;

	while (pTempStudent != nullptr)
		pTempStudent->pNext;

	pTempStudent = new studentScore;

	pTempStudent->prf = pStudent->prf;
	pTempStudent->no = pStudent->No;
	pTempStudent->id = pStudent->id;

	
	pCurECrs = new enrolledCourse;
	copyCourse(pCurECrs, pCurCrs);

	pStudent->countEnroll++;

	cout << "Enroll successfully!";

	cout << "\nPress any key to continue....";
	char a = _getch();
	return;

}

void copyCourse(enrolledCourse*& pEC, course* pC) {
	pEC->id_course = pC->ID_course;
	pEC->name = pC->course_name;
	pEC->name_teacher = pC->teacher_name;
	pEC->credits = pC->credits;
	pEC->ses1 = pC->ses1;
	pEC->ses2 = pC->ses2;
	pEC->next = nullptr;
	return;
}