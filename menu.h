#ifndef MENU_H
#define MENU_H


#include<string>
#include"studentmanager.h"
#include"filemanager.h"
#include"student.h"
#include"globalvar.h"

void SortStudents();//It will asks the type of sort and call their respective function
void Menu(const std::string&);//Main menu used for tutor login
bool askReturnToMenu();//It will asks for return to previous menu
bool askSaveData();//It will asks for data save incase of creation of fresh student details
bool askSaveForOverwrite(const std::string&);//It will asks for for data after editing of already available student data 
void studentMenu();//It is the main menu used for student login
bool getYesNo(const std::string&);//Function to ask YES or NO
std::string toUpper(const std::string&);//It will convert the string letters into its uppercases

#endif