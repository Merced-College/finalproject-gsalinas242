#ifndef EVENT_H
#define EVENT_H

#include <string> // Include string for storing messages

class Event {
public:
    Event(); // Constructor to initialize the event
    std::string getEventMessage() const; // Method to get the type of event (for raylib)
    void displayEvent() const; // Method to display the event (used for terminal to test)
};
#endif