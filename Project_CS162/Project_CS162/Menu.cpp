#include "header.h"
#include "Menu.h"
#include "Data.h"
#include "Support.h"
#include "Input.h"
#include "OutputConsole.h"
#include "Scoreboard.h"
#include "design.h"
#include "Login.h"
void menu_staff() {
	string art = headline();
	while (true) {
		system("cls");
		SetColor(rand() % 14 + 1);
		cout << art << endl;
		int opt = 1;
		int row = 4;//rows of menu lines
		int y = 7;
		ShowConsoleCursor(true);
		SetColor(14);
		gotoxy(8, y + 1);
		cout << "1.Schoolyear management\n";
		gotoxy(8, y + 2);
		cout << "2.Semester management\n";
		gotoxy(8, y + 3);
		cout << "3.Course management\n";
		gotoxy(8, y + 4);
		cout << "0.Exit\n";
		gotoxy(7, y + 1);
		moveChoice(row, y, opt);

		switch (opt) {
		case 1: {
			system("cls");
			manage_Schoolyear();
			system("pause");
			break;
		}
		case 2: {
			system("cls");
			manage_semester();
			system("pause");
			break;
		}
		case 3: {
			system("cls");
			manage_course();
			system("pause");
			break;
		}
		case 4: {
			return;
		}
		}
	}
}
void menu_student(account* &head) {
	schoolyear* sy = nullptr;
	readSchoolyear(sy); schoolyear* tmp = sy;
	while (tmp) {
		if (checkCurrentSchoolyear(tmp)) {
			break;
		}
		else tmp = tmp->next_schyear;
	}
	string cl_name;
	if (tmp) readListOfClass(tmp->list_class, tmp->time);
	Class* ctmp = tmp->list_class;
	bool stop = false; student* stu = new student;
	while (ctmp) {
		readStudent1Class(ctmp->class_name, ctmp);
		stu = ctmp->student_list;
		while (stu) {
			if (stu->id == head->username) {
				cl_name = ctmp->class_name;
				stop = true;
				break;
			}
			else stu = stu->pNext;
		}
		if (stop == true) break;
		else
			ctmp = ctmp->nextClass;
	}

	string art = headline();
	while (true) {
		system("cls");
		SetColor(rand() % 14 );
		cout << art << endl;
		int opt = 1;
		int row = 7;//rows of menu lines
		int y = 7;
		ShowConsoleCursor(true);
		SetColor(10);
		gotoxy(8, y + 1);
		cout << "1.Enroll a course" << endl;
		gotoxy(8, y + 2);
		cout << "2.View a list of enrolled course" << endl;
		gotoxy(8, y + 3);
		cout << "3.Remove enrolled course" << endl; // ktra ngay thang cho phep enroll
		gotoxy(8, y + 4);
		cout << "4.View a list of his/her courses in this semester" << endl;
		gotoxy(8, y + 5);
		cout << "5.View his/her scoreboard in current semester" << endl;
		gotoxy(8, y + 6);
		cout << "6.View his/her scoreboard in every semester" << endl;
		gotoxy(8, y + 7);
		cout << "0.Exit\n";
		gotoxy(7, y + 1);
		moveChoice(row, y, opt);

		switch (opt) {
		case 1: {
			system("cls");
			int sem = currentSemester();
			enrollCourse(sy, tmp->time, sem, stu);
			system("pause");
			break;
		}
		case 2: {
			system("cls");
			showListEnrolledCourse(stu);
			system("pause");
			break;
		}
		case 3: {
			system("cls");
			int sem = currentSemester();
			Delete_enrolled_course(sy, tmp->time, stu, sem);
			system("pause");
			break;
		}
		case 4: {
			system("cls");
			int sem = currentSemester();
			readListEnrolled(tmp->time, stu, sem);
			enrolledCourse* etmp = stu->list_enrolled;
			if (etmp == nullptr) {
				system("pause");
			}
			else {
				int i = 0;
				while (etmp) {
					++i;
					cout << "******COURSE NUMBER: " << i << " ******\n";
					cout << "  * ID: " << etmp->id_course << endl;
					cout << "  * Course name: " << etmp->id_course << endl;
					cout << "  * Teacher's name: " << etmp->name_teacher << endl;
					cout << "  * Credits: " << etmp->credits << endl;
					cout << "  * Session 1: " << etmp->ses1.date << '\t' << etmp->ses1.time << endl;
					cout << "  * Session 2: " << etmp->ses2.date << '\t' << etmp->ses2.time << endl;
					etmp = etmp->next;
					if (!etmp) cout << "**************************************\n";
				}
				system("pause");
			}
			break;
		}
		case 5: {
			system("cls");
			view_scoreboard_stu(stu);
			system("pause");
			break;
		}
		case 6: {
			system("cls");
			view_scoreboard_sem(stu);
			system("pause");
			break;
		}
		case 7: {
			return;
		}
		}
	}
}
void manage_Schoolyear() { // ok
	schoolyear* sy = nullptr;
	string art = headline();
	while (true) {
		system("cls");
		SetColor(rand() % 14 + 1);
		cout << art << endl;
		int opt = 1;
		int row = 5;//rows of menu lines
		int y = 7;
		ShowConsoleCursor(true);
		SetColor(9);
		gotoxy(8, y + 1);
		cout << "1.Create a new schoolyear" << endl;
		gotoxy(8, y + 2);
		cout << "2.Create 1st year class" << endl;
		gotoxy(8, y + 3);
		cout << "3.View classes of a schoolyear" << endl;
		gotoxy(8, y + 4);
		cout << "4.View students in a class" << endl;
		gotoxy(8, y + 5);
		cout << "0.Go backward" << endl;
		gotoxy(7, y + 1);
		moveChoice(row, y, opt);

		switch (opt) {
		case 1: {
			system("cls");
			create_schoolyear(sy);
			system("pause");
			break;
		}
		case 2: {
			system("cls");
			create_class(sy);
			system("pause");
			break;
		}
		case 3: {
			system("cls");
			show_class(sy);
			system("pause");
			break;
		}
		case 4: {
			system("cls");
			showStudentsInClass(sy);
			system("pause");
			break;
		}
		case 5: {
			return;
		}
		}
	}
}

