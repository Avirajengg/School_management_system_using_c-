#include <iostream>
#include "subjects_head.h"
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

void Subject::get_marks()
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
                class_name_temp = to_string(i);
            }
        }
        else
        {
            if (stu_id.substr(n - 1, n + 1) == to_string(i).substr(0, 2))
            {
                class_name_temp = to_string(i);
            }
        }
    }

    string filename = "marks" + class_name_temp + ".txt";
    fetch_marks_data.open(filename);

    if (!fetch_marks_data)
    {
        cout << "Error opening student.txt file." << endl;
        return;
    }

    bool found = false;

    while (getline(fetch_marks_data, m_id, '_'))
    {
        getline(fetch_marks_data, mathsM, '_');
        getline(fetch_marks_data, englishM, '_');
        getline(fetch_marks_data, scienceM, '_');
        getline(fetch_marks_data, social_scienceM, '_');
        getline(fetch_marks_data, hindiM, '_');
        getline(fetch_marks_data, percentage, '\n');

        double maths = stof(mathsM);
        double english = stof(englishM);
        double science = stof(scienceM);
        double social_science = stof(social_scienceM);
        double hindi = stof(hindiM);
        double per = stof(percentage);

        per = ((maths + english + science + social_science + hindi) / 500) * 100;

        if (m_id == stu_id)
        {
            cout << "MATHS" << "          " << "ENGLISH" << "          " << "SCIENCE" << "          " << "SOCIAL SCIENCE" << "          " << "HINDI" << "          " << "PERCENTAGE" << endl;

            cout << mathsM << "                  " << englishM << "              " << scienceM << "              " << social_scienceM << "                " << hindiM << "               " << per << "%" << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "STUDENT NOT FOUND" << endl;
    }

    fetch_marks_data.close();
}