#include "studentsfilemanager.h"

StudentsFileManager::StudentsFileManager(){;}


void StudentsFileManager::load(const std::string &file, ScheduleManager& scheduleManager) {
    std::ifstream ifs("../schedule/"+file);

    std::string header;
    std::getline(ifs, header);

    for(std::string line; std::getline(ifs, line);) {

        std::istringstream iss(line);

        int code;
        std::string name;
        std::string ucCode;
        std::string classCode;

        iss >> code;
        iss.ignore();
        std::getline(iss, name, ',');
        std::getline(iss, ucCode, ',');
        std::getline(iss, classCode, ',');

        if (!classCode.empty() && classCode[classCode.size() - 1] == '\r')
            classCode.erase(classCode.size() - 1);

        Student student = Student(code,name);

        if(!(student == scheduleManager.getStudent(student))) {
            student.addClass(scheduleManager.getClass(classCode, ucCode));
        }
        else {
            student = Student(scheduleManager.getStudent(student));
            student.addClass(scheduleManager.getClass(classCode, ucCode));
        }
        scheduleManager.removeStudent(student);
        scheduleManager.addStudent(student);
    }
}

void StudentsFileManager::save(const string &file, ScheduleManager &scheduleManager) {
    std::ofstream ofs("../schedule/"+file);

    ofs << "StudentCode" << ',' << "StudentName" << ',' << "UcCode" << ',' << "ClassCode" << '\n';

    BST<Student> students = scheduleManager.getStudents().getBST();
    BSTItrLevel<Student> itrLevel = BSTItrLevel<Student>(students);

    while (!itrLevel.isAtEnd()) {
        Student student = itrLevel.retrieve();
        for (Class* classes : student.getClasses()){
            ofs << student.getCode() << ',';
            ofs << student.getName() << ',';
            ofs << classes->getCourseUnitCodeCode() << ',';
            ofs << classes->getCode() << '\n';
        }
        itrLevel.advance();
    }
    ofs.close();
}
