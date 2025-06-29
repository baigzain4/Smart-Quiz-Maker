#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <windows.h>
#include <sstream>
#include <ctime>
#include <vector>
using namespace std;

// Defining Colors
#define YELLOW "\033[33m"        // Yellow
#define RED "\033[1;91m"       // Red
#define GREEN "\033[92m"     // Green
#define RESET "\033[0m"      // Reset 


#define USERS_FILE "Users_StudentAndTeacher.txt"
#define QUIZ_FILE "Quiz.txt"

void teacherlogin();
struct UI {
    void colorApply(string color) {
        cout << color;
    }
    void success(string message){
        cout <<"\033[1;92m[ ✓ ]: " << message << "\033[92m" << endl;
    }
    void error(string message) {
        cout << "\033[1;91m[ X ]: " << message << "\033[92m" << endl;
    }
    
    void exitProgram(){
        cout << "Thank you for using Smart Quiz Maker!";
        Sleep(500);
    }
    void animation() {
    for (int i = 0; i < 3; ++i) {
        Sleep(500);
        cout << "." << flush;
    }

    for (int i = 0; i < 3; ++i) {
        Sleep(500);
        cout << "\b \b" << flush; // Erase dot
    }

    Sleep(300);
    for (int i = 0; i < 3; ++i) {
        Sleep(500);
        cout << "." << flush;
    }
    Sleep(600);
    cout << endl;
}
    void header(string appName = " SMART QUIZ MAKER ") {
        colorApply(GREEN);
        cout << setw(50) << setfill('=') << "" << endl;
        colorApply(YELLOW);
        cout << setfill(' ') << setw((appName.size()) / 2 + 25);
        cout << appName << endl;
        colorApply(GREEN);
        cout << setw(50) << setfill('=') << "" << endl;
    }

    void printMenu() {
    cout << "╭──────────────────────────────────────╮\n";
    cout << "│              \033[33mMAIN MENU\033[92m               │\n";
    cout << "├──────────────────────────────────────┤\n";
    cout << "│ [\033[33m★ 1.\033[92m] Admin                         │\n";
    cout << "│ [\033[33m★ 2.\033[92m] Teacher                       │\n";
    cout << "│ [\033[33m★ 3.\033[92m] Student                       │\n";
    cout << "│ [\033[33m✘ 4.\033[92m] Exit                          │\n";
    cout << "╰──────────────────────────────────────╯\n";
    cout << "Enter your choice [1 to 4]: " << endl;
    cout << "============> ";
    }

    int smallerLimit =1, upperLimit =4;
    void askChoice(int &choice) {
        cin >> choice;
        while ( cin.fail() || choice < smallerLimit || choice > upperLimit) {
            cin.clear();
            cin.ignore(1000, '\n');
            colorApply(RED);
            cout << "[ ERROR ✘ ] Invalid input. Please enter a number between " 
                     << smallerLimit << " and " << upperLimit << ": ";
            cin >> choice;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "[ ERROR ✘ ] Invalid input. Please enter a number between " 
                     << smallerLimit << " and " << upperLimit << ": ";
                     cin >> choice;
                    }
                }
            colorApply(GREEN);
    }
};
struct Admin{
    UI adminUI;
    void backOption(){
        cout << "Press any key to continue... ";
        cin.get();
        adminDashboard();
        adminChoice();
    }
    void adminDashboard(){
        system("cls");
        adminUI.smallerLimit = 1;
        adminUI.upperLimit = 7;
        adminUI.header("WELCOME TO ADMIN DASHBOARD");
        cout << "\033[33m1.\033[92m Register the user (Students & teachers)\n";// ==> done
        cout << "\033[33m2.\033[92m Login to Teacher dashboard\n";
        cout << "\033[33m3.\033[92m Update information (password, designnation, contact, etc.)\n";
        cout << "\033[33m4.\033[92m Generate user Credentials\n"; // ==> Done
        cout << "\033[33m5.\033[92m Remove User \n";
        cout << "\033[33m6.\033[92m Search User\n"; 
        cout << "\033[33m7.\033[92m Exit \n"; 
        cout << "Enter Choice [1 to 7]: \n";
        cout << "========>";
    }
    bool CheckUsername(string &username){
        string fileUsername, line;
        ifstream usernameCheck(USERS_FILE);
        while(getline(usernameCheck, line)){
            istringstream iss(line);
            iss >> fileUsername;
            if(username == fileUsername){
                return true;
            }
        }
        usernameCheck.close();
        return false;
    }

    

