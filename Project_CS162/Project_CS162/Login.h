#pragma once
#include "header.h"
void loadAccountFile(ifstream& fin, account*& head);
void saveAccountFile(ofstream& fout, account* head);
bool checkAccountModel(account* acc, account* head, int type, bool isReg);
void registerView(account*& head, ifstream& fin);
void loginView(account*& head, int type);
void enterProfile(account*& acc, int type);
void viewProfile(account* acc, account*& head);
void changePassword(account* acc, account*& head);