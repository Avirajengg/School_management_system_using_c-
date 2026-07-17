#include <iostream>
#include "subjects_head.h"
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

string getClassFromID(const string& teachId){
    int n = teachId.length();
    string class_name_;
        for (int i = 1; i <= 12; i++)
        {
            if (i <= 9)
            {
                if (teachId.back() == to_string(i).back())
                    class_name_ = to_string(i);
            }
            else
            {
                if (teachId.substr(n - 2, 2) == to_string(i))
                    class_name_ = to_string(i);
            }
        }
    return class_name_;
}
bool class_teacher::calc_no_avg_teach(const string &target_id)
{
    class_teacher_data.open("class_teacher.txt");
    teacher_data_store.open("temp_teacher.txt");

    if (!class_teacher_data || !teacher_data_store)
    {
        cout << "CAN'T GET THAT FILE" << endl;
        if (class_teacher_data.is_open())
            class_teacher_data.close();
        if (teacher_data_store.is_open())
            teacher_data_store.close();
        return false;
    }

    bool success = false;
    string line;

    while (getline(class_teacher_data, line))
    {
        int teach_id_end = line.find('_');
        string this_id = line.substr(0, teach_id_end);

        // not the teacher we care about right now -> copy line unchanged
        if (this_id != target_id)
        {
            teacher_data_store << line << endl;
            continue;
        }

        int p1 = line.find('_', teach_id_end + 1);
        int p2 = line.find('_', p1 + 1);
        int p3 = line.find('_', p2 + 1);
        int p4 = line.find('_', p3 + 1);

        class_teacher_id = this_id;
        class_teacher_name = line.substr(teach_id_end + 1, p1 - teach_id_end - 1);
        teach_class_name = line.substr(p1 + 1, p2 - p1 - 1);
        subject = line.substr(p2 + 1, p3 - p2 - 1);
        student_no = line.substr(p3 + 1, p4 - p3 - 1);
        teacher_avg = line.substr(p4 + 1);

        // derive class number from the tail of the id (e.g. AVI02 -> class 2)
        class_name_temp = getClassFromID(class_teacher_id);

        string filename = "student" + class_name_temp + ".txt";
        string filename2 = "marks" + class_name_temp + ".txt";

        student_data.open(filename);
        fetch_marks_data.open(filename2);

        if (!student_data || !fetch_marks_data)
        {
            cout << "CAN'T GET THAT FILE" << endl;

            if (student_data.is_open())
                student_data.close();
            if (fetch_marks_data.is_open())
                fetch_marks_data.close();
            student_data.clear();
            fetch_marks_data.clear();

            teacher_data_store << line << endl; // keep old (blank) data, don't crash
            success = false;
            continue;
        }

        int count = 0;
        double count2 = 0;
        double sum = 0;
        vector<double> per;
        string studentLine;

        while (getline(student_data, studentLine))
            count++;

        student_no = to_string(count);

        while (getline(fetch_marks_data, id, '_'))
        {
            getline(fetch_marks_data, mathsM, '_');
            getline(fetch_marks_data, englishM, '_');
            getline(fetch_marks_data, scienceM, '_');
            getline(fetch_marks_data, social_scienceM, '_');
            getline(fetch_marks_data, hindiM, '_');
            getline(fetch_marks_data, percentage, '\n');

            per.push_back(stod(percentage));
        }

        for (double p : per)
        {
            sum += p;
            count2++;
        }

        teacher_avg = (count2 > 0) ? to_string(sum / count2) : "N/A";

        teacher_data_store << class_teacher_id << '_' << class_teacher_name << '_'
                           << teach_class_name << '_' << subject << '_'
                           << student_no << '_' << teacher_avg << endl;

        student_data.close();
        fetch_marks_data.close();
        student_data.clear();
        fetch_marks_data.clear();

        success = true;
    }

    class_teacher_data.close();
    teacher_data_store.close();

    remove("class_teacher.txt");
    rename("temp_teacher.txt", "class_teacher.txt");

    return success;
}

