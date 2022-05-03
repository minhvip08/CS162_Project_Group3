#pragma once
#include "header.h"
void exportstulist_menu(schoolyear* scy);
void importscoreboard_menu(schoolyear* scy);
void viewscoboardofc_menu(schoolyear* sy);
void updatestures_menu(schoolyear* sy);
void saveScoreboardCSV(course* c);
void importscoreboardcourse(course*& c);
void print(course* c);
int conditionGPA(float m);
void gpaOfClass(schoolyear* head);
void view_scoreboard_sem(student* stu);
void Scoreboard_staff(schoolyear* head);