/**
* @file Light.cpp
* @brief This script recives and converts the input from a light sensor into Lumen.
*
* @author Kristian Kraken Sarka Nielsen
*
* @date 14/01/2019
*/

#include "mbed.h"

AnalogIn LightSensor(A0); //Sensor connected to A0

float lightResult = 0;

/**
* This method is used to get and convert the input of a light sensor
* @author Kristian Kraken Sarka Nielsen
* @param lightResult (The result of the convertion)
* @date 14/01/2019
*/
void Light()
{
    while(1) //Goes infinitely 
    {
        //Times Sensor-Resistance
        lightResult = LightSensor.read() * 1023; //Read the electrical signal from the Sensor

        //Wait to relieve processor.
        wait(0.1);
    }
}
