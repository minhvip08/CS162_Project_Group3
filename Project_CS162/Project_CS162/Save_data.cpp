#include "header.h"
#include "Data.h"
#include "Support.h"
void saveSchoolyear(schoolyear* sy)
{
	//if (!sy) return;
	schoolyear* tmp = sy; int cnt = 0; 
	while (tmp) {
		++cnt;
		tmp = tmp->next_schyear; 
	}
	ofstream fout; fout.open("Schoolyear.txt");
	fout << cnt << endl; 
	//fout << "Time,Num_sem,Num_class";
	while (sy) {
		fout << sy->time << '\n' << sy->num_sem << '\n' << sy->num_class << '\n';
		sy = sy->next_schyear;
	}
	fout.close();
}

void saveListOfClass(schoolyear* sy) // save the name of classes of each schoolyear
{
	schoolyear* scy = sy; ofstream fout;
	while (scy) {
		Class* cur = scy->list_class; int cnt = 0;
		if (!cur) {
			scy = scy->next_schyear;
			continue;
		}
		while (cur) {
			++cnt;
			cur = cur->nextClass;
		}
		fout.open(scy->time + "_class.txt");
		fout << cnt << endl;
		Class* tmp = scy->list_class;
		while (tmp) {
			fout << tmp->class_name << endl;
			fout << tmp->total_student << endl;
			tmp = tmp->nextClass;
		}
		scy = scy->next_schyear;
	}

	fout.close();
	saveSchoolyear(sy);// update num_class
}

void saveListOfSemester(schoolyear* sy)
{
	ofstream fout; schoolyear* scy = sy;
	while (scy) {
		semester* cur = scy->sem; int cnt = 0;
		if (!cur) {
			scy = scy->next_schyear;
			continue;
		}
		else {
			while (cur) {
				++cnt;
				cur = cur->next;
			}
			string s = scy->time;
			fout.open(s + "_semester.txt");
			semester* tmp = scy->sem; fout << cnt << endl;
			while (tmp) {
				fout << tmp->mark << endl;
				fout << tmp->num_course << endl;
				fout << tmp->start_date.day << '\t' << tmp->start_date.month << '\t' << tmp->start_date.year << endl;
				fout << tmp->end_date.day << '\t' << tmp->end_date.month << '\t' << tmp->end_date.year << endl;
				fout << tmp->start_regist.day << '\t' << tmp->start_regist.month << '\t' << tmp->start_regist.year << endl;
				fout << tmp->end_regist.day << '\t' << tmp->end_regist.month << '\t' << tmp->end_regist.year << endl;
				tmp = tmp->next;
			}
		}
		scy = scy->next_schyear;
	}
	fout.close();
	saveSchoolyear(sy); // update num_sem
}

void saveListOfCourse(schoolyear* sy,course* c, string time, int semester)
{
	course* cur = c; int cnt = 0;
	while (cur) {
		++cnt;
		cur = cur->next; 
	}
	char k = semester + 48;
	ofstream fout; fout.open(time + "_sem" + k + "_course.txt");
	course* tmp = c;
	fout << cnt << endl; 
	while (tmp) {
		fout << tmp->ID_course << endl;
		fout << tmp->course_name << endl;
		fout << tmp->teacher_name << endl;
		fout << tmp->credits << endl;
		fout << tmp->max_student << endl;
		fout << tmp->cur_student << endl;
		fout << tmp->ses1.date << '\t' << tmp->ses1.time << endl;
		fout << tmp->ses2.date << '\t' << tmp->ses2.time << endl;
		tmp = tmp->next;
	}
	fout.close();
	saveListOfSemester(sy);
}

void save_enrollcourse_stu(string time, student* s, int semester)
{
	if (!s->list_enrolled) {
		cout << "Can't save" << endl;
		return;
	}
	string id = s->id; char k = semester + 3*findYear(s->id) + 48;
	ofstream fout; fout.open(id + '_' + k + "sem.txt", ios::trunc);
	enrolledCourse* c = s->list_enrolled; int cnt = 0;
	while (c) {
		++cnt;
		c = c->next;
	}
	fout << cnt << endl;
	enrolledCourse* tmp = s->list_enrolled;
	while (tmp) {
		fout << tmp->id_course << endl;
		fout << tmp->course_name << endl;
		fout << tmp->name_teacher << endl;
		fout << tmp->credits << endl;
		fout << tmp->ses1.date << '\t' << tmp->ses1.time << endl;
		fout << tmp->ses2.date << '\t' << tmp->ses2.time << endl;
		fout << tmp->ecscore.other << endl;
		fout << tmp->ecscore.mid << endl; 
		fout << tmp->ecscore.final << endl; 
		fout << tmp->ecscore.total << endl;
		tmp = tmp->next;
	}
	fout.close();
}
void saveStudentOfCourse(course* c)
{
	ofstream fout; fout.open(c->ID_course + ".txt", ios::trunc);
	if (!c->list_score) {
		cout << "List of student is empty" << endl;
		fout << '0' << endl;
		c->list_score = nullptr;
		return;
	}
	studentScore* tmp = c->list_score; int cnt = 0;
	while (tmp) {
		++cnt;
		tmp = tmp->pNext;
	}
	fout << cnt << endl;
	studentScore* ss = c->list_score;
	while (ss) {
		fout << ss->id << '\n' << ss->name << '\n';
		fout << ss->stscore.other << '\n';
		fout << ss->stscore.mid << '\n';
		fout << ss->stscore.final << '\n';
		fout << ss->stscore.total << '\n';
		ss = ss->pNext;
	}
	fout.close();
}

void exportstulist_menu(schoolyear* scy)
{
	readSchoolyear(scy);
	while (scy) {
		if (checkCurrentSchoolyear(scy)) break;
		scy = scy->next_schyear;
	}
	if (!scy) return;
	readSemester(scy->sem, scy->time);
	int sem = currentSemester();
	semester* s = scy->sem;
	while (s) {
		if (s->mark == sem) break;
		s = s->next;
	}
	readListOfCourse(scy->time, s->course_list, sem);
	cout << "List of courses:" << endl;
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
	ofstream fout;
	readStudentOfCourse(cur);
	if (!cur->list_score) {
		cout << "List of students in this course is empty" << endl;
		return;
	}
	studentScore* stu = cur->list_score;
	fout.open(cur->ID_course + ".csv");
	fout << "No,ID,Fullname,Other,Mid,Final,Total\n";
	int j = 0;
	while (stu) {
		++j; stu->no = j;
		fout << stu->no << ',';
		fout << stu->id << ',';
		fout << stu->name << ',';
		fout << stu->stscore.other << ',';
		fout << stu->stscore.mid << ',';
		fout << stu->stscore.final << ',';
		fout << stu->stscore.total;
		stu = stu->pNext;
		if (stu) fout << '\n';
	}
	fout.close();
	cout << "Export successfully" << endl;
}

void saveScoreboardCSV(course* c) {
	studentScore* stu = c->list_score;
	ofstream fout; fout.open(c->ID_course + ".csv");
	fout << "No,ID,Name,Other,Mid,Final,Total\n";
	while (stu) {
		fout << stu->no << ',';
		fout << stu->id << ',';
		fout << stu->name << ',';
		fout << stu->stscore.other << ',';
		fout << stu->stscore.mid << ',';
		fout << stu->stscore.final << ',';
		fout << stu->stscore.total;
		stu = stu->pNext;
		if (stu) fout << '\n';
	}
	fout.close();
}