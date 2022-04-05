#include "header.h"
void saveSchoolyear(schoolyear* sy)
{
	if (!sy) return;
	ofstream fout; fout.open("Schoolyear.txt");
	fout << "Time,Num_sem,Num_class";
	while (sy) {
		fout << endl;
		fout << sy->time << ',' << sy->num_sem << ',' << sy->num_class;
		sy = sy->next_schyear;
	}
	fout.close();
}

void saveListOfClass(schoolyear* sy) // save the name of classes of each schoolyear
{
	if (!sy || !sy->list_class) return;
	ofstream fout; string s = sy->time;
	fout.open(s + "_class.txt");
	Class* tmp = sy->list_class;
	while (tmp) {
		fout << tmp->class_name << endl;
		fout << tmp->total_student;
		tmp = tmp->nextClass;
		if (tmp) fout << endl;
	}
	fout.close();
	saveSchoolyear(sy);// update num_class
}

void saveListOfSemester(schoolyear* sy)
{
	if (!sy || !sy->sem) return;
	ofstream fout; string s = sy->time;
	fout.open(s + "_semester.txt");
	semester* tmp = sy->sem;
	fout << "No,Num Courses,Start day,End day,Start of registration,End of registration";
	while (tmp) {
		fout << endl;
		fout << tmp->mark << ',' << tmp->num_course << ',' << tmp->start_date.day << '/' << tmp->start_date.month << '/' << tmp->start_date.year << ',';
		fout << tmp->end_date.day << '/' << tmp->end_date.month << '/' << tmp->end_date.year << ',';
		fout << tmp->start_regist.day << '/' << tmp->start_regist.month << '/' << tmp->start_regist.year << ',';
		fout << tmp->end_regist.day << '/' << tmp->end_date.month << '/' << tmp->end_date.month;
		tmp = tmp->next;
	}
	fout.close();
	saveSchoolyear(sy); // update num_sem
}

void saveListOfCourse(schoolyear* sy,course* c, string time, int semester)
{
	if (!c) {
		cout << "No available courses" << endl;
		return;
	}
	char k = semester + 48;
	ofstream fout; fout.open(time + "_sem" + k + "_course.txt");
	fout << "Course ID,Course Name,Lecturer,Credits,Students,Session 1,Session 2";
	while (c) {
		fout << endl; fout << c->ID_course << ',';
		fout << c->course_name << ',' << c->teacher_name << ',';
		fout << c->credits << ',' << c->cur_student << ',' << c->ses1.date << '|';
		fout << c->ses1.time << ',' << c->ses2.date << '|' << c->ses2.time;
		c = c->next;
	}
	fout.close();
	saveListOfSemester(sy);
}