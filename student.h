#ifndef STUDENT_H
#define STUDENT_H

#include<iostream>
#include<string>
#include<vector>


class Student{
    private:
    std::string id;
    std::string name;
    std::string department;
    std::string semester;
    std::vector<float> marks;
    public:
    bool input();
    Student();//Default constructor
    float Gpa() const;
    const std::string& getId() const;
    const std::string& getName() const;
    const std::string& getDepartment() const;
    const std::string& getSemester() const;
    const std::vector<float>& getMarks() const;
    void printProgressCard() const;
    void updateName();
    void updateDept();
    void updateMarks();
    void updateSemester();
    void updateId(std::string&);
    void display() const;
    void setId(const std::string& id);
    void setName(const std::string& name);
    void setMarks(const std::vector<float>& mark);
    void setDept(const std::string& dept);
    void setSemester(const std::string& sem);
};
    bool isIdExists(const std::string& idToCheck);//Function to check the ID is already available in any files of any user directory
#endif