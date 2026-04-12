#include <bits/stdc++.h>
#include "Student.h"
#include "Course.h"
using namespace std;

// struct S_Node
// {
//     int seat_no;
//     S_Node *Snext = NULL;
// };
void insertStudentToCourse(int seat_no, int course_no)
{
    S_Node *temp;

    temp = (S_Node *)malloc(sizeof(S_Node));
    temp->seat_no = seat_no;
    temp->Snext = NULL;

    C_Node *C_current = course_list;
    if (searchStudentInACourse(seat_no, course_no))
    {
        cout << "Student Already Exists In This Course!" << endl;
        return;
    }
    while (C_current != NULL)
    {
        if (C_current->C_no == course_no)
        {
            // current->stu_list = temp;
            if (C_current->stu_list == NULL)
            {
                C_current->stu_list = temp;
                return;
            }
            S_Node *S_current = C_current->stu_list;

            while (S_current->Snext != NULL)
            {

                S_current = S_current->Snext;
            }
            S_current->Snext = temp;
        }
        C_current = C_current->Cnext;
    }
}

void deleteStudentFromACourse(int seat_no, int course_no) // delete a student from a course
{
    if (!searchStudentInACourse(seat_no, course_no))
    {
        cout << "Student or course not exist;" << endl;
        return;
    }
    else
    {
        C_Node *C_current = course_list;
        S_Node *S_current;

        while (C_current != NULL)
        {
            if (course_no == C_current->C_no)
            {
                S_current = C_current->stu_list;
                break;
            }
            C_current = C_current->Cnext;
        }

        if (seat_no == S_current->seat_no)
        {
            C_current->stu_list = C_current->stu_list->Snext;
            free(S_current);
            return;
        }

        S_Node *S_prev = C_current->stu_list;

        while (S_current != NULL)
        {
            S_current = S_current->Snext;

            if (S_current->seat_no == seat_no)
            {
                S_prev->Snext = S_current->Snext;
                free(S_current);
                return;
            }

            S_prev = S_prev->Snext;
            // S_current = S_current->Snext;
        }
    }
}

void deleteAStudent(int seat_no) // will be deleted from everywhere
{
}
void displayCourseStudents(int course_no)
{
    if (course_list == NULL)
    {
        cout << "List is Empty." << endl;
        return;
    }

    C_Node *C_current = course_list;
    S_Node *S_current;

    // if (!searchACourse(course_no))
    // {
    //     return false;
    // }

    while (C_current != NULL)
    {
        if (course_no == C_current->C_no)
        {
            S_current = C_current->stu_list;
            break;
        }
        C_current = C_current->Cnext;
    }

    if (C_current == NULL)
    {
        cout << "Course Not Found: " << endl;
        return;
    }

    if (S_current == NULL)
    {
        cout << "No Students Enrolled In The Course: " << course_no << endl;
        return;
    }

    cout << "Students Are: " << endl;
    while (S_current != NULL)
    {
        cout << S_current->seat_no << endl;
        S_current = S_current->Snext;
    }
    return;
}

bool searchStudentInACourse(int seat_no, int course_no)
{
    if (course_list == NULL)
    {
        cout << "List is Empty." << endl;
        return false;
    }

    C_Node *C_current = course_list;
    S_Node *S_current;

    // if (!searchACourse(course_no))
    // {
    //     return false;
    // }

    while (C_current != NULL)
    {
        if (course_no == C_current->C_no)
        {
            S_current = C_current->stu_list;
            break;
        }
        C_current = C_current->Cnext;
    }

    while (S_current != NULL)
    {
        if (seat_no == S_current->seat_no)
        {
            cout << "Student Found: " << seat_no << endl;
            return true;
        }
        S_current = S_current->Snext;
    }
    return false;
}

int searchAStudent(int seat_no) //how many courses student is enrolled
{
    return 1;
}