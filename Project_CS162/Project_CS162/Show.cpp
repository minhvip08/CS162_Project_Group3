#include "header.h"
#include "OutputConsole.h"
#include "Data.h"
#include "Input.h"
#include "Support.h"
#include "Deallocate_graphic.h"
#include "Menu.h"
#include "Login.h"
#include "Scoreboard.h"
void show_course(schoolyear* head)
{
	readSchoolyear(head);
	if (!head) {
		cout << "You haven't added a new schoolyear" << endl;
		return;
	}

	schoolyear* tmp = head; cout << "List of schoolyear: " << endl; int i = 0;
	while (tmp) {
		++i;
		cout << i << ". " << tmp->time << '\t';
		tmp = tmp->next_schyear;
	} cout << endl;

	cout << "Which schoolyear you want to add semester? "; int x; cin >> x;
	while (x > i) {
		cout << "You input a wrong number. PLease input again: "; cin >> x;
	}
	schoolyear* check = head;
	if (x > 1) {
		int j = 1;
		while (j < x) {
			check = check->next_schyear;
			++j;
		}
	}
	if (check->num_sem == 0) {
		cout << "There is no semester added in this schoolyear\n";  system("pause");
		return;
	}
	else
		readSemester(check->sem, check->time);
	semester* s_tmp = check->sem;
	cout << "There are currently " << check->num_sem << " semesters in this schoolyear" << endl;
	cout << "Which semester you want to update its courses' information: "; cin >> x;
	if (x != check->num_sem) {
		int h = x; while (h < check->num_sem) { s_tmp = s_tmp->next; ++h; }
	}
	if (s_tmp->num_course == 0) {
		cout << "There is no course added in this semester\n"; system("pause");
		return;
	}
	else
		readListOfCourse(check->time, s_tmp->course_list, x);
	cout << "list: \n";
	course* c = s_tmp->course_list;
	while (c) {
		cout << "Course ID: " << c->ID_course << endl;
		cout << "Course name: " << c->course_name << endl;
		cout << "Teacher name: " << c->teacher_name << endl;
		cout << "Number of credits: " << c->credits << endl;
		cout << "Current student(s): " << c->cur_student << endl;
		cout << "Session 1: " << endl; show_session(c->ses1);
		cout << "Session 2: " << endl; show_session(c->ses2);
		c = c->next;
	}
}

void show_session(session s) 
{
	cout << "Day: " << s.date << endl;
	cout << "Time: " << s.time << endl;
}

void show_class(schoolyear* head)
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
	cout << "Which schoolyear you want to view class? "; int x; cin >> x;
	schoolyear* check = head;
	if (x > 1) {
		int j = 1; while (j < x) { check = check->next_schyear; ++j; }
	}
	readListOfClass(check->list_class, check->time);
	Class* cl = check->list_class;
	i = 0;
	while (cl) {
		++i;
		cout << "Class number: " << i << endl;
		cout << "Class name: " << cl->class_name << endl;
		cout << "Number of students: " << cl->total_student << endl;
		cl = cl->nextClass;
	}
}

void show_date(date s) 
{
	cout << "Date: " << setfill('0') << setw(2) << s.day;
	cout << '/' << setfill('0') << setw(2) << s.month << '/' << s.year << endl;
}

void menu_staff()
{
	cout << "*********WELCOME********" << endl;
	cout << "1. Schoolyear management\n";
	cout << "2. Semester management\n";
	cout << "3. Course management\n";
	cout << "0. Exit\n";

	while (true) {
		cout << "Choose your choice: "; int n; cin >> n;
		if (n == 0) break;
		else {
			switch (n) {
			case 1: {
				manage_Schoolyear(); 

				break;
			}
			case 2: {
				manage_semester();
				break;
			}
			case 3: {
				manage_course();
				break;
			}
			}
		}
	}
	system("pause");
	// deallocate schoolyear; 
}

