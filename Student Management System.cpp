#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

class Student {
private:
    int studentID;
    string name;
    int age;
    string course;

public:
    // Constructor
    Student(int id, string n, int a, string c) {
        studentID = id;
        name = n;
        age = a;
        course = c;
    }

    // Getters
    int getStudentID() const { return studentID; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getCourse() const { return course; }

    // Display student details
    void displayStudent() const {
        cout << "ID: " << studentID << " | Name: " << name << " | Age: " << age << " | Course: " << course << endl;
    }

    // Save to file
    void saveToFile(ofstream &outfile) const {
        outfile << studentID << "," << name << "," << age << "," << course << endl;
    }

    // Load from file
    static Student loadFromFile(ifstream &infile) {
        int id, age;
        string name, course;
        infile >> id;
        infile.ignore();
        getline(infile, name, ',');
        infile >> age;
        infile.ignore();
        getline(infile, course);
        return Student(id, name, age, course);
    }
};

// Function to check if student ID is unique
bool isStudentIDUnique(vector<Student> &students, int id) {
    for (const auto &s : students) {
        if (s.getStudentID() == id) {
            return false;
        }
    }
    return true;
}

// Function to find student by ID
Student* findStudent(vector<Student> &students, int id) {
    for (auto &s : students) {
        if (s.getStudentID() == id) {
            return &s;
        }
    }
    return nullptr;
}

// Save students to file
void saveStudentsToFile(vector<Student> &students) {
    ofstream outfile("students.txt", ios::trunc);
    for (const auto &s : students) {
        s.saveToFile(outfile);
    }
    outfile.close();
}

// Load students from file
void loadStudentsFromFile(vector<Student> &students) {
    ifstream infile("students.txt");
    if (!infile) return;

    while (!infile.eof()) {
        int id, age;
        string name, course;

        infile >> id;
        infile.ignore();
        if (getline(infile, name, ',') && infile >> age && infile.ignore() && getline(infile, course)) {
            students.push_back(Student(id, name, age, course));
        }
    }
    infile.close();
}

// Function to delete a student by ID
void deleteStudent(vector<Student> &students, int id) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->getStudentID() == id) {
            students.erase(it);
            cout << "Student record deleted successfully.\n";
            saveStudentsToFile(students);
            return;
        }
    }
    cout << "Student not found!\n";
}

int main() {
    vector<Student> students;
    loadStudentsFromFile(students);

    int choice;
    while (true) {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search Student by ID\n";
        cout << "4. Update Student Details\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int id, age;
            string name, course;
            cout << "Enter Student ID: ";
            cin >> id;
            cin.ignore();
            
            if (!isStudentIDUnique(students, id)) {
                cout << "Error! Student ID already exists.\n";
                continue;
            }

            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Age: ";
            cin >> age;
            cin.ignore();
            cout << "Enter Course: ";
            getline(cin, course);

            students.push_back(Student(id, name, age, course));
            saveStudentsToFile(students);
            cout << "Student added successfully!\n";

        } else if (choice == 2) {
            cout << "\n===== List of Students =====\n";
            for (const auto &s : students) {
                s.displayStudent();
            }

        } else if (choice == 3) {
            int id;
            cout << "Enter Student ID to search: ";
            cin >> id;
            Student* student = findStudent(students, id);

            if (student) {
                student->displayStudent();
            } else {
                cout << "Student not found!\n";
            }

        } else if (choice == 4) {
            int id;
            cout << "Enter Student ID to update: ";
            cin >> id;
            Student* student = findStudent(students, id);

            if (student) {
                string newName, newCourse;
                int newAge;
                cout << "Enter New Name: ";
                cin.ignore();
                getline(cin, newName);
                cout << "Enter New Age: ";
                cin >> newAge;
                cin.ignore();
                cout << "Enter New Course: ";
                getline(cin, newCourse);

                *student = Student(id, newName, newAge, newCourse);
                saveStudentsToFile(students);
                cout << "Student details updated successfully!\n";
            } else {
                cout << "Student not found!\n";
            }

        } else if (choice == 5) {
            int id;
            cout << "Enter Student ID to delete: ";
            cin >> id;
            deleteStudent(students, id);

        } else if (choice == 6) {
            cout << "Exiting Student Management System. Thank you!\n";
            break;
        } else {
            cout << "Invalid choice! Try again.\n";
        }
    }
    return 0;
}
