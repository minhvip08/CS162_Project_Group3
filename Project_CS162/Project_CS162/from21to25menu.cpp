#include "header.h"
#include "Support.h"
#include "Data.h"
#include "Input.h"
#include "Menu.h"
#include "Scoreboard.h"
#include "Deallocate_graphic.h"
#include "Login.h"
void exportstulist_menu(schoolyear* scy) // chay lai
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
		cout << "Invalid number!!" << endl << "Please input again: "; cin >> x;
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
		cout << "List of student in this course is empty" << endl;
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

void importscoreboard_menu(schoolyear* scy)
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
	cout << "List of course:" << endl; readListOfCourse(scy->time, s->course_list, sem);
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

	ifstream fin; fin.open(cur->ID_course + ".csv");
	if (isEmpty(fin)) {
		return;
	}
	studentScore* stu = new studentScore; cur->list_score = stu;
	string a; getline(fin, a, '\n');

	while (!fin.eof()) {
		fin >> stu->no;
		string s; getline(fin, s, ',');
		getline(fin, stu->id, ',');
		getline(fin, stu->name, ',');
		
		fin >> stu->stscore.other;
		string d; getline(fin, d, ',');
		fin >> stu->stscore.mid;

		string c; getline(fin, c, ',');
		fin >> stu->stscore.final;
		getline(fin, d, ',');
		fin >> stu->stscore.total;
		fin.ignore();
		//string e; getline(fin, e, '\n');
		if (fin.eof()) {
			stu->pNext = nullptr;
			break;
		}
		else {
			stu->pNext = new studentScore;
			stu = stu->pNext;
		}
	}
	cout << "Import successfully" << endl;
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
		cout << "Invalid number!!" << endl << "Please input again: "; cin >> x;
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

void importscoreboardcourse(course*& c)
{
	ifstream fin; fin.open(c->ID_course + ".csv");
	if (isEmpty(fin)) {
		return;
	}
	studentScore* stu = new studentScore; c->list_score = stu;
	string a; getline(fin, a, '\n');

	while (!fin.eof()) {
		fin >> stu->no;
		string s; getline(fin, s, ',');
		getline(fin, stu->id, ',');

		getline(fin, stu->name, ',');
		fin >> stu->stscore.other;
		string d; getline(fin, d, ',');
		fin >> stu->stscore.mid;
		string f; getline(fin, f, ',');
		fin >> stu->stscore.final;
		getline(fin, d, ',');
		fin >> stu->stscore.total;
		fin.ignore();
		//string e; getline(fin, e, '\n');
		if (fin.eof()) {
			stu->pNext = nullptr;
			break;
		}
		else {
			stu->pNext = new studentScore;
			stu = stu->pNext;
		}
	}
}
void print(course* c)
{
	cout << "COURSE NAME: " << c->course_name << endl;
	cout << "No\t\tID\t\tFull Name\t\tOther\t\tMid\t\tFinal\t\t\Total\n";
	studentScore* sco = c->list_score;
	while (sco) {
		cout << sco->no << "\t\t" << sco->id << "\t" <<sco->name<< ((sco->name.length() < 16) ? '\t' : ' ') << "\t" << sco->stscore.other << "\t\t" << sco->stscore.mid << "\t\t" << sco->stscore.final << "\t\t" << sco->stscore.total << endl;
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
		cout << "Invalid number!!" << endl << "Please input again: "; cin >> x;
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
		cout << "You input wrong number!!!\nPLease input again: "; cin >> choice;
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
		cout << "Invalid number!!" << endl << "Please input again: "; cin >> x;
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