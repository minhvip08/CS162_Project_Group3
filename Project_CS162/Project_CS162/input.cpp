#include "header.h"
#include "Data.h"
#include "Support.h"
#include "OutputConsole.h"
#include "Input.h"
void create_schoolyear(schoolyear* &head)
{
	readSchoolyear(head);
	showCurrentSchoolyear(head); 
	schoolyear* cur = new schoolyear; cin.get();
	string tmp; 
	cout << "Input time (ex 2021-2022): "; getline(cin, tmp, '\n');
	while (!checkValidSchoolyear(tmp)) {
		cout << "The schoolyear time is not appropriate. Please input again: "; 
		cin >> tmp;
	}
	bool flag = checkExistSchoolyear(head, tmp);
	while (!flag) {
		cout << "The schoolyear is already valid, please input another schoolyear time" << endl;
		//cout << "Input time (ex 2021-2022): "; 
		getline(cin, tmp, '\n');
		flag = checkExistSchoolyear(head, tmp);
	}
	cur->time = tmp;
	cur->sem = nullptr;
	cur->list_class = nullptr;
	if (!head) {
		head = cur;
		head->next_schyear = NULL;
	}
	else {
		cur->next_schyear = head;
		head = cur;
	}
	saveSchoolyear(head);
	cout << "Schoolyear created successfully!!!" << endl;
}

void create_semester(schoolyear* &head)
{
	readSchoolyear(head); 
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
	if (check->num_sem == 3) {
		cout << "There are fully 3 semesters in this schoolyear, you can't add more" << endl;
		return;
	}
	else cout << "There are currently " << check->num_sem << " semesters in this schoolyear" << endl; 
	readSemester(check->sem, check->time);
	++check->num_sem;
	semester* cur = new semester; cur->course_list = NULL;
	cur->mark = check->num_sem;
	bool flag = false;
	while (!flag) {
		cout << "Semester number: " << cur->mark << endl;
		cout << "Start date: "; input_date(cur->start_date);
		flag = checkSem(cur->start_date, cur->mark);
		if (!flag) {
			cout << "Start month does not match with smester"<<endl;
		}
		else {
			cout << "End day: "; input_date(cur->end_date);
			flag = checkSem(cur->end_date, cur->mark);
			if (!flag) {
				cout << "End month does not match with smester"<<endl;
			}
			else {
				flag = true;
			}
		}
	}
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
	saveListOfSemester(head); 
	cout << "Semester created successfully!!!\n";
}

void create_course(schoolyear* &head) // OK 
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
	cout << "Which schoolyear you want to add semester? "; int x; cin >> x;
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
	semester* s_check = check->sem;
	if (k != check->num_sem) {
		int h = k; while (h < check->num_sem) { s_check = s_check->next; ++h; }
	}
	readListOfCourse(check->time, s_check->course_list, k);
	++s_check->num_course;
	course* cur = new course; cur->list_score = nullptr; 
	cin.get();
	cout << "Course ID: "; getline(cin, cur->ID_course, '\n');
	cout << "Course name: "; getline(cin, cur->course_name, '\n');
	cout << "Teacher name: "; getline(cin, cur->teacher_name, '\n');
	cout << "Number of credits: "; cin >> cur->credits;
	cout << "Maximum students(press 1 for default 50): "; int n; cin >> n; 
	if (n == 1) cur->max_student = 50;
	else cur->max_student = n; 
	cur->cur_student = 0;
	cout << "Session 1: "; input_session(cur->ses1);
	cout << "Session 2: "; input_session(cur->ses2);
	while (checkConflictSession(cur->ses1, cur->ses2)) {
		cout << "Two sessions have to be different in date and time" << endl;
		cout << "Please input again" << endl;
		cout << "Session 1: "; input_session(cur->ses1);
		cout << "Session 2: "; input_session(cur->ses2);
	}

	cur->list_score = NULL;
	if (!s_check->course_list) {
		s_check->course_list = cur;
		s_check->course_list->next = NULL;
	}
	else {
		cur->next = s_check->course_list;
		s_check->course_list = cur;
	}
	saveListOfCourse(head,s_check->course_list, check->time, s_check->mark);
	cout << "Course created succesfully\n";
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
	readSchoolyear(head);
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
	readListOfClass(check->list_class, check->time);
	++check->num_class;
	Class* cur = new Class;
	cout << "Class name: "; cin.ignore(10000, '\n'); string a; getline(cin, a, '\n'); 
	while (!checkAvailClass(a, check->time)) {
		cout << "Name of class is not available for this schoolyear" << endl;
		cout << "Please input again" << endl;
		cout << "Class name: "; getline(cin, a, '\n');
	}
	int n = 0; 
	cur->class_name = a; account* cur_acc = NULL; collectOneClassAccount(n, cur->class_name,cur_acc);
	cur->total_student = n;
	cur->student_list = NULL;

	if (!check->list_class) {
		check->list_class = cur;
		cur->nextClass = NULL;
	}
	else {
		cur->nextClass = check->list_class;
		check->list_class = cur;
	}
	cout << "Class created successfully!!!" << endl;
	saveListOfClass(head);
}

