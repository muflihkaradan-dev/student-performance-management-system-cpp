#include <iostream>
#include "menu.h"
#include "users.h"
#include <filesystem>

using namespace std;



int main(){
    ios::sync_with_stdio(false);


    cout<<"Welcome to STUDENT PEFORMANCE MANAGEMENT SYSTEM\n";
    int choice;
    string username;
    int login;
    try {
        loadUser();
    } catch (const exception& e) {
        cerr << "Error loading user data: " << e.what() << "\n";
        return 1; // exit with error
    }
    for(;;){
        cout<<"1.Tutor Login\n2.Student Login\n0.Exit\n";
        cin>>login;
        if(login==0){
            cout << "Exiting....Goodbye!\n";
            break;
        }
        if(login==1){
            cout<<"1.REGISTER\n2.LOG IN\n";
            for(;;){
                if(!(cin >> choice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please enter a number.\n";
                    continue;
                }
                if(choice==1){
                    cin.ignore();
                    username=registerUser();
                    break;
                }
                else if(choice==2){
                    cin.ignore();
                    username=loginUser();
                    break;
                }
                else{
                    cout<<"Wrong Input!!!....Type('1'/'2')\n";
                }
            }
            loadFileName(username);
            Menu(username);
            break;
        }
        else if(login==2){
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            studentMenu();
            break;
        }
        else{
            cout<<"Invalid option. Please choose 0, 1, or 2.\n";
        }
    }
    cout<<"\nClosing Application....\n";
    cout<<"\nThank you for using STUDENT PEFORMANCE MANAGEMENT SYSTEM!!\n\n";
    return 0;
}