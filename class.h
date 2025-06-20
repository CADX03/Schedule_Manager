#ifndef CLASS_H
#define CLASS_H

#include "lecture.h"

class Class {
public:
    Class(std::string code, std::string courseUnitCode, std::vector<Lecture*> lectures);
    Class(const Class& newClass);

    void setStudentsEnrolled(int studentsEnrolled) {studentsEnrolled_ = studentsEnrolled;}
    int getStudentsEnrolled() const { return studentsEnrolled_;}

    void setCode(std::string code) { code_ = code; }
    std::string getCode() const { return code_; }

    void setCourseUnitCode(std::string courseUnitCode) { courseUnitCode_ = courseUnitCode; }
    std::string getCourseUnitCodeCode() const { return courseUnitCode_; }

    std::vector<Lecture*> getLectures() const { return lectures_; }

    /**
     * Adds a pointer to a given lecture to the vector that stores the pointers to all the lectures of the class.\n
     * Time Complexity: O(1).
     * @param lecture A pointer to a lecture.
     */
    void addLecture(Lecture* lecture){ lectures_.push_back(lecture); }

    /**
     * A method to print the information about a class.\n
     * It prints the code of the Course Unit followed by the code of the class.\n
     * Time Complexity: O(1).
     */
    void show() const;

    /**
    * A method to compare two classes by course unit.\n
    * Time Complexity: O(1).
    * @param a A pointer to a Class.
    * @param b A pointer to other Class.
    * @return A boolean that tells if a is smaller than b.
    */
    static bool compareCourseUnit(Class* a, Class* b);

    friend std::ostream& operator <<(std::ostream& out,const Class& classes);

private:
    int studentsEnrolled_;
    std::string code_;
    std::string courseUnitCode_;
    std::vector<Lecture*> lectures_;
};


#endif
