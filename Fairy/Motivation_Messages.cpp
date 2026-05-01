#include "Motivation_Messages.h"
#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

MotivationMessages::MotivationMessages() { // Constructor to initialize the messages vector
    srand(time(0)); // seed the random number generator with the current time so we get a different message each run

    messages = { // Initialize the messages vector with some motivational messages
        "Just keep swimming!",
        "You are doing great, keep it going",
        "Que dios te bendiga, sigue adelante",
        "You look berry nice today",
        "You are the best",
        "I hope you have an amazing day :)",
    };
}

std::string MotivationMessages::getRandomMessage() const { // method to get a random motivational message
    int index = rand() % messages.size(); // get a random index based on the size of the messages vector
    return messages[index]; // return the random message at the generated index
}

void MotivationMessages::displayRandomMessage(std::string message) const { // method to display a random motivational message
    std::cout << "Fairy says: " << message << std::endl; // display the random motivational message
}