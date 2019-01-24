/**
* @file main.cpp
* @brief This initializes the main essential threads that run in this program
*
* @author Kristian Kraken Sarka Nielsen
*
* @date 14/01/2019
*/

#include "mbed.h"

//Seperate Threads
Thread SoundThread;
Thread LightThread;
Thread TempThread;
Thread LabelUpdateThread;

//External voids
extern void LoadStartScreen();
extern void Sound();
extern void Light();
extern void Temp();
extern void LoadUpdatingLabels();

/**
* Main Method, starts seperate threads for sensors
* @author Kristian Kraken Sarka Nielsen
* @date 14/01/2019
*/
int main() 
{
    SoundThread.start(Sound);
    LightThread.start(Light);
    TempThread.start(Temp);
    LabelUpdateThread.start(LoadUpdatingLabels);

    LoadStartScreen();// Continues thread
}


