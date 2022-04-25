#pragma once
#include "header.h"
void Intro();
void loginMenu(account*& head, int type);
void Menu2(account* acc, account*& head, int type);
void menu_student(schoolyear*& sy, int semester, account* head);
void menu_view();
void menu_staff();
void exportstulist_menu(schoolyear* scy);
void importscoreboard_menu(schoolyear* scy);
void viewscoboardofc_menu(schoolyear* sy);
void updatestures_menu(schoolyear* sy);