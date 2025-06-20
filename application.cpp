#include "menu.h"

/**
    * A run method responsible for setting up the reading of the files and the loading of its information to the respective data structures.
    * It also assures one can save all of the changes made by outputting them to the desired files.
 */
inline void run(){
    ScheduleManager scheduleManager = ScheduleManager();

    ScheduleManager* scheduleManagerPtr = &scheduleManager;

    ClassesFileManager classesFileManager = ClassesFileManager();
    ClassesFileManager* classesFileManagerPtr = &classesFileManager;

    StudentsFileManager studentsFileManager = StudentsFileManager();
    StudentsFileManager* studentsFileManagerPtr = &studentsFileManager;

    RequestsFileManager requestsFileManager = RequestsFileManager();
    RequestsFileManager* requestsFileManagerPtr = &requestsFileManager;

    Menu menu = Menu(scheduleManagerPtr, classesFileManagerPtr, studentsFileManagerPtr, requestsFileManagerPtr);

    menu.start();
}
