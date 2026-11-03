#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
using namespace std;

// Node for the singly linked list of students (Lab 05).
struct StudentNode {
    int id;
    string name;
    int age;
    string grade;
    StudentNode* next;

    StudentNode(int studentId, string studentName, int studentAge, string studentGrade)
        : id(studentId), name(studentName), age(studentAge),
          grade(studentGrade), next(nullptr) {}
};

// Node for the circular linked list of class periods (Lab 06).
struct ScheduleNode {
    string subject;
    string teacher;
    string time;
    ScheduleNode* next;

    ScheduleNode(string subjectName, string teacherName, string periodTime)
        : subject(subjectName), teacher(teacherName), time(periodTime), next(nullptr) {}
};

// Node for the doubly linked list of announcements (Lab 07).
struct AnnouncementNode {
    int id;
    string message;
    AnnouncementNode* previous;
    AnnouncementNode* next;

    AnnouncementNode(int announcementId, string announcementMessage)
        : id(announcementId), message(announcementMessage),
          previous(nullptr), next(nullptr) {}
};

#endif
