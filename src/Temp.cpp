#include "mbed.h"
#include "Grove_temperature.h"

Grove_temperature TempSensor(A1); //Sensor connected to A1

float tempResult = 0;

bool GetCelTemp = false; //If false then you'll get 'Fahrenheit

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