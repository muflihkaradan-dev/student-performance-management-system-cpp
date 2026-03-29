#include "users.h"
#include <cstdlib>
#include <cstdint>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <stdexcept>

using namespace std;

const int COLUMNSIZE = 2;  

static int i=0,j=0;//'j' iterator to registerUser()(iterates when give duplicate username),'i' iterator to loginUser()(iterates when give not registered username)


string registerUser(){
    cout<<"You are in the register window\n";
    string username,password,cpassword;
    vector<string> temprow;
    int flag=0,choice;
    for(;;){
        cout<<"Enter the Username(without space): ";
        getline(cin,username);
        if(searchUser(username)<0){
            break;
        }
        else{
            j++;
            if(j==3){
                cout<<"\nEntered username is already taken by another user\n";
                cout<<"Type'1' if you wish to login or Type '2' to continue with register\n";
                for(;;){
                    cin>>choice;
                    if(choice==1){
                        i=0;
                        cin.ignore();
                        return loginUser();
                        flag=1;
                        break;
                    }
                    else if(choice==2){
                        i=0;
                        flag=0;
                        cin.ignore();
                        break;
                    }
                    else{
                        cout<<"Wrong Input!!...Type '1' to REGISTER/Type '2' to continue with LOGIN\n";
                    }
                }
            }
            else{
                cout<<"\nEntered username is already taken by another user,Please try different one\n";
            }
            if(flag==1){
                break;
            }
            else{
                continue;
            }
        }
    }
    for(;;){
        cout<<"\nEnter the Password: ";
        getline(cin,password);
        cout<<"\nConfirm Password: ";
        getline(cin,cpassword);
        if(password==cpassword){
            break;
        }
        else{
            cout<<"\nTwo passwords are different,look carefully and enter same password in two field\n";
            continue;
        }
    }
    string hashed = sha256(password);
    temprow.push_back(username);
    temprow.push_back(hashed);
    userDetails.push_back(temprow);
    try {
        saveUser();
    } catch (const exception &e) {
        cerr << "Error saving new user: " << e.what() << "\n";
    }
    createUserDir(username);
    cout<<"\nSuccessfully Registered\n";
    cout<<"\nPlease Login to enter\n\n";
    return loginUser();
}
string loginUser(){
    cout<<"You are in the login window\n";
    string username,password;
    int index,choice,flag=0;
    for(;;){
        cout<<"Enter the Username: ";
        getline(cin,username);
        index=searchUser(username);
        if(index>=0){
            for(;;){
                cout<<"\nEnter the password: ";
                getline(cin,password);
                string input_hash = sha256(password);
                if(input_hash == userDetails[index][1]){
                    cout<<"\n";
                    return username;
                }
                else{
                    cout<<"\nWrong password,Please check the password once again\n";
                    continue;
                }
            }
        }
        else{
            i++;
            if(i==2){
                cout<<"\nUsername not available\n";
                cout<<"First Register if not registered,Type '1' to REGISTER/Type '2' to continue with LOGIN\n";
                for(;;){
                    cin>>choice;
                    if(choice==1){
                        i=0;
                        cin.ignore();
                        registerUser();
                        flag=1;
                        break;
                    }
                    else if(choice==2){
                        i=0;
                        flag=0;
                        cin.ignore();
                        break;
                    }
                    else{
                        cout<<"Wrong Input!!...Type '1' to REGISTER/Type '2' to continue with LOGIN\n";
                    }
                }
            }
            else{
                cout<<"\nUser name not available,Please check the user name once again\n";
            }
            if(flag==1){
                break;
            }
            else{
                continue;
            }
        }
    }
    cout<<"\n";
    return username;
}

int searchUser(const string& username){
    for(size_t i=0;i<userDetails.size();i++){
        if(username==userDetails[i][0]){
            return static_cast<int>(i);
        }
    }
    return -1;
}

void saveUser() {
    ofstream file("users.bin", ios::binary);
    if (!file) {
        throw runtime_error("Failed to open users.bin for writing.");
    }
    int32_t rows = userDetails.size();
    if(!file.write(reinterpret_cast<char*>(&rows), sizeof(rows))){
        throw runtime_error("Failed to write row count to users.bin.");
    }
    for (const auto& row : userDetails) {
        int32_t cols = row.size();
        if(!file.write(reinterpret_cast<char*>(&cols), sizeof(cols))){
            throw runtime_error("Failed to write column count.");
        }
        for (const auto& s : row) {
            int32_t len = s.size();
            if(!file.write(reinterpret_cast<char*>(&len), sizeof(len))){
                throw runtime_error("Failed to write string length.");
            }
            if(!file.write(s.c_str(), len)){
                throw runtime_error("Failed to write string content.");
            }                            
        }
    }

    file.close();
}

void loadUser() {
    ifstream file("users.bin", ios::binary);
    if (!file) {
        return;
    }
    userDetails.clear();
    int32_t rows;

    if(!file.read(reinterpret_cast<char*>(&rows), sizeof(rows))) {
        throw runtime_error("Failed to read number of rows from users.bin.");
    }

    for (int i = 0; i < rows; i++) {
        int32_t cols;
        if(!file.read(reinterpret_cast<char*>(&cols), sizeof(cols))){
            throw runtime_error("Failed to read column count from users.bin.");
        }
        vector<string> temprow;
        for (int j = 0; j < cols; j++) {
            int32_t len;
            if(!file.read(reinterpret_cast<char*>(&len), sizeof(len))){
                throw runtime_error("Failed to read string length from users.bin.");
            }
            string s(len, '\0');
            if(!file.read(&s[0], len)){
                throw runtime_error("Failed to read string content from users.bin.");
            }
            temprow.push_back(s);
        }
        userDetails.push_back(temprow);
    }
    file.close();
}

string toHexString(const unsigned char* hash, size_t length) {
    stringstream ss;
    for (size_t i = 0; i < length; ++i) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

string sha256(const string& input) {
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx) throw runtime_error("EVP_MD_CTX_new failed");

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int length = 0;

    // Initialize SHA-256 digest
    if (EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr) != 1)
        throw runtime_error("EVP_DigestInit_ex failed");

    // Feed the input data
    if (EVP_DigestUpdate(ctx, input.c_str(), input.size()) != 1)
        throw runtime_error("EVP_DigestUpdate failed");

    // Finalize
    if (EVP_DigestFinal_ex(ctx, hash, &length) != 1)
        throw runtime_error("EVP_DigestFinal_ex failed");

    EVP_MD_CTX_free(ctx);

    return toHexString(hash, length);
}