#pragma once
#include "header.h"

void loadAccountFile(ifstream& fin, account*& head);
void saveAccountFile(ofstream& fout, account* head);
bool checkAccountModel(account* acc, account* head, int type, bool isReg);
void registerView(account*& head);
void loginView(account*& head, int type);
void enterProfile(account*& acc, int type);
void viewProfile(account* acc, account*& head);
void changePassword(account* acc, account* &head);
void saveStudent1Class(ofstream& fout, string name, account* head);
void readStudent1Class(string name, Class*& cl);