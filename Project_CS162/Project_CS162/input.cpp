#include "header.h"

void input_schoolyear(schoolyear* head)
{
	schoolyear* cur = head, * tail = nullptr;
	cin >> cur->time; 
}

void input_semester(semester* head)
{
	semester* cur = head, * tail = nullptr; 
	cout << "start day: "; cin >> cur->start_day; 
	cout << "end day: "; cin >> cur->end_day; 
	cout << "number of course: "; cin >> cur->num_course; 
	cout << "number of class: "; cin >> cur->num_class;
	input_course(cur->course_list); 

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
	
}