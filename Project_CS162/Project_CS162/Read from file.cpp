#include "Header.h"
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
	schoolyear* tmp = new schoolyear; sy = tmp; fin.get(); 
	for (int i = 0; i < n; i++) {
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
		cout << "List of classes in this choolyear is empty" << endl;
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

void read_date(ifstream& fin, date& d, bool check)
{
	/*fin >> d.day; string a; getline(fin, a, '/');
	fin >> d.month; getline(fin, a, '/');
	if (check) {
		fin >> d.year; getline(fin, a, ',');
	}
	else {
		fin >> d.year; getline(fin, a, '\n');
	}*/
}

void readListEnrolled(string time, student*& s, int semester)
{
	ifstream fin; fin.open(time+ '_' + s->id + "_sem" + (char)semester + "enrolled.txt");
	enrolledCourse* cur = new enrolledCourse; s->list_enrolled = cur;
	if (isEmpty(fin)) {
		cout << "You haven't enrolled in any course" << endl;
		cur = nullptr; 
		return; 
	}
	int n; fin >> n;
	s->countEnroll = n;

	fin.get();
	for (int i = 0; i < n; i++) {
		getline(fin, cur->id_course, '\n');
		getline(fin, cur->course_name, '\n');
		getline(fin, cur->name_teacher, '\n');
		getline(fin, cur->ses1.date, '\t'); getline(fin, cur->ses1.time, '\n');
		getline(fin, cur->ses2.date, '\t'); getline(fin, cur->ses2.time, '\n');
		if (i == n - 1) {
			cur->next = nullptr;
		}
		else {
			cur->next = new enrolledCourse;
			cur = cur->next;
		}
	}
}