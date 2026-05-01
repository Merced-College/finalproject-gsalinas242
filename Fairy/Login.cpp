
#include "Login.h"
#include <iostream>
#include <fstream>
#include <sstream>

Login::Login(std::string filePath) : filePath(filePath), loginCount(0), yearLogged(0), monthLogged(0), dayLogged(0) {
    load();
    }
void Login::load() {
    std::ifstream saveFile(filePath);
    if(!saveFile.is_open()) return;  //returns if file does not exist

    std::string line;
    std::getline(saveFile, line);
    
    if (line.empty()) return;

    //This is where we begin to parse the saveFile for data
    std::stringstream ss(line);
    std::string token;
    std::getline(ss,token, ','); loginCount = std::stoi(token); //gets the string representing loginCount from file and converts to integer
    std::getline(ss,token, ','); dayLogged = std::stoi(token); //gets the string representing dayLogged from file and converts to integer
    std::getline(ss,token, ','); monthLogged = std::stoi(token); //gets the string representing monthLogged from file and converts to integer
    std::getline(ss,token, ','); yearLogged = std::stoi(token); //gets the string representing yearLogged from file and converts to integer

    saveFile.close();
}

void Login::save() {
    std::ofstream saveFile(filePath);

    //writes the data to the save file, essentially saving it
    saveFile << std::to_string(loginCount) + "," << std::to_string(dayLogged) + "," <<std::to_string(monthLogged) + ","
         << std::to_string(yearLogged) + "\n";

    saveFile.close();
}

void Login::log() {
    // Get today's date
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int today_year  = ltm->tm_year + 1900;
    int today_month = ltm->tm_mon + 1;
    int today_day   = ltm->tm_mday;

    // Only increment if last login was not today
    if (today_year  != yearLogged  ||
        today_month != monthLogged ||
        today_day   != dayLogged) {

        loginCount++;
        yearLogged  = today_year;
        monthLogged = today_month;
        dayLogged   = today_day;
        save();
    }
}

int Login::getLoginCount() { return loginCount; }