#ifndef SCHOOL_SYSTEM_H
#define SCHOOL_SYSTEM_H

#include "Structures.h"

class SchoolSystem {
private:
    // Singly linked list: student records.
    StudentNode* studentHead;

    // Circular linked list: class schedule.
    ScheduleNode* scheduleHead;
    ScheduleNode* currentPeriod;

    // Doubly linked list: school announcements.
    AnnouncementNode* announcementHead;
    AnnouncementNode* announcementTail;
    AnnouncementNode* currentAnnouncement;

public:
    SchoolSystem();
    ~SchoolSystem();

    // Student management functions (singly linked list).
    void addStudent();
    void insertStudentAtPosition();
    void displayStudents() const;
    void searchStudent() const;
    void deleteStudent();
    void swapStudents();
    void sortStudents();
    void reverseStudents();

    // Schedule functions (circular linked list).
    void addPeriod();
    void removePeriod();
    void displaySchedule() const;
    void moveToNextPeriod();

    // Announcement functions (doubly linked list).
    void addAnnouncement();
    void displayAnnouncementsForward() const;
    void displayAnnouncementsBackward() const;
    void moveToNextAnnouncement();
    void moveToPreviousAnnouncement();
    void removeCurrentAnnouncement();

    // Main menu.
    void run();
};

#endif
