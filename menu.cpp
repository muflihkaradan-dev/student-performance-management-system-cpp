#include"menu.h"
#include<iostream>
#include<limits>

void Menu(const std::string& username){
    string menu;
    int nstudents;
    for(;;){
        cout<<"Please select a service:-\n"
            <<"1.Create a Student list\n"
            <<"2.Open Student data\n"
            <<"3.Exit Application\n";
        getline(cin,menu);
        if(menu=="1"){
            cout<<"Enter the no.of students: ";
            for(;;){
                if(!(cin >> nstudents)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please enter a number.\n";
                    continue;
                }
                if (nstudents <= 0) {
                    cout << "Number of students must be positive(greater than 0).\n";
                    continue;
                }
                break;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            for(int i=0;i<nstudents;i++){
               while(!addStudent()){}
               loadFileName(username);
            }
            if (getYesNo("Do you want to see the created list? (YES/NO): ")) {
                DisplayStudentlist();
            }
            if (askSaveData()){
                try {
                    saveData(username);
                }
                catch (const std::runtime_error& e) {
                    cerr << "Exception: " << e.what() << "\n";
                }
            }

            if (!askReturnToMenu()) return;
        }
        else if(menu=="2"){
            if(openData(username)){
                if (!askReturnToMenu()) return;
                continue;
            }
            DisplayStudentlist();
            if (!getYesNo("Do you want to continue? (YES/NO): ")) {
                if (!askReturnToMenu()) return;
                continue;
            }
            for(;;){
                cout<<"\nChoose an option:\n"
                    <<"1. Sort Student List\n"
                    <<"2. Search Student\n"
                    <<"3. Add Students\n"
                    <<"4. Delete Student\n"
                    <<"5. Update Student\n"
                    <<"6. See Progress Card\n"
                    <<"7. Go to Main Menu\n";
                int option;
                for(;;){
                    if(!(cin >> option)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input! Please enter a number.\n";
                        continue;
                    }
                    break;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                switch (option) {
                    case 1:
                        SortStudents();
                        if (!askReturnToMenu()) return;
                        break;
                    case 2:
                        searchStudent();
                        if (!askReturnToMenu()) return;
                        break;
                    case 3: {
                        int addCount;
                        cout<<"\nEnter number of students to add: ";
                        cin>>addCount;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        for (int i = 0; i < addCount; i++) {
                            while (addStudent() != 1) {}
                            loadFileName(username);
                        }
                        if (getYesNo("Show updated list? (YES/NO): ")) {
                            DisplayStudentlist();
                        }
                        if (!askSaveForOverwrite(username)) return;
                            break;
                        }
                    case 4:
                        deleteStudent();
                        if (!askSaveForOverwrite(username)) return;
                        break;
                    case 5:
                        updateStudent();
                        loadFileName(username);
                        if (!askSaveForOverwrite(username)) return;
                        break;
                    case 6:
                        progressCard();
                        if (!askReturnToMenu()) return;
                        break;
                    case 7:
                        goto backToMenu;
                    default:
                        cout << "Invalid option.\n";
                        break;
                }
            }
            backToMenu: ;
        }

        else if(menu=="3"){
            if (getYesNo("Are you sure you want to exit? (YES/NO): ")) {
                break;
            }
            cout << "Returning to main menu...\n";
        }
        else{
            cout<<"Invalid menu option.\n";
        }
    }
}
void SortStudents(){
    string choice;
    for(;;){
        cout<<"Which sort:-\nSort by GPA: Type 'GPA'\nSort by NAME: Type 'NAME'\nSort by ID: 'ID'\n";
        getline(cin,choice);
        choice = toUpper(choice);
        if(choice=="ID"){
            sortById();
            break;
        }
        else if(choice=="GPA"){
            sortByGpa();
            break;
        }
        else if(choice=="NAME"){
            sortByName();
            break;
        }
        else{
            cout<<"Wrong Input!!\n";
        }
    }
}

bool askReturnToMenu() {
   return getYesNo("Do you want to return to Previuos Menu? (YES/NO): ");
}

bool askSaveData(){
    for(;;){
        if (getYesNo("Do you want to save the data? (YES/NO): ")) return true;
        cout << "If not saved, data will be lost when closing the application.\n";
        if (getYesNo("Do you Confirm to exit without saving (YES / NO): ")) return false;
    }
}

bool askSaveForOverwrite(const string& username){
    int save;
    cout<<"\n";
    for(;;){
        cout<<"Do you want to save the data(else previous data will remain unchanged!!):\nType '1' for YES\nType '2' for NO\n"; 
        for(;;){
            if(!(cin >> save)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number.\n";
                continue;
            }
            break;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if(save==1){
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
            cout<<"Please ensure to enter the original(previuos) file name\n";
            try {
                saveData(username);
            }
            catch (const std::runtime_error& e) {
                cerr << "Exception: " << e.what() << "\n";
            }
            if(askReturnToMenu()){
                return true;
            }
            else{
                return false;
            }
        }
        else if(save==2){
            if(askReturnToMenu()){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            cout<<"wrong input!!\n";
        }
    }
}

void studentMenu(){
    studentsForLogin.clear();
    if(userDetails.empty()){
        cout<<"\nNo student is registered yet,Please enquire with your class teacher\n";
        return;
    }
    for(const auto& row:userDetails){
        loadFileName(row[0]);
        openDataforStudents(row[0]);
    }
    studentSearchForStudentLogin();
}

string toUpper(const string& s) {
    string out = s;
    transform(out.begin(), out.end(), out.begin(), ::toupper);
    return out;
}

bool getYesNo(const string& prompt) {
    string choice;
    while (true) {
        cout << prompt;
        getline(cin, choice);
        choice = toUpper(choice);
        if (choice == "YES") return true;
        if (choice == "NO") return false;
        cout << "Wrong input! Please type YES or NO.\n";
    }
}