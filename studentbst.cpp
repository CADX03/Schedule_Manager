#include "studentbst.h"

StudentBST::StudentBST() {
    studentData_ = std::list<Student>();
}

const Student &StudentBST::findMin() const {
    return studentBST_.findMin();
}

const Student &StudentBST::findMax() const {
    return studentBST_.findMax();
}

const Student &StudentBST::find(const Student &x) const {
    return studentBST_.find(x);
}

bool StudentBST::isEmpty() const {
    return studentData_.empty() && studentBST_.isEmpty();
}

void StudentBST::printTree() const {
    studentBST_.printTree();
}

void StudentBST::makeEmpty() {
    studentBST_.makeEmpty();
    studentData_.clear();
}

bool StudentBST::insert(const Student &x) {
    studentData_.push_back(x);
    if(studentBST_.insert(studentData_.back())) {
        studentData_.sort(Student::compareName);
        return true;
    }
    studentData_.pop_back();
    return false;
}

bool StudentBST::remove(const Student &x) {
    if(studentBST_.remove(x)){
        studentData_.remove(x);
        return true;
    }
    return false;
}

iteratorBST<Student> StudentBST::begin() const {
    return studentBST_.begin();
}

iteratorBST<Student> StudentBST::end() const {
    return studentBST_.end();
}

unsigned long StudentBST::size() const {
    return studentData_.size();
}

BST<Student> StudentBST::getBST() const {
    return studentBST_;
}

std::list<Student> StudentBST::getList() const {
    return studentData_;
}
