#include <iostream>
#include <string>
#include <queue>
using namespace std;

// ---------------- STUDENT LINKED LIST ----------------
struct Student {
    int id;
    string name;
    string course;
    int roomNo;
    Student* next;

    Student(int i, string n, string c, int r) {
        id = i;
        name = n;
        course = c;
        roomNo = r;
        next = nullptr;
    }
};

class HostelManagement {
private:
    Student* head;
    static const int TOTAL_ROOMS = 10;
    int rooms[TOTAL_ROOMS + 1]; // 0 means vacant, 1 means occupied

    queue<string> waitingList;
    queue<string> complaints;

public:
    HostelManagement() {
        head = nullptr;

        for (int i = 1; i <= TOTAL_ROOMS; i++) {
            rooms[i] = 0;
        }
    }

    // Add a student
    void addStudent() {
        int id, roomNo;
        string name, course;

        cout << "\nEnter Student ID: ";
        cin >> id;
        cin.ignore();

        if (searchStudent(id) != nullptr) {
            cout << "Student ID already exists!\n";
            return;
        }

        cout << "Enter Student Name: ";
        getline(cin, name);

        cout << "Enter Course: ";
        getline(cin, course);

        cout << "Enter Room Number (1-10): ";
        cin >> roomNo;

        if (roomNo < 1 || roomNo > TOTAL_ROOMS) {
            cout << "Invalid room number!\n";
            return;
        }

        if (rooms[roomNo] == 1) {
            cout << "Room is already occupied!\n";
            return;
        }

        Student* newStudent = new Student(id, name, course, roomNo);
        newStudent->next = head;
        head = newStudent;

        rooms[roomNo] = 1;

        cout << "Student added and room allocated successfully!\n";
    }

    // Search student by ID
    Student* searchStudent(int id) {
        Student* current = head;

        while (current != nullptr) {
            if (current->id == id) {
                return current;
            }
            current = current->next;
        }

        return nullptr;
    }

    void searchStudentMenu() {
        int id;
        cout << "\nEnter Student ID to search: ";
        cin >> id;

        Student* student = searchStudent(id);

        if (student == nullptr) {
            cout << "Student not found!\n";
        } else {
            cout << "\nStudent Found\n";
            cout << "ID: " << student->id << "\n";
            cout << "Name: " << student->name << "\n";
            cout << "Course: " << student->course << "\n";
            cout << "Room Number: " << student->roomNo << "\n";
        }
    }

    // Display all students
    void displayStudents() {
        if (head == nullptr) {
            cout << "\nNo student records available.\n";
            return;
        }

        Student* current = head;

        cout << "\n========== STUDENT RECORDS ==========\n";

        while (current != nullptr) {
            cout << "ID: " << current->id
                 << " | Name: " << current->name
                 << " | Course: " << current->course
                 << " | Room: " << current->roomNo << "\n";

            current = current->next;
        }
    }

    // Display room status
    void displayRooms() {
        cout << "\n========== ROOM STATUS ==========\n";

        for (int i = 1; i <= TOTAL_ROOMS; i++) {
            cout << "Room " << i << ": "
                 << (rooms[i] == 0 ? "Vacant" : "Occupied") << "\n";
        }
    }

    // Student checkout
    void checkoutStudent() {
        int id;
        cout << "\nEnter Student ID for checkout: ";
        cin >> id;

        Student* current = head;
        Student* previous = nullptr;

        while (current != nullptr && current->id != id) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Student not found!\n";
            return;
        }

        rooms[current->roomNo] = 0;

        if (previous == nullptr) {
            head = current->next;
        } else {
            previous->next = current->next;
        }

        delete current;

        cout << "Checkout successful. Room is now vacant.\n";

        // Allocate room to the first waiting student
        if (!waitingList.empty()) {
            cout << "Waiting list student: " << waitingList.front()
                 << " can now be allocated a room.\n";
            waitingList.pop();
        }
    }

    // Add student to waiting list
    void addToWaitingList() {
        string name;
        cin.ignore();

        cout << "\nEnter Student Name: ";
        getline(cin, name);

        waitingList.push(name);

        cout << "Student added to waiting list.\n";
    }

    // Display waiting list
    void displayWaitingList() {
        if (waitingList.empty()) {
            cout << "\nWaiting list is empty.\n";
            return;
        }

        queue<string> temp = waitingList;

        cout << "\n========== WAITING LIST ==========\n";

        while (!temp.empty()) {
            cout << temp.front() << "\n";
            temp.pop();
        }
    }

    // Add complaint
    void addComplaint() {
        string complaint;
        cin.ignore();

        cout << "\nEnter complaint: ";
        getline(cin, complaint);

        complaints.push(complaint);

        cout << "Complaint registered successfully.\n";
    }

    // Resolve first complaint
    void resolveComplaint() {
        if (complaints.empty()) {
            cout << "\nNo complaints to resolve.\n";
            return;
        }

        cout << "\nResolved Complaint: " << complaints.front() << "\n";
        complaints.pop();
    }

    // Display complaints
    void displayComplaints() {
        if (complaints.empty()) {
            cout << "\nNo pending complaints.\n";
            return;
        }

        queue<string> temp = complaints;

        cout << "\n========== PENDING COMPLAINTS ==========\n";

        while (!temp.empty()) {
            cout << temp.front() << "\n";
            temp.pop();
        }
    }

    // Main menu
    void menu() {
        int choice;

        do {
            cout << "\n\n========================================\n";
            cout << "       HOSTEL MANAGEMENT SYSTEM\n";
            cout << "========================================\n";
            cout << "1. Add Student\n";
            cout << "2. Search Student\n";
            cout << "3. Display All Students\n";
            cout << "4. Display Room Status\n";
            cout << "5. Student Checkout\n";
            cout << "6. Add to Waiting List\n";
            cout << "7. Display Waiting List\n";
            cout << "8. Register Complaint\n";
            cout << "9. Resolve Complaint\n";
            cout << "10. Display Complaints\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: addStudent(); break;
                case 2: searchStudentMenu(); break;
                case 3: displayStudents(); break;
                case 4: displayRooms(); break;
                case 5: checkoutStudent(); break;
                case 6: addToWaitingList(); break;
                case 7: displayWaitingList(); break;
                case 8: addComplaint(); break;
                case 9: resolveComplaint(); break;
                case 10: displayComplaints(); break;
                case 0: cout << "Exiting program...\n"; break;
                default: cout << "Invalid choice!\n";
            }

        } while (choice != 0);
    }
};

int main() {
    HostelManagement system;
    system.menu();

    return 0;
}
