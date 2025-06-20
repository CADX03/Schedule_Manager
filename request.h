#ifndef REQUEST_H
#define REQUEST_H

#include "student.h"


class Request {
public:

    /**
   * An enum.\n
   * Each Task represents a different feature of the Request Menu.
   */
    enum Task{AddStudent, RemoveStudent, AddStudentToClass, RemoveStudentFromClass, ManageStudentClasses};

    Request(Task task, Student student);

    int getTask() const { return task_; }
    Student getStudent() const { return student_; }

private:
    Student student_ = Student(-1, "");
    Task task_;
};


#endif