void manage_semester() { //ok
	schoolyear* sy = nullptr;
	string art = headline();
	while (true) {
		system("cls");
		SetColor(rand() % 14 + 1);
		cout << art << endl;
		int opt = 1;
		int row = 5;//rows of menu lines
		int y = 7;
		ShowConsoleCursor(true);
		SetColor(9);
		gotoxy(8, y + 1);
		cout << "1. Create semester for schoolyear\n";
		gotoxy(8, y + 2);
		cout << "2. Add a course to semester\n";
		gotoxy(8, y + 3);
		cout << "3. View list of course\n";
		gotoxy(8, y + 4);
		cout << "4. GPA of class\n";
		gotoxy(8, y + 5);
		cout << "0.Go backward" << endl;
		gotoxy(7, y + 1);
		moveChoice(row, y, opt);

		switch (opt) {
		case 1: {
			system("cls");
			create_semester(sy);
			system("pause");
			break;
		}
		case 2: {
			system("cls");
			create_course(sy);
			system("pause");
			break;
		}
		case 3: {
			system("cls");
			show_course(sy);
			system("pause");
			break;
		}
		case 4: {
			system("cls");
			gpaOfClass(sy);
			system("pause");
			break;
		}
		case 5: {
			return;
		}
		}
	}
}
void manage_course() {
	schoolyear* sy = nullptr;
	string art = headline();
	while (true) {
		system("cls");
		SetColor(rand() % 14 + 1);
		cout << art << endl;
		int opt = 1;
		int row = 8;//rows of menu lines
		int y = 7;
		ShowConsoleCursor(true);
		SetColor(6);
		gotoxy(8, y + 1);
		cout << "1. Update course information\n";
		gotoxy(8, y + 2);
		cout << "2. Delete a course\n";
		gotoxy(8, y + 3);
		cout << "3. View list of student in a course\n";
		gotoxy(8, y + 4);
		cout << "4. Export list of student to CSV file\n";
		gotoxy(8, y + 5);
		cout << "5. Import scoreboard of a course\n";
		gotoxy(8, y + 6);
		cout << "6. View scoreboard of a course in current semester\n";
		gotoxy(8, y + 7);
		cout << "7. View scoreboard of 1 course\n";
		gotoxy(8, y + 8);
		cout << "8. Update student result\n";
		gotoxy(8, y + 9);
		cout << "0.Go backward\n";
		gotoxy(7, y + 1);
		moveChoice(row, y, opt);

		switch (opt) {
		case 1: {
			system("cls");
			uppdateCourseInfor(sy);
			system("pause");
			break;
		}
		case 2: {
			system("cls");
			Delete_course_staff(sy);
			system("pause");
			break;
		}
		case 3: {
			system("cls");
			showStudentsInCourse(sy);
			system("pause");
			break;
		}
		case 4: {
			system("cls");
			exportstulist_menu(sy);
			system("pause");
			break;
		}
		case 5: {
			system("cls");
			importscoreboard_menu(sy);
			system("pause");
			break;
		}
		case 6: {
			system("cls");
			viewscoboardofc_menu(sy);
			system("pause");
			break;
		}
		case 7: {
			system("cls");
			Scoreboard_staff(sy);
			system("pause");
			return;
		}
		case 8: {
			system("cls");
			updatestures_menu(sy);
			system("pause");
			break;
		}
		case 9: {
			return; 
		}
		}
	}
}