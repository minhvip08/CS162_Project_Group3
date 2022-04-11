#include "header.h"
bool findstuID(student* stu, studentScore* &ss, course* c) {
	if (!c->list_score)
	{
		cout << "Error";
		return;
	}
	studentScore* ss = c->list_score;
	while (ss)
	{
		if (ss->id == stu->id)
			return true;
		ss = ss->pNext;
	}
	return false;
}
double GPAofCourse(studentScore*& stu)
{
	return stu->total = stu->final * 0.4 + stu->mid * 0.3 + stu->other * 0.3;
}
void scoreboardofclass(Class* cur_class, semester* cur_semester, course* c, int i, double GPA)
{
	if (!cur_class->student_list || !cur_semester->course_list || !c->next)
	{
		cout << "\nThe end!";
		return;
	}
	student* stu = cur_class->student_list;
	while (stu)
	{
		studentScore* ss;
		if (findstuID(stu, ss, c))
		{
			cout << "\n" << "Final mark of this student in " << c->ID_course << " is: " << ss->final << endl;
			cout << GPAofCourse(ss) << endl;
			scoreboardofclass(cur_class, cur_semester, c->next, i + 1, GPA + ss->total);
			GPA = 0;
		}
		stu = stu->pNext;
	}
	if (!c->next)
	{
		cout << "\nGPA in this semester: " << GPA / i;
		cout << "\nOverall GPA is: " << stu->gpa;
		return;
	}
}
void CaloverallGPA(student* &s)
{
	if (!s->list_gpa)
		return;
	s->gpa = 0;
	int cnt = 0;
	finalGPA* f = s->list_gpa;
	while (f)
	{
		++cnt;
		s->gpa += f->gpa;
		f = f->next;
	}
	s->gpa /= cnt;
}
