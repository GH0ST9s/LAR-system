#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <sstream>

class User{
    std::string username, email, password;
    std::string searchName, searchEmail, searchPassword;
    std::fstream file;

public:
    void login();
    void signUp();
    void forgotPassword();
    
} usr;

void User::signUp(){

    std::string checkUser;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "\n----------Sign Up----------\n";
    bool userTaken;
    std::vector<std::string> userList;
    file.open("loginData.dat", std::ios::in);
    std::string userCheck, line;
    while(std::getline(file, line)){
        std::stringstream ss(line);
        std::getline(ss, userCheck, '*');
        userList.push_back(userCheck);
    }
    file.close();
    do{
        userTaken = false;
        std::cout << "Enter your name: ";
        std::getline(std::cin, username);
        for(const auto& list: userList){
            if(username == list){
                userTaken = true;
                std::cout << "Username not available!" << std::endl << std::endl;
                break;
            }
        }
    } while(userTaken);
    
    std::cout << "Enter your email address: ";
    std::getline(std::cin, email);
    std::cout << "Enter your password: ";
    std::getline(std::cin, password);

    std::ofstream outFile("loginData.dat", std::ios::out | std::ios::app);
    if(!outFile){
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }
    outFile << username << '*' << email << '*' << password << std::endl;
    std::cout << "\nAccount created successfully!\n";
    outFile.close();
}

void User::login(){

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "----------LOGIN----------\n";
    std::cout << "Enter your username: ";
    std::getline(std::cin, searchName);
    std::cout << "Enter your password: ";
    std::getline(std::cin, searchPassword);

    file.open("loginData.dat", std::ios::in);
    
    while(file.peek() != EOF){
        
        std::getline(file, username, '*');
        std::getline(file, email, '*');
        std::getline(file, password, '\n');

        if(username == searchName){
            if(password == searchPassword){
                
                std::cout << "\nUsername: " << username << std::endl;
                std::cout << "Email: " << email << std::endl;
                std::cout << "Login successfull!\n";
            }
            else{
                std::cout << "Incorrect Password!\n";
            }
            return;
        }
    }
    file.close();
}

void User::forgotPassword(){

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n----------Forgot Password?----------\n";
    std::cout << "Enter your username: ";
    std::getline(std::cin, searchName);
    std::cout << "Enter your email address: ";
    std::getline(std::cin, searchEmail);

    file.open("loginData.dat", std::ios::in);
    while(file.peek() != EOF){

        std::getline(file, username, '*');
        std::getline(file, email, '*');
        std::getline(file, password);

        if(username == searchName && email == searchEmail){
                std::cout << "\nAccount found!\n";
                std::cout << "Username: " << username << std::endl;
                std::cout << "Password: " << password << std::endl;
        }
        else{
            std::cout << "\nAccount not found!\n";
        }
    }
    file.close();
}

int main(){

    int choice;
    do{
        std::cout << std::endl;
        std::cout << "----------LAR System----------\n";
        std::cout << "1. Login\n";
        std::cout << "2. Sign-Up\n";
        std::cout << "3. Forgot Password\n";
        std::cout << "0. Exit\n";
        std::cout << "-> ";
        std::cin >> choice;
        switch(choice){
            case 1:
                usr.login();
                break;

            case 2:
                usr.signUp();
                break;

            case 3:
                usr.forgotPassword();
                break;

            case 0:
                break;

            default:
                std::cout << "Invalid choice!\n";
                break;
        }
    } while(choice != 0);


    return 0;
}