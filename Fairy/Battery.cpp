#include "Battery.h"
#include <iostream>
#include <cstdio>
#include <string>

int Battery::fetchSystemBattery() {
    // Check which OS is being used at compile time and run the appropriate command

#ifdef _WIN32
    // Windows: use wmic command to get battery percentage
    FILE* pipe = popen("wmic path Win32_Battery get EstimatedChargeRemaining /value 2>nul", "r");
    if (!pipe) return 50; // return 50% as a fallback if the command fails

    char buffer[64];
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) // read the output of the command
        result += buffer;
    pclose(pipe); // close the pipe after reading

    // The output looks like "EstimatedChargeRemaining=80" so we find the '=' and grab the number after it
    size_t eq = result.find('=');
    if (eq != std::string::npos) {
        try { return std::stoi(result.substr(eq + 1)); } // convert the string number to an integer
        catch (...) { return 50; } // return 50% as a fallback if parsing fails
    }
    return 50; // return 50% as a fallback if '=' was not found

#elif __APPLE__
    // macOS: use pmset command to get battery percentage
    FILE* pipe = popen("pmset -g batt | grep -o '[0-9]*%' | tr -d '%'", "r");
    if (!pipe) return 50; // return 50% as a fallback if the command fails

    char buffer[8];
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) // read the output of the command
        result += buffer;
    pclose(pipe); // close the pipe after reading

    try { return std::stoi(result); } // convert the string number to an integer
    catch (...) { return 50; } // return 50% as a fallback if parsing fails

#else
    // Linux: read battery percentage directly from the system file
    FILE* pipe = popen("cat /sys/class/power_supply/BAT0/capacity 2>/dev/null", "r");
    if (!pipe) return 50; // return 50% as a fallback if the command fails

    char buffer[8];
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) // read the output of the command
        result += buffer;
    pclose(pipe); // close the pipe after reading

    try { return std::stoi(result); } // convert the string number to an integer
    catch (...) { return 50; } // return 50% as a fallback if parsing fails
#endif
}

// Constructor reads the real battery percentage from the OS instead of taking a hardcoded value
Battery::Battery() : percentage(fetchSystemBattery()) {}

// Method to display the mood indicator based on the battery percentage
void Battery::displayMoodIndicator() const {
    if (percentage >= 75) { // prints happy mood if the battery percentage is above or equal to 75%
        std::cout << "Mood: Happy" << std::endl;
    } else if (percentage >= 25) { // prints neutral mood if the battery percentage is greater than or equal to 25%
        std::cout << "Mood: Neutral" << std::endl;
    } else {
        std::cout << "Mood: Sad" << std::endl; // prints sad mood if the battery percentage is below 25%
    }
}

// Get the battery percentage since it is private (getter)
int Battery::getPercentage() const {
    return percentage;
}

// Method to display the battery percentage
void Battery::displayPercentage() const {
    std::cout << "Battery Percentage: " << percentage << "%" << std::endl;
}