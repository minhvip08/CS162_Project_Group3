#include "header.h"
#include "Data.h"
#include "Support.h"
void readSchoolyear(schoolyear*& sy)
{
	ifstream fin; fin.open("Schoolyear.txt");
	if (isEmpty(fin)) {
		cout << "List of schoolyear is empty" << endl;
		cout << "Please initialize some data" << endl;
		return;
	}
	int n; fin >> n; 
	schoolyear* tmp = new schoolyear; sy = tmp; //fin.get(); 
	for (int i = 0; i < n; i++) {
		fin.get();
		getline(fin, tmp->time, '\n');
		fin >> tmp->num_sem; fin >> tmp->num_class; 
		tmp->sem = nullptr; 
		tmp->list_class = nullptr; 
		if (i == n-1) {
			tmp->next_schyear = nullptr;
		}
		else {
			tmp->next_schyear = new schoolyear;
			tmp = tmp->next_schyear;
		}
	}
	fin.close();
}

void readListOfClass(Class*& cl, string time)
{
	ifstream fin; fin.open(time + "_class.txt");
	if (isEmpty(fin)) {
		cout << "List of classes in this schoolyear is empty" << endl;
		return;
	}
	int n; fin >> n; 
	Class* tmp = new Class; cl = tmp;
	for (int i = 0; i < n; i++) {
		fin.get();
		getline(fin, tmp->class_name, '\n');
		tmp->student_list = nullptr;
		fin >> tmp->total_student;
		//fin.get(); 
		if (i == n - 1) tmp->nextClass = nullptr;
		else {
			tmp->nextClass = new Class;
			tmp = tmp->nextClass;
		}
	}
	fin.close();
}

void readListOfCourse(string time, course*& c, int semester)
{
	char k = semester + 48;
	ifstream fin; fin.open(time + "_sem" + k + "_course.txt");
	if (isEmpty(fin)) {
		cout << "List of courses in this semester is empty" << endl;
		return;
	}
	int n; fin >> n; 
	course* tmp = new course; c = tmp; fin.get(); 
	for (int i = 0; i < n; i++) {
		tmp->list_score = nullptr;
		getline(fin, tmp->ID_course, '\n');
		getline(fin, tmp->course_name, '\n');
		getline(fin, tmp->teacher_name, '\n');
		fin >> tmp->credits >> tmp->max_student >> tmp->cur_student;
		fin.get();
		getline(fin, tmp->ses1.date, '\t'); getline(fin, tmp->ses1.time, '\n');
		getline(fin, tmp->ses2.date, '\t'); getline(fin, tmp->ses2.time, '\n');

		if (i == n - 1) {
			tmp->next = nullptr;
		}
		else {
			tmp->next = new course;
			tmp = tmp->next;
		}
	}
	fin.close(); 
}

void readSemester(semester*& s, string time)
{
	ifstream fin; fin.open(time + "_semester.txt");
	if (isEmpty(fin)) {
		cout << "There is no available semester." << endl;
		cout << "Please initialize some semesters " << endl;
		return;
	}
	int n; fin >> n; 
	semester* tmp = new semester; s = tmp;
	for (int i = 0; i < n; i++) {
		fin >> tmp->mark; fin >> tmp->num_course; 
		tmp->course_list = nullptr; 
		fin >> tmp->start_date.day >> tmp->start_date.month >> tmp->start_date.year;
		fin >> tmp->end_date.day >> tmp->end_date.month >> tmp->end_date.year;
		fin >> tmp->start_regist.day >> tmp->start_regist.month >> tmp->start_regist.year;
		fin >> tmp->end_regist.day >> tmp->end_regist.month >> tmp->end_regist.year;
		if (i == n-1) {
			tmp->next = nullptr;
		}
		else {
			tmp->next = new semester;
			tmp = tmp->next;
		}
	}
	fin.close(); 
}

void readListEnrolled(string time, student*& s, int semester)
{
	char k = semester + 48; string id = s->id; 
	ifstream fin; fin.open(id + '_' + k + "sem.txt");
	if (isEmpty(fin)) {
		cout << "You haven't enrolled in any course" << endl;
		//cur = nullptr; 
		s->list_enrolled = nullptr;
		return;
	}
	int n; fin >> n; fin.get(); 
	s->countEnroll = n;
	enrolledCourse* cur = new enrolledCourse; s->list_enrolled = cur;
	for (int i = 0; i < n; i++) {
		getline(fin, cur->id_course, '\n');
		getline(fin, cur->course_name, '\n');
		getline(fin, cur->name_teacher, '\n');
		fin >> cur->credits; 
		fin.ignore(1000,'\n');
		getline(fin, cur->ses1.date, '\t'); getline(fin, cur->ses1.time, '\n');
		getline(fin, cur->ses2.date, '\t'); getline(fin, cur->ses2.time, '\n');
		
		fin >> cur->ecscore.other; fin >> cur->ecscore.mid; fin >> cur->ecscore.final; fin >> cur->ecscore.total;
		fin.ignore(100, '\n');
		if (i == n - 1) {
			cur->next = nullptr;
		}
		else {
			cur->next = new enrolledCourse;
			cur = cur->next;
		}
	}
}

void readStudentOfCourse(course*& c) {
	ifstream fin; fin.open(c->ID_course + ".txt");
	if (isEmpty(fin)) {
		//cout << "List of student in this course is empty" << endl;
		c->list_score = nullptr;
		return;
	}

	int n; fin >> n; fin.get();
	studentScore* cur = new studentScore; c->list_score = cur;
	for (int i = 0; i < n; i++) {
		getline(fin, cur->id, '\n');
		getline(fin, cur->name, '\n');
		fin >> cur->stscore.other;
		fin >> cur->stscore.mid;
		fin >> cur->stscore.final;
		fin >> cur->stscore.total;
		fin.get();
		if (i == n - 1) {
			cur->pNext = nullptr;
		}
		else {
			cur->pNext = new studentScore;
			cur = cur->pNext;
		}
	}
	fin.close();
}
void readListOfStu(student*& stu, string class_name)
{
	//int no = 0;
	ifstream fin;
	fin.open(class_name + ".csv");
	if (isEmpty(fin)) {
		cout << class_name << " file has not been imported" << endl;
		return;
	}
	student* cur = new student;
	stu = cur;
	string a; getline(fin, a, '\n');
	while (!fin.eof()) {
		fin >> cur->No;
		string a; getline(fin, a, ',');
		getline(fin, cur->id, ',');
		getline(fin, cur->prf.lastname, ',');
		getline(fin, cur->prf.firstname, ',');
		getline(fin, cur->prf.DOB, ',');
		getline(fin, cur->prf.gender, ',');
		getline(fin, cur->prf.social_id, '\n');

		if (fin.eof()) {
			cur->pNext = NULL;
			break;
		}
		else {
			cur->pNext = new student;
			cur = cur->pNext;
		}
	}
	fin.close();
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