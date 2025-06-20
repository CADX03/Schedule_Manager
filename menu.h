#ifndef MENU_H
#define MENU_H

#include "classesfilemanager.h"
#include "studentsfilemanager.h"
#include "requestsfilemanager.h"

class Menu {
public:
    Menu(ScheduleManager* scheduleManager, ClassesFileManager* classesFileManager, StudentsFileManager* studentsFileManager, RequestsFileManager* requestsFileManager);

    /**
     * A start method responsible for setting up the Menu.
     */
    void start();

private:
    ScheduleManager* scheduleManager_;
    ClassesFileManager* classesFileManager_;
    StudentsFileManager* studentsFileManager_;
    RequestsFileManager* requestsFileManager_;

    /**
     * An enum.\n
     * Each State represents a different menu of the global Menu.
     */
    enum State {LoadMenu, MainMenu, InfoMenu, RequestMenu, StudentMenu, ClassMenu, CourseUnitMenu, ScheduleMenu, Exit};
    State state_;

    /**
     * Checks if the user input is a number of type integer.
     * @return An integer corresponding to the user's choice.
     */
    static int checkValidInput();

    /**
     * Checks if the user input is a number of type integer with 9 digits.
     * @return An integer corresponding to the student's number.
     */
    static int checkStudentNumber();

    /**
     * A method responsible for handling the different states of the Menu.
     */
    void handleState();

    /**
     * Prints the header of the Menu.\n
     * Time Complexity: O(1).
     */
    void showHeader() const;

    /**
     * Prints the footer of the Menu.\n
     * Time Complexity: O(1).
     */
    void showFooter() const;

    /**
     * Prints all the different options in the Load Menu and manages the user inputs.
     */
    void showLoadMenu();

    /**
     * Prints all the different options in the Main Menu and manages the user inputs.
     */
    void showMainMenu();

    /**
     * Prints all the different options in the Information Menu and manages the user inputs.
     */
    void showInfoMenu();

    /**
     * Prints all the different options in the Requests Menu and manages the user inputs.
     */
    void showRequestMenu();

    /**
     * Prints all the different options in the Students Menu and manages the user inputs.
     */
    void showStudentMenu();

    /**
     * Prints all the different options in the Classes Menu and manages the user inputs.
     */
    void showClassMenu();

    /**
     * Prints all the different options in the Course Units Menu and manages the user inputs.
     */
    void showCourseUnitMenu();

    /**
     * Prints all the different options in the Schedules Menu and manages the user inputs.
     */
    void showScheduleMenu();
};


#endif
