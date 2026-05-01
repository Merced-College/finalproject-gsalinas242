#ifndef WEATHER_H
#define WEATHER_H

#include <string>
#include <ctime>

class Weather {
private:
    std::string temperature;  // current temperature as a string
    std::string shortForecast; // short description e.g. "Sunny", "Rainy"
    std::string weatherState;  // simplified state: "cold", "neutral", or "hot"
    time_t lastFetched;  // tracks when we last fetched

    void fetchWeather(); // fetches and parses weather from NWS API

public:
    Weather();                          // Constructor - fetches weather on creation
    void update();                        // call this in your main loop
    std::string getTemperature() const; // returns temperature string
    std::string getShortForecast() const; // returns forecast description
    std::string getWeatherState() const;  // returns "cold", "neutral", or "hot"
    std::string getWeather() const;       // returns a full display string
};

#endif