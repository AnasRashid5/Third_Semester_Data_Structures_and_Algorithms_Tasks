#pragma once
#include <iostream>
using namespace std;

struct C_Node; // forward declaration

struct S_Node
{
    int seat_no;
    S_Node *Snext = NULL;
};

void insertStudentToCourse(int seat_no, int course_no);
void deleteStudentFromACourse(int seat_no, int course_no);
void displayCourseStudents(int course_no);
bool searchStudentInACourse(int course_no, int seat_no);
