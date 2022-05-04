#include "header.h"
#include "Deallocate_graphic.h"
#include "Data.h"
#include "Support.h"
void Delete_schoolyear(schoolyear*& head)
{
	if (!head) return; 
	while (head) {
		schoolyear* tmp = head->next_schyear;
		Delete_semester(head->sem);
		Delete_class(head->list_class);
		delete head;
		head = tmp;
	}
}

void Delete_semester(semester*& head)
{
	if (!head) return; 
	while (head) {
		semester* tmp = head->next;
		Delete_course(tmp->course_list);
		delete head;
		head = tmp;
	}
}

void Delete_course(course*& head)
{
	if (!head) return;
	while (head) {
		course* tmp = head->next;
		Delete_stdScore(head->list_score);
		delete head;
		head = tmp;
	}
}

void Delete_class(Class*& head)
{
	if (!head) return;
	while (head) {
		Class* tmp = head->nextClass;
		delete head;
		head = tmp;
	}
}

void Delete_stdScore(studentScore*& head)
{
	if (!head) return;
	while (head) {
		studentScore* tmp = head->pNext;
		delete head;
		head = tmp;
	}
}

void Delete_student(student*& head)
{
	if (!head) return;
	while (head) {
		student* tmp = head->pNext;
		delete head;
		head = tmp;
	}
}

void Delete_enrollCourse(enrolledCourse*& head)
{
	if (!head) return;
	while (head) {
		Delete_stdScore(head->list_score);
		enrolledCourse* tmp = head->next;
		delete head;
		head = tmp;
	}
}


void Delete_enrolled_course(schoolyear* &sy, string time, student*& pS, int sem) {
	schoolyear* scy = nullptr; 
	readSchoolyear(scy); 
	while (scy) {
		if (scy->time == time) break;
		else scy = scy->next_schyear; 
	}
	readSemester(scy->sem, time); 
	semester* ss = scy->sem; 
	while (ss) {
		if (ss->mark == sem) break;
		else ss = ss->next; 
	}
	if (!checkEnrollTime(ss)) {
		cout << "Out of registration time\n";
		return; 
	}
	readListEnrolled(time, pS, sem); 
	enrolledCourse* pECCrs = pS->list_enrolled;
	if (pECCrs == nullptr) {
		system("pause");
		return;
	}

	course* c = new course; 
	readListOfCourse(time, c, sem); 
	cout << "Please choose one of the course you want to delete\n";
	int i = 0; enrolledCourse* tmp = pS->list_enrolled;
	while (tmp) {
		++i;
		cout << i << ".ID Course: " << tmp->id_course << '\t' << "Course name: " << tmp->course_name << endl;
		tmp = tmp->next;
	} cout << "0. Exit" << endl;
	int x; cout << "You choose: ";  cin >> x;
	while (x > i) {
		cout << "Invalid number!!" << endl << "Please input again: "; cin >> x;
	}
	if (x == 0) return;
	enrolledCourse* cur = pS->list_enrolled;
	if (x > 1) {
		int h = 1; while (h < x) {
			cur = cur->next; ++h;
		}
	}
	if (cur) {
		cout << "------COURSE INFORMATION------" << endl;
		cout << "ID: " << cur->id_course << endl;
		cout << "Name: " << cur->course_name << endl;
		cout << "Teacher: " << cur->name_teacher << endl;
		cout << "Credits: " << cur->credits << endl;
		cout << "Session 1: " << cur->ses1.date << '\t' << cur->ses1.time << endl;
		cout << "Session 2: " << cur->ses2.date << '\t' << cur->ses2.time << endl;
	}

	cout << "Are you sure you want to delete: \n"; int n;
	cout << "1. Yes" << '\t' << "2. No" << endl;
	cin >> n;
	course* out = new course;
	if (n == 2) return;
	else if (n == 1) {
		enrolledCourse* head = pS->list_enrolled;
		course* keep = c;
		while (keep->ID_course != cur->id_course) {
			keep = keep->next;
		}
		readStudentOfCourse(keep);
		out = keep;
		--keep->cur_student;
		if (cur == head) {
			enrolledCourse* after = head->next;
			head = after;
			pS->list_enrolled = head;
			delete cur;
		}
		else {
			enrolledCourse* before = head;
			while (before->next != cur)
				before = before->next;
			enrolledCourse* after = before->next;
			before->next = after;
			delete cur;
		}
	}
	--pS->countEnroll;
	// xoa student trong course
	studentScore* sts = out->list_score; studentScore* pre = out->list_score, * he = out->list_score;
	while (sts) {
		if (sts->id == pS->id) {
			studentScore* del = sts;
			if (sts == he) {
				he = he->pNext;
				sts = he;
				pre = he;
			}
			else {
				pre->pNext = sts->pNext;
				sts = sts->pNext;
			}
			delete sts;
			continue;
		}
		pre = sts;
		sts = sts->pNext;
	}
	out->list_score = he;
	save_enrollcourse_stu(time, pS, sem);
	saveStudentOfCourse(out);
	saveListOfCourse(sy, c, time, sem);
}

void Delete_course_staff(schoolyear*head) {

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
	

	cout << "These are all courses in this semester: " << endl;
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

	if (cur) {
		cout << "Course information: " << endl;
		cout << "ID: " << cur->ID_course << endl;
		cout << "Name: " << cur->course_name << endl;
		cout << "Teacher: " << cur->teacher_name << endl;
		cout << "Credits: " << cur->credits << endl;
		cout << "Current students: " << cur->cur_student << endl;
	}
	course* c = s_check->course_list;
	cout << "Are you sure you want to delete: \n"; int n;
	cout << "1. Yes" << endl << "2. No" << endl;
	cin >> n;
	if (n == 2) return;
	else if (n == 1) {
		if (cur == c) {
			course* after = cur->next;
			c = after;
			delete cur;
		}
		else {
			course* before = c;
			while (before->next != cur)
				before = before->next;
			course* after = cur->next;
			before->next = after;
			delete cur;
		}
	}

	semester* se = check->sem;
	while (se && se->mark != k) se = se->next;
	--se->num_course;
	cout << "Course deleted successfully" << endl;
	saveListOfCourse(head, c, check->time, k);
}