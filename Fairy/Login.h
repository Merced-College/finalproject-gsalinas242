#ifndef LOGIN_H
#define LOGIN_H
#include <string>
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>


class Login {
private:
    int dayLogged;
    int monthLogged;
    int yearLogged;
    int loginCount;
    std::string filePath;

    void load();
    void save();

public:
    Login(std::string filePath);
    void log();
    int getLoginCount();
};

#endif