void class_teacher::get_class_teacher_data()
{
    string teacher_id;
    cout << "PLEASE ENTER THE CLASS TEACHER ID(first three letters of name followed by 0 then class{example: AVI02 ==> avi first three letters then 0 then class 2}): ";
    cin >> teacher_id;
    cin.ignore();

    // recompute student_no / teacher_avg for THIS teacher only, right now
    bool ok = calc_no_avg_teach(teacher_id);
    if (!ok)
    {
        cout << "CAN'T GET THAT FILE" << endl;
        return;
    }

    // now read the freshly-updated file and display only this teacher's row
    class_teacher_data.open("class_teacher.txt");
    if (!class_teacher_data)
    {
        cout << "CAN'T GET THAT FILE" << endl;
        return;
    }

    string id_field, name_field, class_field, subject_field, no_field, avg_field;
    bool found = false;

    while (getline(class_teacher_data, id_field, '_'))
    {
        getline(class_teacher_data, name_field, '_');
        getline(class_teacher_data, class_field, '_');
        getline(class_teacher_data, subject_field, '_');
        getline(class_teacher_data, no_field, '_');
        getline(class_teacher_data, avg_field, '\n');

        if (id_field == teacher_id)
        {
            cout << "ID" << "      " << "NAME" << "      " << "CLASS" << "        "
                 << "SUBJECT" << "           " << "NO. OF STUDENTS" << "          "
                 << "TEACHER AVERAGE" << endl;
            cout << id_field << "          " << name_field << "          "
                 << class_field << "          " << subject_field << "          "
                 << no_field << "                         " << avg_field << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "CLASS TEACHER NOT FOUND" << endl;

    class_teacher_data.close();
}

void class_teacher ::get_student_data()
{
    string teacher_id;
    cout << "PLEASE ENTER THE CLASS TEACHER ID: ";
    cin >> teacher_id;
    cin.ignore();

    class_name = getClassFromID(teacher_id);

    string filename = "student" + class_name + ".txt";
    student_data.open(filename);

    if (!student_data)
    {
        cout << "Error opening " << filename << " file." << endl;
        return;
    }
    cout << "ID" << "          " << "NAME" << "          " << "CLASS" << endl;
    while (getline(student_data, id, '_'))
    {
        getline(student_data, name, '_');
        getline(student_data, class_name, '\n');

        cout << id << "          " << name << "          " << class_name << endl;
    }

    student_data.close();
}

void class_teacher ::get_student_marks()
{
    string teacher_id;
    cout << "PLEASE ENTER THE CLASS TEACHER ID: ";
    cin >> teacher_id;
    cin.ignore();

    class_name = getClassFromID(teacher_id);

    string filename2 = "marks" + class_name + ".txt";
    fetch_marks_data.open(filename2);

    if (!fetch_marks_data)
    {
        cout << "Error opening " << filename2 << " file." << endl;
        return;
    }

    cout << "ID" << "          " << "MATHS" << "          " << "ENGLISH" << "          " << "SCIENCE" << "          " << "SOCIAL SCIENCE" << "          " << "HINDI" << "          " << "PERCENTAGE" << endl;
    while (getline(fetch_marks_data, id, '_'))
    {
        getline(fetch_marks_data, mathsM, '_');
        getline(fetch_marks_data, englishM, '_');
        getline(fetch_marks_data, scienceM, '_');
        getline(fetch_marks_data, social_scienceM, '_');
        getline(fetch_marks_data, hindiM, '_');
        getline(fetch_marks_data, percentage, '\n');

        cout << id << "          " << mathsM << "          " << englishM << "                  " << scienceM
             << "                 " << social_scienceM << "                  " << hindiM << "              " << percentage << "%" << endl;
    }

    fetch_marks_data.close();
}

void class_teacher ::add_student()
{
    string teacher_id;
    cout << "PLEASE ENTER THE CLASS TEACHER ID: ";
    cin >> teacher_id;
    cin.ignore();

    vector<string> arr;

    class_name = getClassFromID(teacher_id);

    string filename = "student" + class_name + ".txt";
    string filename2 = "marks" + class_name + ".txt";

    student_data_up.open(filename, ios::app);
    student_data.open(filename);
    student_marks_data.open(filename2, ios::app);
    string line;

    if (!student_data)
    {
        cout << "Error opening " << filename << " file." << endl;
        return;
    }

    string que;
    cout << "DO YOU WANT TO ADD MARKS AS WELL?: ";
    cin >> que;

    int n;
    cout << "PLEASE ENTER THE NUMBER OF STUDENTS TO BE ADDED: ";
    cin >> n;
    cin.ignore();

    if (que == "no")
    {

        while (getline(student_data, line))
        {
            int x = line.find('_');
            string stu_id = line.substr(0, x);
            arr.push_back(stu_id);
        }
        for (int i = 0; i < n; i++)
        {
            cout << "PLEASE ENTER STUDENT ID(first three letters of name followed by 0 then class{example: AVI02 ==> avi first three letters then 0 then class 2}): ";
            getline(cin, id);
            cin.ignore();

            if (find(arr.begin(), arr.end(), id) != arr.end())
            {
                cout << "STUDENT ID ALREADY EXISTS!!!" << endl;
                continue;
            }
            cout << "PLEASE ENTER STUDENT NAME: ";
            getline(cin, name);
            cin.ignore();

            student_data_up << id << '_' << name << '_' << class_name << endl;
            student_marks_data << id << '_' << "TBD" << "_" << "TBD" << "_" << "TBD" << "_" << "TBD" << "_" << "TBD" << "_" << "TBD" << endl;
        }
    }
    else if (que == "yes")
    {
        while (getline(student_data, line))
        {
            int x = line.find('_');
            string stu_id = line.substr(0, x);
            arr.push_back(stu_id);
        }
        for (int i = 0; i < n; i++)
        {
            cout << "PLEASE ENTER STUDENT ID(first three letters of name followed by 0 then class{example: AVI02 ==> avi first three letters then 0 then class 2}): ";
            getline(cin, id);
            cin.ignore();

            if (find(arr.begin(), arr.end(), id) != arr.end())
            {
                cout << "STUDENT ID ALREADY EXISTS!!!" << endl;
                continue;
            }
            cout << "PLEASE ENTER STUDENT NAME: ";
            getline(cin, name);
            cin.ignore();

            cout << "PLEASE ENTER STUDENT MARKS IN MATHS: ";
            getline(cin, mathsM);
            cin.ignore();

            cout << "PLEASE ENTER STUDENT MARKS IN ENGLISH: ";
            getline(cin, englishM);
            cin.ignore();

            cout << "PLEASE ENTER STUDENT MARKS IN SCIENCE: ";
            getline(cin, scienceM);
            cin.ignore();

            cout << "PLEASE ENTER STUDENT MARKS IN SOCIAL SCIENCE: ";
            getline(cin, social_scienceM);
            cin.ignore();

            cout << "PLEASE ENTER STUDENT MARKS IN HINDI: ";
            getline(cin, hindiM);
            cin.ignore();

            double per = ((stod(mathsM) + stod(englishM) + stod(scienceM) + stod(social_scienceM) + stod(hindiM)) / 500) * 100;
            percentage = to_string(per);

            student_data_up << id << '_' << name << '_' << class_name << endl;
            student_marks_data << id << '_' << mathsM << "_" << englishM << "_" << scienceM << "_" << social_scienceM << "_" << hindiM << "_" << percentage << endl;
        }
    }
    else
    {
        cout << "INVALID INPUT" << endl;
    }

    student_data.close();
    student_data_up.close();
    student_marks_data.close();
}

void class_teacher ::delete_student()
{
    string teacher_id;
    cout << "PLEASE ENTER THE CLASS TEACHER ID: ";
    cin >> teacher_id;
    cin.ignore();

    vector<int> arr;

   class_name = getClassFromID(teacher_id);

    string filename = "student" + class_name + ".txt";
    string filename2 = "marks" + class_name + ".txt";

    student_data.open(filename);
    fetch_marks_data.open(filename2);
    temp_students.open("temp_students.txt");
    temp_marks.open("temp_marks.txt");
    string line, line2;

    if (!student_data)
    {
        cout << "Error opening " << filename << " file." << endl;
        return;
    }

    int n;
    cout << "PLEASE ENTER THE NUMBER OF STUDENTS TO BE DELETED: ";
    cin >> n;
    cin.ignore();

    int count = 0;
    while (getline(student_data, line))
    {
        getline(fetch_marks_data, line2);
        int x = line.find('_');
        string stu_id = line.substr(0, x);

        if (count < n)
        {
            cout << "PLEASE ENTER STUDENT ID(first three letters of name followed by 0 then class{example: AVI02 ==> avi first three letters then 0 then class 2}): ";
            getline(cin, id);
            if (id != stu_id)
            {
                temp_students << line << endl;
                temp_marks << line2 << endl;
            }
            count++;
        }
        else
        {
            if (id != stu_id)
            {
                temp_students << line << endl;
                temp_marks << line2 << endl;
            }
        }
    }

    student_data.close();
    temp_students.close();
    temp_marks.close();
    fetch_marks_data.close();

    remove(filename.c_str());
    rename("temp_students.txt", filename.c_str());
    remove(filename2.c_str());
    rename("temp_marks.txt", filename2.c_str());
}

void class_teacher ::update_student()
{
    string teacher_id;
    cout << "PLEASE ENTER THE CLASS TEACHER ID: ";
    cin >> teacher_id;
    cin.ignore();

    vector<int> arr;

    class_name = getClassFromID(teacher_id);

    string filename = "student" + class_name + ".txt";
    string filename2 = "marks" + class_name + ".txt";

    student_data.open(filename);
    fetch_marks_data.open(filename2);
    temp_students.open("temp_students.txt");
    temp_marks.open("temp_marks.txt");
    string line, line2;

    if (!student_data)
    {
        cout << "Error opening " << filename << " file." << endl;
        return;
    }

    string que;
    cout << "DO YOU WANT TO UPDATE MARKS(write->marks) OR STUDENTS(write-> students) DATA OR BOTH(write->both)?: ";
    cin >> que;
    cin.ignore();

    if (que == "marks")
    {
        while (getline(fetch_marks_data, line2))
        {
            cout << line2 << endl;
            int x = line2.find('_');
            string stu_id = line2.substr(0, x);

            cout << "PLEASE ENTER STUDENT ID(first three letters of name followed by 0 then class{example: AVI02 ==> avi first three letters then 0 then class 2}): ";
            getline(cin, id);

            if (id == stu_id)
            {
                // parse the CURRENT student's existing marks first
                int p1 = line2.find('_');
                int p2 = line2.find('_', p1 + 1);
                int p3 = line2.find('_', p2 + 1);
                int p4 = line2.find('_', p3 + 1);
                int p5 = line2.find('_', p4 + 1);

                mathsM = line2.substr(p1 + 1, p2 - p1 - 1);
                englishM = line2.substr(p2 + 1, p3 - p2 - 1);
                scienceM = line2.substr(p3 + 1, p4 - p3 - 1);
                social_scienceM = line2.substr(p4 + 1, p5 - p4 - 1);
                hindiM = line2.substr(p5 + 1);

                int m;
                cout << "HOW MANY SUBJECTS DO YOU WANT TO UPDATE MARKS FOR?: ";
                cin >> m;
                cin.ignore(); // flush the newline left after >> m

                for (int i = 0; i < m; i++)
                {
                    string sub;
                    cout << "PLEASE ENTER THE SUBJECT TO BE UPDATED: ";
                    cin >> sub;
                    cin.ignore(); // flush newline after >> sub, before getline

                    if (sub == "maths")
                    {
                        cout << "NEW MATHS MARKS: ";
                        getline(cin, mathsM);
                    }
                    else if (sub == "english")
                    {
                        cout << "NEW ENGLISH MARKS: ";
                        getline(cin, englishM);
                    }
                    else if (sub == "science")
                    {
                        cout << "NEW SCIENCE MARKS: ";
                        getline(cin, scienceM);
                    }
                    else if (sub == "social science")
                    {
                        cout << "NEW SOCIAL SCIENCE MARKS: ";
                        getline(cin, social_scienceM);
                    }
                    else if (sub == "hindi")
                    {
                        cout << "NEW HINDI MARKS: ";
                        getline(cin, hindiM);
                    }
                    else
                    {
                        cout << "INVALID SUBJECT" << endl;
                        i--;
                    } // retry this slot instead of silently consuming it
                }

                double per = ((stod(mathsM) + stod(englishM) + stod(scienceM) + stod(social_scienceM) + stod(hindiM)) / 500) * 100;
                percentage = to_string(per);

                temp_marks << id << "_" << mathsM << "_" << englishM << "_" << scienceM
                           << "_" << social_scienceM << "_" << hindiM << "_" << percentage << endl;
            }
            else
            {
                temp_marks << line2 << endl;
            }
        }
    }
    else if (que == "students")
    {
        while (getline(student_data, line))
        {
            int x = line.find('_');
            string stu_id = line.substr(0, x);

            cout << "PLEASE ENTER STUDENT ID(first three letters of name followed by 0 then class{example: AVI02 ==> avi first three letters then 0 then class 2}): ";
            getline(cin, id);

            if (id == stu_id)
            {
                cout << "PLEASE ENTER STUDENT'S NEW NAME: ";
                getline(cin, name);

                temp_students << id << "_" << name << "_" << class_name << endl;
            }

            else
            {
                temp_students << line << endl;
            }
        }
    }
    else if (que == "both")
    {
        while (getline(student_data, line))
        {
            getline(fetch_marks_data, line2);

            int x = line.find('_');
            string stu_id = line.substr(0, x);

            cout << "PLEASE ENTER STUDENT ID(first three letters of name followed by 0 then class{example: AVI02 ==> avi first three letters then 0 then class 2}): ";
            getline(cin, id);

            if (id == stu_id)
            {
                cout << "PLEASE ENTER STUDENT ID: ";
                getline(cin, id);
                // parse the CURRENT student's existing marks first
                int p1 = line2.find('_');
                int p2 = line2.find('_', p1 + 1);
                int p3 = line2.find('_', p2 + 1);
                int p4 = line2.find('_', p3 + 1);
                int p5 = line2.find('_', p4 + 1);
                int p6 = line2.find('_', p5 + 1);

                mathsM = line2.substr(p1 + 1, p2 - p1 - 1);
                englishM = line2.substr(p2 + 1, p3 - p2 - 1);
                scienceM = line2.substr(p3 + 1, p4 - p3 - 1);
                social_scienceM = line2.substr(p4 + 1, p5 - p4 - 1);
                hindiM = line2.substr(p5 + 1, p6 - p5 - 1);

                int m;
                cout << "HOW MANY SUBJECTS DO YOU WANT TO UPDATE MARKS FOR?: ";
                cin >> m;
                cin.ignore(); // flush the newline left after >> m

                for (int i = 0; i < m; i++)
                {
                    string sub;
                    cout << "PLEASE ENTER THE SUBJECT TO BE UPDATED: ";
                    cin >> sub;
                    cin.ignore(); // flush newline after >> sub, before getline

                    if (sub == "maths")
                    {
                        cout << "NEW MATHS MARKS: ";
                        getline(cin, mathsM);
                    }
                    else if (sub == "english")
                    {
                        cout << "NEW ENGLISH MARKS: ";
                        getline(cin, englishM);
                    }
                    else if (sub == "science")
                    {
                        cout << "NEW SCIENCE MARKS: ";
                        getline(cin, scienceM);
                    }
                    else if (sub == "social science")
                    {
                        cout << "NEW SOCIAL SCIENCE MARKS: ";
                        getline(cin, social_scienceM);
                    }
                    else if (sub == "hindi")
                    {
                        cout << "NEW HINDI MARKS: ";
                        getline(cin, hindiM);
                    }
                    else
                    {
                        cout << "INVALID SUBJECT" << endl;
                        i--;
                    } // retry this slot instead of silently consuming it
                }

                double per = ((stod(mathsM) + stod(englishM) + stod(scienceM) + stod(social_scienceM) + stod(hindiM)) / 500) * 100;
                percentage = to_string(per);

                temp_students << id << "_" << name << "_" << class_name << endl;

                temp_marks << id << "_" << mathsM << "_" << englishM << "_" << scienceM
                           << "_" << social_scienceM << "_" << hindiM << "_" << percentage << endl;
            }
            else
            {
                temp_students << line << endl;
                temp_marks << line2 << endl;
            }
        }
    }
    else
    {
        cout << "INVALID OPTION";
    }

    student_data.close();
    temp_students.close();
    fetch_marks_data.close();
    temp_marks.close();

    remove(filename.c_str());
    rename("temp_students.txt", filename.c_str());
    remove(filename2.c_str());
    rename("temp_marks.txt", filename2.c_str());
}

void class_teacher ::search_student()
{
    string teacher_id;
    cout << "PLEASE ENTER THE CLASS TEACHER ID: ";
    cin >> teacher_id;
    cin.ignore();

    class_name = getClassFromID(teacher_id);

    string filename = "student" + class_name + ".txt";
    string filename2 = "marks" + class_name + ".txt";
    student_data.open(filename);
    fetch_marks_data.open(filename2);

    if (!student_data)
    {
        cout << "Error opening " << filename << " file." << endl;
        return;
    }

    string stu_id;
    cout << "PLEASE ENTER THE STUDENT ID TO BE SEARCHED(first three letters of name followed by 0 then class{example: AVI02 ==> avi first three letters then 0 then class 2}): ";
    cin >> stu_id;
    cin.ignore();

    bool found = false;

    while (getline(student_data, id, '_'))
    {
        getline(student_data, name, '_');
        getline(student_data, class_name, '\n');

        getline(fetch_marks_data, mathsM, '_');
        getline(fetch_marks_data, englishM, '_');
        getline(fetch_marks_data, scienceM, '_');
        getline(fetch_marks_data, social_scienceM, '_');
        getline(fetch_marks_data, hindiM, '_');
        getline(fetch_marks_data, percentage, '\n');

        if (id == stu_id)
        {
            cout << "ID" << "          " << "NAME" << "          " << "CLASS" << endl;
            cout << id << "          " << name << "          " << class_name << endl;
            cout << "**MARKS**" << endl;
            cout << "Maths: " << mathsM << endl;
            cout << "English: " << englishM << endl;
            cout << "Science: " << scienceM << endl;
            cout << "Social Science: " << social_scienceM << endl;
            cout << "Hindi: " << hindiM << endl;
            cout << "Percentage: " << percentage << "%" << endl;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "STUDENT NOT FOUND" << endl;
    }

    student_data.close();
    fetch_marks_data.close();
}