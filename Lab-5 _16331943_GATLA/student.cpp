#include "student.h"

// Function to check if a string contains only digits using a pointer
bool isNumeric(const string* strPtr) {
    if (strPtr == nullptr) return false;
    for (const char* cPtr = strPtr->c_str(); *cPtr != '\0'; ++cPtr) {
        if (!isdigit(*cPtr)) return false;
    }
    return true;
}

// Function to trim whitespace from a string using pointers
void trimWhitespace(string* strPtr) {
    if (strPtr == nullptr || strPtr->empty()) return;

    size_t first = strPtr->find_first_not_of(" \t\n\r\f\v");
    if (first == string::npos) {
        strPtr->clear();
        return;
    }

    size_t last = strPtr->find_last_not_of(" \t\n\r\f\v");
    *strPtr = strPtr->substr(first, last - first + 1);
}

// Function to calculate score, percentage, and grade
void calculateGrade(studentInfo* student, const string* correctAnswers) {
    student->score = 0;
    const char* studentAns = student->answers->c_str();
    const char* correctAns = correctAnswers->c_str();

    for (int i = 0; i < 20; ++i) {
        if (i >= student->answers->length() || i >= correctAnswers->length()) continue;
        if (studentAns[i] == correctAns[i]) {
            student->score += 2;
        }
        else if (studentAns[i] != ' ') {
            student->score += 1;
        }
    }

    student->percentage = static_cast<double>(student->score) / 40.0 * 100.0;

    if (student->percentage >= 90.0) student->grade = 'A';
    else if (student->percentage >= 80.0) student->grade = 'B';
    else if (student->percentage >= 70.0) student->grade = 'C';
    else if (student->percentage >= 60.0) student->grade = 'D';
    else student->grade = 'F';
}