void createCourseEnrolledTime(semester*& s) 
{
	bool flag = false;
	while (!flag) {
		cout << "Create a course registration time! " << endl;
		cout << "Please enter the start of the semester"; input_date(s->start_regist);
		flag = checkSem(s->start_regist, s->mark);
		if (!flag) {
			cout << "Start month does not match with semester registration time!" << endl;
		}
		else {
			cout << "Please enter the end of the semester"; input_date(s->end_regist);
			flag = checkSem(s->end_regist, s->mark);
			if (!flag) {
				cout << "End month does not match with smester registration time!" << endl;
			}
			else {
				flag = true;
			}
		}
	}
}

void input_date(date &p) // OK
{
	cout << "Day: "; cin >> p.day; 
	cout << "Month: "; cin >> p.month; 
	cout << "Year: "; cin >> p.year; 
}

void uppdateCourseInfor(schoolyear*& head) {
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
	readSemester(check->sem, check->time);
	if (!check->sem) {
		cout << "You haven't add a semester for this schoolyear" << endl;
		return;
	}

	cout << "There are currently " << check->num_sem << " semesters in this schoolyear." << endl;
	cout << "Which semester you want to view course? "; int k; cin >> k;
	semester* s_check = check->sem;
	if (k != check->num_sem) {
		int h = k; while (h < check->num_sem) { s_check = s_check->next; ++h; }
	}
	readListOfCourse(check->time, s_check->course_list, k);

	//system("cls");
	cout << "These are all courses in this semester, please enter one ID Course!" << endl;
	i = 0; course* ctmp = s_check->course_list;
	while (ctmp) {
		++i;
		cout << i << '.' << "Course ID: " << ctmp->ID_course << '\t' << "Course name: " << ctmp->course_name << endl;
		ctmp = ctmp->next;
	}
	cout << "0. Exit" << endl;
	cout << "Please choose the number represented the course (1,2,3, ... ): "; cin >> x;
	while (x > i) {
		cout << "Invalid number!!" << endl << "Please input again: "; cin >> x;
	}
	if (x == 0) return;
	course* cur = s_check->course_list;
	if (x > 1) {
		int h = 1; while (h < x) {
			cur = cur->next; ++h; 
		}
	}
	course* c = s_check->course_list;
	int opt = 100;
	while (opt != 0) {
		//system("cls");
		cout << "Course: " << cur->course_name << endl;
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
		update1InforCourse(cur, opt);
		saveListOfCourse(head, c, check->time, k);
	}
	return;
}

