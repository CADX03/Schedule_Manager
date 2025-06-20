#ifndef STUDENT_H
#define STUDENT_H

#include <algorithm>
#include "class.h"


class Student{
public:
    Student(int code, std::string name, std::vector<Class*> classes_);
    Student(int code, std::string name);
    Student(const Student& student);

    void setCode(int code) { code_ = code; }
    int getCode() const { return code_; }

    void setName(std::string name) { name_ = name; }
    std::string getName() const { return name_; }

    std::vector<Class*> getClasses() const { return classes_; }

    /**
     * Adds a pointer to a given class to the vector that stores the pointers to all classes of the Student.\n
     * Time Complexity: O(1).
     * @param classes A pointer to a class.
     */
    void addClass(Class *classes);

    /**
     * Removes a pointer to a given class from the vector that stores the pointers to all classes of the Student.\n
     * Time Complexity: O(n).
     * @param classes A pointer to a class.
     */
    void removeClass(Class *classes);

    /**
     * Checks if there is not overlap between classes.\n
     * Time Complexity: O(nlog(n)) or O(N*M),where N stands for the number of classes and M stands for the number of lectures of the class.
     * @return Returns true if there is no overlap. Returns false otherwise.
     */
    bool checkValidClasses() const;

    /**
     * Checks if there is not overlap between course units.\n
     * Time Complexity: O(nlog(n)).
     * @return Returns true if there is no overlap. Returns false otherwise.
     */
    bool checkValidCourseUnit() const;

    /**
     * A method to print the information about a student.\n
     * It prints the code of the student followed by their name.\n
     * Time Complexity: O(1).
     */
    void show() const;

    /**
     * A method to compare two students by their corresponding names.\n
     * Time Complexity: O(1).
     * @param student1 A reference to a student.
     * @param student2 A reference to other student.
     * @return A boolean that tells if student1's name is smaller than student2's.
     */
    static bool compareName(const Student& student1, const Student& student2);

    bool operator < (const Student & student) const;
    bool operator == (const Student & student) const;
    friend std::ostream& operator <<(std::ostream& out,const Student& student);


private:
    int code_;
    std::string name_;
    std::vector<Class*> classes_;
};


#endif
