# 🏫 School Management System

A comprehensive **School Management System** developed in **C++** using **Object-Oriented Programming (OOP)** principles. The application provides separate modules for **Principal**, **Teacher**, and **Student**, allowing efficient management of school records through a console-based interface.

---

## 🚀 Features

### 👨‍💼 Principal Module

* View all class teachers
* Add new teachers
* Update teacher information
* Delete teacher records
* Search teachers by ID
* View all students
* Search students
* Automatically calculate class strength and average performance

### 👩‍🏫 Teacher Module

* View personal information
* View students of assigned class
* Add students
* Update student information
* Delete student records
* Search students
* View student marks
* Automatically calculate percentages

### 🎓 Student Module

* View personal information
* View subject-wise marks
* View overall percentage

---

## 💻 Technologies Used

* **Language:** C++
* **Concepts:**

  * Object-Oriented Programming
  * Inheritance
  * Virtual Inheritance
  * Encapsulation
  * File Handling
  * STL (`vector`, `algorithm`)
* **Storage:** Text Files (`.txt`)

---

## 📂 Project Structure

```text
School-Management-System/
│
├── main.cpp
├── principal.cpp
├── class_teacher.cpp
├── student.cpp
├── subject.cpp
│
├── subjects_head.h
│
├── class_teacher.txt
├── student1.txt
├── student2.txt
├── ...
├── student12.txt
├── marks1.txt
├── marks2.txt
├── ...
├── marks12.txt
│
└── README.md
```

---

## 🏗️ Object-Oriented Design

The project is designed using inheritance to represent different user roles.

```text
Subject
   │
   ▼
Student
   │
   ▼
Class Teacher
   │
   ▼
Principal
```

Each class is responsible for its own operations while sharing common functionality through inheritance.

---

## ✨ Functionalities

### Student Management

* Add Student
* Delete Student
* Update Student
* Search Student
* Display Student List
* Display Student Marks

### Teacher Management

* Add Teacher
* Delete Teacher
* Update Teacher
* Search Teacher
* Display Teacher Information

### Academic Management

* Store marks for five subjects
* Automatic percentage calculation
* Automatic class average calculation
* Automatic student count for each class

---

## 📁 Data Storage

The project stores data using text files.

### Student Records

```text
StudentID_Name_Class
```

Example

```text
AVI02_Aviraj_2
```

### Marks Records

```text
StudentID_Maths_English_Science_SocialScience_Hindi_Percentage
```

Example

```text
AVI02_95_90_91_93_96_93
```

### Teacher Records

```text
TeacherID_Name_Class_Subject_NumberOfStudents_ClassAverage
```

Example

```text
AVI02_Aviraj_2_Mathematics_42_88.76
```

---

## ▶️ How to Run

### Clone the repository

```bash
git clone https://github.com/Avirajengg/School-Management-System.git
```

### Compile

```bash
g++ *.cpp -o SchoolManagement
```

### Run

```bash
./SchoolManagement
```

On Windows:

```bash
SchoolManagement.exe
```

---

## 📸 Screenshots

You can add screenshots here showing:

* Main Menu
* Principal Module
* Teacher Module
* Student Module
* CRUD Operations
* Search Results

---

## 🔮 Future Improvements

* SQLite/MySQL Database Integration
* Graphical User Interface (Qt)
* Login Authentication with Passwords
* Password Encryption
* Attendance Management
* Fee Management
* Report Card Generation (PDF)
* Timetable Management
* Subject-wise Analytics
* CSV/PDF Export

---

## 🎯 Learning Outcomes

This project helped strengthen my understanding of:

* Object-Oriented Programming
* C++ File Handling
* Data Structures using STL
* Software Design
* Modular Programming
* Console Application Development
* CRUD Operations
* Real-world Project Organization

---

## 👨‍💻 Author

**Aviraj Ahlawat**

Mechatronics Engineering Student

Passionate about Robotics, AI, Embedded Systems, and Software Development.

---

## ⭐ Support

If you found this project helpful, consider giving the repository a ⭐ on GitHub.
