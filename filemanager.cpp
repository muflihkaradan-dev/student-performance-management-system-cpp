#include"filemanager.h"
#include<iostream>
#include<cstdlib>
#include<algorithm>
using namespace std;


void saveData(const string& username){
    string file_name;
    string choice;
    int flag=0;
    loadFileName(username);
    for(;;){
        cout<<"Enter the file name(with '.txt' extension) without space: ";
        getline(cin,file_name);
        if (file_name.empty()) {
            cerr << "Filename cannot be empty. Try again.\n";
            continue;
        }
        if(filename.empty()){
            break;
        }
        if(!filename.empty()){
            if(searchFile(file_name)>=0){
                cout<<"File "<<file_name<<" already exist,Press 'YES' to continue with same name(previous data will be overwritten),press 'NO' if you decide to give new name\n";
                for(;;){
                    getline(cin,choice);
                    if(choice=="YES"){
                        flag=1;
                        break;
                    }
                    else if(choice=="NO"){
                        flag=0;
                        break;
                    }
                    else{
                        cout<<"Wrong input!!,press YES/NO\n";
                    }
                }
                if(flag==1){
                    break;
                }
                else{
                    continue;
                }
            }
            else{
                cout << "File " << file_name << " not available!!....Press 'YES' to continue with same name(Data will be stored in new file) or Press 'NO' to provide different file name \n";
                for(;;){
                    getline(cin,choice);
                    if(choice=="YES"){
                        flag=1;
                        break;
                    }
                    else if(choice=="NO"){
                        flag=0;
                        break;
                    }
                    else{
                        cout<<"Wrong input!!,press YES/NO\n";
                    }
                }
                if(flag==1){
                    break;
                }
                else{
                    continue;
                }
            }
        }
    }
    string path = getUserFilePath(username, file_name);
    ofstream file(path);
    if(!file){
        throw runtime_error("Error: Could not open file " + path);
    }
    if (students.empty()) {
        cout << "No student data to save!\n";
        return;
    }
    file<<to_string(students.size());
    for(const Student& s:students){
        const auto& marks=s.getMarks();
        file<<"\n"<<s.getId()<<" "<<s.getName().size()<<" "<<s.getName()<<" "<<s.getDepartment()<<" "<<s.getSemester()<<" "<<to_string(marks.size());
        for(size_t i=0;i<marks.size();i++){
            file<<" "<<marks[i];
        }
    }
    saveFileName(username,file_name);
    file.close();
    cout<<"File saved succesfully!\nFile name: "<<file_name<<"\n";
}

int openData(const string& username){
    string file_name;
    string choice;
    int flag=0;
    for(;;){
        loadFileName(username);
        if (filename.empty()) {
            cout << "No files available to open.\n";
            return 1;
        }
        cout<<"\nAvailable files: ";
        for(int i=0;i<filename.size();i++){
            cout<<"'"<<filename[i]<<"'";
            if(i!=filename.size()-1){
                cout<<", ";
            }
            else{
                cout<<"\n";
            }
        }
        cout<<"Enter the file name(with '.txt' extension) without space: ";
        getline(cin,file_name);
        if(!filename.empty()){
            if(searchFile(file_name)>=0){
                cout<<"File "<<file_name<<" exists,Press 'YES' to continue with same name/press 'NO' if you decide to open new file\n";
                for(;;){
                    getline(cin,choice);
                    if(choice=="YES"){
                        flag=1;
                        break;
                    }
                    else if(choice=="NO"){
                        flag=0;
                        break;
                    }
                    else{
                        cout<<"Wrong input!!,press YES/NO\n";
                    }
                }
                if(flag==1){
                    break;
                }
                else{
                    continue;
                }
            }
            else{
                cout<<"File "<<file_name<<" not exist,try another file\n";
            }
        }
    }
    string path = getUserFilePath(username, file_name);
    ifstream infile(path);
    if(!infile){
        cerr<<"File '"<<file_name<<"' not available!\n";
        return 0;
    }
    try{
        int size;
        string sizee;
        string line;
        getline(infile,sizee);
        size=stoi(sizee);
        if (size < 0) throw runtime_error("Invalid size in file.");
        students.clear();
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
                if (!(infile >> marks[j])) throw runtime_error("Invalid mark data.");
            }
            s.setId(id);
            s.setName(name);
            s.setDept(dept);
            s.setSemester(sem);
            s.setMarks(marks);
            students.push_back(s);
        }
    }catch (const exception& e) {
        cerr << "Error while reading file: " << e.what() << "\n";
        return 1;
    }
    cout<<"Data opened successfully!!\n";
    infile.close();
    return 0;
}

void saveFileName(const string& username,const string& file_name){
    if(searchFile(file_name)<0){
        filename.push_back(file_name);
    }
    string path = getUserFilePath(username,"filename.txt");
    ofstream file(path);
    if(!file){
        return;
    }
    file<<to_string(filename.size());
    for(const string& s:filename){
        file <<" "<< s;
    }
    file.close();
}

int searchFile(const string& file_name){
    if(filename.empty()){
        cout << "Nothing available in directory!!\n";
        return -1;
    }

    auto it = find(filename.begin(), filename.end(), file_name);
    if(it != filename.end()){
        cout << "File found!!";
        return static_cast<int>(distance(filename.begin(), it));
    }

    return -1;
}

void loadFileName(const string& username){
    string path = getUserFilePath(username, "filename.txt");
    ifstream file(path);
    if(!file){
        filename.clear(); 
        return;
    }
    try{
        string sizee;
        file>>sizee;
        int size=stoi(sizee);
        if (size < 0) throw runtime_error("Invalid filename list size.");
        filename.clear();
        string files;
        for(int i=0;i<size;i++){
            if (!(file >> files)) throw runtime_error("Corrupted filename list.");
            filename.push_back(files);
        }
    }
    catch (const exception& e) {
        cerr << "Error loading filenames: " << e.what() << "\n";
        filename.clear();
    }
    file.close();
}

void createUserDir(const string& username) {
    string path = "users/" + username;
    if (!fs::exists(path)) {
        fs::create_directories(path);
        cout << "Created directory: " << path << endl;
    }
}

string getUserFilePath(const string& username, const string& filename) {
    return "users/" + username + "/" + filename;
}


void openDataforStudents(const string& username){
    if(filename.empty()){
        return;
    }
    for(const auto& file:filename){
        string path = getUserFilePath(username, file);
        ifstream infile(path);
        if(!infile){
            return;
        }
        int size;
        string sizee;
        string line;
        getline(infile,sizee);
        size=stoi(sizee);
        students.clear();
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
        infile.close();
    }
}