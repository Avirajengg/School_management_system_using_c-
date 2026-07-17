#include <iostream>
#include "subjects_head.h"
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

string getClassFromID(const string& prinId){
    int n = prinId.length();
    string class_name_;
        for (int i = 1; i <= 12; i++)
        {
            if (i <= 9)
            {
                if (prinId.back() == to_string(i).back())
                    class_name_ = to_string(i);
            }
            else
            {
                if (prinId.substr(n - 2, 2) == to_string(i))
                    class_name_ = to_string(i);
            }
        }
    return class_name_;
}

void principal ::calc_no_avg_princi()
{
    class_teacher_data.open("class_teacher.txt");
    teacher_data_store.open("temp_teacher.txt");
    string line;

    if (!class_teacher_data)
    {
        cout << "error opening class teacher  file" << endl;
        return;
    }

    if (!teacher_data_store)
    {
        cout << "error opening temp teacher file" << endl;
        return;
    }

    while (getline(class_teacher_data, line))
    {
        int teach_id = line.find('_');
        int p1 = line.find('_', teach_id + 1);
        int p2 = line.find('_', p1 + 1);
        int p3 = line.find('_', p2 + 1);
        int p4 = line.find('_', p3 + 1);

        class_teacher_id = line.substr(0, teach_id);
        class_teacher_name = line.substr(teach_id + 1, p1 - teach_id - 1);
        teach_class_name = line.substr(p1 + 1, p2 - p1 - 1);
        subject = line.substr(p2 + 1, p3 - p2 - 1);
        student_no = line.substr(p3 + 1, p4 - p3 - 1);
        teacher_avg = line.substr(p4 + 1);

        class_name_temp = getClassFromID(class_teacher_id);

        string filename = "student" + class_name_temp + ".txt";
        string filename2 = "marks" + class_name_temp + ".txt";
        student_data.open(filename);
        fetch_marks_data.open(filename2);

        if (!student_data)
        {
            cout << "error opening student" << class_name_temp << "file" << endl;
            return;
        }
        if (!fetch_marks_data)
        {
            cout << "error opening marks file" << endl;
            return;
        }

        string line;
        int count = 0;
        double count2 = 0;
        double avg = 0;
        vector<double> per;
        double sum = 0;

        while (getline(student_data, line))
        {
            count++;
        }

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

        for (double i : per)
        {
            sum += i;
            count2++;
        }

        cout << count << endl;
        teacher_avg = to_string(sum / count);

        teacher_data_store << class_teacher_id << '_' << class_teacher_name << '_' << class_name_temp << '_' << subject << '_' << student_no << '_' << teacher_avg << endl;
    }

    class_teacher_data.close();
    teacher_data_store.close();

    remove("class_teacher.txt");
    rename("temp_teacher.txt", "class_teacher.txt");
}

void principal::get_teacher_data()
{
    class_teacher_data.open("class_teacher.txt");

    if (!class_teacher_data)
    {
        cout << "CANNOT OPEN CLASS TEACHER FILE!!!" << endl;
        return;
    }

    string stored_id = "GHPS0012";

    string prin_id;
    cout << "PLEASE ENTER THE PRINCIPAL ID(school name short form then 00 + personal id): ";
    cin >> prin_id;
    cin.ignore();

    bool found = false;

    if (prin_id == stored_id)
    {

        cout << "ID" << "          " << "NAME" << "          " << "CLASS" << "          " << "SUBJECT" << "          " << "NO. OF STUDENTS" << "          " << "TEACHER AVERAGE" << endl;

        while (getline(class_teacher_data, class_teacher_id, '_'))
        {
            getline(class_teacher_data, class_teacher_name, '_');
            getline(class_teacher_data, teach_class_name, '_');
            getline(class_teacher_data, student_no, '_');
            getline(class_teacher_data, teacher_avg, '\n');

            cout << class_teacher_id << "          " << class_teacher_name << "          " << class_name << "          " << subject << "          " << student_no << "          " << teacher_avg << endl;
            found = true;
            break;
        }

        if (!found)
        {
            cout << "CLASS TEACHER NOT FOUND" << endl;
        }
    }
    else
    {
        cout << "INVALID ID" << endl;
        return;
    }

    class_teacher_data.close();
}

