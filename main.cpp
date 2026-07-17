#include <iostream>
#include "subjects_head.h"

using namespace std;

void menu(principal &aviraj)
{
    cout << "=====================================" << endl;
    cout << "        SCHOOL MANAGEMENT" << endl;
    cout << "=====================================" << endl;

    cout << "*****PLEASE CHOOSE YOUR POSITION*****"<<endl;
    cout << "1.   PRINCIPAL" << endl;
    cout << "2.   TEACHER" << endl;
    cout << "3.   STUDENT" << endl;

    cout << "======================================" << endl;

    int opt;
    cout << "ENTER YOUR OPTION: ";
    cin >> opt;

    if (opt == 1)
    {
        cout << "************************************************************" << endl;
        cout << "                 WELCOME PRINCIPAL" << endl;
        cout << "************************************************************" << endl;

        cout << "::PLEASE CHOOSE THE OPERATION YOU WANT TO PERFORM::" << endl;
        cout << "1.   TEACHER DATA" << endl;
        cout << "2.   STUDENT DATA" << endl;

        int opt_princi;
        cout << "ENTER: " << endl;
        cout << "---------------------------------------------------------------------" << endl;
        cin >> opt_princi;
        if (opt_princi == 1)
        {
            cout << "---------------------------------------------------------------------" << endl;
            cout << "::PLEASE CHOOSE THE OPERATION YOU WANT TO PERFORM ON TEACHER'S DATA::" << endl;
            cout << "---------------------------------------------------------------------" << endl;
            cout << "1.   SHOW TEACHER'S LIST" << endl;
            cout << "2.   ADD TEACHERS" << endl;
            cout << "3.   DELETE TEACHERS" << endl;
            cout << "4.   UPDATE TEACHER" << endl;
            cout << "5.   SEARCH TEACHER" << endl;
            int opt_crud;
            cout << "ENTER: ";
            cin >> opt_crud;
            cout << "---------------------------------------------------------------------" << endl;
            switch (opt_crud)
            {
            case 1:
                aviraj.calc_no_avg_princi();
                aviraj.get_teacher_data();
                break;
            case 2:
                aviraj.add_teacher_data();
                break;
            case 3:
                aviraj.delete_teacher_data();
                break;
            case 4:
                aviraj.update_teacher_data();
                break;
            case 5:
                aviraj.search_teacher_data();
                break;
            }
        }
        else if (opt_princi == 2)
        {
            cout << "---------------------------------------------------------------------" << endl;
            cout << "::PLEASE CHOOSE THE OPERATION YOU WANT TO PERFORM ON STUDENT'S DATA::" << endl;
            cout << "---------------------------------------------------------------------" << endl;
            cout << "1.   SHOW STUDENT'S LIST" << endl;
            cout << "2.   SEARCH STUDENT" << endl;
            int opt_crud;
            cout << "ENTER: ";
            cin >> opt_crud;
            cout << "---------------------------------------------------------------------" << endl;
            switch (opt_crud)
            {
            case 1:
                aviraj.get_student_data();
                aviraj.get_student_marks();
                break;
            case 2:
                aviraj.search_student();
                break;
            }
        }
        else
        {
            cout << "INVALID OPERATION" << endl;
        }
    }
    else if (opt == 2)
    {
        cout << "************************************************************" << endl;
        cout << "                 WELCOME TEACHER" << endl;
        cout << "************************************************************" << endl;

        cout << "::PLEASE CHOOSE THE OPERATION YOU WANT TO PERFORM::" << endl;
        cout << "1.   TEACHER PERSONAL DATA" << endl;
        cout << "2.   STUDENT DATA" << endl;

        int opt_teach;
        cout << "ENTER: " << endl;
        cin >> opt_teach;
        if (opt_teach == 1)
        {
            cout << "---------------------------------------------------------------------" << endl;
            aviraj.get_class_teacher_data();
        }
        else if (opt_teach == 2)
        {
            cout << "---------------------------------------------------------------------" << endl;
            cout << "::PLEASE CHOOSE THE OPERATION YOU WANT TO PERFORM ON STUDENT'S DATA::" << endl;
            cout << "---------------------------------------------------------------------" << endl;
            cout << "1.   SHOW STUDENT'S LIST" << endl;
            cout << "2.   ADD STUDENTS" << endl;
            cout << "3.   DELETE STUDENTS" << endl;
            cout << "4.   UPDATE STUDENT" << endl;
            cout << "5.   SEARCH STUDENT" << endl;
            int opt_crud;
            cout << "ENTER: ";
            
            cin >> opt_crud;
             cout << "---------------------------------------------------------------------" << endl;
            switch (opt_crud)
            {
            case 1:
                aviraj.get_student_data();
                aviraj.get_student_marks();
                break;
            case 2:
                aviraj.add_student();
                break;
            case 3:
                aviraj.delete_student();
                break;
            case 4:
                aviraj.update_student();
                break;
            case 5:
                aviraj.search_student();
                break;
            }
        }
        else
        {
            cout << "INVALID OPERATION" << endl;
        }
    }
    else if (opt == 3)
    {
        cout << "************************************************************" << endl;
        cout << "                 WELCOME STUDENT" << endl;
        cout << "************************************************************" << endl;

        cout << "::PLEASE CHOOSE THE OPERATION YOU WANT TO PERFORM::" << endl;
        cout << "1.   STUDENT PERSONAL DATA" << endl;
        cout << "2.   STUDENT MARKS DATA" << endl;

        int opt_stud;

        cout << "ENTER: " << endl;
        cin >> opt_stud;
        cout << "---------------------------------------------------------------------" << endl;
        if (opt_stud == 1)
        {
            aviraj.get_student();
        }
        else if (opt_stud == 2)
        {
            aviraj.get_marks();
        }
        else
        {
            cout << "INVALID OPERATION" << endl;
        }
    }
    else
    {
        cout << "INVALID CHOICE" << endl;
    }
}

int main()
{
    principal aviraj;

    menu(aviraj);
    return 0;
    
}