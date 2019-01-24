/**
* @file Temp.cpp
* @brief This script recives and converts the input from a temperature sensor into Lumen.
*
* @author Kristian Kraken Sarka Nielsen
*
* @date 17/01/2019
*/

#include "mbed.h"
#include "Grove_temperature.h"

Grove_temperature TempSensor(A1); //Sensor connected to A1

float tempResult = 0;

bool GetCelTemp = false; //If false then you'll get 'Fahrenheit


/**
* This method is used to get and convert the input of a temperature sensor
* @author Kristian Kraken Sarka Nielsen
* @param tempResult (The result of the convertion)
* @date 17/01/2019
*/
void Temp()
{
    while(1)
    {
        if (!GetCelTemp)
        {
            tempResult = TempSensor.getTemperature() * 1.8 + 32;
        }
        else
        {
            tempResult = TempSensor.getTemperature();
        }
        wait(0.1);
    }
}