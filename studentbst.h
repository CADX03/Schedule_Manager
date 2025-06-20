#ifndef STUDENTBST_H
#define STUDENTBST_H

#include <list>
#include "bst.h"
#include "student.h"


class StudentBST {
public:
    explicit StudentBST();

    /**
     * Finds the student with the smallest student number in the BST of students.\n
     * Time Complexity: O(h) where h is the height of BST.
     * @return A reference to a Student.
     */
    const Student& findMin( ) const;

    /**
    * Finds the student with the biggest student number in the BST of students.\n
    * Time Complexity: O(h) where h is the height of BST.
    * @return A reference to a Student.
    */
    const Student& findMax( ) const;

    /**
     * Finds a student in the BST of students.\n
     * Time Complexity: O(h) where h is the height of BST.
     * @param x A reference to a student.
     * @return A reference to a student.
     */
    const Student& find(const Student& x) const;

    /**
     * Checks if the BST of students and the list of students are empty.\n
     * Time Complexity: O(1).
     */
    bool isEmpty( ) const;

    /**
     * Prints the students in the BST of students.\n
     * Time Complexity: O(n).
     */
    void printTree( ) const;

    /**
     * Clears the BST of students and the list of students.\n
     * Time Complexity: O(n).
     */
    void makeEmpty( );

    /**
     * Inserts the given student in the BST of students and in the list of students.\n
     * Time Complexity: O(nlog(n)).
     * @param x A reference to a student.
     * @return A boolean that tells if the insertion was successful.
     */
    bool insert(const Student& x);

    /**
     * Removes the given student from the BST of students and from the list of students.\n
     * Time Complexity: O(n).
     * @param x A reference to a student.
     * @return A boolean that tells if the removal was successful.
     */
    bool remove(const Student& x);

    iteratorBST<Student> begin() const;
    iteratorBST<Student> end() const;

    /**
     * Calculates the size of the list of students.\n
     * Time Complexity: O(1).
     * @return An unsigned long representing the size of the list of students.
     */
    unsigned long size() const;

    BST<Student> getBST() const;
    std::list<Student> getList() const;

private:
    BST<Student> studentBST_ = BST<Student>(Student(-1, "Not Found"));
    std::list<Student> studentData_;

    friend class BSTItrIn<Student>;
    friend class BSTItrInReverse<Student>;
    friend class BSTItrPre<Student>;
    friend class BSTItrPost<Student>;
    friend class BSTItrLevel<Student>;
    friend class iteratorBST<Student>;
};


#endif
