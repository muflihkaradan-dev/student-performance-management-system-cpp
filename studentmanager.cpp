#include"studentmanager.h"
#include"filemanager.h"
#include<limits>
using namespace std;

bool addStudent(){
    Student s;
    try{
        if(s.input()){
            students.push_back(s);
            cout<<"\nStudent added successfully!!"<<endl;
            return true; 
        }
        else{
            cout << "Student input failed. Student not added.\n";
            return false;
        }
    }catch (const exception &e) {
        cerr << "Error adding student: " << e.what() << "\n";
        return false;
    }
}

void sortByGpa(){
    if (students.empty()) {
        cout << "No students available to sort.\n";
        return;
    }
    sort(students.begin(),students.end(),[](const auto& a,const auto& b){
        return a.Gpa()>b.Gpa();
    });
    if(askYesNo("Student list sorted based on GPA succesfully!!\nDo you want to see the list?(type YES/NO)\n")){
        for(const Student& s:students){
            DisplayStudent(s);
        }
    }
    else{
        cout<<"OKAY!!\n";
    }
}

void sortById(){
    if (students.empty()) {
        cout << "No students available to sort.\n";
        return;
    }
    sort(students.begin(),students.end(),[](const auto& a,const auto& b){
        return a.getId()<b.getId();
    });
    if(askYesNo("Student list sorted based on ID succesfully!!\nDo you want to see the list?(type YES/NO)\n")){
        for(const Student& s:students){
            DisplayStudent(s);
        }
    }
    else{
        cout<<"OKAY!!\n";
    }
}

void sortByName(){
    if (students.empty()) {
        cout << "No students available to sort.\n";
        return;
    }
    sort(students.begin(),students.end(),[](const auto& a,const auto& b){
        return a.getName()<b.getName();
    });
    if(askYesNo("Student list sorted based on NAME succesfully!!\nDo you want to see the list?(type YES/NO)\n")){
        for(const Student& s:students){
            DisplayStudent(s);
        }
    }
    else{
        cout<<"OKAY!!\n";
    }
}

void deleteStudent(){
    if (students.empty()) {
        cout << "No students available to delete.\n";
        return;
    }
    string id;
    cout<<"Enter the below detail to delete:-\n";
    for(;;){
        cout<<"\nEnter the student ID: ";
        getline(cin,id);
        if(id=="EXIT"){
            break;
        }
        auto it=find_if(students.begin(),students.end(),[id](const Student& s){
            return s.getId()==id;
        });
        if(it!=students.end()){
            students.erase(it);
            cout<<"Student with ID "<<id<<" deleted successfully!!\n";
            break;
        }
        else{
            cout<<"No data found to delete,please check entered ID!!\nIf entered ID is correct type 'EXIT' to exit\n";
        }
    }
}

int searchStudent(){
    if (students.empty()) {
        cout << "No students available.\n";
        return -1;
    }
    string id;
    bool flag;
    int i;
    for(;;){
        cout<<"Enter the student ID: ";
        getline(cin,id);
        if(id=="EXIT"){
            i=-1;
            break;
        }
        i=0;
        for(const Student& s:students){
            flag=false;
            if(id==s.getId()){
                cout<<"Student found,Student details:\n";
                DisplayStudent(s);
                flag=true;
                break;
            }
            i++;
        }
        if(flag==false){
            if(isIdExists(id)){
                cout<<"Student with ID: "<<id<<" Available,But you can't access.it's in different User directory\nplease check entered ID and try again,If entered ID is correct type 'EXIT' to exit!\n";
            }
            else{
                cout<<"Sorry,Student with ID: "<<id<<" not available,please check entered ID and try again,If entered ID is correct type 'EXIT' to exit!\n";
            }
            i=-1;
        }
        if(flag==true){
            break;
        }
    }
    return i;
}

void DisplayStudent(const Student& s) {
    s.display();
}

void DisplayStudentlist() {
    for(const Student& s:students){
        DisplayStudent(s);
    }
}

void updateStudent(){
    if (students.empty()) {
        cout << "No students available to update.\n";
        return;
    }
    cout<<"You are in edit mode,please give below data to edit\n";
    string id;
    bool flag=false;
    int index=searchStudent();
    if(index>=0){
        cout<<"\nWhat you want to edit of student "<<students[index].getName()<<"(ID/NAME/DEPARTMENT/SEMESTER/MARKS/NOTHING(if nothing to edit)): ";
        string edit;
        for(;;){
            getline(cin,edit);
            edit=lower(edit);
            if(edit=="id"){
                for(;;){
                    cout<<"\nEnter New ID to Update Student ID: ";
                    cin>>id;
                    if(!isIdExists(id)){
                        break;
                    }
                }
                students[index].updateId(id);
                break;
            }
            else if(edit=="name"){
                students[index].updateName();
                break;
            }
            else if(edit=="department"){
                students[index].updateDept();
                break;
            }
            else if(edit=="marks"){
                students[index].updateMarks();
                break;
            }
            else if(edit=="semester"){
                students[index].updateSemester();
                break;
            }
            else if(edit=="nothing"){
                break;
            }
            else{
                cout<<"Wrong Input!!..ID/NAME/DEPARTMENT/MARKS/NOTHING\n";
            }
        }
        if(edit=="nothing"){
            cout<<"\nNothing updated of Student with ID: "<<students[index].getId()<<" !!"<<endl;
        }
        else{
            cout<<"\nStudent data updated successfully!!"<<endl;
        }
    }
    else{
        cout<<"ID to update not found!!\n";
    }
}

void progressCard(){
    if (students.empty()) {
        cout << "No students available.\n";
        return;
    }
    string id;
    bool flag=false;
    int index=searchStudent();
    if(index>=0){
        cout<<"\n Loading Progress Card.....\n";
        students[index].printProgressCard();
    }
    else{
        cout<<"ID not found!!\n";
    }
}

static string lower(string s){ 
    for(char& c: s) c=tolower((unsigned char)c); 
    return s; 
}

static bool askYesNo(const string& prompt){
    string ans;
    for(;;){
        cout << prompt;
        getline(cin, ans);
        auto a = lower(ans);
        if(a=="yes") return true;
        if(a=="no")  return false;
        cout << "Please answer YES or NO.\n";
    }
}

void studentSearchForStudentLogin(){
    if (studentsForLogin.empty()) {
        cout << "No students available for login.\n";
        return;
    }
    string id,name;
    bool flag;
    for(;;){
        cout<<"Enter the student ID: ";
        getline(cin,id);
        if(id=="EXIT"){
            break;
        }
        for(const Student& s:studentsForLogin){
            flag=false;
            if(id==s.getId()){
                for(;;){
                    cout<<"Enter the student Name: ";
                    getline(cin,name);
                    if(name==s.getName()){
                        cout<<"\nWelcome "<<s.getName()<<"\nStudent details:\n";
                        DisplayStudent(s);
                        s.printProgressCard();
                        flag=true;
                        break;
                    }
                    else{
                        cout<<"\nEntered name is wrong,doesn't match with Student ID,Try again\n";
                    }
                }
                break;
            }
        }
        if(flag==false){
            cout<<"Sorry,Student with ID: "<<id<<" not available,please check entered ID and try again,If enetered ID is correct Please enquire to your class teacher and type 'EXIT' to exit!\n";
        }
        if(flag==true){
            break;
        }
    }
}