#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H

#include <limits>
#include <utility>
#include "studentbst.h"
#include "request.h"
#include "courseunit.h"

class ScheduleManager {
public:
    ScheduleManager();
    ScheduleManager(StudentBST students, std::vector<Class*> schedules, std::vector<CourseUnit*> courseUnits, std::queue<Request> requests);

    StudentBST getStudents() const{return students_;}
    std::vector<Class*> getShedules() const{return schedules_;}
    std::vector<CourseUnit*> getCourseUnits() const{return courseUnits_;}
    std::queue<Request> getRequest() const {return requests_;}
    std::queue<Request> getInvalidRequests() const {return invalidRequests_;}

    /**
     * A method that finds a given student in the BST of students and returns it.\n
     * Time Complexity: O(n).
     * @param student A reference to a student.
     * @return The student that was found in the BST.
     */
    Student getStudent(const Student& student);

    /**
     * A method that finds a certain Course Unit in the vector of course units and returns a pointer to that Course Unit.\n
     * Time Complexity: O(n).
     * @param code A string corresponding to the code of a Course Unit.
     * @return A pointer to a Course Unit.
     */
    CourseUnit* getCourseUnit(const std::string& code);

    /**
     * A method that finds a certain Class of a certain Course Unit in the vector of course units and returns a pointer to that Class.\n
     * Time Complexity: O(n).
     * @param code A string corresponding to the code a Class.
     * @param courseUnitCode A string corresponding to the code a Course Unit.
     * @return A pointer to a Class.
     */
    Class* getClass(const std::string& code, const std::string& courseUnitCode);

    void setClassCap(int cap) {CLASS_CAP = cap;}
    int getClassCap() const {return CLASS_CAP;}

    void addStudent(const Student& student) {students_.insert(student);}
    void addSchedule(Class* classes) {schedules_.push_back(classes);};
    void addRequest(Request request) {requests_.push(request);};
    void addInvalidRequest(Request request) {invalidRequests_.push(request);};
    void addCourseUnit(CourseUnit* courseUnit) {courseUnits_.push_back(courseUnit);};

    /**
     * A method responsible for handling the requests in the queue of requests.\n
     * Time Complexity: O(n).
     */
    void handleRequests();

    /**
     * Removes a student from the BST of students, given a reference to that Student.\n
     * Time Complexity: O(n).
     * @param student A student.
     */
    void removeStudent(const Student& student) {students_.remove(student);}

    /**
     * Removes a student from the BST of students, given that student's number.\n
     * Time Complexity: O(n).
     * @param student A student.
     */
    void removeStudent(const int code) {students_.remove(Student(code, ""));}

    /**
     * Removes a next invalid request from the invalid requests queue.
     */
    void popInvalidRequest() {invalidRequests_.pop();}

    /**
     * Creates a new Class and returns a pointer to that Class.\n
     * Time Complexity: O(n).
     * @param classCode A string corresponding to a class' code.
     * @param courseUnitCode A string corresponding to a course unit's code.
     * @return A pointer to a Class.
     */
    Class* createClass(std::string classCode, std::string courseUnitCode);

    /**
    * Creates a new Lecture and returns a pointer to that Lecture.\n
    * Time Complexity: O(n).
    * @param weekday A string corresponding to the weekday that lecture is schedule to.
    * @param startTime A float corresponding to the start time of that lecture.
    * @param durationTime A float corresponding to the duration of that lecture.
    * @param type A string corresponding to the type of that lecture.
    * @return A pointer to a Lecture.
    */
    Lecture* createLecture(std::string weekday, float startTime, float durationTime, std::string type);

    /**
   * Creates a new Course Unit and returns a pointer to that Course Unit.\n
   * Time Complexity: O(n).
   * @param courseUnitCode A string corresponding to a course unit's code.
   * @return A pointer to a Course Unit.
   */
    CourseUnit* createCourseUnit(std::string courseUnitCode);

    /**
     * Lists the students in the BST of students alphabetically.\n
     * Time Complexity: O(n).
     */
    void listStudentsAlpha() const;

    /**
    * Lists the students in the BST of students by their student number.\n
    * Time Complexity: O(n).
    */
    void listStudentsNum() const;

    /**
    * Lists the students of a given class alphabetically.\n
    * Time Complexity: O(N*M), where N stands for the number of students and M stands for the number of classes of the student.
    */
    void listStudentsOfClassAlpha();

    /**
    * Lists the students of a given class by their student number.\n
    * Time Complexity: O(N*M), where N stands for the number of students and M stands for the number of classes of the student.
    */
    void listStudentsOfClassNum();

    /*
     * Lists the schedule of a given student.\n
     * Time Complexity: O(n²).
     */
    void listStudentSchedule();

    /**
     * Lists the schedule of a given class.\n
     * Time Complexity: O(n).
     */
    void listClassSchedule();

    /**
     * Lists the students in the BST of students whose number is bigger than a given one.\n
     * Time Complexity: O(n).
     * @param ascending A boolean that defines if the listing is done in ascending or descending order.
     */
    void listStudentsGreaterThan(bool ascending) const;

    /**
     * Lists the classes and their number of students.\n
     * Time Complexity: O(nlog(n)).
     */
    void listClassNumOfStudents();

    /**
    * Lists the classes and their number of students by the number of students.\n
    * Time Complexity: O(nlog(n)).
    * @param ascending A boolean that defines if the listing is done in ascending or descending order.
    */
    void listClassNumOfStudents(bool ascending);

    /**
    * Lists the course units and their number of students.\n
    * Time Complexity: O(nlog(n)) or O(N*M),where N stands for the number of course units and M stands for the number of classes of the course unit.
    */
    void listCourseUnitNumOfStudents();

    /**
    * Lists the course units and their number of students by the number of students.\n
    * Time Complexity: O(nlog(n)) or O(N*M),where N stands for the number of course units and M stands for the number of classes of the course unit.
    * @param ascending A boolean that defines if the listing is done in ascending or descending order.
    */
    void listCourseUnitNumOfStudents(bool ascending);

private:
    StudentBST students_;
    std::vector<Class*> schedules_;
    std::vector<CourseUnit*> courseUnits_;
    std::queue<Request> requests_;
    std::queue<Request> invalidRequests_ = std::queue<Request>();

    int CLASS_CAP = 26;

    /**
     * A method that asks the user for the class information.\n
     * Time Complexity: O(1).
     * @param courseUnitCode A string corresponding to a Course Unit's code.
     * @param classCode A string corresponding to a Class' code.
     */
    static void askClassInfo(std::string& courseUnitCode, std::string& classCode);

    /**
     * Checks if the user input is a number of type integer.
     * @return An integer corresponding to the user's choice.
     */
    static void checkValidInput(int &code);

    /**
     * Conducts a binary search through the given vector and compares its elements with the integer key, returning the index of the first element that is bigger than the key or equal to it.\n
     * Time Complexity: O(log(n)).
     * @param v A vector of pairs of pointers to course units and integers.
     * @param key An integer corresponding to the key to which the vector's elements are compared to.
     * @return An integer corresponding to the index of the first element that is bigger than the given key or equal to it. Returns -1 if all elements are smaller than the key.
     */
    static int lowerBound(std::vector<pair<CourseUnit*, int>> v, int key);

    bool checkValidClasses(const Student& student);
};

#endif
