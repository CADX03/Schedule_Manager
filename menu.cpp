#include "menu.h"

/**
 * Gets the number of digits of a given integer n.\n
 * Time Complexity: O(log(n)).
 * @param n An integer.
 * @return An integer corresponding to the number of digits of the given integer.
 */
int getNumOfDigits(int n){
    int numberOfDigits = 0;
    do {
        ++numberOfDigits;
        n /= 10;
    } while (n);
    return numberOfDigits;
}

/**
 * Checks if the input by the user is a number (integer) and warns him if it isn't.
 * @return An integer corresponding to the user's choice.
 */
int checkNumber() {
    int choice;
    std::cin >> choice;
    while(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "WARNING: Invalid input.  Please, enter a number: ";
        std::cin >> choice;
    }
    std::cout << std::endl;
    return choice;
}


Menu::Menu(ScheduleManager* scheduleManager, ClassesFileManager* classesFileManager, StudentsFileManager* studentsFileManager, RequestsFileManager* requestsFileManager) {
    scheduleManager_ = scheduleManager;
    classesFileManager_ = classesFileManager;
    studentsFileManager_ = studentsFileManager;
    requestsFileManager_ = requestsFileManager;
}

int Menu::checkValidInput() {
    int choice;
    std::cout << "Select an option: ";
    std::cin >> choice;
    while(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "Invalid input.  Please, enter a number: ";
        std::cin >> choice;
    }
    std::cout << std::endl;
    return choice;
}

int Menu::checkStudentNumber() {
    int choice;
    std::cin >> choice;
    while(std::cin.fail() || getNumOfDigits(choice) != 9) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "WARNING: Invalid input.  Please, enter a number: ";
        std::cin >> choice;
    }
    std::cout << std::endl;
    return choice;
}

void Menu::showHeader() const {
    std::cout << "---------- SCHEDULE MANAGER ----------" << std::endl;
}
void Menu::showFooter() const {
    std::cout << std::endl;
    std::cout << "9. Back" << std::endl;
    std::cout << "0. Start Menu" << std::endl;
    std::cout << std::endl;
}

void Menu::start() {
    state_ = State::LoadMenu;
    showHeader();
    std::cout << std::endl;
    std::cout << "Before anything else..." << std::endl;
    std::cout << "Please set the maximum number of students any class can have: ";
    int cap = checkNumber();
    scheduleManager_->setClassCap(cap);
    while(state_ != State::Exit){
        handleState();
    }
    requestsFileManager_->save("invalid_requests.txt", *scheduleManager_);
}

void Menu::handleState() {
    switch (state_) {
        case State::LoadMenu:
            showLoadMenu();
            break;
        case State::MainMenu:
            showMainMenu();
            break;
        case State::InfoMenu:
            showInfoMenu();
            break;
        case State::RequestMenu:
            showRequestMenu();
            break;
        case State::StudentMenu:
            showStudentMenu();
            break;
        case State::ClassMenu:
            showClassMenu();
            break;
        case State::CourseUnitMenu:
            showCourseUnitMenu();
            break;
        case State::ScheduleMenu:
            showScheduleMenu();
            break;
    }
}

void Menu::showLoadMenu() {
    showHeader();
    std::string classesFile;
    std::string studentsFile;

    std::cout << std::endl;
    std::cout << "Choose the file from which you want to load the classes information [classes.csv]: ";
    std::cin >> classesFile;
    std::cout << "Choose the file from which you want to load the students information [students_classes.csv]: ";
    std::cin >> studentsFile;
    std::cout << std::endl;

    classesFileManager_->load(classesFile, *scheduleManager_);
    studentsFileManager_->load(studentsFile, *scheduleManager_);

    state_ = State::MainMenu;

}

void Menu::showMainMenu() {
    showHeader();

    int choice;
    std::cout << "1. Listing Menu" << std::endl;
    std::cout << "2. Manage Students" << std::endl;
    std::cout << "3. Save Changes" << std::endl;
    std::cout << "9. Credits" << std::endl;
    std::cout << std::endl;
    std::cout << "0. Quit" << std::endl;
    std::cout << std::endl;

    choice = checkValidInput();

    switch (choice) {
        case 1:
            state_ = State::InfoMenu;
            return;
        case 2:
            state_ = State::RequestMenu;
            return;
        case 3:
        {
            std::string classesFile;
            std::string classesPerCourseUnitFile;
            std::string studentsFile;

            std::cout << "Choose the file in which you want to save the classes information [classes_modified.csv]: ";
            std::cin >> classesFile;
            std::cout << "Choose the file in which you want to save the classes and course unit information [classes_per_uc_modified.csv]: ";
            std::cin >> classesPerCourseUnitFile;
            std::cout << "Choose the file in which you want to save the students information [students_classes_modified.csv]: ";
            std::cin >> studentsFile;
            std::cout << std::endl;
            classesFileManager_->save(classesFile, *scheduleManager_);
            classesFileManager_->saveClassesPerCourseUnit(classesPerCourseUnitFile,*scheduleManager_);
            studentsFileManager_->save(studentsFile, *scheduleManager_);
        }
            return;
        case 9:
            std::cout << "Software developed by:" << std::endl;
            std::cout << "Joao Costa" << " - " << "Marco Costa" << " - " << "Tiago Viana" << std::endl;
            std::cout << "G40" << " - " << "2LEIC04" << " - " << "AED 2022/2023" << std::endl;
            std::cout << std::endl;
            return;
        case 0:
            state_ = State::Exit;
            return;
    }
}

