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
void viewscoreboard(course* c)
{
	cout << "\033[2J\033[1;1H";
	if (!c->list_score)
	{
		cout << "Empty!";
		system("pause");
		return;
	}
	cout << "No\tID\tFull Name\tTotal\tTinal\tMid\tOther";
	studentScore* sco = c->list_score;
	while (sco)
	{
		cout << sco->no << "\t" << sco->id << "\t" << sco->name << "\t" << sco->total << "\t" << sco->final << "\t" << sco->mid << "\t" << sco->other << endl;
		sco = sco->pNext;
	}
}
void updateastudentscore(course*& c)
{
	cout << "\033[2J\033[1;1H";
	if (!c->list_score) {
		cout << "The student list is empty!\n";
		return;
	}
	string id;
	studentScore* cur = c->list_score;
	cout << "Enter the ID of the student you want to change score: ";
	cin >> id;
	bool check = false;
	while (cur && id <= cur->id)
	{
		if (id == cur->id)
		{
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
			cout << "5. Exit." << endl << endl;
			cout << "Your option: ";
			int b; cin >> b; 
			double a;
			switch (b)
			{
			case 1:
				cout << "Enter new total score: ";
				cin >> a;
				cur->total = a;
				cout << "Successful!\n";
				system("pause");
				cout << "\033[2J\033[1;1H";
				break;
			case 2:
				cout << "Enter new final score: ";
				cin >> a;
				cur->final = a;
				cout << "Successful!\n";
				system("pause");
				cout << "\033[2J\033[1;1H";
				break;
			case 3:
				cout << "Enter new mid score: ";
				cin >> a;
				cur->mid = a;
				cout << "Successful!\n";
				system("pause");
				cout << "\033[2J\033[1;1H";
				break;
			case 4:
				cout << "Enter new total score: ";
				cin >> a;
				cur->other = a;
				cout << "Successful!\n";
				system("pause");
				cout << "\033[2J\033[1;1H";
				break;
			case 5:
				c = false;
				break;
			}
		}
		return;
	}

}