void showListEnrolledCourse(student* pS) {
	// choose schoolyear
	schoolyear* sy = new schoolyear;
	readSchoolyear(sy);
	int i = 0; schoolyear* tmpsch = sy; cout << "List of schoolyear: " << endl;
	while (tmpsch) {
		++i;
		cout << i << '.' << tmpsch->time << endl;
		tmpsch = tmpsch->next_schyear;
	}
	cout << "Which schoolyear you want to view your courses: "; int x; cin >> x;
	while (x > i) {
		cout << "invalid schoolyear" << endl << "input again" << endl;
		cin >> x;
	}

	schoolyear* check = sy;
	if (x > 1) {
		int j = 1; while (j < x) { check = check->next_schyear; ++j; }
	}

	// choose semester
	cout << "There are " << check->num_sem << " semesters in this schoolyear" << endl;
	cout << "Which semester you want to view your courses: ";
	int xx; cin >> xx; semester* s_tmp = new semester;
	while (xx > check->num_sem) {
		cout << "Invalid number!!" << endl << "Please input again: "; cin >> xx;
	}

	readListEnrolled(check->time, pS, xx);

	enrolledCourse* cur = pS->list_enrolled;
	if (cur == nullptr) {
		cout << "\nPress any key to continue....";
		char a = _getch();
		return;
	}

	int j = 0;
	while (cur != nullptr) {
		++j;
		cout << "******COURSE NUMBER: " << j << "******\n";
		cout << "  * ID: " << cur->id_course << endl;
		cout << "  * Course name: " << cur->id_course << endl;
		cout << "  * Teacher's name: " << cur->name_teacher << endl;
		cout << "  * Credits: " << cur->credits << endl;
		cout << "  * Session 1: " << cur->ses1.date << '\t' << cur->ses1.time << endl;
		cout << "  * Session 2: " << cur->ses2.date << '\t' << cur->ses2.time << endl;
		cur = cur->next;
	}
	system("pause");
}

void showStudentsInClass(schoolyear* head) {
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
	cout << "Which schoolyear you want to view class? "; int x; cin >> x;
	schoolyear* check = head;
	if (x > 1) {
		int j = 1; while (j < x) { check = check->next_schyear; ++j; }
	}
	readListOfClass(check->list_class, check->time);
	cout << "List of class: " << endl;
	Class* cl = check->list_class; int a = 1;
	while (cl) {
		cout << a << ". " << cl->class_name << endl; ++a;
		cl = cl->nextClass;
	}
	cout << "Which class you want to view information: "; int t; cin >> t;
	Class* ctmp = check->list_class;
	if (t > 1) {
		int j = 1; while (j < t) { ctmp = ctmp->nextClass; ++j; }
	}
//	showStuInOneClass(ctmp);
	Class* read = new Class;
	readStudent1Class(ctmp->class_name, read);
	student* pStudentHead = read->student_list; int b = 1;

	cout << "No\tID\t\tName\t\t\t\tBirthday\tGender\tSocial ID\n";
	while (pStudentHead) {
		cout << b << '\t';
		string fullname = pStudentHead->prf.lastname + ' ' + pStudentHead->prf.firstname;
		cout << pStudentHead->id << '\t' << fullname << '\t' << ((fullname.length() < 16) ? '\t' : ' ') << '\t' << pStudentHead->prf.DOB << "\t" << pStudentHead->prf.gender << "\t" << pStudentHead->prf.social_id << "\n";
		++b;
		pStudentHead = pStudentHead->pNext;
	}
}

