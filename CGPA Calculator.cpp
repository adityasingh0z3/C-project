#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <numeric>

using namespace std;

// Structure to store course information
struct Course {
    string name;
    char grade;
    int creditHours;
    double gradePoints;
};

// Function to convert letter grade to grade points
double gradeToPoints(char grade) {
    switch(toupper(grade)) {
        case 'A': return 4.0;
        case 'B': return 3.0;
        case 'C': return 2.0;
        case 'D': return 1.0;
        case 'F': return 0.0;
        default: return -1.0; // Invalid grade
    }
}

// Function to calculate GPA for a semester
double calculateGPA(const vector<Course>& courses) {
    double totalGradePoints = 0.0;
    int totalCredits = 0;
    
    for(const auto& course : courses) {
        totalGradePoints += course.gradePoints * course.creditHours;
        totalCredits += course.creditHours;
    }
    
    return (totalCredits == 0) ? 0.0 : totalGradePoints / totalCredits;
}

int main() {
    vector<Course> currentSemester;
    vector<double> allSemesterGPAs;
    
    cout << "===== GPA/CGPA Calculator =====" << endl;
    
    while(true) {
        cout << "\n=== Semester " << (allSemesterGPAs.size() + 1) << " Data Entry ===" << endl;
        currentSemester.clear();
        
        int numCourses;
        cout << "Enter number of courses for this semester: ";
        cin >> numCourses;
        
        // Input validation
        while(numCourses <= 0) {
            cout << "Please enter a positive number: ";
            cin >> numCourses;
        }
        
        cin.ignore(); // Clear newline from buffer
        
        for(int i = 0; i < numCourses; i++) {
            Course course;
            
            cout << "\nCourse " << (i + 1) << ":" << endl;
            
            // Course name
            cout << "  Course name: ";
            getline(cin, course.name);
            
            // Grade input with validation
            while(true) {
                cout << "  Grade (A/B/C/D/F): ";
                cin >> course.grade;
                course.grade = toupper(course.grade);
                
                if(gradeToPoints(course.grade) >= 0) break;
                cout << "Invalid grade! Please enter A, B, C, D, or F.\n";
            }
            
            // Credit hours with validation
            while(true) {
                cout << "  Credit hours: ";
                cin >> course.creditHours;
                
                if(course.creditHours > 0) break;
                cout << "Credit hours must be positive! Please try again.\n";
            }
            
            course.gradePoints = gradeToPoints(course.grade);
            currentSemester.push_back(course);
            cin.ignore(); // Clear newline from buffer
        }
        
        // Calculate semester GPA
        double semesterGPA = calculateGPA(currentSemester);
        allSemesterGPAs.push_back(semesterGPA);
        
        // Display current semester results
        cout << "\n=== Semester Results ===" << endl;
        cout << left << setw(25) << "Course" 
             << setw(10) << "Grade" 
             << setw(15) << "Credit Hours" 
             << setw(15) << "Grade Points" << endl;
        cout << string(65, '-') << endl;
        
        for(const auto& course : currentSemester) {
            cout << left << setw(25) << course.name 
                 << setw(10) << course.grade 
                 << setw(15) << course.creditHours 
                 << setw(15) << fixed << setprecision(2) 
                 << (course.gradePoints * course.creditHours) << endl;
        }
        
        cout << "\nSemester GPA: " << fixed << setprecision(2) << semesterGPA << endl;
        
        // Ask if user wants to add another semester
        char choice;
        cout << "\nAdd another semester? (Y/N): ";
        cin >> choice;
        
        if(toupper(choice) != 'Y') break;
        cin.ignore(); // Clear newline from buffer
    }
    
    // Calculate and display CGPA if there are multiple semesters
    if(allSemesterGPAs.size() > 1) {
        double totalGPA = accumulate(allSemesterGPAs.begin(), allSemesterGPAs.end(), 0.0);
        double cgpa = totalGPA / allSemesterGPAs.size();
        
        cout << "\n=== Cumulative Results ===" << endl;
        cout << "Number of semesters: " << allSemesterGPAs.size() << endl;
        cout << "Cumulative GPA (CGPA): " << fixed << setprecision(2) << cgpa << endl;
    }
    
    return 0;
}
