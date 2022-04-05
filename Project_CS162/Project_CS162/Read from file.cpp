#include "Header.h"

void readSchoolyear(schoolyear*& sy)
{
	ifstream fin; fin.open("Schoolyear.txt");
	if (isEmpty(fin)) {
		cout << "List of schoolyear is empty" << endl;
		cout << "Please initialize some data" << endl;
		return;
	}

	schoolyear* tmp = new schoolyear; string a; getline(fin, a, '\n');
	if (!sy) sy = tmp;
	while (!fin.eof()) {
		getline(fin, tmp->time, ',');
		fin >> tmp->num_sem;
		string a; getline(fin, a, ',');
		fin >> tmp->num_class; getline(fin, a, '\n');
		if (fin.eof()) {
			tmp->next_schyear = nullptr;
			break;
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
	Class* tmp = new Class; cl = tmp;
	while (!fin.eof()) {
		getline(fin, tmp->class_name, '\n');
		fin >> tmp->total_student;
		string b; getline(fin, b, '\n');
		if (fin.eof()) {
			tmp->nextClass = nullptr;
			break;
		}
		else {
			tmp->nextClass = new Class;
			tmp = tmp->nextClass;
		}
	}
}

void readListOfCourse(string time, course*& c, int semester)
{
	char k = semester + 48;
	ifstream fin; fin.open(time + "_sem" + k + "_course.txt");
	if (isEmpty(fin)) {
		cout << "List of courses in this semester is empty" << endl;
		return;
	}
	course* tmp = new course; c = tmp;
	string a; getline(fin, a, '\n');
	while (!fin.eof()) {
		getline(fin, tmp->ID_course, ',');
		getline(fin, tmp->course_name, ',');
		getline(fin, tmp->teacher_name, ',');
		fin >> tmp->credits; getline(fin, a, ',');
		fin >> tmp->cur_student; getline(fin, a, ',');
		getline(fin, tmp->ses1.date, '|'); getline(fin, tmp->ses1.time, ',');
		getline(fin, tmp->ses2.date, '|'); getline(fin, tmp->ses2.time, '\n');

		if (fin.eof()) {
			tmp->next = nullptr;
			break;
		}
		else {
			tmp->next = new course;
			tmp = tmp->next;
		}
	}
	cout << c->ID_course << endl;
}

void readSemester(semester*& s, string time)
{
	ifstream fin; fin.open(time + "_semester.txt");
	if (isEmpty(fin)) {
		cout << "There is no available semester." << endl;
		cout << "Please initialize some semesters " << endl;
		return;
	}
	string k; getline(fin, k, '\n');
	semester* tmp = new semester; s = tmp;
	while (!fin.eof()) {
		fin >> tmp->mark; string a; getline(fin, a, ',');
		fin >> tmp->num_course; getline(fin, a, ',');
		read_date(fin, tmp->start_date, true);
		read_date(fin, tmp->end_date, true);
		read_date(fin, tmp->start_regist, true);
		read_date(fin, tmp->end_regist, false);
		if (fin.eof()) {
			tmp->next = nullptr;
			break;
		}
		else {
			tmp->next = new semester;
			tmp = tmp->next;
		}
	}
}

void read_date(ifstream& fin, date& d, bool check)
{
	fin >> d.day; string a; getline(fin, a, '/');
	fin >> d.month; getline(fin, a, '/');
	if (check) {
		fin >> d.year; getline(fin, a, ',');
	}
	else {
		fin >> d.year; getline(fin, a, '\n');
	}

}