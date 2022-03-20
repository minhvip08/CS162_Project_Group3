#include "header.h"

void input_schoolyear(schoolyear* &head)
{
	schoolyear* cur = head; 
	while (true) {
		cout << "Input time (ex: 2021-2022): "; 
		getline(cin, cur->time); 
		if (cur->num_sem >= 3) {
			cout << "Full of semester, you can't add more" << endl; 
			return; 
		}
		if (cur->num_sem > 1) {
			semester* sNew = new semester; 
			cur->sem->next = sNew; 
			cur->sem = sNew;
		}
		input_semester(cur->sem);
		++cur->num_sem; 
		cout << "Press any key if you want to input more school year, else press 0"; 
		char k; cin >> k; 
		if (k == '0') {
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
//	while (true){
	//	/*cin.get();*/
		cout << "Start day: " << endl;
		input_date(cur->start_day); 
		cout << "End day: " << endl; input_date(cur->end_day); 
		cout << "Number of course: "; cin >> cur->num_course;
		cout << "Number of class: "; cin >> cur->num_class;
		for(int i = 0; i < cur->num_course; ++i)
			input_course(cur->course_list);
		for(int i = 0; i < cur->num_class; ++i)
			input_class(cur->list_class);

		/*cout << "Press any key to add more semester, else press 0" << endl; 
		char k; k = _getch(); 
		if (k == '0') {
			cur->next = nullptr; 
			break;
		}
		else {
			cur->next = new semester; 
			cur = cur->next; 
		}*/
//	}
	
}

void input_course(course* &head) // OK 
{
	course* cur = head;
	while (true) {
		cout << "Course ID: "; cin >> cur->ID_course; 
		cin.get();
		cout << "Course name: "; getline(cin, cur->course_name); 
		cout << "Teacher name: ";  getline(cin, cur->teacher_name); 
		cout << "Number of credits: "; cin >> cur->credits;
		cout << "Number of student: "; cin >> cur->cur_student;
		cout << "Session: "; //input_session(cur->sess);
		
		cout << "Press any key to continue, Press 0 to stop inputting course: "; 
		char k; //cin >> k;
		k = _getch(); cout << endl;
		if (k == '0') {
			cur->next = nullptr; 
			break;
		}
		else {
			cur->next = new course; 
			cur = cur->next; 
			//continue; 
		}

	}
	
}

void input_session(session* &head) // OK
{
	session_date sdate; session_time stime;
	session *cur = head; 
	for (int i = 1; i <= 2; i++) {
		if (i == 1) cur->pNext = new session;
		else if (i == 2) cur->pNext = nullptr; 
		cout << "Session " << i << ':' << endl; 
		cout << "Date of session: " << endl;
		cout << "1. MON\t 2.TUE\t 3.WED \t 4. THU\t 5.PRI\t 6. SAT \n"; int date; cin >> date;
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
			cur = cur->pNext;
	}
	
}

void input_class(Class* &head) //OK
{
	Class *cur = head; 
	while (true) {
	//	cin.get(); 
		cout << "Class name: "; cin.get(); getline(cin, cur->class_name);
		cout << "Number of current students (press 1 for default 50): "; int n; cin >> n; 
		if (n == 0) cur->cur_student = 50;
		else cur->cur_student = n; 
		cout << "Start date: "; input_date(cur->start_date); 
		cout << "End date: "; input_date(cur->end_day); 
		cout << "Press any key to continue, Press 0 to stop inputting course: ";
		char k; k = _getch(); 
		if (k == '0') {
			cur->nextClass = nullptr;
			break;
		}
		else {
			cur->nextClass = new Class;
			cur = cur->nextClass;
			//continue;
		}
	}
}

void input_date(date &p) // OK
{
	cout << "Day: "; cin >> p.day; 
	cout << "Month: "; cin >> p.month; 
	cout << "Year: "; cin >> p.year; 
}

void show_schoolyear(schoolyear* head)
{
	schoolyear *cur = head;
	while (head) {
		cout << "Time: " << cur->time << endl; 
		cout << "Number of semesters: " << cur->num_sem << endl; 
		show_semester(cur->sem); 
		head = head->next_schyear; 
	}
}

void show_semester(semester* s)
{
	while (s) {
		cout << "Start day: "; show_date(s->start_day);
		cout << "End day: "; show_date(s->end_day);
		cout << "Number of courses: " << s->num_course << endl;
		cout << "Number of class: " << s->num_class << endl; 
		show_course(s->course_list); 
		show_class(s->list_class); 
		s = s->next; 
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
		//show_session(c->sess); 
		c = c->next; 
	}
}

void show_session(session* head) // OK 
{
	int i = 1; 
	while (head) {
		cout << "Session " << i << endl; 
		cout << "Date: " << head->date << "\t";
		cout << "Time: " << head->time << endl; 
		head = head->pNext; 
		++i; 
	}
}

void show_class(Class* head) //OK
{
	Class* tmp = head; 
	while (tmp) {
		cout << "Class name: " << tmp->class_name << endl; 
		cout << "Number of current students: " << tmp->cur_student << endl; 
		cout << "Start day: " << endl; show_date(tmp->start_date); 
		cout << "End day: " << endl; show_date(tmp->end_day); 
		tmp = tmp->nextClass; 
	}
}

void show_date(date s) // OK
{
	cout << "Date: " << setfill('0') << setw(2) << s.day; 
	cout << '/' << setfill('0') << setw(2) << s.month << '/' << s.year << endl;
}