void showStudentsInCourse(schoolyear* head) {
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
	if (check->num_sem == 0) {
		cout << "You haven't add a semester for this schoolyear" << endl; system("pause");
		return;
	}
	else
		readSemester(check->sem, check->time);

	cout << "There are currently " << check->num_sem << " semesters in this schoolyear." << endl;
	cout << "Which semester you want to add course? "; int k; cin >> k;
	semester* s_check = check->sem;
	if (k != check->num_sem) {
		int h = k; while (h < check->num_sem) { s_check = s_check->next; ++h; }
	}
	if (s_check->num_course == 0) {
		cout << "There is no course added in this semester\n"; system("pause");
		return;
	}
	else
		readListOfCourse(check->time, s_check->course_list, k);
	course* ctmp = s_check->course_list; i = 0;
	cout << "List of course: \n";
	while (ctmp) {
		++i;
		cout << i << ".ID: " << ctmp->ID_course << '\t' << "Course name: " << ctmp->course_name << endl;
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
	readStudentOfCourse(cur);
	studentScore* pStuCrs = cur->list_score;
	if (!pStuCrs) {
		cout << "No student enrolled in this course\n";
		system("pause");
		return;
	}
	else
		cout << "No\tID\tName\n";
	int b = 0;
	while (pStuCrs != nullptr) {
		++b;
		cout << b << "\t";
		cout << pStuCrs->id << "\t";
		cout << pStuCrs->name << "\n";
		pStuCrs = pStuCrs->pNext;
	}
}

void menu_student(account*& head) {
	schoolyear* sy = nullptr;
	readSchoolyear(sy); schoolyear* tmp = sy;
	while (tmp) {
		if (checkCurrentSchoolyear(tmp)) {
			break;
		}
		else tmp = tmp->next_schyear;
	}
	string cl_name; 
	if(tmp) readListOfClass(tmp->list_class, tmp->time);
	Class* ctmp = tmp->list_class;
	bool stop = false; student* stu = new student;
	while (ctmp) {
		readStudent1Class(ctmp->class_name, ctmp);
		stu = ctmp->student_list;
		while (stu) {
			if (stu->id == head->username) {
				cl_name = ctmp->class_name;
				stop = true;
				break;
			}
			else stu = stu->pNext;
		}
		if (stop == true) break;
		else
			ctmp = ctmp->nextClass;
	}
	while (true) {
		system("cls");
		int opt; 
		cout << "1. Enroll a course" << endl;
		cout << "2. View a list of enrolled course" << endl;
		cout << "3. Remove enrolled course" << endl; // ktra ngay thang cho phep enroll
		cout << "4. View a list of his/her courses in this semester" << endl;
		cout << "5. View his/her scoreboard" << endl;
		cout << "0. Exit" << endl;
		cout << "Choose: ";
		cin >> opt; if (opt == 0) break;
		switch (opt) {
		case 1: {
			int sem = currentSemester();
			enrollCourse(sy, tmp->time, sem, stu);
			system("pause");
			break;
		}
		case 2: {
			showListEnrolledCourse(stu);
			system("pause");
			break;
		}
		case 3: {
			int sem = currentSemester();
			Delete_enrolled_course(sy, tmp->time, stu, sem);
			system("pause");
			break;
		}
		case 4: {
			int sem = currentSemester();
			readListEnrolled(tmp->time, stu, sem);
			enrolledCourse* etmp = stu->list_enrolled;
			if (etmp == nullptr) {
				cout << "Press any key to back....\n";
				char a = _getch();
			}
			else {
				int i = 0;
				while (etmp) {
					++i;
					cout << "******COURSE NUMBER: " << i << " ******\n";
					cout << "  * ID: " << etmp->id_course << endl;
					cout << "  * Course name: " << etmp->id_course << endl;
					cout << "  * Teacher's name: " << etmp->name_teacher << endl;
					cout << "  * Credits: " << etmp->credits << endl;
					cout << "  * Session 1: " << etmp->ses1.date << '\t' << etmp->ses1.time << endl;
					cout << "  * Session 2: " << etmp->ses2.date << '\t' << etmp->ses2.time << endl;
					etmp = etmp->next;
					if (!etmp) cout << "**************************************\n";
				}
			}
			system("pause");
			break;
		}
		case 5:{
			view_scoreboard_stu(stu);
			system("pause");
			break;
		}
		case 6: {
			view_scoreboard_sem(stu);
			system("pause");
			break;
		}

		default: {
			cout << "You input wrong number '\nPlease input again: ";
			break;
		}
		}
	}
}

