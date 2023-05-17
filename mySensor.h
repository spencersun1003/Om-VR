#ifndef mySensor_h
#define mySensor_h
#include <Arduino.h>
#include "MAX30105.h"
#include "heartRate.h"
#include <Wire.h>
#define RATE_SIZE 4

class MAX30105_sensor{

    private:
        MAX30105 *particleSensor;
        //const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
        byte rates[RATE_SIZE]={0}; //Array of heart rates
        byte rateSpot = 0;
        long lastBeat =0; //Time at which the last beat occurred
        long irValue=0;
        float beatsPerMinute=0;
        int beatAvg=0;

    public:
        MAX30105_sensor();
        void setup();
        void read_data();
        float getBPM();



};





#endif