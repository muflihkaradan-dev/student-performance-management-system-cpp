#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include<vector>
#include"student.h"
#include<fstream>
#include<string>
#include"globalvar.h"
#include<filesystem>
#include<stdexcept>

using namespace std;
namespace fs=filesystem;


void saveData(const string&);//It saves the data available in students variable(vector<Student>) as a text file.
int openData(const string&);//It read the data from text file and copy to students variable.
void saveFileName(const string&,const string&);//It saves the file name given by the user during saveData().
int searchFile(const string&);//It searches file in filename variable(stores the filenames of file available in respective user directory) and return its index
void loadFileName(const string&);//It loads the filenames that is saved in file during saveFileName() to filename variable.
void createUserDir(const string& );//It creates the user directory for each user
string getUserFilePath(const string&, const string&);//It returns the file path that needed
void openDataforStudents(const string&);//It will read the data from files and add the all students details(that available in each files of each user) to studentsForLogin variable(vector<Student>)

#endif