void principal ::add_teacher_data()
{

    string prin_id;
    cout << "PLEASE ENTER THE CLASS PRINCIPAL ID: ";
    cin >> prin_id;
    cin.ignore();

    vector<string> arr;

    teacher_data_store.open("class_teacher.txt", ios::app);
    class_teacher_data.open("class_teacher.txt");
    string line;

    if (!student_data)
    {
        cout << "Error opening " << "class_teacher.txt" << " file." << endl;
        return;
    }

    int n;
    cout << "PLEASE ENTER THE NUMBER OF TECAHERS TO BE ADDED: ";
    cin >> n;
    cin.ignore();

    int no_teacher = 0;

    while (getline(class_teacher_data, line))
    {
        no_teacher++;
    }

    if (no_teacher < 12)
    {
        if (no_teacher + n < 12)
        {
            while (getline(class_teacher_data, line))
            {
                int x = line.find('_');
                string teacher_id = line.substr(0, x);
                arr.push_back(teacher_id);
            }
            for (int i = 0; i < n; i++)
            {
                cout << "PLEASE ENTER TEACHER ID(first three letters of name followed by 0 then class{example: AVI02 ==> avi first three letters then 0 then class 2}): ";
                getline(cin, class_teacher_id);
                cin.ignore();

                class_name = getClassFromID(class_teacher_id);

                if (find(arr.begin(), arr.end(), id) != arr.end())
                {
                    cout << "TEACHER ID ALREADY EXISTS!!!" << endl;
                    continue;
                }
                cout << "PLEASE ENTER TECAHER NAME: ";
                getline(cin, class_teacher_name);
                cin.ignore();

                cout << "PLEASE ENTER TECAHER SUBJECT: ";
                getline(cin, subject);
                cin.ignore();

                teacher_data_store << class_teacher_id << '_' << class_teacher_name << '_' << class_name << '_' << subject << '_' << "TBD" << '_' << "TBD" << endl;
            }
        }
        else if (no_teacher + n > 12)
        {
            cout << "CANNOT ADD ANYMORE" << endl;
            cout << "NO. OF TEACHERS REMAINING: " << (12 - no_teacher) << endl;
        }
    }
    else if (no_teacher > 12)
    {
        cout << "NUMBER OF CLASS TEACHER ALREADY REACHED" << endl;
    }

    class_teacher_data.close();
    teacher_data_store.close();
}

void principal ::delete_teacher_data()
{

    string prin_id;
    cout << "PLEASE ENTER THE CLASS PRINCIPAL ID: ";
    cin >> prin_id;

    vector<int> arr;

    class_teacher_data.open("class_teacher.txt");
    temp_teacher.open("temp_teacher.txt");
    string line;

    if (!class_teacher_data)
    {
        cout << "Error opening " << "class_teacher" << " file." << endl;
        return;
    }

    int n;
    cout << "PLEASE ENTER THE NUMBER OF TEACHERS TO BE DELETED: ";
    cin >> n;
    cin.ignore();

    int count = 0;
    while (getline(class_teacher_data, line))
    {
        cout << line << endl;
        int x = line.find('_');
        string teach_id = line.substr(0, x);

        if (count < n)
        {
            cout << "PLEASE ENTER TEACHER ID(first three letters of name followed by 0 then class{example: AVI02 ==> avi first three letters then 0 then class 2}): ";
            getline(cin, class_teacher_id);

            if (class_teacher_id != teach_id)
            {
                temp_teacher << line << endl;
            }
            count++;
        }
        else
        {
            temp_teacher << line << endl;
        }
    }

    class_teacher_data.close();
    temp_teacher.close();

    remove("class_teacher.txt");
    rename("temp_teacher.txt", "class_teacher.txt");
}

