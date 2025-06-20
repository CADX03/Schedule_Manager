#include "requestsfilemanager.h"

RequestsFileManager::RequestsFileManager() {;}

void RequestsFileManager::save(const string &file, ScheduleManager &scheduleManager) {
    std::ofstream ofs("../schedule/"+file);

    ofs << "##### ALL INVALID REQUESTS ARE STORED IN THIS FILE #####" << '\n';
    if (scheduleManager.getInvalidRequests().empty()){
        ofs.close();
        return;
    }
    else {
        while (!scheduleManager.getInvalidRequests().empty()) {
            Request request = scheduleManager.getInvalidRequests().front();
            switch (request.getTask()) {
                case Request::Task::AddStudent:
                {
                    ofs << "Failed to add student" << ' ';
                    ofs << request.getStudent() << ' ';
                    if(!request.getStudent().getClasses().empty()){
                        for(Class* classes : request.getStudent().getClasses()){
                            if(classes == nullptr){
                                ofs << "[ ] ";
                                break;
                            }
                            ofs << '[' << *classes << ']' << ' ';
                        }
                    }
                    ofs << '\n';
                    break;
                }
                case Request::Task::RemoveStudent:
                {
                    ofs << "Failed to remove student" << ' ';
                    ofs << request.getStudent().getCode() << ' ';
                    ofs << '\n';
                    break;
                }
                case Request::Task::AddStudentToClass:
                {
                    ofs << "Failed to add student" << ' ';
                    ofs << request.getStudent().getCode() << ' ';
                    ofs << "to class" << ' ';
                    if(!request.getStudent().getClasses().empty()){
                        for(Class* classes : request.getStudent().getClasses()){
                            if(classes == nullptr){
                                ofs << "[ ] ";
                                break;
                            }
                            ofs << '[' << *classes << ']' << ' ';
                        }
                    }
                    ofs << '\n';
                    break;
                }
                case Request::Task::RemoveStudentFromClass:
                {
                    ofs << "Failed to remove student" << ' ';
                    ofs << request.getStudent().getCode() << ' ';
                    ofs << "from class.";
                    ofs << '\n';
                    break;
                }
                case Request::Task::ManageStudentClasses:
                {
                    ofs << "Failed to manage student's classes" << ' ';
                    ofs << request.getStudent().getCode() << ' ';
                    if(!request.getStudent().getClasses().empty()){
                        for(Class* classes : request.getStudent().getClasses()){
                            if(classes == nullptr){
                                ofs << "[ ] ";
                                break;
                            }
                            ofs << '[' << *classes << ']' << ' ';
                        }
                    }
                    ofs << '\n';
                    break;
                }

            }


            scheduleManager.popInvalidRequest();

        }
    }
    ofs.close();
}
