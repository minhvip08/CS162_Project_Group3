#include "header.h"

void create_schoolyear(schoolyear* &head)
{
	if (!head) {
		cout << "List of schoolyear is empty" << endl;
		cout << "Pls input new schoolyear" << endl;
	}

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
}

void create_semester(schoolyear* &head)
{
	if (!head) {
		cout << "List of schoolyear is empty" << endl;
		cout << "Pls input new schoolyear" << endl;
		return;
	}

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
}

void create_course(schoolyear* &head) // OK 
{
	if (!head) {
		cout << "You haven't input a semester" << endl;
		return;
	}
	else if (!head->sem) {
		cout << "You haven't add a semester" << endl; 
		return; 
	}
	course* cur = new course;
	cout << "Course ID: "; cin >> cur->ID_course;
	cin.get();
	cout << "Course name: "; getline(cin, cur->course_name, '\n');
	cout << "Teacher name: "; getline(cin, cur->teacher_name, '\n');
	cout << "Number of credits: "; cin >> cur->credits;
	cout << "Total student: "; cin >> cur->cur_student;

	cout << "Session 1: "; input_session(cur->ses1);
	cout << "Session 2: "; input_session(cur->ses2);

	cur->list_score = NULL;
	if (!head->sem->course_list) {
		head->sem->course_list = cur;
		head->sem->next = NULL;
	}
	else {
		cur->next = head->sem->course_list;
		head->sem->course_list = cur;
	}
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

	Class* cur = new Class;
	cout << "Class name: "; cin >> cur->class_name;
	cout << "Total student (press 1 for default 50): "; int n; cin >> n;
	if (n == 1) cur->total_student = 50;
	else cur->total_student = n;
	cout << "Start date: "; input_date(cur->start_date);
	cout << "End date: "; input_date(cur->end_day);
	cur->student_list = NULL;

	if (!head->list_class) {
		head->list_class = cur;
		cur->nextClass = NULL;
	}
	else {
		cur->nextClass = head->list_class;
		head->list_class = cur;
	}
}

void input_date(date &p) // OK
{
	cout << "Day: "; cin >> p.day; 
	cout << "Month: "; cin >> p.month; 
	cout << "Year: "; cin >> p.year; 
}
