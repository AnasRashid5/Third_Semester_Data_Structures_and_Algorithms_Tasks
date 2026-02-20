#include <bits/stdc++.h>
// #include "models/Course.h"
#include "models/Course.cpp"
#include "models/Student.cpp"
using namespace std;

// int courseNoInput()
// {

//     int courseNo = 0;
//     cout << "Enter Course no:  " << endl;
//     cin >> courseNo;
//     return courseNo;
// }

int main()
{

    int n, t = 0;
    bool flag = true;

    while (flag)
    {
        cout << "Enter 1 to insert course.  2 to delete a course.  3 to search a course. 4 to display course list. 5 to add student to a course. 6 to delete a student. ";
        cout << "7 to delete a student from a course. 8 to search a student(How many courses student has enrolled). 9 to display students in a course. 10 to display all";
        cout << "11 to exit";
        cin >> t;

        if (t == 1)
        {
            int course_no = 0;
            // cout << "Enter number of courses you want to insert:";
            // cin >> n;
            // for (int i = 0; i < n; i++)
            // {
            cout << "Enter Course Number To Insert: ";
            cin >> course_no;
            insertCourse(course_no);
            // cout<<i;
            // }
        }
        else if (t == 2)
        {
            int courseNo = 0;
            cout << "Enter Course no To Delete:  " << endl;
            cin >> courseNo;
            deleteCourse(courseNo);
        }

        else if (t == 3)
        {
            int courseNo = 0;
            cout << "Enter Course no to Search:  " << endl;
            cin >> courseNo;

            if (!searchACourse(courseNo))
            {
                cout << "Course Not Exist: " << courseNo << endl;
            }
        }
        else if (t == 4)
        {
            displayCourses();
        }
        else if (t == 5)
        {
            int id = 0;
            int courseNo = 0;
            cout << "Enter Student Id : " << endl;
            cin >> id;
            cout << "Enter Course no you wannna enroll! " << endl;
            cin >> courseNo;
            insertStudentToCourse(id, courseNo);
        }
        else if (t == 6)
        {
            int id = 0;
            string choice;
            cout << "Notice Student will be deleted from everywhere!Are you sure?Type Y for yes and N for no.";
            cin >> choice;
            if (choice == "yes" || choice == "YES" || choice == "Yes" || choice == "y" || choice == "Y")
            {

                cout << "Enter Student Id : " << endl;
                cin >> id;
                deleteAStudent(id);
            }
            else
            {
                cout << "No student deleted";
            }
        }
        else if (t == 7)
        {
            int courseNo, id = 0;
            cout << "Enter Course no to search student:  " << endl;
            cin >> courseNo;
            cout << "Enter Student Id to search in course: " << endl;
            cin >> id;
            deleteStudentFromACourse(id, courseNo);
        }
        else if (t == 8)
        {
            int courseNo, id = 0;
            cout << "Enter Course no to search student:  " << endl;
            cin >> courseNo;
            cout << "Enter Student Id to search in course: " << endl;
            cin >> id;

            if (!searchStudentInACourse(id, courseNo))
            {
                cout << "Either list is empty or course / student not exist " << courseNo << endl;
            }
        }
        else if (t == 9)
        {
            int courseNo = 0;
            cout << "Enter Course no:  " << endl;
            cin >> courseNo;
            displayCourseStudents(courseNo);
        }
        else if (t == 10)
        {
            displayAll();
        }
        else if (t == 10)
        {
            flag = false;
        }
        else
        {
            cout << "Invalid Input!";
        }
    }
}
