#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>

using namespace std;

// Struct to hold student data
struct studentInfo {
    string* studentID;
    string* answers;
    int score;
    double percentage;
    char grade;
};

// Function declarations
bool isNumeric(const string* strPtr);
void trimWhitespace(string* strPtr);
void calculateGrade(studentInfo* student, const string* correctAnswers);

#endif // STUDENT_H