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

	semester* cur = new semester; cur->course_list = NULL;
	cout << "Start date: "; input_date(cur->start_date);
	cout << "End day: "; input_date(cur->end_date);

	//Course enrolled time:
	createCourseEnrolledTime(cur);
	++check->num_sem;
	cur->course_list = NULL;
	if (!check->sem) {
		check->sem = cur;
		cur->next = NULL;
	}
	else {
		cur->next = check->sem;
		check->sem = cur;
	}
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
	semester* se = check->sem; cout << "List of semester: " << endl; int t = 1;
	while (se) {
		cout << t << ". Semester " << t << endl; ++t;
		se = se->next;
	} cout << endl;

	cout << "Which semester you want to add course? "; int k; cin >> k;
	semester* s_check = check->sem;
	if (k > 1) {
		int j = 1; while (j < k) { s_check = s_check->next; ++j; }
	}

	++s_check->num_course;

	course* cur = new course; cur->list_score = nullptr; 
	cout << "Course ID: "; cin >> cur->ID_course;
	cin.get();
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
		cur->next = NULL;
	}
	else {
		cur->next = s_check->course_list;
		s_check->course_list = cur;
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
	cout << "Class name: "; cin.get(); getline(cin, cur->class_name, '\n');
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
}

void createCourseEnrolledTime(semester*& pTemp) {
	date dateTmp;
	cout << "Create a course registration time! ";
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

void input_date(date &p) // OK
{
	cout << "Day: "; cin >> p.day; 
	cout << "Month: "; cin >> p.month; 
	cout << "Year: "; cin >> p.year; 
}
