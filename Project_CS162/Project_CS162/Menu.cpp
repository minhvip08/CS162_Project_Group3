#include "Header.h"
#include "Menu.h"
#include "Data.h"
#include "Support.h"
#include "Input.h"
#include "OutputConsole.h"
#include "Scoreboard.h"

void manage_Schoolyear() { // ok
	schoolyear* sy = nullptr;
	int n;
	while (1) {
		cout << "1. Create a new schoolyear" << endl;
		cout << "2. Create 1st year class" << endl;
		cout << "3. View classes of a schoolyear" << endl;
		cout << "4. View student in a class" << endl;
		cout << "0. Go backward" << endl;
		cout << "Choose your choice: "; int n; cin >> n;
		if (n == 0) break;
		switch (n) {
		case 1: {
			create_schoolyear(sy); 
			system("pause");  
			break;
		}
		case 2: {
			create_class(sy); 
			system("pause"); 
			break;
		}
		case 3: {
			show_class(sy); 
			system("pause"); 
			break;
		}
		case 4: {
			showStudentsInClass(sy); 
			system("pause"); 
			break;
		}
		}
	}
}

void manage_semester() { //ok
	schoolyear* sy = nullptr;
	while (1) {
		int n;
		cout << "1. Create semester for schoolyear\n";
		cout << "2. Add a course to semester\n";
		cout << "3. View list of course\n";
		cout << "4. GPA of class\n";
		cout << "Choose your choice: "; cin >> n;
		if (n == 0) break;
		switch (n) {
		case 1: {
			create_semester(sy); 
			system("pause"); 
			break;
		}
		case 2: {
			create_course(sy); 
			system("pause"); 
			break;
		}
		case 3: {
			show_course(sy); 
			system("pause"); 
			break;
		}
		case 4: {
			gpaOfClass(sy); 
			system("pause"); 
			break;
		}
		}
	}
}
void manage_course() {
	schoolyear* sy = nullptr;

	while (1) {
		int n;
		cout << "1. Update course information\n";
		cout << "2. Delete a course\n";
		cout << "3. View list of student in a course\n";
		cout << "4. Export list of student to CSV file\n";
		cout << "5. Import scoreboard of a course\n";
		cout << "6. View scoreboard of a course\n";
		cout << "7. Update student result\n";
		cout << "0. Exit\n";
		cout << "Choose your choice: "; cin >> n;
		if (n == 0) break;
		switch (n) {
		case 1: {
			uppdateCourseInfor(sy);
			break;
		}
		case 2: {
			Delete_course_staff(sy);
			break;
		}
		case 3: {
			showStudentsInCourse(sy);
			break;
		}
		case 4: {
			exportstulist_menu(sy);
			break;
		}
		case 5: {
			importscoreboard_menu(sy);
			break;
		}
		case 6: {
			viewscoboardofc_menu(sy);
			break;
		}
		case 7: {
			updatestures_menu(sy);
			break;
		}
		}
	}
}