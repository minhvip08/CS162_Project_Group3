#include "header.h"
#include "Support.h"
#include "Data.h"
#include "Scoreboard.h"
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
	if (isEmpty(fin)) {
		cout << "No data\n"; return;
	}
	student* cur = head->student_list;
	while (!fin.eof())
	{
		++no;
		fin >> cur->No; 
		fin.get(); 
		getline(fin, cur->id, ',');
		getline(fin, cur->prf.firstname, ',');
		getline(fin, cur->prf.lastname, ',');
		getline(fin, cur->prf.gender, ',');
		getline(fin, cur->prf.DOB, ',');
		getline(fin, cur->prf.social_id, '\n');
		if (fin.eof()) {
			cur->pNext = nullptr;
			break;
		}
		else {
			cur->pNext = new student;
			cur = cur->pNext;
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
void exportonestu(ofstream& fout, studentScore* stu)
{
	fout << stu->no << ",";
	fout << stu->id << ",";
	fout << stu->name << ",";
	fout << stu->stscore.total << ",";
	fout << stu->stscore.mid << ",";
	fout << stu->stscore.final << ",";
	fout << stu->stscore.other <<endl;
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
	fout << "No,ID,Fullname,Total,Mid,Final,Other" << endl;
	studentScore* cur = cour->list_score;
	while (cur)
	{
		exportonestu(fout, cur);
		cur = cur->pNext;
	}
	fout.close();
}
void import1studentscore(ifstream& fin, studentScore* stusc)
{
	fin.ignore('\n');
	fin >> stusc->id;
	getline(fin, stusc->id, '\n');
	getline(fin, stusc->name, '\n');
	fin >> stusc->stscore.total;
	fin.ignore();
	fin >> stusc->stscore.final;
	fin.ignore();
	fin >> stusc->stscore.mid;
	fin.ignore();
	fin >> stusc->stscore.other;
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
void viewstudentscore(studentScore* sco)
{
	if (!sco)
		return;
	viewstudentscore(sco->pNext);
	cout << sco->no << "\t\t\t" << sco->id << "\t\t\t" << sco->name << "\t\t\t" << sco->stscore.total << "\t\t\t" << sco->stscore.final << "\t\t\t" << sco->stscore.mid << "\t\t\t" << sco->stscore.other << endl;
}
void viewscoreboardcourse(course* c)
{

	//cout << "\033[2J\033[1;1H";
	if (!c->list_score)
	{
		//cout << "\t\t\tThe end!";
		system("pause");
		return;
	}
	cout << c->course_name << endl;
	cout << "No\t\t\tID\t\t\tFull Name\t\t\tTotal\t\t\tTinal\t\t\tMid\t\t\tOther";
	studentScore* sco = c->list_score;
	viewstudentscore(sco);
}
void updateastudentscore(course*& c, string id)
{
	//cout << "\033[2J\033[1;1H";
	if (!c->list_score) {
		cout << "Data is empty!\n";
		return;
	}
	studentScore* tmp = nullptr;
	bool check = false;
	studentScore* cur = c->list_score;
	while (cur)
	{
		if (id == cur->id)
		{
			tmp = cur;
			check = true;
			break;
		}
		cur = cur->pNext;
	}
	if (!check)
	{
		string n;
		cout << "Not found!\n";
		cout << "Enter 1 to try again: ";
		if (stoi(n) == 1)
		{
			updateastudentscore(c);
		}
		else
			return;
	}
	else
	{
		bool c = true;
		while (c)
		{
			cout << "Enter:" << endl;
			cout << "1. Update total score." << endl;
			cout << "2. Update final score." << endl;
			cout << "3. Update mid score." << endl;
			cout << "4. Update other score." << endl;
			cout << "0. Exit." << endl << endl;
			cout << "Your option: ";
			int b; cin >> b;
			double a;
			if (b == 0)
				return;
			switch (b)
			{
			case 1:
				cout << "Enter new total score: ";
				cin >> a;
				tmp->stscore.total = a;
				cout << "Successful!\n";
				system("pause");
				//cout << "\033[2J\033[1;1H";
				break;
			case 2:
				cout << "Enter new final score: ";
				cin >> a;
				tmp->stscore.final = a;
				cout << "Successful!\n";
				system("pause");
				//cout << "\033[2J\033[1;1H";
				break;
			case 3:
				cout << "Enter new mid score: ";
				cin >> a;
				tmp->stscore.mid = a;
				cout << "Successful!\n";
				system("pause");
				//cout << "\033[2J\033[1;1H";
				break;
			case 4:
				cout << "Enter new total score: ";
				cin >> a;
				tmp->stscore.other = a;
				cout << "Successful!\n";
				system("pause");
				//cout << "\033[2J\033[1;1H";
				break;
			}
		}
		return;
	}
}