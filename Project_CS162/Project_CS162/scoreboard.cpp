#include "header.h"
#include "Scoreboard.h"
#include "Data.h"
#include "Support.h"
#include "Login.h"
int conditionGPA(float m)
{
	if (m >= 8.5 && m <= 10) return 4;
	else if (m < 8.5 && m >= 6.5) return 3;
	else if (m < 6.5 && m >= 4) return 2;
	else if (m < 4 && m >= 1) return 1;
	else return 0; 
}

void gpaOfClass(schoolyear* head)
{
	readSchoolyear(head);
	if (!head) {
		cout << "You haven't input a schoolyear" << endl;
		return;
	}

	schoolyear* tmp = head; cout << "List of schoolyear: " << endl; int i = 0;
	while (tmp) {
		++i;
		cout << i << ". " << tmp->time << '\t';
		tmp = tmp->next_schyear;
	} cout << endl;
	cout << "Which schoolyear you want to view semester? "; int x; cin >> x;
	while (x > i) {
		cout << "You input the wrong number. Please input again: "; cin >> x; 
	}
	schoolyear* check = head;
	if (x > 1) {
		int j = 1; while (j < x) { check = check->next_schyear; ++j; }
	}
	readListOfClass(check->list_class, check->time);
	cout << "List of class: " << endl;
	Class* cl = check->list_class; int a = 0;
	while (cl) {
		++a;
		cout << a << ". " << cl->class_name << endl;
		cl = cl->nextClass;
	}
	cout << "Which class you want to view information: "; int t; cin >> t;
	while (t > a) {
		cout << "You input the wrong number. Please input again: "; cin >> t; 
	}
	Class* ctmp = check->list_class;
	if (t > 1) {
		int j = 1; while (j < t) { ctmp = ctmp->nextClass; ++j; }
	}
	Class* read = new Class;
	readStudent1Class(ctmp->class_name, ctmp);
	if (!read) {
		cout << "Please choose another class to view"<<endl;
		return;
	}
	else {
		student* stu = ctmp->student_list;
		int sem = currentSemester();
		int z = 0;
		while (stu) {
			++z;
			cout << "***********STUDENT NUMBER: " << z << "**********\n";
			cout << "\t* Name: " << stu->prf.lastname + ' ' + stu->prf.firstname << endl;
			cout << "\t* Course enrolled: \n"; int b = 1;
			readListEnrolled(check->time, stu, sem);
			enrolledCourse* ec = stu->list_enrolled;
			float gpa = 0; float cred = 0;
			while (ec) {
				cout << "\t\t* Course number: " << b << endl;
				cout << "\t\t* Course name: " << ec->course_name << endl;
				cout << "\t\t* Course ID: " << ec->id_course << endl;
				cout << "\t\t\tOther\tMid\tFinal\tTotal:\n";
				cout << "\t\t\t" << ec->ecscore.other << '\t' << ec->ecscore.mid << '\t' << ec->ecscore.final << '\t' << ec->ecscore.total << endl;
				gpa += conditionGPA(ec->ecscore.total) * ec->credits;
				cred += ec->credits;
				++b;
				ec = ec->next;
			}
			float end = gpa / cred;
			cout << "\t* Total GPA in semester " << sem << ": " << end << endl;
			float gpaf = 0; float credf = 0;
			for (int i = 1; i <= 3; i++) {
				readListEnrolled(check->time, stu, i);
				enrolledCourse* ecf = stu->list_enrolled;
				while (ecf) {
					gpaf += conditionGPA(ecf->ecscore.total) * ecf->credits;
					credf += ecf->credits;
					ecf = ecf->next;
				}
			}
			float endf = gpaf / credf;
			cout << "\t* Total GPA of schoolyear: " << endf << endl;
			stu = stu->pNext;
		}
	}
}

