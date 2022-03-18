#include "header.h"
student* inputonestu(student** cur)
{

}
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
	student* cur = head->stu;
	while (!fin.eof())
	{
		++no;
		if (head -> stu == nullptr)
		{
			head->stu = new student;
			head->stu->prf.no = no;
			getline(fin, head->stu->prf.id, ',');
			getline(fin, head->stu->prf.firstname, ',');
			getline(fin, head->stu->prf.lastname, ',');
			getline(fin, head->stu->prf.gender, ',');
			getline(fin, head->stu->prf.birthday, ',');
			getline(fin, head->stu->prf.social_id, ',');
			head->stu->pNext = nullptr;
			cur = head->stu;
			cur->pNext = nullptr;
		}
		else
		{
			cur->pNext = new student;
			cur = cur->pNext;
			cur->prf.no = no;
			getline(fin, cur->prf.id, ',');
			getline(fin, cur->prf.firstname, ',');
			getline(fin, cur->prf.lastname, ',');
			getline(fin, cur->prf.gender, ',');
			getline(fin, cur->prf.birthday, ',');
			getline(fin, cur->prf.social_id, ',');
			cur->pNext = nullptr;
		}
	}
	fin.close();
}
void copystudentinfo(student* stu1, student* stu2)
{
	if (stu1 == nullptr)
		return;
	stu1->prf.no = stu2->prf.no;
	stu1->prf.firstname =stu2->prf.firstname;
	stu1->prf.lastname, stu2->prf.lastname;
	stu1->prf.id, stu2->prf.id;
	stu1->prf.gender, stu2->prf.gender;
	stu1->prf.social_id, stu2->prf.social_id;
	stu1->prf.birthday, stu2->prf.birthday;

}
void copyliststu(Class*& c1, Class* c2) // c1 is the new class (dont have any students)
{
	
	if (c2->stu == nullptr)
		return;
	student* tmp = nullptr;
	student* cur = c2->stu;
	while (cur)
	{
		if (c1->stu == nullptr)
		{
			copystudentinfo(c1->stu, cur);
			tmp = c1->stu;
		}
		else
		{
			tmp->pNext = new student;
			tmp = tmp->pNext;
			copystudentinfo(tmp, cur);
			tmp->pNext = nullptr;
		}
		cur = cur->pNext;
	}

}