    string username, password, role, designation,contact;
    void registerDetails(){
    do {
        if (CheckUsername(username)){
            cout << "\033[1;91m[ ✘ ]: Username already exists. Please try again.\033[0m" << endl;
        }
        cout << "Enter username (at least 4 charcaters): ";
        cin >> username;
        while (cin.fail() || username.size() < 4) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Enter username (at least 4 charcaters): ";
            cin >> username;
        }
    } while (CheckUsername(username));
    cout << "Enter password (at least 8 characters long): ";
    cin >> password;
    while (cin.fail() || password.size() < 8) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Enter password (at least 8 charcaters): ";
        cin >> password;
    }
    cout << "Enter your designation: ";
    cin >> designation;
    cout << "Enter your role(Student, Teacher): ";
    cin >> role;
    while(role != "Teacher" && role != "teacher" && role != "Student" && role != "student"){
        cout << "Enter your correct role( Student, Teacher): ";
        cin >> role;
    }
    cout << "Enter your contact number: ";
    cin >> contact;

}

    void Register(bool debug = true){
        ifstream FileCheck(USERS_FILE);
        if(FileCheck.good()){
        cout<< "";
        }
        else {
        ofstream createFile(USERS_FILE);
        createFile.close();
        }
        FileCheck.close();
        ofstream RegisterWrite(USERS_FILE, ios::app);
        if (!RegisterWrite.is_open()) {
          adminUI.error("Failed to open Users_StudentAndTeacher.txt for writing.");
          return;
        }      
        if (debug){
            registerDetails();
        }
        RegisterWrite << username << " " << password  << " " << role << " " << designation << " " << contact << endl;
        RegisterWrite.close();
        adminUI.success("Successfully Registered!");
        backOption();
    }
    


    // User Credentials

    string Random_String_Generator( int length){
        string result;
        string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        for (int i = 0; i < length ; i++){
            result = result + chars[rand() % chars.size()];
        }
        return result;
    }




void userCredentials(){
    string firstName;
    cout << "Enter your first name: ";
    cin >> firstName;
    cout << "Enter your role(Student, Teacher): ";
    cin >> role;
    while(role != "Teacher" && role != "teacher" && role != "Student" && role != "student"){
        cout << "Enter your correct role(Student, Teacher): ";
        cin >> role;
    }
    cout << "Enter your designation: ";
    cin >> designation;
    cout << "Enter your contact number: ";
    cin >> contact;
    username = firstName + "_" + Random_String_Generator(4);
    password = Random_String_Generator(8);
    Register(false);
    adminUI.colorApply(YELLOW);
    cout  << "User Credentials: " << endl;
    adminUI.colorApply(GREEN);
    cout << "\033[1;92mUsername:\033[0;92m " << username << endl;
    cout << "\033[1;92mPassword:\033[0;92m " << password << endl;
    cout << "\033[1;92mRole:\033[0;92m " << role << endl;
    cout << "\033[1;92mDesignation:\033[0;92m " << designation << endl;
    cout << "\033[1;92mContact:\033[0;92m " << contact << endl;
    adminUI.colorApply(GREEN);
    backOption();
    }

    bool userSearch(string username, bool debug = true){
        
        int check = 0;
        ifstream UsersFile(USERS_FILE);
        if (!UsersFile.is_open()) {
           adminUI.error("Failed to open Users_StudentAndTeacher.txt for reading.");
           if (debug) backOption();
           return false;
         }
        string line, user, userPass, userDesig, userRole, userContact;
        while(getline(UsersFile, line)){
            istringstream iss(line);
            iss >> user >> userPass >> userRole >> userDesig >> userContact;
            if(user == username){
                check =1;
                cout << "\033[1;92mUsername:\033[0;92m " << user << endl;
                cout << "\033[1;92mPassword:\033[0;92m " << userPass << endl;
                cout << "\033[1;92mRole:\033[0;92m " << userRole << endl;
                cout << "\033[1;92mDesignation:\033[0;92m " << userDesig << endl;
                cout << "\033[1;92mContact:\033[0;92m " << userContact << endl;
                if(debug){
                    backOption();
                }
                return true;   
            }
        }
        UsersFile.close();
        if (check ==0){
            cout << "User not found." << endl;
            if(debug){
                    backOption();
            }
            return false;
        }
    }

    // Update User Information


    void updateInformation() {
    string username;
    cout << "Enter username to update: ";
    cin >> username;
    adminUI.colorApply(YELLOW);
    cout << "Current Information: " << endl;
    adminUI.colorApply(GREEN);
    if (!userSearch(username, false)) {
    return; // Exit if user not found
    }
    ifstream inputting(USERS_FILE);
    if (!inputting.is_open()) {
    adminUI.error("Failed to open Users_StudentAndTeacher.txt for reading.");
    backOption();
    return;
}
    vector<string> fileContents;  // To store modified contents
    string line, user, userPass, userRole, userDesig, userContact;

    while (getline(inputting, line)) {
        istringstream iss(line);
        if (iss >> user >> userPass >> userRole >> userDesig >> userContact) {
            if (user == username) {
                int choice=0;
                adminUI.smallerLimit = 1;
                adminUI.upperLimit = 4;
                string newPassword, newRole, newDesig, newContact;
                adminUI.colorApply(YELLOW);
                cout << "Select the information you want to update:" << endl;
                adminUI.colorApply(GREEN);
                cout << "1. Update Password" << endl;
                cout << "2. Update Role(Student, Teacher)" << endl;
                cout << "3. Update Designation" << endl;
                cout << "4. Update Contact" << endl;
                cout << "Enter choice to update (1-4): ";
                adminUI.askChoice(choice);
                switch (choice)
                {
                case 1:
                    cout << "Enter new password: ";
                    cin >> newPassword;
                    cout << "Enter password (at least 8 characters long): ";
            cin >> password;
            while (cin.fail() || password.size() < 8) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Enter password (at least 8 characters): ";
                cin >> password;
            }
                    userPass = newPassword;
                    cout << "Password updated successfully for user: " << username << endl;
                    break;
                    case 2:
                    cout << "Enter new role: ";
                    cin >> newRole;
                    while(newRole != "Teacher" && newRole != "teacher" && newRole != "Student" && newRole != "student"){
                     cout << "Enter your correct role( Student, Teacher): ";
                     cin >> newRole;
                    }
                    userRole = newRole;
                    cout << "Role updated successfully for user: " << username;
                    break;
                    case 3:
                    cout << "Enter new designation: ";
                    cin >> newDesig;
                    userDesig = newDesig;
                    cout << "Designation updated successfully for user: " << username;
                    break;
                    case 4:
                    cout << "Enter new contact: ";
                    cin >> newContact;
                    userContact = newContact;
                    cout << "Contact updated successfully for user: " << username;
                    break;
                    
                default:
                cout << "Wrong Input" << endl;
                    break;
                }
                
                // Reconstruct the line with updated password
                ostringstream strCreate;
                strCreate << user << " " << userPass << " " << userRole 
                    << " " << userDesig << " " << userContact;
                line = strCreate.str();
            }
        }
        fileContents.push_back(line);
    }
    inputting.close();

    // Open file for writing (this will overwrite the file)
    ofstream outFile(USERS_FILE);

