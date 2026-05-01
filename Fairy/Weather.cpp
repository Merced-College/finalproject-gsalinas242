#include "Weather.h"
#include <iostream>
#include <curl/curl.h>
#include <string>

// NWS API endpoint for Merced College
static const std::string API_URL = "https://api.weather.gov/gridpoints/HNX/33,130/forecast/hourly";

// Callback function required by libcurl to capture the response
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

// Simple helper to extract a value from JSON by key
// Looks for "key": value or "key": "value"
static std::string extractJsonValue(const std::string& json, const std::string& key) {
    std::string searchKey = "\"" + key + "\":";
    size_t keyPos = json.find(searchKey);
    if (keyPos == std::string::npos) return "";

    size_t valueStart = keyPos + searchKey.length();

    // Skip whitespace
    while (valueStart < json.size() && json[valueStart] == ' ') valueStart++;

    if (json[valueStart] == '"') {
        // String value
        valueStart++;
        size_t valueEnd = json.find('"', valueStart);
        return json.substr(valueStart, valueEnd - valueStart);
    } else {
        // Numeric value
        size_t valueEnd = json.find_first_of(",}", valueStart);
        return json.substr(valueStart, valueEnd - valueStart);
    }
}

void Weather::fetchWeather() {
    CURL* curl = curl_easy_init();
    if (!curl) {
        temperature    = "N/A";
        shortForecast  = "Unavailable";
        weatherState   = "neutral";
        return;
    }

    std::string response;

    curl_easy_setopt(curl, CURLOPT_URL, API_URL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    // NWS API requires a User-Agent header
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "ProjectFairy/1.0 (student project)");

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        temperature   = "N/A";
        shortForecast = "Unavailable";
        weatherState  = "neutral";
        return;
    }

    // Extract first period's temperature and forecast from the JSON response
    temperature   = extractJsonValue(response, "temperature");
    shortForecast = extractJsonValue(response, "shortForecast");

    // Determine weather state based on temperature
    int temp = 0;
    try {
        temp = std::stoi(temperature);
    } catch (...) {
        temp = 70; // default to neutral if parsing fails
    }

    if (temp <= 60) {
        weatherState = "cold";
    } else if (temp <= 80) {
        weatherState = "neutral";
    } else {
        weatherState = "hot";
    }
}

Weather::Weather() {
    lastFetched = 0; // force a fetch on first call
    fetchWeather(); // fetch on construction
    lastFetched = time(0);
}

void Weather::update() {
    time_t now = time(0);
    double secondsElapsed = difftime(now, lastFetched);

    if (secondsElapsed >= 3600) { // 3600 seconds = 1 hour
        fetchWeather();
        lastFetched = time(0);
    }
}

std::string Weather::getTemperature()   const { return temperature; }
std::string Weather::getShortForecast() const { return shortForecast; }
std::string Weather::getWeatherState()  const { return weatherState; }

std::string Weather::getWeather() const {
    return shortForecast + " | " + temperature + "F";
}