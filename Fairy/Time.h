#ifndef Time_H
#define Time_H

#include <string> // Include string for storing messages

class deviceTime {
public:
    deviceTime(); // Constructor to initialize the time
    std::string getCurrentTime() const; // Method to get the current time
    void displayCurrentTime() const; // Method to display the current time
};

#endif