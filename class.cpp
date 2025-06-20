#include "class.h"

Class::Class(std::string code, std::string courseUnitCode, std::vector<Lecture*> lectures) {
    studentsEnrolled_ = 0;
    code_ = code;
    courseUnitCode_ = courseUnitCode;
    lectures_ = lectures;
}

Class::Class(const Class& newClass) {
    studentsEnrolled_ = newClass.getStudentsEnrolled();
    code_ = newClass.getCode();
    courseUnitCode_ = newClass.getCourseUnitCodeCode();
    lectures_ = newClass.getLectures();
}

void Class::show() const {
    std::cout << courseUnitCode_ << "    " << code_;
}

bool Class::compareCourseUnit(Class *a, Class *b) {
    if(a != nullptr && b != nullptr) return false;
    return a->getCourseUnitCodeCode() < b->getCourseUnitCodeCode();
}

std::ostream &operator<<(std::ostream &out, const Class &classes) {
    out << classes.getCode()  << ' ' << ',' << ' ' << classes.getCourseUnitCodeCode();
    return out;
}
