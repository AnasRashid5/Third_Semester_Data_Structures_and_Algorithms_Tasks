#include <bits/stdc++.h>
#include "models/Course.cpp"
#include "models/Student.cpp"
using namespace std;

int main()
{
    int choice;
    bool exitProgram = false;

    while (!exitProgram)
    {
        cout << "\n===== Course & Student Management Menu =====" << endl;
        cout << "1.  Insert course" << endl;
        cout << "2.  Delete a course" << endl;
        cout << "3.  Search a course" << endl;
        cout << "4.  Display all courses" << endl;
        cout << "5.  Add student to a course" << endl;
        cout << "6.  Delete a student completely" << endl;
        cout << "7.  Delete a student from a specific course" << endl;
        cout << "8.  Search a student in a course" << endl;
        cout << "9.  Display students in a course" << endl;
        cout << "10. Display all courses with students" << endl;
        cout << "11. Exit program" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: // Insert course
        {
            int course_no;
            cout << "Enter Course Number to Insert: ";
            cin >> course_no;
            insertCourse(course_no);
            break;
        }

        case 2: // Delete course
        {
            int courseNo;
            cout << "Enter Course Number to Delete: ";
            cin >> courseNo;
            deleteCourse(courseNo);
            break;
        }

        case 3: // Search course
        {
            int courseNo;
            cout << "Enter Course Number to Search: ";
            cin >> courseNo;
            if (!searchACourse(courseNo))
                cout << "Course does not exist: " << courseNo << endl;
            break;
        }

        case 4: // Display courses
            displayCourses();
            break;

        case 5: // Add student to course
        {
            int id, courseNo;
            cout << "Enter Student ID: ";
            cin >> id;
            cout << "Enter Course Number to enroll: ";
            cin >> courseNo;
            insertStudentToCourse(id, courseNo);
            break;
        }

        case 6: // Delete student completely
        {
            int id;
            string choiceStr;
            cout << "Notice: Student will be deleted from all courses! Confirm (Y/N): ";
            cin >> choiceStr;
            if (choiceStr == "yes" || choiceStr == "YES" || choiceStr == "y" || choiceStr == "Y")
            {
                cout << "Enter Student ID to delete: ";
                cin >> id;
                deleteAStudent(id);
            }
            else
            {
                cout << "No student deleted." << endl;
            }
            break;
        }

        case 7: // Delete student from a specific course
        {
            int courseNo, id;
            cout << "Enter Course Number: ";
            cin >> courseNo;
            cout << "Enter Student ID to delete from course: ";
            cin >> id;
            deleteStudentFromACourse(id, courseNo);
            break;
        }

        case 8: // Search student in course
        {
            int courseNo, id;
            cout << "Enter Course Number: ";
            cin >> courseNo;
            cout << "Enter Student ID to search: ";
            cin >> id;
            if (!searchStudentInACourse(id, courseNo))
                cout << "Either course/student does not exist or list is empty." << endl;
            break;
        }

        case 9: // Display students in a course
        {
            int courseNo;
            cout << "Enter Course Number: ";
            cin >> courseNo;
            displayCourseStudents(courseNo);
            break;
        }

        case 10: // Display all courses and students
            displayAll();
            break;

        case 11: // Exit
            exitProgram = true;
            cout << "Exiting program. Goodbye!" << endl;
            break;

        default:
            cout << "Invalid input! Please choose a number between 1 and 11." << endl;
            break;
        }
    }

    return 0;
}