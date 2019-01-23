#include "mbed.h"

//Seperate Threads
Thread SoundThread;
Thread LightThread;
Thread TempThread;

//External voids
extern void LoadStartScreen();
extern void Sound();
extern void Light();
extern void Temp();

//Main Function
int main() 
{
    SoundThread.start(Sound);
    LightThread.start(Light);
    TempThread.start(Temp);

    LoadStartScreen();// Continues thread
}