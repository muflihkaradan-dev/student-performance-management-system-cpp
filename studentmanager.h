#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H


#include"filemanager.h"
#include<algorithm>
#include"globalvar.h"

bool addStudent();//Returns int (return true if Id enetered is already added,otherwise it will return false)
void sortByGpa();
void sortById();
void sortByName();
void deleteStudent();
int searchStudent();//Returns the index of the searched student
void DisplayStudent(const Student&);//Display the student details of student given 
void DisplayStudentlist();//Call function DisplayStudent(const Student&) for each student available in students
void updateStudent();
void progressCard();
static std::string lower(std::string s);//Convert the string into its lowercase
static bool askYesNo(const std::string& prompt);//Asks Yes or No
void studentSearchForStudentLogin();//Search student in studentsForLogin variable during Student login

#endif