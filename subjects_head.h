#include <fstream>

using namespace std;

class Subject
{
protected:
    string mathsM, englishM, scienceM, social_scienceM, hindiM, percentage,class_name_temp,m_id;
    ifstream fetch_marks_data;

public:
    void get_marks();
};

class Student : virtual protected Subject
{
protected:
    string name, id, class_name, class_name_temp;
    ifstream student_data;

public:
    void get_student();
};

class class_teacher : virtual public Student, virtual public Subject
{

protected:
    string class_teacher_name, class_teacher_id, subject, teach_class_name,student_no, teacher_avg;;
    ifstream class_teacher_data;
    ofstream student_marks_data, student_data_up, temp_students, temp_marks, teacher_data_store;;

public:
    bool calc_no_avg_teach(const string &target_id);
    void get_class_teacher_data();

    void get_student_data();

    void add_student();
    void delete_student();
    void update_student();
    void search_student();

    void get_student_marks();
};

class principal : public class_teacher, virtual public Student
{
    ofstream temp_teacher;

public:
    void get_teacher_data();

    void calc_no_avg_princi();

    void add_teacher_data();
    void delete_teacher_data();
    void update_teacher_data();
    void search_teacher_data();
};