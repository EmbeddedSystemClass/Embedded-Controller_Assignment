/**
* @file Light.cpp
* @brief This script recives and converts the input from a light sensor into Lumen.
*
* @author Kristian Kraken Sarka Nielsen
*
* @date 17/01/2019
*/

#include "mbed.h"

AnalogIn LightSensor(A0); //Sensor connected to analog input A0

float lightResult = 0; //Holds the result of Sensor convertion


/**
* This method is used to get and convert the input of a light sensor
* @author Kristian Kraken Sarka Nielsen
* @param lightResult (The result of the convertion)
* @date 17/01/2019
*/
void Light()
{
    while(1) //Goes infinitely 
    {
        //Read the electrical signal from the Sensor
        //Input * Sensor-Resistance
        lightResult = LightSensor.read() * 1023;

        //Wait to relieve processor.
        wait(0.1);
    }
}