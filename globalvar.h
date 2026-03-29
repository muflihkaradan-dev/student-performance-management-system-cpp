#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include"student.h"
#include<string>
#include<vector>

extern std::vector<Student> students;//Global variable to store the student data inside a file(At a time stores the data of one file only)
extern std::vector<std::string> filename;//Global variable to store the filenames of file available inside a user directory(At a time stores the data inside one user directory only)
extern std::vector<std::vector<std::string>> userDetails;//Global variable to store user details(username and their respective password for each user)
extern std::vector<Student> studentsForLogin;//Global variable to store the data of all students(students data stored inside all files of all user directory) It uses for student login
#endif