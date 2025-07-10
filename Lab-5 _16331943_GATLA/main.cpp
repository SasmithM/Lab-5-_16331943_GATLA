#include "student.h"

int main() {
    ifstream* inputFilePtr = new ifstream("C:\\Users\\User\\source\\repos\\LAB 5\\student.txt");
    ofstream* errorFilePtr = new ofstream("error.txt");
    ofstream* reportFilePtr = new ofstream("report.txt");

    if (!inputFilePtr->is_open()) {
        cerr << "Error: Could not open student.txt" << endl;
        delete inputFilePtr;
        delete errorFilePtr;
        delete reportFilePtr;
        return 1;
    }

    if (!errorFilePtr->is_open()) {
        cerr << "Error: Could not open error.txt" << endl;
        inputFilePtr->close();
        delete inputFilePtr;
        delete errorFilePtr;
        delete reportFilePtr;
        return 1;
    }

    if (!reportFilePtr->is_open()) {
        cerr << "Error: Could not open report.txt" << endl;
        inputFilePtr->close();
        errorFilePtr->close();
        delete inputFilePtr;
        delete errorFilePtr;
        delete reportFilePtr;
        return 1;
    }

    // Declare all variables here, before any goto
    string* correctAnswersPtr = new string();
    vector<studentInfo*> students;
    string* linePtr = new string();

    if (!getline(*inputFilePtr, *correctAnswersPtr)) {
        cerr << "Error: Could not read correct answers" << endl;
        goto cleanup;
    }
    trimWhitespace(correctAnswersPtr);

    while (getline(*inputFilePtr, *linePtr)) {
        size_t spacePos = linePtr->find(' ');
        if (spacePos == string::npos) {
            *errorFilePtr << "Rejected Record: Invalid format in line: " << *linePtr << endl;
            continue;
        }

        string* studentIdStrPtr = new string(linePtr->substr(0, spacePos));
        string* studentAnswersPtr = new string(linePtr->substr(spacePos + 1));

        trimWhitespace(studentIdStrPtr);
        trimWhitespace(studentAnswersPtr);

        if (!isNumeric(studentIdStrPtr) || studentAnswersPtr->length() != 20) {
            *errorFilePtr << "Rejected Record: Invalid Student ID or answer length in line: " << *linePtr << endl;
            delete studentIdStrPtr;
            delete studentAnswersPtr;
            continue;
        }

        studentInfo* student = new studentInfo();
        student->studentID = studentIdStrPtr;
        student->answers = studentAnswersPtr;
        calculateGrade(student, correctAnswersPtr);
        students.push_back(student);
    }

    // Write report header
    *reportFilePtr << setw(10) << left << "STUD ID"
        << setw(25) << "ANSWERS"
        << setw(10) << "SCORE/40"
        << setw(10) << "PERCENT"
        << setw(5) << "GRADE" << endl;

    // Output results to console and write to file
    cout << "\nQuiz Grading Report:\n";
    cout << "--------------------\n";
    cout << setw(10) << left << "STUD ID"
        << setw(25) << "ANSWERS"
        << setw(10) << "SCORE/40"
        << setw(10) << "PERCENT"
        << setw(5) << "GRADE" << endl;
    cout << "----------------------------------------------------------\n";

    for (auto student : students) {
        cout << setw(10) << left << *student->studentID
            << setw(25) << *student->answers
            << setw(10) << student->score
            << fixed << setprecision(2) << setw(10) << student->percentage
            << setw(5) << student->grade << endl;

        *reportFilePtr << setw(10) << left << *student->studentID
            << setw(25) << *student->answers
            << setw(10) << student->score
            << fixed << setprecision(2) << setw(10) << student->percentage
            << setw(5) << student->grade << endl;
    }

cleanup:
    // Clean up memory
    for (auto student : students) {
        delete student->studentID;
        delete student->answers;
        delete student;
    }

    delete correctAnswersPtr;
    delete linePtr;

    inputFilePtr->close();
    errorFilePtr->close();
    reportFilePtr->close();

    delete inputFilePtr;
    delete errorFilePtr;
    delete reportFilePtr;

    cout << "\nGrading complete. Results written to report.txt. Errors written to error.txt.\n";

    return 0;
}