#include "header.h"

void createlistofstu(Class*& head, const string str) //str is the id of the class
{
	int no = 0;
	ifstream fin;
	fin.open(str + ".csv");
	if (!fin.eof())
	{
		cout << "Can't open the file!\n";
		return;
	}
	student* cur = head->student_list;
	while (!fin.eof())
	{
		++no;
		if (head -> student_list == nullptr)
		{
			head->student_list = new student;
			head->student_list->No = no;
			getline(fin, head->student_list->id, ',');
			getline(fin, head->student_list->prf.firstname, ',');
			getline(fin, head->student_list->prf.lastname, ',');
			getline(fin, head->student_list->prf.DOB, '/');
			getline(fin, head->student_list->prf.gender, ',');
			getline(fin, head->student_list->prf.social_id, ',');
			head->student_list->pNext = nullptr;
			cur = head->student_list;
			cur->pNext = nullptr;
		}
		else
		{
			cur->pNext = new student;
			cur = cur->pNext;
			cur->No = no;
			getline(fin, cur->id, ',');
			getline(fin, cur->prf.firstname, ',');
			getline(fin, cur->prf.lastname, ',');
			getline(fin, cur->prf.gender, ',');
			getline(fin, cur->prf.DOB, ',');
			getline(fin, cur->prf.social_id, ',');
			cur->pNext = nullptr;
		}
	}
	fin.close();
}
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
void exportonestu(ofstream& fout, student* stu)
{
	fout << stu->No << ',';
	fout << stu->id << ',';
	fout << stu->prf.firstname + " "+ stu->prf.lastname << ',';
	fout << stu->prf.gender << ',';
	fout << stu->prf.DOB << ',';
	fout << stu->prf.social_id << ',' << endl;
}
void exportlistofstudent(Class* c, course *cour)
{
	ofstream fout;
	fout.open(cour->ID_course + ".csv");
	studentScore* cur = cour->list_score;
	while (cur)
	{
		student* stu = c->student_list;
		while (stu)
		{
			if (stu->id == cur->id)
			{
				exportonestu(fout, stu);
			}
			stu = stu->pNext;
		}
		cur = cur->pNext;
	}
	fout.close();
}
void sortbyID(Class* &c)
{
	student* cur = c->student_list;
	while (cur)
	{
		student* next = cur->pNext;
		while (next)
		{
			if (stoi(cur->id) > stoi(next->id)) // stoi - chuyen doi string sang int
				swap(cur, next); // hi vong la ok
		}
	}
}
void import1studentscore(ifstream& fin, studentScore* stusc)
{
	fin.ignore('\n');
	fin >> stusc->id;
	getline(fin, stusc->id, '\n');
	getline(fin, stusc->name, '\n');
	fin >> stusc->total;
	fin.ignore();
	fin >> stusc->final;
	fin.ignore();
	fin >> stusc->mid;
	fin.ignore();
	fin >> stusc->other;
	fin.ignore();

}
void importscoretoCourse(course* &c)
{
	ifstream fin;
	fin.open(c->ID_course + ".csv");
	studentScore* stusc = c->list_score;
	if (!fin.eof())
	{
		cout << "Can't open the file.\n";
		return;
	}
	while (!fin.eof())
	{
		import1studentscore(fin, stusc);
		stusc = stusc->pNext;
	}
	fin.close();
}