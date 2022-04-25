#include "header.h"
#include "OutputConsole.h"
#include "Data.h"
#include "Input.h"
#include "Support.h"
#include "Deallocate_graphic.h"
#include "Menu.h"
#include"Login.h"
void show_semester(schoolyear* &head, semester* &s)
{
	readSemester(s, head->time);
	semester* tmp = s; 
	while (tmp) {
		cout << "Semester: " << tmp->mark << endl;
		cout << "Start date: " << endl; show_date(tmp->start_date); 
		cout << "End date: " << endl; show_date(tmp->end_date);
		cout << "Number of course: " << tmp->num_course << endl;
		tmp = tmp->next;
	}
	while (1) {
		int n;
		cout << "1. View course list" << endl;
		cout << "2. Update course information" << endl;
		cout << "3. Delete a course" << endl; 
		cout << "0. Go backward" << endl;
		cout << "You choose: "; cin >> n;

		if (n == 0) break;
		switch (n) {
			case 1: {
				semester* s_tmp = s;
				cout << "There are currently " << head->num_sem << " semesters in this schoolyear" << endl;
				cout << "Which semester you want to view its courses: "; int x; cin >> x;
				if (x != head->num_sem) {
					int h = x; while (h < head->num_sem) { s_tmp = s_tmp->next; ++h; }
				}
				readListOfCourse(head->time, s_tmp->course_list, x);
				show_course(s_tmp->course_list, s_tmp->num_course); break;
			}
			case 2: {
				semester* s_tmp = s;
				cout << "There are currently " << head->num_sem << " semesters in this schoolyear" << endl;
				cout << "Which semester you want to update its courses' information: "; int x; cin >> x;
				if (x != head->num_sem) {
					int h = x; while (h < head->num_sem) { s_tmp = s_tmp->next; ++h; }
				}
				readListOfCourse(head->time, s_tmp->course_list, x);
				uppdateCourseInfor(head, s_tmp);
				break;
			}
			case 3: {
				semester* s_tmp = s;
				cout << "There are currently " << head->num_sem << " semesters in this schoolyear" << endl;
				cout << "Which semester you want to update its courses' information: "; int x; cin >> x;
				if (x != head->num_sem) {
					int h = x; while (h < head->num_sem) { s_tmp = s_tmp->next; ++h; }
				}
				readListOfCourse(head->time, s_tmp->course_list, x);
				Delete_course_staff(head, s_tmp->course_list, head->time, x);
				break;
			}
		}
	}
}

void show_course(course* c, int i)
{
	if (!c) return;
	show_course(c->next, i - 1);
	cout << "Course ID: " << c->ID_course << endl;
	cout << "Course name: " << c->course_name << endl;
	cout << "Teacher name: " << c->teacher_name << endl;
	cout << "Number of credits: " << c->credits << endl;
	cout << "Current student(s): " << c->cur_student << endl;
	cout << "Session 1: " << endl; show_session(c->ses1);
	cout << "Session 2: " << endl; show_session(c->ses2);
}

void show_ID_course(course* c) {
	/*if (!c) return;
	while (c) {
		cout << "Course ID: " << c->ID_course << '\t' << "Name Course: " << c->course_name << endl;
		c = c->next; 
	}*/
	
}

void show_enrolled_course(enrolledCourse* c) {
	/*if (!c) return;
	show_enrolled_course(c->next);
	cout << endl << "Course ID: " << c->id_course << endl << "Name Course: " << c->course_name << endl;*/
}


void show_session(session s) // OK 
{
	cout << "Day: " << s.date << endl;
	cout << "Time: " << s.time << endl;
}

void show_class(Class* head, int i) //OK
{
	if (!head) return;
	show_class(head->nextClass, i - 1);
	cout << "Class number: " << i << endl;
	cout << "Class name: " << head->class_name << endl;
	cout << "Number of current students: " << head->total_student << endl;
}

void show_date(date s) // OK
{
	cout << "Date: " << setfill('0') << setw(2) << s.day;
	cout << '/' << setfill('0') << setw(2) << s.month << '/' << s.year << endl;
}

void show_schoolyear(schoolyear* head)
{
	readSchoolyear(head); 
	if (!head) return; schoolyear* tmp = head; 
	int i = 1;
	while (tmp) {
		cout << i << ". " << tmp->time << '\t'; ++i;
		tmp = tmp->next_schyear;
	} cout << endl; 
	cout << "which schoolyear you want to view information: ";
	int x; cin >> x;
	while (x > i) {
		cout << "invalid schoolyear" << endl << "input again" << endl;
		cin >> x;
	}

	schoolyear* check = head;
	if (x > 1) {
		int j = 1; while (j < x) { check = check->next_schyear; ++j; }
	}

	while (1) {
		cout << "1. View list of semesters" << endl;
		cout << "2. View list of classes" << endl;
		cout << "0. Back to School Year Menu" << endl;

		int choice; cout << "You choose: "; cin >> choice;
		if (choice == 0) break;
		switch (choice) {
			case 1: {
				//readSemester(check->sem, check->time);
				show_semester(check, check->sem); break;
			}
			case 2: {
				readListOfClass(check->list_class, check->time);
				show_class(check->list_class, check->num_class);
				break;
			}
		}
	}
}

