#include "mbed.h"

AnalogIn LightSensor(A0); //Sensor connected to A0

float lightResult = 0;

void Light()
{
    while(1)
    {
        //Times Sensor-Resistance
        lightResult = LightSensor.read() * 1023; //Read the electrical signal from the Sensor

        wait(0.1);
    }
}