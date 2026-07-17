#include <iostream>
#include "subjects_head.h"
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

void Student::get_student()
{
    string stu_id;
    cout << "PLEASE ENTER THE STUDENT ID(first three letters of name followed by 0 then class{example: AVI02 ==> avi first three letters then 0 then class 2}): ";
    cin >> stu_id;
    cin.ignore();

    int n = stu_id.length();

    for (int i = 1; i <= 12; i++)
    {
        if (i <= 9)
        {
            if (stu_id.back() == to_string(i).back())
            {
                class_name = to_string(i);
            }
        }
        else
        {
            if (stu_id.substr(n - 1, n + 1) == to_string(i).substr(0, 2))
            {
                class_name = to_string(i);
            }
        }
    }
    cout << class_name << endl;

    string filename = "student" + class_name + ".txt";
    student_data.open(filename);

    if (!student_data)
    {
        cout << "Error opening student.txt file." << endl;
        return;
    }

    bool found = false;

    while (getline(student_data, id, '_'))
    {
        getline(student_data, name, '_');
        getline(student_data, class_name, '\n');

        if (id == stu_id)
        {
            cout << "ID" << "          " << "NAME" << "          " << "CLASS" << endl;
            cout << id << "          " << name << "          " << class_name << endl;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "STUDENT NOT FOUND" << endl;
    }

    student_data.close();
}