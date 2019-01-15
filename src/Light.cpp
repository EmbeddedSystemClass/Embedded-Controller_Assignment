#include "mbed.h"

AnalogIn LightSensor(A0); //Sensor connected to A0

int lightResult = 0;

void Light()
{
    while(1)
    {
        lightResult = LightSensor.read(); //Read the electrical signal from the Sensor

        wait(0.1);
    }
}