void update1InforCourse(course* &pCourse, int opt) {
	if (opt == 0)
		return;
	switch (opt) {
	case 1: {
		//system("cls");
		cout << "-----UPDATE COURSE ID-----";
		cout << "\nOld ID of Course: " << pCourse->ID_course;
		cout << "\nPlease enter new ID of Course: ";
		cin >> pCourse->ID_course;
		cout << "ID of course has been changed successfully!!";
		break;
	}
	case 2: {
		//system("cls");
		cout << "-----UPDATE COURSE NAME-----";
		cout << "\nOld Name of Course: " << pCourse->course_name;
		cout << "\nPlease enter Name of Course : ";
		cin.get(); 
		getline(cin, pCourse->course_name, '\n');
		cout << "Name of course has been changed successfully!!";
		break;
	}
	case 3: {
		//system("cls");
		cout << "-----UPDATE LECTURER'S NAME OF COURSE-----";
		cout << "\nOld Teacher's Name of Course: " << pCourse->teacher_name;
		cout << "\nPlease enter new Teacher's Name of Course: ";
		cin.get();
		getline(cin, pCourse->teacher_name, '\n');
		cout << "Teacher's Name of course has been changed successfully!!";
		break;
	}
	case 4: {
		//system("cls");
		cout << "-----UPDATE COURSE'S CREDITS-----";
		cout << "\nOld Credits of Course: " << pCourse->credits;
		cout << "\nPlease enter new Credits of Course: ";
		cin >> pCourse->credits;
		cout << "Credits of course has been changed successfully!!";
		break;
	}
	case 5: {
		//system("cls");
		cout << "-----UPDATE SESSION 1-----";
		cout << "\nOld Session 1 is: "; show_session(pCourse->ses1);
		cout << "\nPlease enter new Session 1: ";
		input_session(pCourse->ses1);
		cout << "Session 1 has been changed successfully!!";
		break;
	}
	case 6: {
		//system("cls");
		cout << "-----UPDATE SESSION 2-----";
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

void enrollCourse(schoolyear*& sy, string time, int sem, student*& stu) {
	// kiem tra ngay thang cho phep enroll
	schoolyear* scy = nullptr;
	readSchoolyear(scy);
	while (scy) {
		if (scy->time == time) break;
		else
			scy = scy->next_schyear; 
	}
	readSemester(scy->sem, scy->time);
	semester* s = scy->sem; 
	while (s) {
		if (s->mark == sem) break;
		s = s->next; 
	}
	if (!checkEnrollTime(s)) {
		cout << "Out of registration time.\n";
		return;
	}

	readListEnrolled(time, stu, sem);
	//semester* check = sy->sem; 
	if (stu->countEnroll >= 5) {
		cout << "You cannot enroll over 5 course in this semester.";
		cout << "\nPress any key to continue....";
		char a = _getch();
		return;
	}
	course* c = new course; 
	readListOfCourse(time, c, sem); 
	if (!c) {
		cout << "List of course in this semester is empty" << endl;
		return;
	}
	course* tmpc = c; int i = 0;
	while (tmpc) {
		++i;
		cout << "******COURSE NUMBER: " << i << " *******" << endl;
		cout << "ID Course: " << tmpc->ID_course << '\t' << "Course Name: " << tmpc->course_name << endl;
		cout << "Lecturer: " << tmpc->teacher_name << endl;
		cout << "Session 1: " << tmpc->ses1.date << '\t' << tmpc->ses1.time << endl;
		cout << "Session 2: " << tmpc->ses2.date << '\t' << tmpc->ses2.time << endl;
		tmpc = tmpc->next;
		if (!tmpc) cout << "**************************\n";
	} cout << "0. Exit" << endl;
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
	readStudentOfCourse(cur);
	if (alreadyEnrolled(cur->ID_course, stu->list_enrolled)) {
		cout << "You're already enrolled in this course" << endl;
		return;
	}
	else if (cur->cur_student == cur->max_student) {
		cout << "The course is full of slots" << endl << "You can't enroll in this course" << endl;
		cout << "\nPress any key to continue....";
		char a = _getch();
		return;
	}
	else if (conflictSessionEnroll(stu->list_enrolled, cur)) {
		cout << "Conflict session!!!" << endl;
		return;
	}
	enrolledCourse* head = stu->list_enrolled;
	if (!head) {
		enrolledCourse* ec = new enrolledCourse;
		ec->id_course = cur->ID_course;
		ec->course_name = cur->course_name;
		ec->name_teacher = cur->teacher_name;
		ec->credits = cur->credits;
		ec->ses1.date = cur->ses1.date;
		ec->ses1.time = cur->ses1.time;
		ec->ses2.date = cur->ses2.date;
		ec->ses2.time = cur->ses2.time;
		ec->ecscore.final = ec->ecscore.mid = ec->ecscore.other = ec->ecscore.total = 0; 
		stu->list_enrolled = ec;
		ec->next = nullptr;
	}
	else {
		enrolledCourse* add = new enrolledCourse;
		add->id_course = cur->ID_course;
		add->course_name = cur->course_name;
		add->name_teacher = cur->teacher_name;
		add->credits = cur->credits;
		add->ses1.date = cur->ses1.date;
		add->ses1.time = cur->ses1.time;
		add->ses2.date = cur->ses2.date;
		add->ses2.time = cur->ses2.time;
		add->ecscore.final = add->ecscore.mid = add->ecscore.other = add->ecscore.total = 0; 
		add->next = stu->list_enrolled;
		stu->list_enrolled = add;
	}

	studentScore* ss = cur->list_score;
	studentScore* snew = new studentScore;
	snew->id = stu->id;
	snew->name = stu->prf.lastname + ' ' + stu->prf.firstname;
	snew->stscore.final = snew->stscore.mid = snew->stscore.total = snew->stscore.other = 0;
	if (!ss) {
		ss = snew;
		cur->list_score = ss;
		ss->pNext = nullptr;
	}
	else {
		snew->pNext = ss;
		cur->list_score = snew;
	}
	cout << "Enroll succesfull" << endl;
	++cur->cur_student;
	save_enrollcourse_stu(time, stu, sem);
	saveStudentOfCourse(cur);
	saveListOfCourse(sy, c, time, sem);
}

void copyCourse(enrolledCourse*& pEC, course* pC) {
	pEC->id_course = pC->ID_course;
	pEC->course_name = pC->course_name;
	pEC->name_teacher = pC->teacher_name;
	pEC->credits = pC->credits;
	pEC->ses1 = pC->ses1;
	pEC->ses2 = pC->ses2;
	//pEC->next = nullptr;
}