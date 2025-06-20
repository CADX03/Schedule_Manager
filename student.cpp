#include "student.h"

Student:: Student(int code, std::string name, std::vector<Class*> classes){
    code_ = code;
    name_ = name;
    classes_ = classes;
}

Student::Student(int code, std::string name) {
    code_ = code;
    name_ = std::move(name);
    classes_ = std::vector<Class*>();
}

Student::Student(const Student& student){
    code_ = student.getCode();
    name_ = student.getName();
    classes_ = student.getClasses();
}

void Student::addClass(Class *classes) {
    classes_.push_back(classes);
    classes->setStudentsEnrolled(classes->getStudentsEnrolled()+1);
}

void Student::removeClass(Class *classes) {
    for(auto it = classes_.begin(); it != classes_.end(); it++) {
        auto aux = *it;
        if (aux->getCode()==classes->getCode() && aux->getCourseUnitCodeCode() == classes->getCourseUnitCodeCode()){
            classes_.erase(it);
            break;
        }
    }
    classes->setStudentsEnrolled(classes->getStudentsEnrolled()-1);
}

bool Student::compareName(const Student &student1, const Student &student2) {
    return student1.getName() < student2.getName();
}

bool Student::operator < (const Student & student) const{
    return code_ < student.code_;
}

bool Student::operator==(const Student &student) const {
    return code_ == student.getCode();
}

std::ostream& operator <<(std::ostream& out,const Student& student){
    out << '[' << student.getCode() << ']' << "    " << student.getName();
    return out;
}

void Student::show() const {
    std::cout << '[' << code_ << ']' << "    " << name_;
}

bool Student::checkValidClasses() const {
    std::vector<Lecture*> lecturesTP;
    if(!checkValidCourseUnit()) return false;
    for(Class* classes : classes_){
        for(Lecture* lecture : classes->getLectures())
            if (lecture->getType() == "TP" || lecture->getType() == "PL" )
                lecturesTP.push_back(lecture);
    }
    std::sort(lecturesTP.begin(),lecturesTP.end(),Lecture::compareLecture);
    for(auto it = lecturesTP.begin(); it != lecturesTP.end()-1; it++) {
        Lecture* lecture = *it;
        Lecture* lectureAux = *(it+1);
        if(lecture->getWeekday() == lectureAux->getWeekday() &&
        lectureAux->getStartTime() >= lecture->getStartTime() &&
        lectureAux->getStartTime() <= lecture->getStartTime()+lecture->getDurationTime())
            return false;
    }
    return true;
}

bool Student::checkValidCourseUnit() const {
    std::vector<Class*> classesAux;
    for(Class* classes : classes_){
        if(classes == nullptr) return false;
        classesAux.push_back(classes);}
    std::sort(classesAux.begin(),classesAux.end(), Class::compareCourseUnit);
    for(auto it = classesAux.begin(); it != classesAux.end()-1; it++) {
        Class* classes = *it;
        Class* classesNext = *(it+1);
        if(classes->getCourseUnitCodeCode() == classesNext->getCourseUnitCodeCode())
            return false;
    }
    return true;
}
