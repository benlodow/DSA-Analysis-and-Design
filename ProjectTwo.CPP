#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

class Course {
public:
    std::string courseNumber;
    std::string courseTitle;
    std::vector<std::string> prerequisites;

    Course(const std::string& number, const std::string& title, const std::vector<std::string>& prereqs)
        : courseNumber(number), courseTitle(title), prerequisites(prereqs) {}
};

class TreeNode {
public:
    Course data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const Course& course) : data(course), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    TreeNode* root;

    BinaryTree() : root(nullptr) {}
};

Course createCourseObject(const std::string& line) {
    std::istringstream iss(line);
    std::string courseNumber, courseTitle, prerequisite;

    getline(iss, courseNumber, ',');
    getline(iss, courseTitle, ',');

    std::vector<std::string> prerequisites;
    while (getline(iss, prerequisite, ',')) {
        prerequisites.push_back(prerequisite);
    }

    return Course(courseNumber, courseTitle, prerequisites);
}

void insertCourse(TreeNode*& root, const Course& course) {
    if (root == nullptr) {
        root = new TreeNode(course);
    } else {
        if (course.courseNumber < root->data.courseNumber) {
            insertCourse(root->left, course);
        } else if (course.courseNumber > root->data.courseNumber) {
            insertCourse(root->right, course);
        } else {
            std::cout << "Duplicate course number: " << course.courseNumber << ". Not allowed.\n";
        }
    }
}

void loadDataStructure(const std::string& fileName, BinaryTree& courses) {
    std::ifstream file(fileName);
    std::string line;

    while (getline(file, line)) {
        Course course = createCourseObject(line);
        insertCourse(courses.root, course);
    }
}

void printCourseList(TreeNode* root) {
    if (root != nullptr) {
        printCourseList(root->left);
        std::cout << root->data.courseNumber << " - " << root->data.courseTitle << std::endl;
        printCourseList(root->right);
    }
}

void printCourseInformation(TreeNode* root, const std::string& courseNumber) {
    if (root == nullptr) {
        std::cout << "Course not found with number: " << courseNumber << std::endl;
        return;
    }

    if (courseNumber < root->data.courseNumber) {
        printCourseInformation(root->left, courseNumber);
    } else if (courseNumber > root->data.courseNumber) {
        printCourseInformation(root->right, courseNumber);
    } else {
        // Course found, print its details
        std::cout << "Course Number: " << root->data.courseNumber << std::endl;
        std::cout << "Course Title: " << root->data.courseTitle << std::endl;
        std::cout << "Prerequisites: ";
        for (const auto& prereq : root->data.prerequisites) {
            std::cout << prereq << " ";
        }
        std::cout << std::endl;
    }
}

void displayMenu(BinaryTree& courses) {
    int choice;
    while (true) {
        std::cout << "Menu\n";
        std::cout << "1. Load Data Structure\n";
        std::cout << "2. Print Course List\n";
        std::cout << "3. Print Course Information\n";
        std::cout << "9. Exit\n";

        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // Load Data Structure
                std::string fileName;
                std::cout << "Enter file name: \n";
                std::cin >> fileName;
                loadDataStructure(fileName, courses);
                break;
            }
            case 2: {
                // Print Course List
                printCourseList(courses.root);
                break;
            }
            case 3: {
                // Print Course Information
                std::string courseNumber;
                std::cout << "Enter course number: ";
                std::cin >> courseNumber;
                printCourseInformation(courses.root, courseNumber);
                break;
            }
            case 9: {
                // Exit
                std::cout << "Good-bye.\n";
                return;
            }
            default: {
                std::cout << "Invalid choice. Please try again.\n";
            }
        }
    }
}

int main() {
    BinaryTree courses;
    displayMenu(courses);

    return 0;
}