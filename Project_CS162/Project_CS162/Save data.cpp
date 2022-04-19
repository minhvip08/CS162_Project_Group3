#include "header.h"
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
	//if (!sy || !sy->list_class) return;
	Class* cur = sy->list_class; int cnt = 0;
	while (cur) {
		++cnt;
		cur = cur->nextClass;
	}
	ofstream fout; fout.open(sy->time + "_class.txt");
	fout << cnt << endl; 
	Class* tmp = sy->list_class;
	while (tmp) {
		fout << tmp->class_name << endl;
		fout << tmp->total_student << endl;
		tmp = tmp->nextClass;
	}
	fout.close();
	saveSchoolyear(sy);// update num_class
}

void saveListOfSemester(schoolyear* sy)
{
	//if (!sy || !sy->sem) return;
	semester* cur = sy->sem; int cnt = 0; 
	while (cur) {
		++cnt; 
		cur = cur->next;
	}
	ofstream fout; string s = sy->time;
	fout.open(s + "_semester.txt");
	semester* tmp = sy->sem; fout << cnt << endl; 
	//fout << "No,Num Courses,Start day,End day,Start of registration,End of registration";
	while (tmp) {
		fout << tmp->mark << endl;
		fout << tmp->num_course << endl;
		fout << tmp->start_date.day << '\t' << tmp->start_date.month << '\t' << tmp->start_date.year << endl;
		fout << tmp->end_date.day << '\t' << tmp->end_date.month << '\t' << tmp->end_date.year << endl;
		fout << tmp->start_regist.day << '\t' << tmp->start_regist.month << '\t' << tmp->start_regist.year << endl;
		fout << tmp->end_regist.day << '\t' << tmp->end_regist.month << '\t' << tmp->end_regist.year << endl;
		tmp = tmp->next;
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
	//fout << "Course ID,Course Name,Lecturer,Credits,Students,Session 1,Session 2";
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