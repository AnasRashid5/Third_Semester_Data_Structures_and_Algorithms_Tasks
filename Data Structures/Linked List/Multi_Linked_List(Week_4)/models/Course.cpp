#include "Course.h"
#include "Student.h"
using namespace std;

// struct C_Node
// {
//     int C_no;
//     C_Node *Cnext = NULL;
//     S_Node *stu_list = NULL;
// };

C_Node *course_list = NULL;

void insertCourse(int course_no)
{
    // C_Node *current = course_list;

    C_Node *temp;
    temp = (C_Node *)malloc(sizeof(C_Node));
    temp->C_no = course_no;
    temp->Cnext = NULL;
    temp->stu_list = NULL;

    if (course_list == NULL)
    {
        course_list = temp;
        return;
    }
    if (searchACourse(course_no))
    {
        // cout << "Course Already Exists" << endl;
        return;
    }
    else
    {

        C_Node *current = course_list;

        while (current->Cnext != NULL)
        {
            current = current->Cnext;
        }
        current->Cnext = temp;
    }
}

bool searchACourse(int course_no)
{
    if (course_list == NULL)
    {
        cout << "No Courses Present Inside List" << endl;
        return false;
    }

    C_Node *current = course_list;

    while (current != NULL)
    {
        if (course_no == current->C_no)
        {
            // flag=true;
            cout << "Course Exist: " << course_no << endl;
            return true;
        }
        current = current->Cnext;
    }
    return false;
}

void deleteCourse(int course_no)
{
    if (course_list == NULL)
    {
        cout << "No Courses Present Inside List" << endl;
        return;
    }
    // only for first head logic:

    // if student list is null
    if (course_no == course_list->C_no && course_list->stu_list == NULL)
    {
        C_Node *C_current = course_list;
        course_list = course_list->Cnext;
        free(C_current);
        return;
    }

    // if student list is not null
    if (course_no == course_list->C_no)
    {
        S_Node *S_current = course_list->stu_list;
        C_Node *C_current = course_list;

        while (S_current != NULL)
        {
            S_Node *next = S_current->Snext;
            free(S_current);
            S_current = next;
        }
        course_list = course_list->Cnext;
        free(C_current);
        return;
    }

    // if course is elsewhere head and student list is null.
    C_Node *C_prev = course_list;
    C_Node *C_current = course_list;
    C_current = C_current->Cnext;

    while (C_current != NULL)
    {
        if (C_current->C_no == course_no && C_current->stu_list == NULL)
        {
            C_prev->Cnext = C_current->Cnext;
            free(C_current);
            return;
        }
        C_current = C_current->Cnext;
        C_prev = C_prev->Cnext;
    }

    // non head and also student list is present
}

void displayCourses()
{
    if (course_list == NULL)
    {
        cout << "No Courses Present Inside List";
        return;
    }

    C_Node *current = course_list;

    cout << "Courses Are: " << endl;
    while (current != NULL)
    {
        cout << current->C_no << endl;
        current = current->Cnext;
    }
}
void displayAll()
{
    C_Node *C_current = course_list;

    while (C_current != NULL)
    {
        cout << "Cousre Number: " << C_current->C_no << endl;
        S_Node *S_current = C_current->stu_list;


        // cout << "Course Students Are: " << endl;
        displayCourseStudents(C_current->C_no);
        // while (S_current != NULL)
        // {
        //     cout << S_current->seat_no;
        //     S_current = S_current->Snext;
        // }
        C_current = C_current->Cnext;
    }
}
