#ifndef USERS_H
#define USERS_H

#include "filemanager.h"
#include<string>

std::string registerUser();//Function to register user
std::string loginUser();//Function to Login
void saveUser();//It will stores the details of each user(username and password) that available in userDetails to binary file users.bin
int searchUser(const std::string&);//It will search user in userDetails variable and returns its index when finds
void loadUser();//It will read data from users.bin and store it into userDetails variable
std::string sha256(const std::string& );//This function is a hashing function that computes the SHA-256 hash of a given string.

#endif