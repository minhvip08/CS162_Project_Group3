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
void scoreboardofclass(student* cur_stu, semester* cur_semester, course* c)
{
	if (!cur_stu)
	{
		cout << "\n\t\tThe end!";
		system("pause");
		return;
	}
	if (!c)
	{
		return;
	}
	scoreboardofclass(cur_stu->pNext, cur_semester, cur_semester->course_list);
	studentScore* stuscore;
	double cnt = 0;
	double GPA = 0;
	if (findstuID(cur_stu, stuscore, c))
	{
		cout << "\nStudent ID: " << cur_stu->id << endl;
		while (c)
		{
			cout << c->course_name << ":";
			cout << "\nFinal mark: " << GPAofCourse(stuscore) << endl;
			GPA += stuscore->final;
			++cnt;
			if (!c->next)
			{
				cout << "GPA in this semester: " << GPA / cnt;
				CaloverallGPA(cur_stu);
				cout << "\nOverall GPA: " << cur_stu->gpa;
			}
			c = c->next;
		}
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
