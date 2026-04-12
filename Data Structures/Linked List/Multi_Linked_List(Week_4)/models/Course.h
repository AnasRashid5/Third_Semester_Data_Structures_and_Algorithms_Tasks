#pragma once
#include <iostream>
#include <stdlib.h>
using namespace std;

struct S_Node; // forward declaration

struct C_Node
{
    int C_no; //course number
    C_Node *Cnext = NULL; //next pointer
    S_Node *stu_list = NULL; //student list
};

extern C_Node *course_list; // declaration only

void insertCourse(int course_no);
void deleteCourse(int course_no);
bool searchACourse(int course_no);
void displayCourses();
void displayAll();
