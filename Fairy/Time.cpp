#include "Time.h"
#include <iostream>
#include <ctime> // Include ctime for getting the current time

deviceTime::deviceTime() {
    
}

std::string deviceTime::getCurrentTime() const {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec);
}

void deviceTime::displayCurrentTime() const {
    std::cout << "Current Time: " << getCurrentTime() << std::endl;
}