void view_scoreboard_sem(student* stu)
{
	schoolyear* head = nullptr;
	readSchoolyear(head);
	if (!head) {
		cout << "You haven't input a schoolyear" << endl;
		return;
	}

	schoolyear* tmp = head; cout << "List of schoolyear: " << endl; int i = 0;
	while (tmp) {
		++i; 
		cout << i << ". " << tmp->time << '\t';
		tmp = tmp->next_schyear;
	} cout << endl;
	cout << "Which schoolyear you want to view information? "; int x; cin >> x;
	while (x > i) {
		cout << "You input wrong number. PLease input again: "; cin >> x;
	}
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
	while (k > check->num_sem) {
		cout << "You input the wrong number. Please input again: "; cin >> k;
	}
	semester* s_check = check->sem;
	if (k != check->num_sem) {
		int h = 1; while (h < k) { s_check = s_check->next; ++h; }
	}
	readListEnrolled(check->time, stu, k);
	cout << "*********Semester " << k << "********\n";
	cout << "\t* Courses: \n";
	enrolledCourse* ec = stu->list_enrolled;
	float gpa = 0; float cred = 0; int b = 0;
	while (ec) {
		++b;
		cout << "\t\t* Course number: " << b << endl;
		cout << "\t\t* Name: " << ec->course_name << endl;
		cout << "\t\t* ID: " << ec->id_course << endl;
		cout << "\t\t* Teacher: " << ec->name_teacher << endl;
		cout << "\t\t* Credits: " << ec->credits << endl;
		cout << "\t\t* Mark: \n";
		cout << "\t\t\tOther\tMid\tFinal\tTotal\n";
		cout << "\t\t\t" << ec->ecscore.other << '\t' << ec->ecscore.mid << '\t' << ec->ecscore.final << '\t' << ec->ecscore.total << '\n';
		gpa += conditionGPA(ec->ecscore.total) * ec->credits;
		cred += ec->credits;
		ec = ec->next;
		cout << "******************************************************************************"<<endl;
	}
	float end = gpa / cred;
	cout << "\t* Total GPA in semester " << k << ": " << end << endl;

	float gpaf = 0; float credf = 0;
	for (int i = 1; i <= 3; i++) {
		readListEnrolled(check->time, stu, i);
		enrolledCourse* ecf = stu->list_enrolled;
		while (ecf) {
			gpaf += conditionGPA(ecf->ecscore.total) * ecf->credits;
			credf += ecf->credits;
			ecf = ecf->next;
		}
	}
	float endf = gpaf / credf;
	cout << "\t* Total GPA of schoolyear: " << endf << endl;
}

void Scoreboard_staff(schoolyear* head)
{
	readSchoolyear(head);
	if (!head) {
		cout << "You haven't input a schoolyear" << endl;
		return;
	}

	schoolyear* tmp = head; cout << "List of schoolyear: " << endl; int i = 0;
	while (tmp) {
		++i;
		cout << i << ". " << tmp->time << '\t';
		tmp = tmp->next_schyear;
	} cout << endl;
	cout << "Which schoolyear you want to view information? "; int x; cin >> x;
	while (x > i) {
		cout << "You input wrong number. PLease input again: "; cin >> x;
	}
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
	while (k > check->num_sem) {
		cout << "You input the wrong number. Please input again: "; cin >> k;
	}
	semester* s_check = check->sem;
	if (k != check->num_sem) {
		int h = k; while (h < check->num_sem) { s_check = s_check->next; ++h; }
	}
	readListOfCourse(check->time, s_check->course_list, s_check->mark);
	course* c = s_check->course_list;
	while (c) {
		importscoreboardcourse(c);
		print(c);
		c = c->next;
	}
}

void viewscoboardofc_menu(schoolyear* sy)
{
	readSchoolyear(sy);
	while (sy) {
		if (checkCurrentSchoolyear(sy)) break;
		sy = sy->next_schyear;
	}
	if (!sy) return;
	readSemester(sy->sem, sy->time);
	int sem = currentSemester();
	semester* s = sy->sem;
	while (s) {
		if (s->mark == sem) break;
		s = s->next;
	}
	readListOfCourse(sy->time, s->course_list, sem);
	cout << "List of course:" << endl;
	int i = 0;
	course* tmp = s->course_list;
	while (tmp) {
		++i;
		cout << i << ". Course ID: " << tmp->ID_course << '\t' << "Course name: " << tmp->course_name << endl;
		tmp = tmp->next;
	}	cout << "0. Exit" << endl;
	cout << "Please choose the number represented the course(1, 2, 3, ...) : "; int x; cin >> x;
	while (x > i) {
		cout << "You input the wrong number. Please input again: "; cin >> x;
	}
	if (x == 0) return;
	course* cur = s->course_list;
	if (x > 1) {
		int h = 1; while (h < x) {
			cur = cur->next; ++h;
		}
	}
	importscoreboardcourse(cur);
	print(cur);
}

void print(course* c)
{
	cout << "COURSE NAME: " << c->course_name << endl;
	cout << "No\t\tID\t\tFull Name\t\tOther\t\tMid\t\tFinal\t\t\Total\n";
	studentScore* sco = c->list_score;
	while (sco) {
		cout << sco->no << "\t\t" << sco->id << "\t" << sco->name << ((sco->name.length() < 16) ? '\t' : ' ') << "\t" << sco->stscore.other << "\t\t" << sco->stscore.mid << "\t\t" << sco->stscore.final << "\t\t" << sco->stscore.total << endl;
		sco = sco->pNext;
	}
}

