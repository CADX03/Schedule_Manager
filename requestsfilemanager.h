#ifndef REQUESTFILEMANAGER_H
#define REQUESTFILEMANAGER_H

#include "schedulemanager.h"
#include <fstream>

class RequestsFileManager {
public:
    RequestsFileManager();

    /**
     * A method that gets information about invalid requests from the respective data structures of a Schedule Manager and saves it in a file.\n
     * Time Complexity: O(N*M), where N stands for the number of requests and M stands for the number of classes per requests.
     * @param File A string corresponding to the file's path in the system.
     * @param scheduleManager A reference to a Schedule Manager.
     */
    void save(const std::string& file, ScheduleManager& scheduleManager);
};


#endif