// Should check:
    if (!outFile.is_open()) {
    adminUI.error("Failed to open Users_StudentAndTeacher.txt for writing.");
    backOption();
    return;
    }

    for (size_t i = 0; i < fileContents.size(); ++i) {
    outFile << fileContents[i] << endl;
}
    outFile.close();
    backOption();
}

    void delUser(){
        adminUI.colorApply(GREEN);
        string username;
        cout << "Enter username that you want to delete: ";
        cin >> username;
        bool condition = CheckUsername(username);
        if(condition){
            cout << "User Found. Now Deleting ";
            adminUI.animation();
            adminUI.success("User Deleted Successfully.");
            fstream completeFile(USERS_FILE);
            if (!completeFile.is_open()) {
            adminUI.error("Failed to open Users_StudentAndTeacher.txt for reading.");
            backOption();
            return;
        }
        ofstream tempFile("temp.txt");
        if (!tempFile.is_open()) {
        adminUI.error("Failed to create temp.txt for writing.");
        completeFile.close();
        backOption();
        return;
        } 
            string line, user, userPass, userDesig; 
            while(getline(completeFile, line)){
                istringstream iss(line);
                iss >> user;
                if( username!=user){
                    tempFile << line << endl;
                }
            }
            completeFile.close();
            tempFile.close();
            // remove,rename returns 0 if successfully deleted
            if (remove(USERS_FILE) != 0) {
    adminUI.error("Failed to remove original file.");
    backOption();
    return;
    }
    if (rename("temp.txt", USERS_FILE) != 0) {
    adminUI.error("Failed to rename temp file.");
    backOption();
    return;
    }
        }
        else {
            adminUI.error("User not found. Please try again.");
        }
        backOption();
    }
    void adminChoice(){
        int choice =0;
        adminUI.smallerLimit =1;
        adminUI.upperLimit =7;
        adminUI.askChoice(choice);
        switch(choice){
            case 1:{
                adminUI.header("Register User");
                Register();
                break;
            }
            case 2:{
                system("cls");
                adminUI.header("Login to Teacher Dashboard");
                cout << "This feature is coming soon.\n";
                break;
            }
            case 3:{
                system("cls");
                adminUI.header("Update Information");
                updateInformation();
                break;
            }
            case 4:{
                system("cls");
                adminUI.header("Generate User Credentials");
                userCredentials();
                break;
            }
            case 5:{
                system("cls");
                adminUI.header("Remove User");
                delUser();
                break;
            }
            case 6:{
                system("cls");
                adminUI.header("Search User");                
                string username;
                cout << "Enter username: ";
                cin >> username;
                userSearch(username, false);
                backOption();
                break;
            }
            case 7:{
                adminUI.exitProgram();
            }
        }
    }
};