void updatestures_menu(schoolyear* sy)
{
	readSchoolyear(sy);
	while (sy) {
		if (checkCurrentSchoolyear(sy)) break;
		sy = sy->next_schyear;
	}
	if (!sy) return;
	readSemester(sy->sem, sy->time);
	int sem = currentSemester();
	semester* s = sy->sem;
	while (s) {
		if (s->mark == sem) break;
		s = s->next;
	}
	cout << "List of course:" << endl; readListOfCourse(sy->time, s->course_list, sem);
	int i = 0;
	course* tmp = s->course_list;
	while (tmp) {
		++i;
		cout << i << ". Course ID: " << tmp->ID_course << '\t' << "Course name: " << tmp->course_name << endl;
		tmp = tmp->next;
	}	cout << "0. Exit" << endl;
	cout << "Please choose the number represented the course(1, 2, 3, ...) : "; int x; cin >> x;
	while (x > i) {
		cout << "You input the wrong number. Please input again: "; cin >> x;
	}
	if (x == 0) return;
	course* cur = s->course_list;
	if (x > 1) {
		int h = 1; while (h < x) {
			cur = cur->next; ++h;
		}
	}
	importscoreboardcourse(cur);
	print(cur);
	cout << "Enter student's number you want to update his/her score: "; int k; cin >> k;
	while (k > cur->cur_student) {
		cout << "You input wrong number. PLease input again: "; cin >> k; 
	}
	studentScore* stu = cur->list_score;
	while (stu) {
		if (stu->no == k) break;
		else
			stu = stu->pNext;
	}
	cout << "Student name: " << stu->name << endl;
	studentScore* stc = stu;
	if (!stu) {
		cout << "Can't find student!!!" << endl;
		return;
	}
	cout << "Which score you want to update: " << endl;
	cout << "1. Update other score." << endl;
	cout << "2. Update midterm score." << endl;
	cout << "3. Update final score." << endl;
	cout << "0. Exit." << endl;
	int choice; cout << "Your option: "; cin >> choice;
	if (choice == 0) return;
	else if (choice > 3) {
		cout << "You input the wrong number. Please input again: "; cin >> choice;
	}
	switch (choice) {
	case 1: {
		float other; cout << "New other score: "; cin >> other;
		stc->stscore.other = other;
		break;
	}
	case 2: {
		float mid; cout << "New midterm score: "; cin >> mid;
		stc->stscore.mid = mid;
		break;
	}
	case 3: {
		float final; cout << "New final score: "; cin >> final;
		stc->stscore.final = final;
		break;
	}
	}
	float total = stc->stscore.other * 0.3 + stc->stscore.mid * 0.3 + stc->stscore.final * 0.4;
	cout << "New total score: " << total << endl;
	stc->stscore.total = total;
	stu = stc;
	saveScoreboardCSV(cur);
	saveStudentOfCourse(cur);
	student* snew = new student;
	snew->id = stu->id;
	readListEnrolled(sy->time, snew, sem);
	enrolledCourse* ec = snew->list_enrolled;
	while (ec) {
		if (ec->id_course == cur->ID_course) {
			ec->ecscore = stc->stscore;
			break;
		}
		else ec = ec->next;
	}
	save_enrollcourse_stu(sy->time, snew, sem);
}

void view_scoreboard_stu(student* stu) {
	schoolyear* sy = nullptr;
	readSchoolyear(sy);
	while (sy) {
		if (checkCurrentSchoolyear(sy)) break;
		sy = sy->next_schyear;
	}
	if (!sy) return;
	readSemester(sy->sem, sy->time);
	int sem = currentSemester();
	semester* s = sy->sem;
	while (s) {
		if (s->mark == sem) break;
		else
			s = s->next;
	}
	readListOfCourse(sy->time, s->course_list, sem);
	cout << "List of course:" << endl;
	int i = 0;
	course* tmp = s->course_list;
	while (tmp) {
		++i;
		cout << i << ". Course ID: " << tmp->ID_course << '\t' << "Course name: " << tmp->course_name << endl;
		tmp = tmp->next;
	}	cout << "0. Exit" << endl;

	cout << "Please choose the number represented the course(1, 2, 3, ...) : "; int x; cin >> x;
	while (x > i) {
		cout << "You input the wrong number. Please input again: "; cin >> x;
	}
	if (x == 0) return;
	course* cur = s->course_list;
	if (x > 1) {
		int h = 1; while (h < x) {
			cur = cur->next; ++h;
		}
	}

	importscoreboardcourse(cur);
	cout << "COURSE NAME: " << cur->course_name << endl;
	studentScore* ec = cur->list_score;
	while (ec) {
		if (ec->id == stu->id) {
			cout << "Other\t\tMid\t\tFinal\t\t\Total\n";
			cout << ec->stscore.other << "\t\t" << ec->stscore.mid << "\t\t" << ec->stscore.final << "\t\t" << ec->stscore.total << endl;
			break;
		}
		else
			ec = ec->pNext;
	}
}