#include "courseunit.h"

CourseUnit::CourseUnit(std::string code) { code_ = code; classes_ = std::vector<Class*>(); }
CourseUnit::CourseUnit(std::string code, std::vector<Class*> classes) { code_ = code; classes_ = classes; }
CourseUnit::CourseUnit(const CourseUnit& courseUnit) { code_ = courseUnit.getCode(); classes_ = courseUnit.getClasses(); }

void CourseUnit::show() const { std::cout << code_; }

bool CourseUnit::checkBalance() {
    int maxStudents = 0;
    int minStudents = INT_MAX;
    for(Class* classes: classes_){
        if(classes->getStudentsEnrolled() > maxStudents) maxStudents = classes->getStudentsEnrolled();
        if(classes->getStudentsEnrolled() < minStudents) minStudents = classes->getStudentsEnrolled();
    }

    return abs(maxStudents-minStudents) <= 4;
}
