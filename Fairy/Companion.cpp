#include "Companion.h"
#include <cstdlib> // for getenv

// Helper to get the base assets path relative to where the program is running
static std::string getAssetsPath() {
#ifdef _WIN32
    // Windows: use the FAIRY_PATH environment variable or default to current directory
    const char* base = getenv("FAIRY_PATH");
    return base ? std::string(base) + "\\assets\\" : ".\\assets\\";
#elif __APPLE__
    // macOS: use the FAIRY_PATH environment variable or default to current directory
    const char* base = getenv("FAIRY_PATH");
    return base ? std::string(base) + "/assets/" : "./assets/";
#else
    // Linux: use the FAIRY_PATH environment variable or default to current directory
    const char* base = getenv("FAIRY_PATH");
    return base ? std::string(base) + "/assets/" : "./assets/";
#endif
}

// Constructor
Companion::Companion(std::string name) : name(name) {
    // face, outfit, hat will be set in loadTextures()
}

// Destructor - unloads all textures to prevent memory leaks
Companion::~Companion() {
    for (auto& pair : faceMap)   UnloadTexture(pair.second);
    for (auto& pair : outfitMap) UnloadTexture(pair.second);
    for (auto& pair : hatMap)    UnloadTexture(pair.second);
}

// Load all textures once after InitWindow()
void Companion::loadTextures() {
    std::string assets = getAssetsPath(); // get the base assets path once

    // --- FACES ---
    faceMap["happy"]   = LoadTexture((assets + "fairyHappy.png").c_str());
    faceMap["neutral"] = LoadTexture((assets + "fairyNeutral.png").c_str());
    faceMap["sad"]     = LoadTexture((assets + "fairyMad.png").c_str());

    // --- OUTFITS ---
    outfitMap["cold"]           = LoadTexture((assets + "winterOutfit.png").c_str());
    outfitMap["neutralWeather"] = LoadTexture((assets + "default.png").c_str());
    outfitMap["hot"]            = LoadTexture((assets + "sunglasses.png").c_str());

    // --- HATS ---
    hatMap["default"]      = LoadTexture((assets + "defaultHat.png").c_str());
    hatMap["halloween"]    = LoadTexture((assets + "pumpkin.png").c_str());
    hatMap["birthday"]     = LoadTexture((assets + "bdayHat.png").c_str());
    hatMap["presentation"] = LoadTexture((assets + "gradCap.png").c_str());

    // Set default appearance
    face   = faceMap["happy"];
    outfit = outfitMap["neutralWeather"];
    hat    = hatMap["default"];
}

// Update appearance based on battery, weather, temperature, and event
void Companion::updateAppearance(int batteryPercentage, std::string weather, int temperature, std::string eventMessage) {

    // --- FACE: controlled by battery percentage ---
    if (batteryPercentage >= 75) {
        face = faceMap["happy"];
    } else if (batteryPercentage >= 25) {
        face = faceMap["neutral"];
    } else {
        face = faceMap["sad"];
    }

    // --- OUTFIT: controlled by temperature ---
    if (temperature <= 60) {
        outfit = outfitMap["cold"];
    } else if (temperature <= 75) {
        outfit = outfitMap["neutralWeather"];
    } else {
        outfit = outfitMap["hot"];
    }

    // --- HAT: controlled by special events (highest priority) ---
    if (eventMessage == "Happy Halloween!") {
        hat = hatMap["halloween"];
    } else if (eventMessage == "Happy Birthday Santiago!" || eventMessage == "Happy Birthday Genisa!") {
        hat = hatMap["birthday"];
    } else if (eventMessage == "Project Fairy Presentation") {
        hat = hatMap["presentation"];
    } else {
        hat = hatMap["default"];
    }
}

// Draw companion on screen - layers outfit, face, then hat
void Companion::draw(int x, int y) {
    DrawTexture(outfit, x, y, WHITE);  // Bottom layer: outfit
    DrawTexture(face,   x, y, WHITE);  // Middle layer: face
    DrawTexture(hat,    x, y, WHITE);  // Top layer: hat
}

// --- GETTERS ---
std::string Companion::getName()   const { return name; }
Texture2D   Companion::getFace()   const { return face; }
Texture2D   Companion::getOutfit() const { return outfit; }
Texture2D   Companion::getHat()    const { return hat; }