void displayStudentMenu() {
    system("cls");
    UI ui;
    ui.header("Welcome to Student Dashboard");
    cout << "1. Update Information\n";
    cout << "2. Take Quiz (Input Your Own Questions)\n";
    cout << "3. View Result\n";
    cout << "4. View Grade\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}


void CreateQuiz(){
    system("cls");
    UI ui;
    ui.header("Create Quiz");
    int numberOfQuestions =0;
    time_t quizTime = 0;
    string quizTitle, quizDescription, quizSubject;
    cout << "Enter the number of questions you want to add: ";
    cin >> numberOfQuestions;
    cin.ignore(); 
    cout << "Enter the title of the quiz: ";
    getline(cin, quizTitle);
    cout << "Enter the description of the quiz: ";
    getline(cin, quizDescription);
    cout << "Enter the subject of the quiz: ";
    getline(cin, quizSubject);
    cout << "Enter the time limit for the quiz in minutes: ";
    cin >> quizTime;
    cin.ignore();
    string question, option1, option2, option3, option4;
    int correctOption = 0;
    ofstream quizFile(QUIZ_FILE, ios::app);
    quizFile << quizTitle << "," << quizDescription << "," << quizSubject << "," << quizTime << ",";
    for(size_t i = 0; i< numberOfQuestions; i++){
        cout << "Enter question " << i+1 << ": ";
        getline(cin, question); 
        cout << "Enter option 1: ";
        getline(cin, option1);
        cout << "Enter option 2: ";
        getline(cin, option2);
        cout << "Enter option 3: ";
        getline(cin, option3);
        cout << "Enter option 4: ";
        getline(cin, option4);
        cout << "Enter the correct option (1, 2, 3, or 4): ";
        cin >> correctOption;
        quizFile << question << "," << option1 << "," << option2 << "," << option3 << "," << option4 << "," << correctOption;
    }
    quizFile << endl;
    quizFile.close();
    ifstream quizFileR(QUIZ_FILE, ios::app);
    cout << "Preview of the quiz you created: " << endl;
    if (!quizFileR.is_open()) {
        ui.error("Failed to open Quiz.txt for reading.");
        return;
    }
    string line;
    while (getline(quizFileR, line)) {
        cout << line << endl;
    }
    quizFileR.close();

}

void displayTeacherMenu() {
    UI ui;
    Admin updateFunction;
    int choice =0;
    system("cls");
    ui.header("Welcome to Teacher Dashboard");
    cout << "1. Login to teacher dashboard \n2. Update information (password, designation, contact etc.) \n3. Create quizzes with customizable parameters \n4.Editing Existing Quizzes \n5. Assign Quizzes to specifi Classes \n6. Results and Grading \n7. Exit \n";
    cout << "Choose an option: ";
    ui.smallerLimit = 1;
    ui.upperLimit = 7;
    ui.askChoice(choice);
    switch (choice){
        case 1:{
            teacherlogin();
            break;
        }
        case 2:{
            updateFunction.updateInformation();
        }
        case 3:{
            CreateQuiz();
            break;
        }
    }
}

struct User {
    string username;
    string password;
    string role;
};

    void teacherlogin(){
    User user;
    Admin admin;
    user.role = "teacher"; 
    string user1, userPass, userRole, userDesig, userContact, line;
    cout << "Enter your username to login: ";
    cin >> user.username;
    admin.CheckUsername(user.username);
    if(!admin.CheckUsername(user.username)) {
        cout << "Username not found. Please register first.\n";
        return;
    }
    else if (admin.CheckUsername(user.username)){
    cout << "Enter your password to login: ";
    cin >> user.password;
    ifstream inputting("Users_StudentAndTeacher.txt");
    while (getline(inputting, line)) {
    istringstream iss(line);
    iss >> user1 >> userPass >> userRole >> userDesig >> userContact;
    if (user.username == user1 && user.password == userPass && user.role == userRole) {
        cout << "Login successful! Welcome, " << user1 << ".\n";
        return; // Exit after successful login
    }
    }
    cout << "Invalid username or password. Please try again.\n";
 }
}

void student(){

}













int main() {
    SetConsoleOutputCP(CP_UTF8); // Set console output to UTF-8 for proper character display
    srand(time(0));
    UI ui;
    Admin admin;
    int choice = 0;
    ui.header();
    ui.printMenu();
    ui.askChoice(choice);

    switch (choice) {
    case 1: {
        admin.adminDashboard();
        admin.adminChoice();
        break;
    }
    case 2: {
        displayTeacherMenu();
        break;
    }
    case 3: {
    student();
    break;
    }
    case 4: {
        ui.exitProgram();
        return 1;
        break;
    }
    default:{
        cout << "Wrong Input.\n";
    }
}
    return 0;
}