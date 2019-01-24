/**
* @file Sound.cpp
* @brief This script recives and converts the input from a sound sensor into decibel.
*
* @author Kristian Kraken Sarka Nielsen
*
* @date 17/01/2019
*/

#include "mbed.h"

AnalogIn SoundSensor(A2); //Sensor connected to A2

float soundResult = 0;

/**
* This method is used to get and convert the input of a sound sensor
* @author Kristian Kraken Sarka Nielsen
* @param soundResult (The result of the convertion)
* @date 17/01/2019
*/
void Sound()
{
    
    while(1)
    {
        //Times Voltage Devided with Sensor-Resistance
        soundResult = SoundSensor.read_u16() * 3.3 / 1024; //Read the electrical signal from the Sensor

        wait(0.1);
    }
    
}