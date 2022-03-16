#include "header.h"

void input_schoolyear(schoolyear* head)
{
	schoolyear* cur = head; 
	while (true) {
		cin >> cur->time;
		input_semester(cur->semseter);

		cout << "Press any key if you want to input more school year, else press 0"; 
		char k; cin >> k; 
		if (k == 0) {
			cur->next_schyear = nullptr;
			break;
		}
		else {
			cur->next_schyear = new schoolyear; 
			cur = cur->next_schyear; 
		}
	}
}

void input_semester(semester* &head)
{
	semester* cur = head;
	cout << "start day: "; cin >> cur->start_day;
	cout << "end day: "; cin >> cur->end_day; 
	cout << "number of course: "; cin >> cur->num_course; 
	cout << "number of class: "; cin >> cur->num_class;
	input_course(cur->course_list); 
	input_class(cur->list_class); 
}

void input_course(course* &head)
{
	course* cur = head;
	while (true) {
		cout << "Course ID: "; cin >> cur->ID_course;
		cout << "Course name: "; cin >> cur->course_name;
		cout << "Teacher name: "; cin >> cur->teacher_name;
		cout << "Number of credits: "; cin >> cur->credits;
		cout << "Number of student: "; cin >> cur->cur_student;
		input_session(cur->sess);
		
		cout << "Press any key to continue, Press 0 to stop inputting course: "; 
		char k; cin >> k; 
		if (k == '0') {
			cur->next = nullptr; 
			break;
		}
		else {
			cur->next = new course; 
			cur = cur->next; 
			continue; 
		}

	}
	
}

void input_session(session* &head)
{
	session_date sdate; session_time stime;
	session *cur = head; 
	for (int i = 1; i <= 2; i++) {
		if (i == 1) cur->next = new session;
		else if (i == 2) cur->next = nullptr; 
		cout << "Session " << i << ':' << endl; 
		cout << "Date of session: " << endl;
		cout << "1. MON\t 2.TUE\t 3.WED \t 4. THU\t 5.PRI\t 6. FRI \n"; int date; cin >> date;
		switch (date) {
			case 1: {
				cur->date = sdate.MON;
				break; }
			case 2: {
				cur->date = sdate.TUE;
				break; }
			case 3: {
				cur->date = sdate.WED;
				break; }
			case 4: {
				cur->date = sdate.THU;
				break; }
			case 5: {
				cur->date = sdate.FRI;
				break; }
			case 6: {
				cur->date = sdate.SAT;
				break; }
		}

		cout << "Time of session: " << endl;
		cout << "1. S1(7:30)\t 2. S2(09:30)\t 3.S3(13:30)\t 4. S4(15:30) \n"; int time; cin >> time;
		switch (time) {
			case 1: {
				cur->time = stime.S1; break;
			}
			case 2: {
				cur->time = stime.S2; break;
			}
			case 3: {
				cur->time = stime.S3; break;
			}
			case 4: {
				cur->time = stime.S4; break;
			}
		}
		if (i == 2) break; 
		else
			cur = cur->next;
	}
	
}

void input_class(Class* head)
{
	Class *cur = head; 
	while (true) {
		cout << "Class name: "; cin >> cur->class_name; 
		cout << "Number of current students: "; cin >> cur->cur_student; 
		cout << "Start date: "; input_date(cur->start_date); 
		cout << "End date: "; input_date(cur->end_day); 
		cout << "Press any key to continue, Press 0 to stop inputting course: ";
		char k; cin >> k;
		if (k == '0') {
			cur->nextClass = nullptr;
			break;
		}
		else {
			cur->nextClass = new Class;
			cur = cur->nextClass;
			continue;
		}
	}
}

void input_date(date &p) {
	cout << "Day: "; cin >> p.day; 
	cout << "Month: "; cin >> p.month; 
	cout << "Year: "; cin >> p.year; 
}

void show_schoolyear(schoolyear* head) // continue
{
	schoolyear* cur = head; 
}

void show_semester(semester* s)
{
	while (s) {
		cout << "Start day: " << s->start_day << endl;
		cout << "End day: " << s->end_day << endl;
		cout << "Number of courses: " << s->num_course << endl;
		cout << "Number of class: " << s->num_class << endl; 
		show_course(s->course_list); 
		show_class(s->list_class); 
	}
}

void show_course(course* c)
{
	while (c) {
		cout << "Course ID: " << c->ID_course << endl; 
		cout << "Course name: " << c->course_name << endl; 
		cout << "Teacher name: " << c->teacher_name << endl; 
		cout << "Number of credits: " << c->credits << endl;
		cout << "Current student(s): " << c->cur_student << endl; 
		show_session(c->sess); 
		c = c->next; 
	}
}

void show_session(session* head)
{
	while (head) {
		cout << "Date: " << head->date << endl; 
		cout << "Time: " << head->time << endl; 
		head = head->next; 
	}
}

void show_class(Class* head)
{
	Class* tmp = head; 
	while (tmp) {
		cout << "Class name: " << tmp->class_name << endl; 
		cout << "Number of current students: " << tmp->cur_student << endl; 
		cout << "Start day: " << endl; show_date(tmp->start_date); 
		cout << "End day: " << endl; show_date(tmp->end_day); 
	}
}

void show_date(date s)
{
	cout << "Day: " << setfill('0') << setw(2) << s.day << '\n'; 
	cout << "Month: " << setfill('0') << setw(2) << s.month << '\n';
	cout << "Year: " << s.year << '\n';
}