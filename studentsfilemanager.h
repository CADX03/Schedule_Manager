#ifndef STUDENTSFILEMANAGER_H
#define STUDENTSFILEMANAGER_H


#include <fstream>
#include <sstream>
#include "schedulemanager.h"

class StudentsFileManager {
public:
    StudentsFileManager();

    /**
    * A method that loads and reads a file and stores the information about the students in the respective data structures of a Schedule Manager.\n
    * Time Complexity: O(n).
    * @param file A string corresponding to the file's path in the system.
    * @param scheduleManager A reference to a Schedule Manager.
    */
    void load(const std::string& file, ScheduleManager& scheduleManager);

    /**
     * A method that gets information about the students from the respective data structures of a Schedule Manager and saves it in a file.\n
     * Time Complexity: O(N*M), where N stands for the number of students and M stands for the number of classes of the student.
     * @param File A string corresponding to the file's path in the system.
     * @param scheduleManager A reference to a Schedule Manager.
     */
    void save(const std::string& file, ScheduleManager& scheduleManager);
};


#endif
