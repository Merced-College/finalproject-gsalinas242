#ifndef Battery_H 
#define Battery_H 

class Battery {
private:
    int percentage;
    int fetchSystemBattery();

public:
    Battery();
    void displayPercentage() const;
    void displayMoodIndicator() const;
    int getPercentage() const;
};

#endif