void principal::update_teacher_data()
{
    string prin_id;
    cout << "PLEASE ENTER THE CLASS PRINCIPAL ID: ";
    cin >> prin_id;
    cin.ignore();

    class_teacher_data.open("class_teacher.txt");
    temp_teacher.open("temp_teacher.txt");
    string line;

    if (!class_teacher_data)
    {
        cout << "Error opening class_teacher file." << endl;
        return;
    }

    int n;
    cout << "PLEASE ENTER THE NUMBER OF TEACHERS TO BE UPDATED: ";
    cin >> n;
    cin.ignore();

    // one entry per teacher: id -> list of (field, new value)
    struct TeacherUpdate
    {
        string id;
        vector<pair<string, string>> fields;
    };
    vector<TeacherUpdate> updates;

    // --- collect all IDs and their new field values BEFORE touching the file ---
    for (int i = 0; i < n; i++)
    {
        TeacherUpdate u;
        cout << "PLEASE ENTER TEACHER ID (e.g. AVI02): ";
        getline(cin, u.id);

        cout << "PLEASE ENTER THE FIELDS TO BE UPDATED "
             << "(comma separated, e.g. name, subject, avgerage): ";
        string sub;
        getline(cin, sub);

        // split sub on commas, trimming spaces
        vector<string> fieldNames;
        size_t start = 0;
        while (start <= sub.size())
        {
            size_t comma = sub.find(',', start);
            string field = (comma == string::npos)
                               ? sub.substr(start)
                               : sub.substr(start, comma - start);

            size_t a = field.find_first_not_of(' ');
            size_t b = field.find_last_not_of(' ');
            if (a != string::npos)
                field = field.substr(a, b - a + 1);
            else
                field = "";

            if (!field.empty())
                fieldNames.push_back(field);

            if (comma == string::npos)
                break;
            start = comma + 1;
        }

        // prompt for the new value of each requested field, store it
        for (const string &f : fieldNames)
        {
            string newVal;
            if (f == "name")
                cout << "NEW NAME: ";
            else if (f == "class name")
                cout << "NEW CLASS NAME: ";
            else if (f == "subject")
                cout << "NEW SUBJECT: ";
            else if (f == "number of students")
                cout << "NEW NUMBER OF STUDENTS: ";
            else if (f == "avgerage")
                cout << "NEW TEACHER AVERAGE: ";
            else
            {
                cout << "INVALID FIELD: " << f << endl;
                continue;
            }
            getline(cin, newVal);
            u.fields.push_back({f, newVal});
        }

        updates.push_back(u);
    }

    // --- single pass over the file: apply updates by ID match ---
    while (getline(class_teacher_data, line))
    {
        int p1 = line.find('_');
        string teach_id = line.substr(0, p1);

        // look for a matching update request
        TeacherUpdate *match = nullptr;
        for (auto &u : updates)
        {
            if (u.id == teach_id)
            {
                match = &u;
                break;
            }
        }

        if (!match)
        {
            temp_teacher << line << endl;
            continue;
        }

        int p2 = line.find('_', p1 + 1);
        int p3 = line.find('_', p2 + 1);
        int p4 = line.find('_', p3 + 1);
        int p5 = line.find('_', p4 + 1);

        class_teacher_name = line.substr(p1 + 1, p2 - p1 - 1);
        teach_class_name = line.substr(p2 + 1, p3 - p2 - 1);
        subject = line.substr(p3 + 1, p4 - p3 - 1);
        student_no = line.substr(p4 + 1, p5 - p4 - 1);
        teacher_avg = line.substr(p5 + 1);

        for (const auto &fv : match->fields)
        {
            const string &f = fv.first;
            const string &newVal = fv.second;

            if (f == "name")
                class_teacher_name = newVal;
            else if (f == "class name")
                teach_class_name = newVal;
            else if (f == "subject")
                subject = newVal;
            else if (f == "number of students")
                student_no = newVal;
            else if (f == "average")
                teacher_avg = newVal;
        }

        temp_teacher << teach_id << "_" << class_teacher_name << "_"
                     << teach_class_name << "_" << subject << "_"
                     << student_no << "_" << teacher_avg << endl;
    }

    class_teacher_data.close();
    temp_teacher.close();

    remove("class_teacher.txt");
    rename("temp_teacher.txt", "class_teacher.txt");
}

void principal ::search_teacher_data()
{
    string prin_id;
    cout << "PLEASE ENTER THE CLASS PRINCIPAL ID: ";
    cin >> prin_id;
    cin.ignore();

    class_teacher_data.open("class_teacher.txt");
    temp_teacher.open("temp_teacher.txt");
    string line;

    if (!student_data)
    {
        cout << "Error opening " << "class_teacher" << " file." << endl;
        return;
    }

    string teach_id;
    cout << "PLEASE ENTER THE TEACHER ID TO BE SEARCHED(first three letters of name followed by 0 then class{example: AVI02 ==> avi first three letters then 0 then class 2}): ";
    cin >> teach_id;
    cin.ignore();

    bool found = false;

    while (getline(class_teacher_data, class_teacher_id, '_'))
    {
        getline(class_teacher_data, class_teacher_name, '_');
        getline(class_teacher_data, teach_class_name, '_');
        getline(class_teacher_data, subject, '_');
        getline(class_teacher_data, student_no, '_');
        getline(class_teacher_data, teacher_avg, '\n');

        if (class_teacher_id == teach_id)
        {
            cout << "ID" << "          " << "NAME" << "          " << "CLASS" << "          " << "SUBJECT" << "          " << "NO. OF STUDENT" << "          " << "TEACHER AVERAGE" << endl;
            cout << class_teacher_id << "          " << class_teacher_name << "          " << teach_class_name << "          " << subject << "          " << student_no << "          " << teacher_avg << endl;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "TEACHER NOT FOUND" << endl;
    }
    class_teacher_data.close();
}