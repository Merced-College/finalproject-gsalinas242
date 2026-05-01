#ifndef MOTIVATION_MESSAGES_H
#define MOTIVATION_MESSAGES_H

#include <string> // Include string for storing messages
#include <vector> // Include vector for storing multiple messages

class MotivationMessages {
private:
    std::vector<std::string> messages; // Vector to store multiple motivational messages

public:
    MotivationMessages(); // Constructor to initialize the messages vector
    std::string getRandomMessage() const; // Method to get a random motivational message
    void displayRandomMessage(std::string message) const; // Method to display a random motivational message
    // the reason we pass the message as a parameter is because we want to display the message that we get from the getRandomMessage() method
};

#endif