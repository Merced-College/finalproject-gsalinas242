#include "Battery.h"
#include "Event.h"
#include "Time.h"
#include "Motivation_Messages.h"
#include "Weather.h"
#include "Companion.h"
#include "raylib.h"
#include "Login.h"
#include <iostream>
#include <cstdlib> // for getenv

// Helper to get the base project path
static std::string getBasePath() {
#ifdef _WIN32
    // Windows: use the FAIRY_PATH environment variable or default to current directory
    const char* base = getenv("FAIRY_PATH");
    return base ? std::string(base) + "\\" : ".\\";
#else
    // macOS/Linux: use the FAIRY_PATH environment variable or default to current directory
    const char* base = getenv("FAIRY_PATH");
    return base ? std::string(base) + "/" : "./";
#endif
}

int main() {
    // Initialize window
    InitWindow(480, 320, "Project Fairy");
    SetTargetFPS(60);

    std::string base = getBasePath(); // get the base path once

    // Initialize all objects
    Battery battery;                                    // reads real battery from OS
    Event event;
    deviceTime timer;
    MotivationMessages motivation;
    Weather weather;
    Companion companion("Fairy");
    Login login(base + "data/saveFile.txt");            // relative path to save file

    login.log(); // call once at startup

    // Load textures ONCE after InitWindow
    Texture2D fairyBlob = LoadTexture((base + "assets/fairyBase.png").c_str()); // relative path to base texture
    companion.loadTextures();

    std::string msg = motivation.getRandomMessage();

    while (!WindowShouldClose()) {

        // Update weather (only refetches once per hour)
        weather.update();

        // Update companion appearance
        companion.updateAppearance(
            battery.getPercentage(),
            weather.getWeatherState(),
            std::stoi(weather.getTemperature()),
            event.getEventMessage()
        );

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw base fairy texture
        DrawTexture(fairyBlob, 0, 0, WHITE);

        // Draw companion layers on top
        companion.draw(0, 0);

        // Draw UI text
        DrawText(("Time: " + timer.getCurrentTime()).c_str(),                           10,  10, 10, DARKGRAY);
        DrawText(("Battery: " + std::to_string(battery.getPercentage()) + "%").c_str(), 400, 10, 10, DARKGRAY);
        DrawText(("Event: " + event.getEventMessage()).c_str(),                          10,  30, 10, DARKGRAY);
        DrawText(("Weather: " + weather.getWeather()).c_str(),                           10,  50, 10, DARKGRAY);
        DrawText(("Fairy says: " + msg).c_str(),                                         10,  70, 10, DARKGRAY);
        DrawText(("Days logged in: " + std::to_string(login.getLoginCount())).c_str(),   10,  90, 10, DARKGRAY);

        EndDrawing();
    }

    // Unload base texture before closing
    UnloadTexture(fairyBlob);

    CloseWindow();
    return 0;
}