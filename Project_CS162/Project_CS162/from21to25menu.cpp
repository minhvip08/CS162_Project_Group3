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
	ofstream fout;
	readStudentOfCourse(cur);
	studentScore* stu = cur->list_score; fout.open(cur->ID_course + ".csv");
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
	studentScore* stu = new studentScore;
	string a; getline(fin, a, '\n');
	cout << a << endl;

	while (!fin.eof()) {
		fin >> stu->no;
		cout << stu->no << endl;
		string s; getline(fin, s, ',');
		getline(fin, stu->id, ',');
		cout << stu->id << endl;
		getline(fin, stu->name, ',');
		cout << stu->name << endl;
		string c; getline(fin, c, ',');
		fin >> stu->stscore.other;
		cout << stu->stscore.other << endl;
		string d; getline(fin, d, ',');
		fin >> stu->stscore.mid;
		cout << stu->stscore.mid << endl;

		getline(fin, c, ',');
		fin >> stu->stscore.final;
		cout << stu->stscore.final << endl;
		getline(fin, d, ',');
		fin >> stu->stscore.total;
		cout << stu->stscore.final << endl;
		fin.ignore();
		string e; getline(fin, e, '\n');
		if (!cur->list_score) {
			cur->list_score = stu;
		}
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
	viewscoreboardcourse(cur);
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
void updatestures_menu(schoolyear* sy)
{
	readSchoolyear(sy);
	while (sy) {
		if (checkCurrentSchoolyear(sy)) break;
		sy = sy->next_schyear;
	}
	if (!sy) return;
	readSemester(sy->sem, sy->time);
	int sem = currentSemeser();
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

	cout << "Enter student's number you want to update his/her score: "; int k; cin >> k;
	importscoreboardcourse(cur);
	studentScore* stu = cur->list_score;
	while (stu) {
		if (stu->no == k) break;
		else
			stu = stu->pNext;
	}
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
}
void saveScoreboardCSV(course* c) {
	if (!c || !c->list_score) {
		cout << "Empty data\n"; return;
	}
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
		fout << stu->stscore.total << '\n';
		stu = stu->pNext;
	}
	fout.close();
}
//#include "header.h"
//#include "Support.h"
//#include "Data.h"
//#include "Input.h"
//#include "Menu.h"
//#include "Scoreboard.h"
//#include "Deallocate_graphic.h"
//#include "Login.h"
//void menu_staff2()
//{
//	//system("cls");
//	while (1) {
//		int n; cout << "WELCOME" << endl;
//		cout << "1. Create new schoolyear" << endl;
//		cout << "2. Create new semester to current schoolyear" << endl;
//		cout << "3. Add course to semester" << endl;
//		cout << "4. Add class to this schoolyear " << endl;
//		cout << "5. Export a list of students in a course to a CSV file" << endl;
//		cout << "6. Import the scoreboard of a course" << endl;
//		cout << "7. View the scoreboard of a course" << endl;
//		cout << "8. Update a student result" << endl;
//		cout << "9. View the scoreboard of a class" << endl;
//		cout << "0. Exit" << endl;
//		cout << "Choose your choice: "; cin >> n;
//		schoolyear* sy = NULL;
//		if (n == 0) break;
//		else {
//			switch (n) {
//			case 1:
//				create_schoolyear(sy);
//				break;
//			case 2:
//				create_semester(sy);
//				break;
//			case 3:
//				create_course(sy);
//				break;
//			case 4:
//				create_class(sy);
//				break;
//			case 5:
//				exportstulist_menu(sy);
//				break;
//			case 6:
//				importscoreboard_menu(sy);
//				break;
//			case 7:
//				viewscoboardofc_menu(sy);
//				break;
//			case 8:
//				updatestures_menu(sy);
//				break;
//			case 9:
//
//				break;
//			}
//		}
//	}
//	system("cls");
//	menu_view();
//	//Delete_schoolyear(sy);
//}
//void printlistclass(Class* c, int x)
//{
//	if (!c)
//		return;
//	printlistclass(c->nextClass, x + 1);
//	cout << "\n" << x << ". " << c->class_name;
//}
//void exportstulist_menu(schoolyear* scy) // chay lai
//{
//	readSchoolyear(scy); 
//	while (scy) {
//		if (checkCurrentSchoolyear(scy)) break; 
//		scy = scy->next_schyear; 
//	}
//	if (!scy) return;
//	readSemester(scy->sem, scy->time); 
//	int sem = currentSemester();
//	semester* s = scy->sem; 
//	while (s) {
//		if (s->mark == sem) break; 
//		s = s->next; 
//	}
//	cout << "List of course:" << endl; readListOfCourse(scy->time, s->course_list, sem);
//	int i = 0;  
//	course* tmp = s->course_list; 
//	while (tmp) {
//		++i; 
//		cout << i << ". Course ID: " << tmp->ID_course << '\t' << "Course name: " << tmp->course_name << endl; 
//		tmp = tmp->next; 
//	}	cout << "0. Exit" << endl;
//	cout << "Please choose the number represented the course(1, 2, 3, ...) : "; int x; cin >> x;
//		while (x > i) {
//			cout << "Invalid number!!" << endl << "Please input again: "; cin >> x;
//		}
//	if (x == 0) return;
//	course* cur = s->course_list;
//	if (x > 1) {
//		int h = 1; while (h < x) {
//			cur = cur->next; ++h;
//		}
//	}
//	exportlistofstudent(cur);
//	cout << "Export successfully" << endl;
//}
//void printcourse(course* c, int x)
//{
//	if (!c)
//		return;
//	printcourse(c->next, x + 1);
//	cout << x << ". " << c->ID_course << " - " << c->course_name << endl;
//}
//
//void viewscoboardofcourse(schoolyear* scy)
//{
//	//system("cls");
//	if (!checkdata(scy))
//	{
//		cout << "Data is empty!";
//		system("pause");
//		return;
//	}
//	course* c = scy->sem->course_list;
//	cout << "List of courses:" << endl;
//	printcourse(scy->sem->course_list, 1);
//	cout << "\n0. Exit " << endl;
//	cout << "Enter ID of course: ";
//	string str;
//	cin >> str;
//	if (stoi(str) == 0)
//	{
//		menu_staff2();
//	}
//	else {
//		while (c)
//		{
//			if (c->ID_course == str) cout << 'y' << endl;
//				//viewscoreboardcourse(c);
//			c = c->next;
//		}
//		if (!c)
//		{
//			cout << "Invalid input!" << endl;
//			cout << "Press 1 to try again. 0 to exit";
//			string s;
//			if (stoi(s) == 1)
//				viewscoboardofcourse(scy);
//			else
//				menu_staff2();
//		}
//	}
//}
//void importscoreboard_menu(schoolyear* scy)
//{
//	readSchoolyear(scy);
//	while (scy) {
//		if (checkCurrentSchoolyear(scy)) break;
//		scy = scy->next_schyear;
//	}
//	if (!scy) return;
//	readSemester(scy->sem, scy->time);
//	int sem = currentSemester();
//	semester* s = scy->sem;
//	while (s) {
//		if (s->mark == sem) break;
//		s = s->next;
//	}
//	cout << "List of course:" << endl; readListOfCourse(scy->time, s->course_list, sem);
//	int i = 0;
//	course* tmp = s->course_list;
//	while (tmp) {
//		++i;
//		cout << i << ". Course ID: " << tmp->ID_course << '\t' << "Course name: " << tmp->course_name << endl;
//		tmp = tmp->next;
//	}	cout << "0. Exit" << endl;
//	cout << "Please choose the number represented the course(1, 2, 3, ...) : "; int x; cin >> x;
//	while (x > i) {
//		cout << "Invalid number!!" << endl << "Please input again: "; cin >> x;
//	}
//	if (x == 0) return;
//	course* cur = s->course_list;
//	if (x > 1) {
//		int h = 1; while (h < x) {
//			cur = cur->next; ++h;
//		}
//	}
//	importscoretoCourse(scy->time, cur, sem);
//	cout << "Import successfully" << endl;
//}
//void importscoretoCourse(string time, course*& c, int sem)
//{
//	ifstream fin;
//	fin.open(c->ID_course + ".csv");
//
//	if (!fin.eof())
//	{
//		cout << "Can't open the file.\n";
//		return;
//	}
//	string a; getline(fin, a, '\n');
//	studentScore* stu = c->list_score;
//	while (!fin.eof())
//	{
//		fin >> stu->no; string b; getline(fin, b, ','); fin.get();
//		getline(fin, stu->id, ',');
//		getline(fin, stu->name, ',');
//		fin.get();
//		fin >> stu->stscore.other;
//		getline(fin, b, ',');
//		fin >> stu->stscore.mid;
//		getline(fin, b, ',');
//		fin >> stu->stscore.final;
//		getline(fin, b, ',');
//		fin >> stu->stscore.total;
//		student* s = new student; 
//		readListEnrolled(time, s, sem);
//		enrolledCourse* tmpec = s->list_enrolled; 
//		while (tmpec) {
//			if (tmpec->id_course == c->ID_course) break; 
//			tmpec = tmpec->next; 
//		}
//		tmpec->ecscore.other = stu->stscore.other; 
//		tmpec->ecscore.mid = stu->stscore.mid; 
//		tmpec->ecscore.final = stu->stscore.final; 
//		tmpec->ecscore.total = stu->stscore.total;
//		if (fin.eof()) {
//			stu->pNext = nullptr;
//			break;
//		}
//		else {
//			stu->pNext = new studentScore;
//			stu = stu->pNext;
//		}
//	}
//	fin.close();
//}
//void updatestures_menu(schoolyear* sy)
//{
//	readSchoolyear(sy);
//	while (sy) {
//		if (checkCurrentSchoolyear(sy)) break;
//		sy = sy->next_schyear;
//	}
//	if (!sy) return;
//	readSemester(sy->sem, sy->time);
//	int sem = currentSemester();
//	semester* s = sy->sem;
//	while (s) {
//		if (s->mark == sem) break;
//		s = s->next;
//	}
//	cout << "List of course:" << endl; readListOfCourse(sy->time, s->course_list, sem);
//	int i = 0;
//	course* tmp = s->course_list;
//	while (tmp) {
//		++i;
//		cout << i << ". Course ID: " << tmp->ID_course << '\t' << "Course name: " << tmp->course_name << endl;
//		tmp = tmp->next;
//	}	cout << "0. Exit" << endl;
//	cout << "Please choose the number represented the course(1, 2, 3, ...) : "; int x; cin >> x;
//	while (x > i) {
//		cout << "Invalid number!!" << endl << "Please input again: "; cin >> x;
//	}
//	if (x == 0) return;
//	course* cur = s->course_list;
//	if (x > 1) {
//		int h = 1; while (h < x) {
//			cur = cur->next; ++h;
//		}
//	}
//	//viewscoreboardcourse(cur); 
//	cout << "Enter student's number you want to update his/her score: "; int k; cin >> k;
//	studentScore* stu = cur->list_score; 
//	while (stu) {
//		if (stu->no == k) break;
//		else
//			stu = stu->pNext; 
//	}
//	if (!stu) {
//		cout << "Can't find student!!!" << endl;
//		return; 
//	}
//	while (1) {
//		cout << "Which score you want to update: " << endl;
//		cout << "1. Update other score." << endl;
//		cout << "2. Update midterm score." << endl;
//		cout << "3. Update final score." << endl;
//		cout << "0. Exit." << endl;
//		int choice; cout << "Your option: "; cin >> choice;
//		if (choice == 0) return;
//		else if (choice > 3) {
//			cout << "You input wrong number!!!\nPLease input again: "; cin >> choice; 
//		}
//		switch (choice) {
//		case 1: {
//			float other; cout << "New other score: "; cin >> other;
//			stu->stscore.other = other; 
//			break; 
//		}
//		case 2: {
//			float mid; cout << "New midterm score: "; cin >> mid; 
//			stu->stscore.mid = mid; 
//			break;
//		}
//		case 3: {
//			float final; cout << "New final score: "; cin >> final; 
//			stu->stscore.final = final; 
//			break;
//		}
//		}
//		float total = stu->stscore.other * 0.3 + stu->stscore.mid * 0.3 + stu->stscore.final * 0.4; 
//		cout << "New total score: " << total << endl;
//		stu->stscore.total = total; 
//	}
//	saveScoreboardCSV(cur);
//}
//
//void saveScoreboardCSV(course* c) {
//	if (!c || !c->list_score) {
//		cout << "Empty data\n"; return; 
//	}
//	studentScore* stu = c->list_score;
//	ofstream fout; fout.open(c->ID_course + ".csv"); 
//	fout << "No,ID,Name,Other,Mid,Final,Total\n"; 
//	while (stu) {
//		fout << stu->no << ',';
//		fout << stu->id << ',';
//		fout << stu->name << ','; 
//		fout << stu->stscore.other << ','; 
//		fout << stu->stscore.mid << ',';
//		fout << stu->stscore.final << ',';
//		fout << stu->stscore.total << '\n';
//		stu = stu->pNext; 
//	}
//	fout.close(); 
//}
//
//void viewscoboardofc_menu(schoolyear* sy)
//{
//	readSchoolyear(sy);
//	while (sy) {
//		if (checkCurrentSchoolyear(sy)) break;
//		sy = sy->next_schyear;
//	}
//	if (!sy) return;
//	readSemester(sy->sem, sy->time);
//	int sem = currentSemester();
//	semester* s = sy->sem;
//	while (s) {
//		if (s->mark == sem) break;
//		s = s->next;
//	}
//	cout << "List of course:" << endl; readListOfCourse(sy->time, s->course_list, sem);
//	int i = 0;
//	course* tmp = s->course_list;
//	while (tmp) {
//		++i;
//		cout << i << ". Course ID: " << tmp->ID_course << '\t' << "Course name: " << tmp->course_name << endl;
//		tmp = tmp->next;
//	}	cout << "0. Exit" << endl;
//	cout << "Please choose the number represented the course(1, 2, 3, ...) : "; int x; cin >> x;
//	while (x > i) {
//		cout << "Invalid number!!" << endl << "Please input again: "; cin >> x;
//	}
//	if (x == 0) return;
//	course* cur = s->course_list;
//	if (x > 1) {
//		int h = 1; while (h < x) {
//			cur = cur->next; ++h;
//		}
//	}
//	//viewscoreboardcourse(cur);
//}
//
//void viewScoreOfClass(schoolyear* sy) {
//	readSchoolyear(sy);
//	while (sy) {
//		if (checkCurrentSchoolyear(sy)) break;
//		sy = sy->next_schyear;
//	}
//	if (!sy) return;
//	readListOfClass(sy->list_class, sy->time); 
//	int i = 0; 
//	Class* cl = sy->list_class; 
//	while (cl) {
//		++i; 
//		cout << i << ".Class name: " << cl->class_name << endl; 
//		cl = cl->nextClass; 
//	}
//	cout << "Choose the class you want to view score: "; int x; cin >> x; 
//	while (x > i) {
//		cout << "You inout wrong number, please input again: "; cin >> x; 
//	}
//	Class* tmp = sy->list_class; int h = 0; 
//	while (tmp) {
//		++h; 
//		tmp = tmp->nextClass;
//		if (h == x) break;
//	}
//	readStudent1Class(tmp->class_name, tmp);
//	student* stu = tmp->student_list; int sem = currentSemester(); 
//	while (stu) {
//		readListEnrolled(sy->time, stu, sem); 
//		enrolledCourse* ec = stu->list_enrolled; 
//		float gpa = 0; int cred = 0; 
//		while (ec) {
//			cout << "Course name: " << ec->course_name << endl; 
//			cout << "Final mark: " << ec->ecscore.final << endl;
//			gpa += ec->ecscore.total; cred += ec->credits; 
//			ec = ec->next; 
//		}
//		cout << "GPA in this semester: " << conditionGPA(gpa / cred) << endl; 
//		//cout << "Total GPA: " (kt lai)
//		stu = stu->pNext; 
//	}
//}
//
//int conditionGPA(float a) {
//	if (8.5 <= a && a <= 10) return 4;
//	else if (7 <= a && a <= 8.4) return 3;
//	else if (5.5 <= a && a <= 6.9) return 2;
//	else return 1; 
//}

//export va import
//updatestures_menu(schoolyear* sy)