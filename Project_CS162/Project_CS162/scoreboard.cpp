#include "header.h"
#include "Scoreboard.h"
bool findstuID(student* stu, studentScore* &ss, course* c) {
	if (!c->list_score)
	{
		cout << "Error";
		return false;
	}
	ss = c->list_score;
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
	return stu->stscore.total = stu->stscore.final * 0.4 + stu->stscore.mid * 0.3 + stu->stscore.other * 0.3;
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
			GPA += stuscore->stscore.final;
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
	scoreboardofclass(cur_stu->pNext, cur_semester, cur_semester->course_list);
}
//void viewhisherscoreboard(student* cur_stu)
//{
//	enrolledcourse* enrollc = cur_stu->list_enrolled;
//	if (!enrollc) {
//		cout << "you haven't enrolled any course yet!" << endl;
//		return;
//	}
//	studentscore* stu_score = enrollc->list_score;
//	while (enrollc) {
//		if (!stu_score) {
//			cout << "your score in "<< enrollc->course_name <<"has not been marked yet!" << endl;
//		}
//		else {
//			cout << "course name: " << enrollc->course_name << endl;
//			cout << "other mark: " << stu_score->stscore.other << endl;
//			cout << "midterm mark: " << stu_score->stscore.mid << endl;
//			cout << "final mark: " << stu_score->stscore.final << endl;
//			cout << "total mark:" << stu_score->stscore.total << endl;
//			cout << endl;
//		}
//		enrollc = enrollc->next;
//	}
//}
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
