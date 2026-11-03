#include "SchoolSystem.h"
#include <iostream>
#include <limits>
#include <algorithm>
using namespace std;

// Constructor initializes all list pointers as empty.
SchoolSystem::SchoolSystem()
    : studentHead(nullptr), scheduleHead(nullptr), currentPeriod(nullptr),
      announcementHead(nullptr), announcementTail(nullptr),
      currentAnnouncement(nullptr) {}

// Destructor releases dynamically allocated nodes from all three lists.
SchoolSystem::~SchoolSystem() {
    while (studentHead != nullptr) {
        StudentNode* temp = studentHead;
        studentHead = studentHead->next;
        delete temp;
    }

    if (scheduleHead != nullptr) {
        ScheduleNode* current = scheduleHead->next;
        while (current != scheduleHead) {
            ScheduleNode* temp = current;
            current = current->next;
            delete temp;
        }
        delete scheduleHead;
    }

    while (announcementHead != nullptr) {
        AnnouncementNode* temp = announcementHead;
        announcementHead = announcementHead->next;
        delete temp;
    }
}

// ---------------- STUDENT MANAGEMENT: SINGLY LINKED LIST ----------------

void SchoolSystem::addStudent() {
    int id, age;
    string name, grade;

    cout << "Enter student ID: ";
    cin >> id;

    // Check that the ID is not already in use.
    StudentNode* check = studentHead;
    while (check != nullptr) {
        if (check->id == id) {
            cout << "A student with this ID already exists.\n";
            return;
        }
        check = check->next;
    }

    cout << "Enter student name: ";
    getline(cin >> ws, name);
    cout << "Enter age: ";
    cin >> age;
    cout << "Enter grade/class: ";
    getline(cin >> ws, grade);

    StudentNode* newNode = new StudentNode(id, name, age, grade);

    // Insert at the end of the singly linked list.
    if (studentHead == nullptr) {
        studentHead = newNode;
    } else {
        StudentNode* current = studentHead;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

    cout << "Student added successfully.\n";
}

void SchoolSystem::insertStudentAtPosition() {
    int position, id, age;
    string name, grade;

    cout << "Enter position (starting from 1): ";
    cin >> position;
    if (position < 1) {
        cout << "Invalid position.\n";
        return;
    }

    cout << "Enter student ID: ";
    cin >> id;

    // Prevent duplicate student IDs.
    for (StudentNode* p = studentHead; p != nullptr; p = p->next) {
        if (p->id == id) {
            cout << "A student with this ID already exists.\n";
            return;
        }
    }

    cout << "Enter student name: ";
    getline(cin >> ws, name);
    cout << "Enter age: ";
    cin >> age;
    cout << "Enter grade/class: ";
    getline(cin >> ws, grade);

    StudentNode* newNode = new StudentNode(id, name, age, grade);

    // Insert at the head when position is 1.
    if (position == 1) {
        newNode->next = studentHead;
        studentHead = newNode;
        cout << "Student inserted successfully.\n";
        return;
    }

    // Move to the node just before the required position.
    StudentNode* current = studentHead;
    for (int i = 1; current != nullptr && i < position - 1; i++) {
        current = current->next;
    }

    if (current == nullptr) {
        delete newNode;
        cout << "Position is outside the list.\n";
        return;
    }

    newNode->next = current->next;
    current->next = newNode;
    cout << "Student inserted successfully.\n";
}

void SchoolSystem::displayStudents() const {
    if (studentHead == nullptr) {
        cout << "No student records found.\n";
        return;
    }

    cout << "\n--- STUDENT RECORDS ---\n";
    StudentNode* current = studentHead;

    // Traverse the list until the next pointer becomes null.
    while (current != nullptr) {
        cout << "ID: " << current->id
             << " | Name: " << current->name
             << " | Age: " << current->age
             << " | Grade: " << current->grade << '\n';
        current = current->next;
    }
}

void SchoolSystem::searchStudent() const {
    int id;
    cout << "Enter student ID to search: ";
    cin >> id;

    StudentNode* current = studentHead;

    // Search each node one by one.
    while (current != nullptr) {
        if (current->id == id) {
            cout << "Student found: " << current->name
                 << ", Age: " << current->age
                 << ", Grade: " << current->grade << '\n';
            return;
        }
        current = current->next;
    }

    cout << "Student not found.\n";
}

void SchoolSystem::deleteStudent() {
    int id;
    cout << "Enter student ID to delete: ";
    cin >> id;

    if (studentHead == nullptr) {
        cout << "Student list is empty.\n";
        return;
    }

    // Handle deletion of the first node separately.
    if (studentHead->id == id) {
        StudentNode* temp = studentHead;
        studentHead = studentHead->next;
        delete temp;
        cout << "Student deleted successfully.\n";
        return;
    }

    StudentNode* current = studentHead;

    // Find the node before the student that should be deleted.
    while (current->next != nullptr && current->next->id != id) {
        current = current->next;
    }

    if (current->next == nullptr) {
        cout << "Student not found.\n";
    } else {
        StudentNode* temp = current->next;
        current->next = temp->next;
        delete temp;
        cout << "Student deleted successfully.\n";
    }
}

void SchoolSystem::swapStudents() {
    int firstId, secondId;
    cout << "Enter first student ID: ";
    cin >> firstId;
    cout << "Enter second student ID: ";
    cin >> secondId;

    StudentNode* first = studentHead;
    StudentNode* second = studentHead;

    // Locate both student nodes.
    while (first != nullptr && first->id != firstId) first = first->next;
    while (second != nullptr && second->id != secondId) second = second->next;

    if (first == nullptr || second == nullptr) {
        cout << "One or both student IDs were not found.\n";
        return;
    }

    // Swap student data while keeping the linked-list connections unchanged.
    swap(first->id, second->id);
    swap(first->name, second->name);
    swap(first->age, second->age);
    swap(first->grade, second->grade);
    cout << "Student records swapped successfully.\n";
}

void SchoolSystem::sortStudents() {
    if (studentHead == nullptr || studentHead->next == nullptr) {
        cout << "Not enough students to sort.\n";
        return;
    }

    // Bubble sort the student data by ID.
    for (StudentNode* i = studentHead; i->next != nullptr; i = i->next) {
        for (StudentNode* j = studentHead; j->next != nullptr; j = j->next) {
            if (j->id > j->next->id) {
                swap(j->id, j->next->id);
                swap(j->name, j->next->name);
                swap(j->age, j->next->age);
                swap(j->grade, j->next->grade);
            }
        }
    }
    cout << "Students sorted by ID.\n";
}

void SchoolSystem::reverseStudents() {
    StudentNode* previous = nullptr;
    StudentNode* current = studentHead;

    // Reverse each link so that it points to the previous node.
    while (current != nullptr) {
        StudentNode* nextNode = current->next;
        current->next = previous;
        previous = current;
        current = nextNode;
    }

    studentHead = previous;
    cout << "Student list reversed.\n";
}

// ---------------- CLASS SCHEDULE: CIRCULAR LINKED LIST ----------------

void SchoolSystem::addPeriod() {
    string subject, teacher, time;
    cout << "Enter subject: ";
    getline(cin >> ws, subject);
    cout << "Enter teacher name: ";
    getline(cin >> ws, teacher);
    cout << "Enter period time: ";
    getline(cin >> ws, time);

    ScheduleNode* newNode = new ScheduleNode(subject, teacher, time);

    // The first node points to itself to make a circular list.
    if (scheduleHead == nullptr) {
        scheduleHead = newNode;
        newNode->next = scheduleHead;
        currentPeriod = scheduleHead;
    } else {
        ScheduleNode* last = scheduleHead;
        while (last->next != scheduleHead) {
            last = last->next;
        }
        last->next = newNode;
        newNode->next = scheduleHead;
    }

    cout << "Class period added successfully.\n";
}

void SchoolSystem::removePeriod() {
    if (scheduleHead == nullptr) {
        cout << "Schedule is empty.\n";
        return;
    }

    string subject;
    cout << "Enter subject to remove: ";
    getline(cin >> ws, subject);

    ScheduleNode* current = scheduleHead;
    ScheduleNode* previous = nullptr;

    // Search one full circle, stopping when we return to the head.
    do {
        if (current->subject == subject) {
            if (current->next == current) {
                scheduleHead = nullptr;
                currentPeriod = nullptr;
            } else {
                if (previous == nullptr) {
                    ScheduleNode* last = scheduleHead;
                    while (last->next != scheduleHead) last = last->next;
                    scheduleHead = current->next;
                    last->next = scheduleHead;
                } else {
                    previous->next = current->next;
                }

                if (currentPeriod == current) currentPeriod = current->next;
            }

            delete current;
            cout << "Period removed successfully.\n";
            return;
        }

        previous = current;
        current = current->next;
    } while (current != scheduleHead);

    cout << "Subject not found.\n";
}

void SchoolSystem::displaySchedule() const {
    if (scheduleHead == nullptr) {
        cout << "Schedule is empty.\n";
        return;
    }

    cout << "\n--- CIRCULAR CLASS SCHEDULE ---\n";
    ScheduleNode* current = scheduleHead;

    // Stop after visiting the head node for the second time.
    do {
        cout << current->subject << " | Teacher: " << current->teacher
             << " | Time: " << current->time << '\n';
        current = current->next;
    } while (current != scheduleHead);
}

void SchoolSystem::moveToNextPeriod() {
    if (currentPeriod == nullptr) {
        cout << "No class periods are available.\n";
        return;
    }

    // Circular link automatically returns to the first period.
    currentPeriod = currentPeriod->next;
    cout << "Current period: " << currentPeriod->subject
         << " | Teacher: " << currentPeriod->teacher
         << " | Time: " << currentPeriod->time << '\n';
}

// ---------------- ANNOUNCEMENTS: DOUBLY LINKED LIST ----------------

void SchoolSystem::addAnnouncement() {
    string message;
    int id;

    cout << "Enter announcement ID: ";
    cin >> id;
    cout << "Enter announcement message: ";
    getline(cin >> ws, message);

    AnnouncementNode* newNode = new AnnouncementNode(id, message);

    // Connect the new node after the current tail.
    if (announcementHead == nullptr) {
        announcementHead = announcementTail = currentAnnouncement = newNode;
    } else {
        announcementTail->next = newNode;
        newNode->previous = announcementTail;
        announcementTail = newNode;
    }

    cout << "Announcement added successfully.\n";
}

void SchoolSystem::displayAnnouncementsForward() const {
    if (announcementHead == nullptr) {
        cout << "No announcements available.\n";
        return;
    }

    cout << "\n--- ANNOUNCEMENTS (FORWARD) ---\n";
    AnnouncementNode* current = announcementHead;

    // Move from the first announcement to the last.
    while (current != nullptr) {
        cout << current->id << ". " << current->message << '\n';
        current = current->next;
    }
}

void SchoolSystem::displayAnnouncementsBackward() const {
    if (announcementTail == nullptr) {
        cout << "No announcements available.\n";
        return;
    }

    cout << "\n--- ANNOUNCEMENTS (BACKWARD) ---\n";
    AnnouncementNode* current = announcementTail;

    // Use previous pointers to move from last to first.
    while (current != nullptr) {
        cout << current->id << ". " << current->message << '\n';
        current = current->previous;
    }
}

void SchoolSystem::moveToNextAnnouncement() {
    if (currentAnnouncement == nullptr) {
        cout << "No announcements available.\n";
        return;
    }

    if (currentAnnouncement->next != nullptr) {
        currentAnnouncement = currentAnnouncement->next;
        cout << "Current announcement: " << currentAnnouncement->message << '\n';
    } else {
        cout << "Already at the last announcement.\n";
    }
}

void SchoolSystem::moveToPreviousAnnouncement() {
    if (currentAnnouncement == nullptr) {
        cout << "No announcements available.\n";
        return;
    }

    if (currentAnnouncement->previous != nullptr) {
        currentAnnouncement = currentAnnouncement->previous;
        cout << "Current announcement: " << currentAnnouncement->message << '\n';
    } else {
        cout << "Already at the first announcement.\n";
    }
}

void SchoolSystem::removeCurrentAnnouncement() {
    if (currentAnnouncement == nullptr) {
        cout << "No current announcement to remove.\n";
        return;
    }

    AnnouncementNode* target = currentAnnouncement;

    // Reconnect the previous node with the next node.
    if (target->previous != nullptr)
        target->previous->next = target->next;
    else
        announcementHead = target->next;

    // Reconnect the next node with the previous node.
    if (target->next != nullptr)
        target->next->previous = target->previous;
    else
        announcementTail = target->previous;

    // Select a valid current node after deletion.
    currentAnnouncement = (target->next != nullptr) ? target->next : target->previous;

    delete target;
    cout << "Current announcement removed.\n";
}

// ---------------- MAIN MENU ----------------

void SchoolSystem::run() {
    int choice;

    do {
        cout << "\n========== SCHOOL MANAGEMENT SYSTEM ==========\n";
        cout << "1. Student Management (Singly Linked List)\n";
        cout << "2. Class Schedule (Circular Linked List)\n";
        cout << "3. Announcements (Doubly Linked List)\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Select the required section using the menu choice.
        switch (choice) {
            case 1: {
                int option;
                do {
                    cout << "\n--- STUDENT MANAGEMENT ---\n";
                    cout << "1. Add Student\n2. Insert at Position\n3. Display Students\n";
                    cout << "4. Search Student\n5. Delete Student\n6. Swap Students\n";
                    cout << "7. Sort by ID\n8. Reverse List\n0. Back\n";
                    cout << "Choice: ";
                    cin >> option;

                    switch (option) {
                        case 1: addStudent(); break;
                        case 2: insertStudentAtPosition(); break;
                        case 3: displayStudents(); break;
                        case 4: searchStudent(); break;
                        case 5: deleteStudent(); break;
                        case 6: swapStudents(); break;
                        case 7: sortStudents(); break;
                        case 8: reverseStudents(); break;
                        case 0: break;
                        default: cout << "Invalid choice.\n";
                    }
                } while (option != 0);
                break;
            }

            case 2: {
                int option;
                do {
                    cout << "\n--- CLASS SCHEDULE ---\n";
                    cout << "1. Add Period\n2. Remove Period\n";
                    cout << "3. Display Schedule\n4. Move to Next Period\n0. Back\n";
                    cout << "Choice: ";
                    cin >> option;

                    switch (option) {
                        case 1: addPeriod(); break;
                        case 2: removePeriod(); break;
                        case 3: displaySchedule(); break;
                        case 4: moveToNextPeriod(); break;
                        case 0: break;
                        default: cout << "Invalid choice.\n";
                    }
                } while (option != 0);
                break;
            }

            case 3: {
                int option;
                do {
                    cout << "\n--- SCHOOL ANNOUNCEMENTS ---\n";
                    cout << "1. Add Announcement\n2. Display Forward\n";
                    cout << "3. Display Backward\n4. Next Announcement\n";
                    cout << "5. Previous Announcement\n6. Remove Current Announcement\n0. Back\n";
                    cout << "Choice: ";
                    cin >> option;

                    switch (option) {
                        case 1: addAnnouncement(); break;
                        case 2: displayAnnouncementsForward(); break;
                        case 3: displayAnnouncementsBackward(); break;
                        case 4: moveToNextAnnouncement(); break;
                        case 5: moveToPreviousAnnouncement(); break;
                        case 6: removeCurrentAnnouncement(); break;
                        case 0: break;
                        default: cout << "Invalid choice.\n";
                    }
                } while (option != 0);
                break;
            }

            case 0:
                cout << "Thank you for using the School Management System.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}
