#include "header.h"
#include "Support.h"
#include "Data.h"
#include "Scoreboard.h"
void copystudentinfor(student* &stu1, student* &stu2)
{
	if (stu1 == nullptr)
		return;
	stu1->No = stu2->No;
	stu1->prf.firstname = stu2->prf.firstname;
	stu1->prf.lastname = stu2->prf.lastname;
	stu1->id = stu2->id;
	stu1->prf.gender = stu2->prf.gender;
	stu1->prf.social_id = stu2->prf.social_id;
	stu1->prf.DOB = stu2->prf.DOB;

}
void copyliststu(Class*& c1, Class* c2) // c1 is the new class (dont have any students)
{
	
	if (c2->student_list == nullptr)
		return;
	student* tmp = c1->student_list;
	student* cur = c2->student_list;
	while (cur)
	{
		if (c1->student_list == nullptr)
		{
			copystudentinfor(c1->student_list, cur);
			tmp = c1->student_list;
		}
		else
		{
			tmp->pNext = new student;
			tmp = tmp->pNext;
			copystudentinfor(tmp, cur);
			tmp->pNext = nullptr;
		}
		cur = cur->pNext;
	}

}
void exportlistofstudent(course *cour)
{
	ofstream fout;
	fout.open(cour->ID_course + ".csv");
	if (!fout.is_open())
	{
		cout << "Error!" << endl;
		system("pause");
		return;
	}
	void updatestures_menu(schoolyear * sy)
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
			cout << "Invalid number!!" << endl << "Please input again: "; cin >> x;
		}
		if (x == 0) return;
		course* cur = s->course_list;
		if (x > 1) {
			int h = 1; while (h < x) {
				cur = cur->next; ++h;
			}
		}
		//viewscoreboardcourse(cur); 
		cout << "Enter student's number you want to update his/her score: "; int k; cin >> k;
		studentScore* stu = cur->list_score;
		while (stu) {
			if (stu->no == k) break;
			else
				stu = stu->pNext;
		}
		if (!stu) {
			cout << "Can't find student!!!" << endl;
			return;
		}
		while (1) {
			cout << "Which score you want to update: " << endl;
			cout << "1. Update other score." << endl;
			cout << "2. Update midterm score." << endl;
			cout << "3. Update final score." << endl;
			cout << "0. Exit." << endl;
			int choice; cout << "Your option: "; cin >> choice;
			if (choice == 0) return;
			else if (choice > 3) {
				cout << "You input wrong number!!!\nPLease input again: "; cin >> choice;
			}
			switch (choice) {
			case 1: {
				float other; cout << "New other score: "; cin >> other;
				stu->stscore.other = other;
				break;
			}
			case 2: {
				float mid; cout << "New midterm score: "; cin >> mid;
				stu->stscore.mid = mid;
				break;
			}
			case 3: {
				float final; cout << "New final score: "; cin >> final;
				stu->stscore.final = final;
				break;
			}
			}
			float total = stu->stscore.other * 0.3 + stu->stscore.mid * 0.3 + stu->stscore.final * 0.4;
			cout << "New total score: " << total << endl;
			stu->stscore.total = total;
		}
		saveScoreboardCSV(cur);
	}
	studentScore* cur = cour->list_score;
	int i = 0; 
	while (cur)
	{
		++i; 
		fout << i << ',';
		fout << cur->id << ',';
		fout << cur->name << ',';
		fout << cur->stscore.other << ','; 
		fout << cur->stscore.mid << ',';
		fout << cur->stscore.final << ',';
		fout << cur->stscore.total << '\n';
		cur = cur->pNext; 

	}
	fout.close();
}

void viewstudentscore(studentScore* sco)
{
	while (sco) {
		cout << sco->no << "\t\t\t" << sco->id << "\t\t\t" << sco->name << "\t\t\t" << sco->stscore.total << "\t\t\t" << sco->stscore.final << "\t\t\t" << sco->stscore.mid << "\t\t\t" << sco->stscore.other << endl;
		sco = sco->pNext; 
	}
}
//void viewscoreboardcourse(course* c)
//{
//	importscoretoCourse(c); 
//	/*if (!c->list_score)
//	{
//		cout << "Empty list of student" << endl;
//		cout << "...Press any key to continue\n"; 
//		system("pause");
//		return;
//	}*/
//	cout << "COURSE NAME:" << c->ID_course << endl;
//	cout << "No\t\t\tID\t\t\tFull Name\t\t\tOther\t\t\tMid\t\t\tFinal\t\t\Total\n";
//	studentScore* sco = c->list_score;
//	while (sco) {
//		cout << sco->no << "\t\t\t" << sco->id << "\t\t\t" << sco->name << "\t\t\t" << sco->stscore.other << "\t\t\t" << sco->stscore.mid << "\t\t\t" << sco->stscore.final << "\t\t\t" << sco->stscore.total << endl;
//		sco = sco->pNext;
//	}
//}
