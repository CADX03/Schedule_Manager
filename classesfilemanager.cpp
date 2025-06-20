#include "classesfilemanager.h"

ClassesFileManager::ClassesFileManager(){;}

void ClassesFileManager::load(const std::string& file, ScheduleManager& scheduleManager){
    std::ifstream ifs("../schedule/"+file);

    std::string header;
    std::getline(ifs, header);

    for(std::string line; std::getline(ifs, line);){
        std::istringstream iss(line);

        std::string classCode;
        std::string courseUnitCode;
        std::string weekday;
        float startTime;
        float durationTime;
        std::string type;

        std::getline(iss, classCode, ',');
        std::getline(iss, courseUnitCode, ',');
        std::getline(iss, weekday, ',');
        iss >> startTime;
        iss.ignore();
        iss >> durationTime;
        iss.ignore();
        std::getline(iss, type, ',');

        if (!type.empty() && type[type.size() - 1] == '\r')
            type.erase(type.size() - 1);

        Lecture* lecturePtr = scheduleManager.createLecture(weekday,startTime,durationTime,type);
        Class* classesPtr = scheduleManager.getClass(classCode, courseUnitCode);
        if(classesPtr == nullptr){
            classesPtr = scheduleManager.createClass(classCode, courseUnitCode);
            classesPtr->addLecture(lecturePtr);
            scheduleManager.addSchedule(classesPtr);
        }
        else classesPtr->addLecture(lecturePtr);

        CourseUnit* courseUnitPtr = scheduleManager.getCourseUnit(courseUnitCode);
        if(courseUnitPtr == nullptr){
            courseUnitPtr = scheduleManager.createCourseUnit(courseUnitCode);
            courseUnitPtr->addClass(classesPtr);
            scheduleManager.addCourseUnit(courseUnitPtr);
        }
        else if(courseUnitPtr->getClass(classCode) == nullptr) courseUnitPtr->addClass(classesPtr);

    }
    ifs.close();
}


void ClassesFileManager::save(const std::string& file, ScheduleManager& scheduleManager) {
    std::ofstream ofs("../schedule/"+file);

    ofs << "ClassCode" << ',' << "UcCode" << ',' << "Weekday" << ',' << "StartHour" << ',' << "Duration" << ',' << "Type" << '\n';

    for(const Class* classes : scheduleManager.getShedules()){
        for(const Lecture* lecture : classes->getLectures()){
            ofs << classes->getCode() << ',';
            ofs << classes->getCourseUnitCodeCode() << ',';
            ofs << lecture->getWeekday() << ',';
            ofs << lecture->getStartTime() << ',';
            ofs << lecture->getDurationTime() << ',';
            ofs << lecture->getType() << '\n';
        }
    }
    ofs.close();
}


void ClassesFileManager::saveClassesPerCourseUnit(const std::string& file, ScheduleManager& scheduleManager) {
    std::ofstream ofs("../schedule/" + file);

    ofs << "UcCode" << ',' << "ClassCode" << '\n';
    for(const CourseUnit* courseUnit : scheduleManager.getCourseUnits()){
        for(Class *classes: courseUnit->getClasses()){
            ofs << courseUnit->getCode() << ',';
            ofs << classes->getCode() << '\n';
        }
    }
    ofs.close();
}
