#include "mbed.h"

AnalogIn SoundSensor(A2); //Sensor connected to A2

float soundResult = 0;

void Sound()
{
    
    while(1)
    {
        //Times Voltage Devided with Sensor-Resistance
        soundResult = SoundSensor.read_u16() * 3.3 / 1024; //Read the electrical signal from the Sensor

        wait(0.1);
    }
    
}