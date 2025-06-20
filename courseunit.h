
#ifndef COURSEUNIT_H
#define COURSEUNIT_H

#include <climits>
#include "class.h"

class CourseUnit {
public:
    CourseUnit(std::string code);
    CourseUnit(std::string code, std::vector<Class*> classes);
    CourseUnit(const CourseUnit& courseUnit);

    void setCode(std::string code){code_ = code;}
    std::string getCode() const {return code_;}

    std::vector<Class*> getClasses() const {return classes_;}

    /**
     *  A method that returns a pointer to a certain class given that class' code.\n
     * Time Complexity: O(n).
     * @param A string of the class code.
     * @return A pointer to the class with the given class code.
     */
    Class* getClass(std::string classCode) {
        for(Class* classes : classes_){
            if(classCode == classes->getCode())
                return classes; }
        return nullptr;}

    /**
     * Adds a pointer to a given class to the vector that stores the pointers to all classes of the Course Unit.\n
     * Time Complexity: O(1).
     * @param classes A pointer to a class.
     */
    void addClass(Class* classes){classes_.push_back(classes);}

    /**
     * Checks all the classes in a Course Unit to make sure the difference of students enrolled in each of them is never bigger than 4.\n
     * Time Complexity: O(n).
     * @return A boolean that tells if the balance criteria is being respected.
     */
    bool checkBalance();

    /**
     * A method to print the information about a Course Unit.\n
     * It prints the code of the Course Unit.\n
     * Time Complexity: O(1).
     */
    void show() const;

private:
    std::string code_;
    std::vector<Class*> classes_;
};


#endif
