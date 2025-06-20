#ifndef CLASSESFILEMANAGER_H
#define CLASSESFILEMANAGER_H


#include "schedulemanager.h"
#include <fstream>
#include <sstream>

class ClassesFileManager {
public:
    ClassesFileManager();

    /**
     * A method that loads and reads a file and stores the information about classes and their lectures in the respective data structures of a Schedule Manager.\n
     * Time Complexity: O(n).
     * @param file A string corresponding to the file's path in the system.
     * @param scheduleManager A reference to a Schedule Manager.
     */
    void load(const std::string& file, ScheduleManager& scheduleManager);

    /**
     * A method that gets information about classes and their lectures from the respective data structures of a Schedule Manager and saves it in a file.\n
     * Time Complexity: O(N*M), where N stands for the number of classes and M stands for the number of lectures of the class.
     * @param File A string corresponding to the file's path in the system.
     * @param scheduleManager A reference to a Schedule Manager.
     */
    void save(const std::string& file, ScheduleManager& scheduleManager);

    /**
     * A method that gets information about all the classes for each Course Unit from the respective data structures of a Schedule Manager and saves it to a file.\n
     * Time Complexity: O(N*M), where N stands for the number of course units and M stands for the number of classes of the course unit.
     * @param File A string corresponding to the file's path in the system.
     * @param scheduleManager A reference to a Schedule Manager.
     */
    void saveClassesPerCourseUnit(const std::string& file, ScheduleManager& scheduleManager);
};


#endif
