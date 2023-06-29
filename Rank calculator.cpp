#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

// Structure to hold student information
struct Student {
    std::string name;
    int biologyMarks;
    int physicsMarks;
    int chemistryMarks;
    int totalMarks;
};

// Function to calculate the total marks of a student
int calculateTotalMarks(const Student& student) {
    return student.biologyMarks + student.physicsMarks + student.chemistryMarks;
}

// Function to compare two students based on their total marks
bool compareStudentsByTotalMarks(const Student& student1, const Student& student2) {
    return student1.totalMarks > student2.totalMarks;
}

// Function to rank students based on total marks
void rankStudents(std::vector<Student>& students) {
    std::sort(students.begin(), students.end(), compareStudentsByTotalMarks);
    int rank = 1;
    for (auto& student : students) {
        std::cout << "Rank: " << rank << ", Name: " << student.name << ", Total Marks: " << student.totalMarks << std::endl;
        rank++;
    }
}

// Function to read student data from a file
std::vector<Student> readStudentData(const std::string& filename) {
    std::vector<Student> students;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string name;
            int biologyMarks, physicsMarks, chemistryMarks;
            if (iss >> name >> biologyMarks >> physicsMarks >> chemistryMarks) {
                Student student;
                student.name = name;
                student.biologyMarks = biologyMarks;
                student.physicsMarks = physicsMarks;
                student.chemistryMarks = chemistryMarks;
                student.totalMarks = calculateTotalMarks(student);
                students.push_back(student);
            }
        }
        file.close();
    }
    return students;
}

// Function to write student ranks to a file
void writeStudentRanks(const std::vector<Student>& students, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        int rank = 1;
        for (const auto& student : students) {
            file << "Rank: " << rank << ", Name: " << student.name << ", Total Marks: " << student.totalMarks << std::endl;
            rank++;
        }
        file.close();
    }
}

int main() {
    std::vector<Student> students = readStudentData("student_data.txt");
    rankStudents(students);
    writeStudentRanks(students, "student_ranks.txt");

    return 0;
}