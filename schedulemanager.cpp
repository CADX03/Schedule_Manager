#include "schedulemanager.h"
#include <utility>

ScheduleManager::ScheduleManager() {
    students_ = StudentBST();
    schedules_ = std::vector<Class*>();
    courseUnits_ = std::vector<CourseUnit*>();
    requests_ = std::queue <Request>();
}

ScheduleManager::ScheduleManager(StudentBST students, std::vector<Class*> schedules, std::vector<CourseUnit*> courseUnits, std::queue<Request> requests){
    students_ = std::move(students);
    schedules_ = std::move(schedules);
    requests_ = std::move(requests);
    courseUnits_ = std::move(courseUnits);
}

Class *ScheduleManager::createClass(std::string classCode, std::string courseUnitCode) {
    Class* newClass = new Class(std::move(classCode), std::move(courseUnitCode), std::vector<Lecture*>());
    return newClass;
}

Lecture *ScheduleManager::createLecture(std::string weekday, float startTime, float durationTime, std::string type) {
    Lecture* lecture = new Lecture(std::move(weekday), startTime, durationTime, std::move(type));
    return lecture;

}

CourseUnit *ScheduleManager::createCourseUnit(std::string courseUnitCode) {
    CourseUnit* courseUnit = new CourseUnit(std::move(courseUnitCode));
    return courseUnit;
}

Student ScheduleManager::getStudent(const Student &student) {
    auto result = students_.find(student);
    return result;
}

CourseUnit *ScheduleManager::getCourseUnit(const string &code) {
    for(CourseUnit* courseUnit : courseUnits_)
        if(courseUnit->getCode() == code)
            return courseUnit;
    return nullptr;
}

Class *ScheduleManager::getClass(const string &code, const string &courseUnitCode) {
    for(CourseUnit* courseUnit : courseUnits_)
        if(courseUnit->getCode() == courseUnitCode)
            return courseUnit->getClass(code);
    return nullptr;
}

