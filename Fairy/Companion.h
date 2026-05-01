#ifndef COMPANION_H
#define COMPANION_H

#include <iostream>
#include <string>
#include <map>
#include "raylib.h"

class Companion {
private:
    std::string name;
    Texture2D face;
    Texture2D outfit;
    Texture2D hat;

    // Maps to store preloaded textures
    std::map<std::string, Texture2D> faceMap;
    std::map<std::string, Texture2D> outfitMap;
    std::map<std::string, Texture2D> hatMap;

public:
    Companion(std::string name);   // Constructor
    ~Companion();                  // Destructor to unload textures

    // Getters
    std::string getName() const;
    Texture2D getFace() const;
    Texture2D getOutfit() const;
    Texture2D getHat() const;

    // Methods
    void loadTextures();           // Call once after InitWindow()
    void updateAppearance(int batteryPercentage, std::string weather, int temperature, std::string eventMessage); // Update appearance based on conditions
    void draw(int x, int y);       // Draw companion on screen
};

#endif