void menu_staff()
{
	while (true) {
		system("cls");
		int n; cout << "WELCOME" << endl;
		cout << "1. Creat new schoolyear" << endl;
		cout << "2. Create new semester to current schoolyear" << endl;
		cout << "3. Add course to semester" << endl;
		cout << "4. Add class to this schoolyear " << endl;
		cout << "5. MENU_VIEW" << endl;
		cout << "6. Exit" << endl;
		cout << "Choose your choice: "; cin >> n;

		schoolyear* sy = NULL;
		switch (n) {
		case 1: create_schoolyear(sy); break;
		case 2: create_semester(sy); break;
		case 3: create_course(sy); break;
		case 4: create_class(sy); break;
		case 5: menu_view(); break;
		case 6: return;
		}
		Delete_schoolyear(sy);
	}
}

void showListEnrolledCourse(student* pS) {
	// choose schoolyear
	schoolyear* sy = new schoolyear;
	readSchoolyear(sy);
	int i = 0; schoolyear* tmpsch = sy; cout << "List of schoolyear: " << endl;
	while (tmpsch) {
		++i;
		cout << i << '.' << tmpsch->time << endl;
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
		cout << "You haven't enrolled any course yet! ";
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
}

void showStudentsInClass(Class*pC) {
	student* pStudentHead = pC->student_list;
	if (!pStudentHead) {
		cout << "No Data" << endl; return;
	}
	cout << "No\tID\t\tName\t\t\t\tBirthday\tGender\tSocial ID\n";
	while (pStudentHead != NULL) {
		string fullname = pStudentHead->prf.lastname + ' ' +pStudentHead->prf.firstname;
		cout << pStudentHead->No << '\t'<<pStudentHead->id << '\t'<<fullname<<'\t'<< ((fullname.length()<16) ? '\t' : ' ') << '\t' << pStudentHead->prf.DOB << "\t" << pStudentHead->prf.gender << "\t" << pStudentHead->prf.social_id << "\n";
		pStudentHead = pStudentHead->pNext;
	}
}

//Vi la show student trong bien student score khong phai bien student nen bat buoc phai cap nhat 
//thong tin student score ngay tu dau chu khong duoc de thi xong nhap diem moi cap nhat
void showStudentsInCourse(course* pC) {
	studentScore* pStuCrs = pC->list_score;
	system("cls");
	cout << "No\tID\tName";
	while (pStuCrs != nullptr) {
		cout << pStuCrs->no << "\t";
		cout << pStuCrs->id << "\t";
		cout << pStuCrs->name << "\t";
		pStuCrs = pStuCrs->pNext;
	}
}
void showEveryClasses(schoolyear*&sy) {
	readSchoolyear(sy);
	int i = 0;
	while (sy != NULL) {
		readListOfClass(sy->list_class, sy->time);
		if (!sy->list_class) {
			sy = sy->next_schyear;
		}
		else {
			while (sy->list_class) {
				i++;
				readListOfStu(sy->list_class->student_list, sy->list_class->class_name);
				if (!sy->list_class->student_list) {
					sy->list_class = sy->list_class->nextClass;
				}
				else {
					cout << i << "." << sy->list_class->class_name << endl;
					showStudentsInClass(sy->list_class);
					sy->list_class = sy->list_class->nextClass;
				}
			}
			sy = sy->next_schyear;
		}
	}
	
}
void menu_view()
{
	system("cls");
	schoolyear* sy = nullptr;
	int n;
	while (true) {
		cout << "1. View list schoolyear" << endl;
		cout << "2. View a list of students in a class " << endl;
		cout << "3. View a list of students in a course" << endl;
		cout << "0. Exit" << endl;
		cin >> n;
		if (!n) break;
		switch (n) {
		case 1:
			//readSchoolyear(sy);
			show_schoolyear(sy); break;
		case 2:
			showEveryClasses(sy);
			system("pause");
			break;
		case 3:
			break;
		}
	}
}

void menu_student(schoolyear*& sy, int semester, account* head) {
	string cl_name; 
	readListOfClass(sy->list_class, sy->time);
	Class* tmp = sy->list_class;
	bool stop = false; student* ret = nullptr; student* stu = new student;
	while (tmp) {
		readStudent1Class(tmp->class_name, tmp);
		stu = tmp->student_list;
		while (stu) {
			if (stu->id == head->username) {
				cl_name = tmp->class_name;
				stop = true;
				break;
			}
			else stu = stu->pNext;
		}
		if (stop == true) break;
		else
			tmp = tmp->nextClass;
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
			enrollCourse(sy, sy->time, sem, stu);
			break;
		}
		case 2: {
			showListEnrolledCourse(stu);
			break;
		}
		case 3: {
			int sem = currentSemester();
			Delete_enrolled_course(sy, sy->time, stu, sem);
			break;
		}
		case 4: {
			int sem = currentSemester();
			readListEnrolled(sy->time, stu, sem);
			enrolledCourse* tmp = stu->list_enrolled;
			if (tmp == nullptr) {
				cout << "Press any key to back.... \n";
				char a = _getch();
			}
			else {
				int i = 0;
				while (tmp) {
					cout << "******COURSE NUMBER: " << i << "******\n";
					cout << "  * ID: " << tmp->id_course << endl;
					cout << "  * Course name: " << tmp->id_course << endl;
					cout << "  * Teacher's name: " << tmp->name_teacher << endl;
					cout << "  * Credits: " << tmp->credits << endl;
					cout << "  * Session 1: " << tmp->ses1.date << '\t' << tmp->ses1.time << endl;
					cout << "  * Session 2: " << tmp->ses2.date << '\t' << tmp->ses2.time << endl;
					tmp = tmp->next;
				}
			}
			break;
		}
		case 5:
			//viewHisHerScore(cur_stu, sy);
			break;
		default: {
			cout << "You input wrong number '\nPlease input again: ";
			break;
		}
		}
	}
}