void Menu::showInfoMenu(){
    showHeader();

    int choice;
    std::cout << "----- Listing Menu -----" << std::endl;
    std::cout << "1. View students" << std::endl;
    std::cout << "2. Number of students per class" << std::endl;
    std::cout << "3. Number of students per Course Unit" << std::endl;
    std::cout << "4. Check schedule" << std::endl;

    showFooter();

    choice = checkValidInput();

    switch (choice) {
        case 1:
            state_ = State::StudentMenu;
            break;
        case 2:
            state_ = State::ClassMenu;
            break;
        case 3:
            state_ = State::CourseUnitMenu;
            break;
        case 4:
            state_ = State::ScheduleMenu;
            break;
        case 9: case 0:
            state_ = State::MainMenu;
            break;
        default:
            break;
    }
}

void Menu::showRequestMenu() {
    showHeader();

    int choice;

    std::cout << "----- Request Menu -----" << std::endl;
    std::cout << "1. Add a student" << std::endl;
    std::cout << "2. Remove a student" << std::endl;
    std::cout << "3. Add a student to a class" << std::endl;
    std::cout << "4. Remove a student from a class" << std::endl;
    std::cout << "5. Manage a student's classes" << std::endl;

    showFooter();

    choice = checkValidInput();

    switch (choice) {
        case 1:
        {
            int studentCode;
            std::cout << "Enter the student's number: ";
            studentCode = checkStudentNumber();

            std::string studentName;
            std::string courseUnitCode;
            std::string classCode;

            std::cout << "Enter the student's name: ";
            cin.ignore();
            std::getline(std::cin, studentName);
            std::cout << std::endl;

            std::cout << "Enter the course unit code: ";
            std::getline(std::cin, courseUnitCode);
            std::cout << std::endl;

            std::cout << "Enter the class code: ";
            std::getline(std::cin, classCode);
            std::cout << std::endl;

            std::vector<Class*> classes;
            classes.push_back(scheduleManager_->getClass(classCode, courseUnitCode));
            while(true){
                std::cout << "Do you want to add any more classes to this student? [Yes/No]" << std::endl;
                std::string check;
                std::getline(std::cin, check);
                if(check == "No" || check == "no") break;
                else if (check == "Yes" || check == "yes"){
                    std::cout << "Enter the course unit code: ";
                    std::getline(std::cin, courseUnitCode);
                    std::cout << std::endl;
                    std::cout << "Enter the class code: ";
                    std::getline(std::cin, classCode);
                    std::cout << std::endl;
                    classes.push_back(scheduleManager_->getClass(classCode, courseUnitCode));
                }
                else std::cout << "ERROR: Invalid input." << std::endl;
            }
            scheduleManager_->addRequest(Request(Request::AddStudent, Student(studentCode, studentName, classes)));
            break;
        }
        case 2:
        {
            int studentCode;
            std::cout << "Enter the student's number: ";
            studentCode = checkStudentNumber();
            scheduleManager_->addRequest(Request(Request::RemoveStudent, Student(studentCode, "")));
            break;
        }
        case 3:
        {
            int studentCode;
            std::string courseUnitCode;
            std::string classCode;

            std::cout << "Enter the student's number: ";
            studentCode = checkStudentNumber();

            cin.ignore();
            std::cout << "Enter the course unit code: ";
            std::getline(std::cin, courseUnitCode);
            std::cout << std::endl;

            std::cout << "Enter the class code: ";
            std::getline(std::cin, classCode);
            std::cout << std::endl;

            std::vector<Class*> classes;
            classes.push_back(scheduleManager_->getClass(classCode, courseUnitCode));

            scheduleManager_->addRequest(Request(Request::AddStudentToClass, Student(studentCode, "", classes)));
            break;
        }
        case 4:
        {
            int studentCode;
            std::string courseUnitCode;
            std::string classCode;

            std::cout << "Enter the student's number: ";
            studentCode = checkStudentNumber();

            cin.ignore();
            std::cout << "Enter the course unit code: ";
            std::getline(std::cin, courseUnitCode);
            std::cout << std::endl;
            Class classAux = Class("", courseUnitCode, vector<Lecture*>());
            Class* classAuxPtr = &classAux;
            scheduleManager_->addRequest(Request(Request::RemoveStudentFromClass, Student(studentCode, "",vector<Class*>{classAuxPtr})));
            break;
        }
        case 5:
        {
            int studentCode;
            std::cout << "Enter the student's number: ";
            studentCode = checkStudentNumber();

            std::string courseUnitCode;
            std::string classCode;

            std::cout << "Enter the course unit for which you intend to change the class: ";
            cin.ignore();
            std::getline(std::cin, courseUnitCode);
            std::cout << std::endl;

            std::cout << "Enter the class you want to change to: ";
            std::getline(std::cin, classCode);
            std::cout << std::endl;

            std::vector<Class*> classes;
            classes.push_back(scheduleManager_->getClass(classCode, courseUnitCode));
            while(true){
                std::cout << "Do you want to change any more classes of this student? [Yes/No]" << std::endl;
                std::string check;
                std::getline(std::cin, check);
                if(check == "No" || check == "no") break;
                else if (check == "Yes" || check == "yes"){
                    std::cout << "Enter the course unit for which you intend to change the class: ";
                    std::getline(std::cin, courseUnitCode);
                    std::cout << std::endl;
                    std::cout << "Enter the class you want to change to: ";
                    std::getline(std::cin, classCode);
                    std::cout << std::endl;
                    classes.push_back(scheduleManager_->getClass(classCode, courseUnitCode));
                }
                else std::cout << "ERROR: Invalid input." << std::endl;
            }
            scheduleManager_->addRequest(Request(Request::ManageStudentClasses, Student(studentCode, "", classes)));
            break;
        }
        case 9: case 0:
            scheduleManager_->handleRequests();
            state_ = State::MainMenu;
            break;
        default:
            break;
    }
}

