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
	fout << "No,ID,Fullname,Other,Mid,Final,Total" << endl;
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
void importscoretoCourse(course* &c)
{
	ifstream fin;
	fin.open(c->ID_course + ".csv");
	
	if (!fin.eof())
	{
		cout << "Can't open the file.\n";
		return;
	}
	string a; getline(fin, a, '\n'); 
	studentScore* stu = c->list_score;
	while (!fin.eof())
	{
		fin >> stu->no; string b; getline(fin, b, ','); fin.get(); 
		getline(fin, stu->id, ','); 
		getline(fin, stu->name, ','); 
		fin.get(); 
		fin >> stu->stscore.other; 
		getline(fin, b, ',');
		fin >> stu->stscore.mid; 
		getline(fin, b, ',');
		fin >> stu->stscore.final; 
		getline(fin, b, ',');
		fin >> stu->stscore.total;
		if (fin.eof()) {
			stu->pNext = nullptr;  
			break;
		}
		else {
			stu->pNext = new studentScore; 
			stu = stu->pNext; 
		}
	}
	fin.close();
}
void viewstudentscore(studentScore* sco)
{
	while (sco) {
		cout << sco->no << "\t\t\t" << sco->id << "\t\t\t" << sco->name << "\t\t\t" << sco->stscore.total << "\t\t\t" << sco->stscore.final << "\t\t\t" << sco->stscore.mid << "\t\t\t" << sco->stscore.other << endl;
		sco = sco->pNext; 
	}
}
void viewscoreboardcourse(course* c)
{
	importscoretoCourse(c); 
	/*if (!c->list_score)
	{
		cout << "Empty list of student" << endl;
		cout << "...Press any key to continue\n"; 
		system("pause");
		return;
	}*/
	cout << "COURSE NAME:" << c->ID_course << endl;
	cout << "No\t\t\tID\t\t\tFull Name\t\t\tOther\t\t\tMid\t\t\tFinal\t\t\Total\n";
	studentScore* sco = c->list_score;
	while (sco) {
		cout << sco->no << "\t\t\t" << sco->id << "\t\t\t" << sco->name << "\t\t\t" << sco->stscore.other << "\t\t\t" << sco->stscore.mid << "\t\t\t" << sco->stscore.final << "\t\t\t" << sco->stscore.total << endl;
		sco = sco->pNext;
	}
}

//void updateastudentscore(course*& c, string id)
//{
//
//	if (!c->list_score) {
//		cout << "Data is empty!\n";
//		return;
//	}
//	studentScore* tmp = nullptr;
//	bool check = false;
//	studentScore* cur = c->list_score;
//	while (cur)
//	{
//		if (id == cur->id)
//		{
//			tmp = cur;
//			check = true;
//			break;
//		}
//		cur = cur->pNext;
//	}
//	if (!check)
//	{
//		string n;
//		cout << "Not found!\n";
//		cout << "Enter 1 to try again: ";
//		if (stoi(n) == 1)
//		{
//			updateastudentscore(c);
//		}
//		else
//			return;
//	}
//	else
//	{
//		bool c = true;
//		while (c)
//		{
//			cout << "Enter:" << endl;
//			cout << "1. Update total score." << endl;
//			cout << "2. Update final score." << endl;
//			cout << "3. Update mid score." << endl;
//			cout << "4. Update other score." << endl;
//			cout << "0. Exit." << endl << endl;
//			cout << "Your option: ";
//			int b; cin >> b;
//			double a;
//			if (b == 0)
//				return;
//			switch (b)
//			{
//			case 1:
//				cout << "Enter new total score: ";
//				cin >> a;
//				tmp->stscore.total = a;
//				cout << "Successful!\n";
//				system("pause");
//				//cout << "\033[2J\033[1;1H";
//				break;
//			case 2:
//				cout << "Enter new final score: ";
//				cin >> a;
//				tmp->stscore.final = a;
//				cout << "Successful!\n";
//				system("pause");
//				//cout << "\033[2J\033[1;1H";
//				break;
//			case 3:
//				cout << "Enter new mid score: ";
//				cin >> a;
//				tmp->stscore.mid = a;
//				cout << "Successful!\n";
//				system("pause");
//				//cout << "\033[2J\033[1;1H";
//				break;
//			case 4:
//				cout << "Enter new total score: ";
//				cin >> a;
//				tmp->stscore.other = a;
//				cout << "Successful!\n";
//				system("pause");
//				//cout << "\033[2J\033[1;1H";
//				break;
//			}
//		}
//		return;
//	}
//}