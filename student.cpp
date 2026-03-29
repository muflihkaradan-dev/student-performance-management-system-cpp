#include "student.h"
#include <limits>
#include"globalvar.h"
#include<iomanip>
#include"filemanager.h"


using namespace std;

Student::Student() : id(""), name(""), department(""), semester(""), marks({}) {}


bool Student::input(){
    cout<<"\nEnter the Student ID: ";
    getline(cin,id);
    if (id.empty()) {
        cout << "ID cannot be empty!\n";
        return false;
    }
    if(isIdExists(id)){
        return false;
    }
    cout<<"\nEnter the name of student "<<id<<": ";
    getline(cin,name);
    if (name.empty()) {
        cout << "Name cannot be empty!\n";
        return false;
    }
    cout<<"\nEnter the Department of "<<name<<": ";
    getline(cin,department);
    cout<<"\nEnter the Semester of "<<name<<": ";
    getline(cin,semester);
    int n;
    for(;;){
        cout<<"\nEnter the no.of Subject for "<<name<<": ";
        if(!(cin >> n)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }
        if (n <= 0) {
            cout << "Number of subjects must be positive(greater than 0).\n";
            continue;
        }
        break;
    }
    marks.clear();
    float m;
    for(int i=0;i<n;i++){
        for(;;){
            cout<<"Enter the Marks of subject "<<i+1<<": ";
            if(!(cin >> m)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number.\n";
                continue;
            }
            if (m < 0||m>100) {
                cout << "Marks must be between 0 and 100.\n";
                continue;
            }
            break;
        }
        marks.push_back(m);
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}
void Student::display() const{
    cout<<"\nID: "<<id<<"\nName: "<<name<<"\nDepartment: "<<department<<"\nSemester: "<<semester<<"\nMarks: ";
    for(float m:marks){
        cout<<m<<" ";
    }
    try {
        cout << "\nGPA: " << fixed << setprecision(2) << Gpa() << "\n\n";
    } catch (const exception &e) {
        cout << "\nError calculating GPA: " << e.what() << "\n";
    }
}
const string& Student::getId() const{
    return id;
}
const string& Student::getName() const{
    return name;
}
const string& Student::getDepartment() const{
    return department;
}
const vector<float>& Student::getMarks() const{
    return marks;
}
const string& Student::getSemester() const{
    return semester;
}
void Student::updateName(){
    cout<<"\nEnter the new name to Update name of student "<<id<<": ";
    getline(cin,name);
    if (name.empty()) {
        cout << "Name cannot be empty. Keeping old value.\n";
    }
}
void Student::updateId(string& id){
    this->id=id;
}
void Student::updateDept(){
    cout<<"\nUpdate Department of "<<name<<": ";
    getline(cin,department);
}
void Student::updateSemester(){
    cout<<"\nUpdate Semester of "<<name<<": ";
}
void Student::updateMarks(){
    int n;
    for(;;){
        cout<<"\nUpdate no.of Subject for ID "<<name<<": ";
        if(!(cin >> n)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }
        if (n <= 0) {
            cout << "Number of subjects must be positive(greater than 0).\n";
            continue;
        }
        break;
    }
    float m;
    marks.clear();
    marks.reserve(n);
    for(int i=0;i<n;i++){
        for(;;){
            cout<<"Enter the Marks of subject"<<i+1<<": ";
            if(!(cin >> m)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number.\n";
                continue;
            }
            if (m < 0||m>100) {
                cout << "Marks must be between 0 and 100.\n";
                continue;
            }
            break;
        }
        marks.push_back(m);
    }
}
float Student::Gpa() const{
    if(marks.empty()){
        return 0;
    }
    float sum=0;
    for(float m:marks){
        sum += m;
    }
    return sum/(marks.size()*10.0f);
}
void Student::setId(const string& id){
    this->id=id;
}
void Student::setName(const string& name){
    this->name=name;
}
void Student::setDept(const string& dept){
    department=dept;
}
void Student::setSemester(const string& sem){
    semester=sem;
}
void Student::setMarks(const vector<float>& mark){
    marks.clear();
    marks.reserve(mark.size());
    marks=mark;
}
bool isIdExists(const std::string& idToCheck){
    if(userDetails.empty()){
        return false;
    }
    for(const auto& row:userDetails){
        loadFileName(row[0]);
        if(filename.empty()){
            continue;
        }
        for(const auto& file:filename){
            studentsForLogin.clear();
            string path = getUserFilePath(row[0], file);
            ifstream infile(path);
            if(!infile){
                return false;
            }
            int size;
            string sizee;
            string line;
            getline(infile,sizee);
            size=stoi(sizee);
            Student s;
            string id;
            string name;
            string second_name;
            int name_size;
            string dept;
            string sem;
            vector<float> marks;
            string length;
            for(size_t i=0;i<size;i++){
                infile>>id>>name_size>>name;
                while(name_size!=name.size()){
                    infile>>second_name;
                    name += " " + second_name;
                }
                infile>>dept>>sem>>length;
                marks.resize(stoi(length));
                for(size_t j=0;j<stoi(length);j++){
                    infile>>marks[j];
                }
                s.setId(id);
                s.setName(name);
                s.setDept(dept);
                s.setSemester(sem);
                s.setMarks(marks);
                studentsForLogin.push_back(s);
            }
            for(const auto& s:studentsForLogin){
                if(s.getId()== idToCheck){
                    cout<<"ID already available inside User Name: "<<row[0]<<" File name: "<<file<<" ,Give different ID!!\n";
                    return true;
                }
            }
            infile.close();
        }
    }
    return false;
}
void Student::printProgressCard() const {
        cout << "\n============================================\n";
    cout << "             STUDENT PROGRESS CARD           \n";
    cout << "============================================\n";
    cout << left << setw(15) << "Student ID:"  << id << endl;
    cout << left << setw(15) << "Name:"        << name << endl;
    cout << left << setw(15) << "Department:"  << department << endl;
    cout << left << setw(15) << "Semester:"    << semester << endl;
    cout << "--------------------------------------------\n";
    cout << " Marks:\n";
    for (size_t i = 0; i < marks.size(); i++) {
        cout << "   Subject " << setw(2) << (i+1) << ": " << marks[i] << endl;
    }
    cout << "--------------------------------------------\n";
   try {
        cout << left << setw(15) << "CGPA:"
             << fixed << setprecision(2) << Gpa() << endl;
    } catch (const exception &e) {
        cout << "Error calculating GPA: " << e.what() << endl;
    }
    cout << "============================================\n\n";
}