void Menu::showStudentMenu() {
    showHeader();

    int choice;

    std::cout << "----- Students Menu -----" << std::endl;
    std::cout << "1. List all students -> Alphabetically" << std::endl;
    std::cout << "2. List all students -> By student number" << std::endl;
    std::cout << "3. List students in a class of a certain UC -> Alphabetically" << std::endl;
    std::cout << "4. List students in a class of a certain UC -> By student number" << std::endl;
    std::cout << "5. List students with a student number greater than n -> Ascending order" << std::endl;
    std::cout << "6. List students with a student number greater than n -> Descending order" << std::endl;

    showFooter();

    choice = checkValidInput();

    switch (choice) {
        case 1:
            scheduleManager_->listStudentsAlpha();
            break;
        case 2:
            scheduleManager_->listStudentsNum();
            break;
        case 3:
            scheduleManager_->listStudentsOfClassAlpha();
            break;
        case 4:
            scheduleManager_->listStudentsOfClassNum();
            break;
        case 5:
            scheduleManager_->listStudentsGreaterThan(true);
            break;
        case 6:
            scheduleManager_->listStudentsGreaterThan(false);
            break;
        case 9:
            state_ = State::InfoMenu;
            break;
        case 0:
            state_ = State::MainMenu;
            break;
        default:
            break;
    }
}

void Menu::showClassMenu() {
    showHeader();

    int choice;

    std::cout << "----- Classes Menu -----" << std::endl;
    std::cout << "1. List the number of students per class" << std::endl;
    std::cout << "2. List the number of students per class -> Ascending order" << std::endl;
    std::cout << "3. List the number of students per class -> Descending order" << std::endl;

    showFooter();

    choice = checkValidInput();

    switch (choice) {
        case 1:
            scheduleManager_->listClassNumOfStudents();
            break;
        case 2:
                scheduleManager_->listClassNumOfStudents(true);
                break;
        case 3:
                scheduleManager_->listClassNumOfStudents(false);
                break;
        case 9:
            state_ = State::InfoMenu;
            break;
        case 0:
            state_ = State::MainMenu;
            break;
        default:
            break;
    }
}

void Menu::showCourseUnitMenu() {
    showHeader();

    int choice;

    std::cout << "----- Course Units Menu -----" << std::endl;
    std::cout << "1. List the number of students per Course Unit" << std::endl;
    std::cout << "2. List the number of students per Course Unit -> Ascending order" << std::endl;
    std::cout << "3. List the number of students per Course Unit -> Descending order" << std::endl;

    showFooter();

    choice = checkValidInput();

    switch (choice) {
        case 1:
            scheduleManager_->listCourseUnitNumOfStudents();
            break;
        case 2:
            scheduleManager_->listCourseUnitNumOfStudents(true);
            break;
        case 3:
            scheduleManager_->listCourseUnitNumOfStudents(false);
            break;
        case 9:
            state_ = State::InfoMenu;
            break;
        case 0:
            state_ = State::MainMenu;
            break;
        default:
            break;
    }
}

void Menu::showScheduleMenu() {
    showHeader();

    int choice;

    std::cout << "----- Schedules Menu -----" << std::endl;
    std::cout << "1. Check a student's schedule" << std::endl;
    std::cout << "2. Check a class' schedule" << std::endl;

    showFooter();

    choice = checkValidInput();

    switch (choice) {
        case 1:
            scheduleManager_->listStudentSchedule();
            break;
        case 2:
            scheduleManager_->listClassSchedule();
            break;
        case 9:
            state_ = State::InfoMenu;
            break;
        case 0:
            state_ = State::MainMenu;
            break;
        default:
            break;
    }
}