void ScheduleManager::listStudentsAlpha() const {
    std::cout << "Student Number" << ' ' << "Student Name" << std::endl;
    for(auto & it : getStudents().getList())
    {
        it.show();
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void ScheduleManager::listStudentsNum() const {
    std::cout << "Student Number" << ' ' << "Student Name" << std::endl;
    students_.printTree();
    std::cout << std::endl;
}

void ScheduleManager::listStudentsOfClassAlpha() {
    std::string courseUnitCode;
    std::string classCode;
    askClassInfo(courseUnitCode, classCode);

    Class* classPtr = getClass(classCode, courseUnitCode);
    if(classPtr != nullptr){
        std::cout << "Course Unit" << ' ' << "Class Code" << ' ' << "Student Number" << ' ' << "Student Name" << std::endl;
        for(auto & it : getStudents().getList()) {
            for (auto &classIt: it.getClasses()) {
                if (classIt->getCode() == classCode && classIt->getCourseUnitCodeCode() == courseUnitCode) {
                    classIt->show();
                    std::cout << "    ";
                    it.show();
                    std::cout << std::endl;
                }
            }
        }
    }
    else
        std::cout << "ERROR: Class '" << classCode << "' not found for Course Unit '" << courseUnitCode << "'." << std::endl;
    std::cout << std::endl;
}

void ScheduleManager::listStudentsOfClassNum() {
    std::string courseUnitCode;
    std::string classCode;
    askClassInfo(courseUnitCode, classCode);

    Class* classPtr = getClass(classCode, courseUnitCode);
    if(classPtr != nullptr){
        std::cout << "Course Unit" << ' ' << "Class Code" << ' ' << "Student Number" << ' ' << "Student Name" << std::endl;

        BST<Student> students = getStudents().getBST();
        BSTItrIn<Student> itrIn = BSTItrIn<Student>(students);

        while (!itrIn.isAtEnd()) {
            const Student& student = itrIn.retrieve();
            for(Class* classes : student.getClasses()){
                if(classes->getCourseUnitCodeCode() == courseUnitCode && classes->getCode() == classCode){
                    classes->show();
                    std::cout << "    ";
                    student.show();
                    std::cout << std::endl;
                    break;
                }
            }
            itrIn.advance();
        }
    }
    else
        std::cout << "ERROR: Class '" << classCode << "' not found for Course Unit '" << courseUnitCode << "'." << std::endl;
    std::cout << std::endl;
}

void ScheduleManager::listStudentsGreaterThan(bool ascending) const {
    int code;
    checkValidInput(code);
    std::cout << "Student Number" << ' ' << "Student Name" << std::endl;
    BST<Student> students = getStudents().getBST();

    if(ascending){
        BSTItrIn<Student> itrIn = BSTItrIn<Student>(students);

        while (!itrIn.isAtEnd()) {
            const Student& student = itrIn.retrieve();
            if(student.getCode() > code){
                student.show();
                std::cout << std::endl;
            }
            itrIn.advance();
        }
    }

    else{
        BSTItrInReverse<Student> itrInReverse = BSTItrInReverse<Student>(students);

        while (!itrInReverse.isAtEnd()) {
            const Student& student = itrInReverse.retrieve();
            if(student.getCode() > code){
                student.show();
                std::cout << std::endl;
            }
            itrInReverse.advance();
        }
    }

    std::cout << std::endl;
}

void ScheduleManager::listStudentSchedule() {

    int code;
    checkValidInput(code);
    Student student = students_.find(Student(code,""));
    if (student.getCode() == -1) std::cout << "ERROR: No student was found for the number '" << code << "'." << std::endl;
    else {
        std::vector<Lecture *> lectures = std::vector<Lecture *>();
        for (Class *classes: student.getClasses())
            for (Lecture *lecture: classes->getLectures())
                lectures.push_back(lecture);
        sort(lectures.begin(), lectures.end(), Lecture::compareLecture);
        std::cout << "Course Unit" << ' ' << "Class Code" << "  " << "Weekday" << "  \t" << "Start Time" << "\t" << "Duration" << '\t' << "Type" << std::endl;
        for (Lecture *lecture: lectures)
            for(Class* classes : student.getClasses())
                for(Lecture* lecture1 : classes->getLectures())
                    if(lecture == lecture1){
                        classes->show();
                        std::cout << "  \t";
                        lecture->show();
                        std::cout << std::endl;
                    }
    }
    std::cout << std::endl;
}

void ScheduleManager::listClassSchedule() {
    std::string courseUnitCode;
    std::string classCode;
    askClassInfo(courseUnitCode, classCode);

    Class* classPtr = getClass(classCode, courseUnitCode);
    if(classPtr != nullptr){
        std::cout << "Course Unit" << ' ' << "Class Code" << "  " << "Weekday" << "  \t" << "Start Time" << "\t" << "Duration" << '\t' << "Type" << std::endl;
        for(auto it : classPtr->getLectures()){
            classPtr->show();
            std::cout << "     ";
            it->show();
            std::cout << std::endl;
        }
    }
    else{
        std::cout << "ERROR: Class '" << classCode << "' not found for Course Unit '" << courseUnitCode << "'." << std::endl;
    }

    std::cout << std::endl;
}

void ScheduleManager::listClassNumOfStudents() {
    if(schedules_.empty()) return;
    vector<Class*> classes = schedules_;
    sort(classes.begin(),classes.end(),  [](Class* a, Class* b) {
        return (a->getCourseUnitCodeCode() < b->getCourseUnitCodeCode()||(a->getCourseUnitCodeCode() == b->getCourseUnitCodeCode() && a->getCode() < b->getCode()));
        }
    );
    std::cout << "Course Unit" << ' ' << "Class" << "   " << "Number of Students" << std::endl;
    for(Class* aux : classes){
        aux->show();
        std::cout << ' ';
        std::cout << aux->getStudentsEnrolled();
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void ScheduleManager::listClassNumOfStudents(bool ascending) {
    if(schedules_.empty()) return;
    vector<Class*> classes = schedules_;
    if(ascending){
        sort(classes.begin(),classes.end(),  [](Class* a, Class* b) {
                 return (a->getStudentsEnrolled() < b->getStudentsEnrolled() ||
                 (a->getStudentsEnrolled() == b->getStudentsEnrolled() && (a->getCourseUnitCodeCode() < b->getCourseUnitCodeCode()||(a->getCourseUnitCodeCode() == b->getCourseUnitCodeCode() && a->getCode() < b->getCode())))
                 );
             }
        );
    }
    else{
        sort(classes.begin(),classes.end(),  [](Class* a, Class* b) {
            return (a->getStudentsEnrolled() > b->getStudentsEnrolled() ||
                    (a->getStudentsEnrolled() == b->getStudentsEnrolled() && (a->getCourseUnitCodeCode() < b->getCourseUnitCodeCode()||(a->getCourseUnitCodeCode() == b->getCourseUnitCodeCode() && a->getCode() < b->getCode())))
            );
             }
        );
    }

    std::cout << "Course Unit" << ' ' << "Class" << "   " << "Number of Students" << std::endl;
    for(Class* aux : classes){
        aux->show();
        std::cout << ' ';
        std::cout << aux->getStudentsEnrolled();
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void ScheduleManager::listCourseUnitNumOfStudents() {
    if(courseUnits_.empty()) return;
    vector<CourseUnit*> courseUnit = courseUnits_;
    sort(courseUnit.begin(),courseUnit.end(),  [](CourseUnit* a, CourseUnit* b) {
             return (a->getCode() < b->getCode());
         }
    );
    std::cout << "Course Unit" << ' ' << "Number of Students" << std::endl;
    for(CourseUnit* aux : courseUnit){
        int studentsEnrolled = 0;
        for(Class* classes : aux->getClasses()) studentsEnrolled += classes->getStudentsEnrolled();
        aux->show();
        std::cout << "    ";
        std::cout << studentsEnrolled;
        std::cout << std::endl;
    }
    std::cout << std::endl;

}

void ScheduleManager::listCourseUnitNumOfStudents(bool ascending) {
    if(courseUnits_.empty()) return;
    vector<pair<CourseUnit*, int>> courseUnit;
    for(CourseUnit* courseUnit1 : courseUnits_){
        int studentsEnrolled = 0;
        for(Class* classes : courseUnit1->getClasses())
            studentsEnrolled += classes->getStudentsEnrolled();
        pair<CourseUnit*, int> entry(courseUnit1, studentsEnrolled);
        int index = lowerBound(courseUnit, studentsEnrolled);
        if(index == -1) courseUnit.push_back(entry);
        else courseUnit.insert(courseUnit.begin()+index, entry);
    }

    std::cout << "Course Unit" << ' ' << "Number of Students" << std::endl;
    if(ascending) {
        for (pair<CourseUnit *, int> aux: courseUnit) {
            aux.first->show();
            std::cout << "    ";
            std::cout << aux.second;
            std::cout << std::endl;
        }

    }
    else{
        for (auto it = courseUnit.rbegin(); it != courseUnit.rend(); it++) {
            pair<CourseUnit *, int> aux = *it;
            aux.first->show();
            std::cout << "    ";
            std::cout << aux.second;
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

void ScheduleManager::askClassInfo(string &courseUnitCode, string &classCode) {
    std::cout << "Enter a Course Unit: ";
    std::cin >> courseUnitCode;
    std::cout << "Enter a Class of the Course Unit: ";
    std::cin >> classCode;
    std::cout << std::endl;
}

void ScheduleManager::checkValidInput(int &code)  {
    std::cout << "Enter a student number: ";
    std::cin >> code;
    while(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "WARNING: Invalid input.  Please, enter a number: ";
        std::cin >> code;
    }
    std::cout << std::endl;
}

int ScheduleManager::lowerBound(std::vector<pair<CourseUnit *, int>> v, int key) {
    if (v.empty()) return -1;
    int low = 0, high = (int)v.size()-1;
    while(low<high){
        int middle = low +(high-low) / 2;
        if(v[middle].second  >= key) high = middle;
        else low = middle+1;
    }
    if (v[low].second < key) return -1;
    return low;
}

void ScheduleManager::handleRequests() {
    if(requests_.empty()) return;
    while(!requests_.empty()){
        Request currentRequest = requests_.front();
        switch (currentRequest.getTask()) {
            case Request::Task::AddStudent:
            {
                Student student = students_.getBST().find(currentRequest.getStudent());
                if(student.getCode() != -1) addInvalidRequest(currentRequest);
                else
                {
                    if(checkValidClasses(currentRequest.getStudent())) {
                        Student realStudent = Student(currentRequest.getStudent().getCode(), currentRequest.getStudent().getName());
                        for (Class *classes: currentRequest.getStudent().getClasses())
                            realStudent.addClass(classes);
                        addStudent(realStudent);
                    }
                    else addInvalidRequest(currentRequest);
                }
                break;
            }

            case Request::Task::RemoveStudent:
            {
                Student student = students_.getBST().find(currentRequest.getStudent());
                if(student.getCode() == -1) addInvalidRequest(currentRequest);
                else
                {
                    for(Class* classes : student.getClasses())
                        student.removeClass(classes);
                    removeStudent(student);
                }
                break;
            }
            case Request::Task::AddStudentToClass: {
                if (currentRequest.getStudent().getClasses().front() == nullptr) addInvalidRequest(currentRequest);
                else {
                    Student student = students_.getBST().find(currentRequest.getStudent());
                    if (student.getCode() == -1) addInvalidRequest(currentRequest);
                    else {
                        student.addClass(currentRequest.getStudent().getClasses().front());
                        if (checkValidClasses(student)) {
                            students_.remove(student);
                            addStudent(student);
                        }
                        else {
                            addInvalidRequest(currentRequest);
                            student.removeClass(currentRequest.getStudent().getClasses().front());
                        }

                    }
                }
                break;
            }
            case Request::Task::RemoveStudentFromClass:
            {
                Student student = students_.getBST().find(currentRequest.getStudent());
                if(student.getCode() == -1) addInvalidRequest(currentRequest);
                else{
                    bool successRemoval = false;
                    for(Class* classes : student.getClasses())
                        if(currentRequest.getStudent().getClasses().at(0) != nullptr && currentRequest.getStudent().getClasses().at(0)->getCourseUnitCodeCode() == classes->getCourseUnitCodeCode()){
                            student.removeClass(classes);
                            successRemoval = true;
                            break;
                        }
                    if(successRemoval){
                    students_.remove(student);
                    students_.insert(student);
                    }
                    else addInvalidRequest(currentRequest);
                }
                break;
            }
            case Request::Task::ManageStudentClasses:
            {
                bool requestIsValid = true;
                if(!currentRequest.getStudent().checkValidCourseUnit()) requestIsValid = false;
                else{
                    Student student = students_.getBST().find(currentRequest.getStudent());
                    if(student.getCode() == -1) requestIsValid = false;
                    else{
                        vector<Class*> originalClasses = student.getClasses();
                        for(Class* classes : currentRequest.getStudent().getClasses()){
                            bool found = false;
                            for(Class* classesAux : student.getClasses()){
                                if(classesAux->getCourseUnitCodeCode() == classes->getCourseUnitCodeCode()) {
                                    student.removeClass(classesAux);
                                    student.addClass(classes);
                                    found = true;
                                    break;
                                }
                            }
                            if(!found) {
                                requestIsValid = false;
                                break;
                            }
                        }
                        if(requestIsValid && checkValidClasses(student)) {
                            students_.remove(student);
                            students_.insert(student);
                        }
                        else
                        {
                            for(Class* classes : student.getClasses()) student.removeClass(classes);
                            for(Class* classes : originalClasses) student.addClass(classes);
                        }
                    }
                }
                if(!requestIsValid) addInvalidRequest(currentRequest);
            break;
            }
        }
        requests_.pop();
    }
}

bool ScheduleManager::checkValidClasses(const Student &student) {
    for (Class *classes: student.getClasses())
        if (classes == nullptr || CLASS_CAP <= classes->getStudentsEnrolled() || !getCourseUnit(classes->getCourseUnitCodeCode())->checkBalance())
           return false;
    if(!student.checkValidClasses()) return false;
    return true;
}
