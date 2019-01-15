#include "mbed.h"
#include "Grove_temperature.h"

AnalogIn TempSensor1(A1);
Grove_temperature TempSensor(A1); //Sensor connected to A1

float tempResult = 0;

bool GetCelTemp = false; //If false then you'll get 'Fahrenheit

const int B=4275; // B value of the thermistor 
const int R0 = 100000; // R0 = 100

void Temp()
{
    while(1)
    {
        if (!GetCelTemp)
        {
            tempResult = TempSensor.getTemperature();
        }
        else
        {
            int a = TempSensor1.read(); 
 
            float R = 1023.0/((float)a)-1.0; 
            R = 100000.0*R; 
 
            //convert to temperature via datasheet ; 
            tempResult = 1.0/(log(R/100000.0)/B+1/298.15)-273.15;
        }
        wait(0.1);
    }
}