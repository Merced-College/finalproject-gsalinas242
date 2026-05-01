#include "Event.h"
#include <iostream>
#include <ctime>

Event::Event() {} // Constructor to initialize the event and is empty since we are not using it right now
std::string Event::getEventMessage() const { // Method to get the type of event (for raylib)
    time_t now = time(0); // Get the current time
    tm *ltm = localtime(&now); // Convert the current time to local time
    int month = ltm->tm_mon + 1; // Get the current month from the local time (add 1 since tm_mon is 0-based)
    int day = ltm->tm_mday; // Get the current day from the local time
    int year = ltm->tm_year + 1900; // Get the current year from the local time (add 1900 since tm_year is years since 1900)

    if (year == 2026 && month == 4 && day == 30) {
        return "Project Fairy Presentation"; // Return a specific event message if the date is April 30th
    }
    else if (month == 5 && day == 2) {
        return "Happy Birthday Santiago!"; // Return a specific event message if the date is May 2nd
    }
    else if (month == 10 && day == 24) {
        return "Happy Birthday Genisa!"; // Return a specific event message if the date is October 24th
    }
    else if (month == 10 && day == 31) {
        return "Happy Halloween!"; // Return a specific event message if the date is October 31st
    }
    else {
        return "No special events today."; // Return a default message if there are no special events on the current date
    }
}

    