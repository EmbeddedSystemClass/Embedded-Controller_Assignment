#include "mbed.h"

AnalogIn SoundSensor(A2); //Sensor connected to A2

int soundResult = 0;

void Sound()
{
    
    while(1)
    {
        soundResult = SoundSensor.read_u16(); //Read the electrical signal from the Sensor

        wait(0.1);
    }
    
}