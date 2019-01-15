#include "mbed.h"
#include "F746_GUI.hpp"

LCD_DISCO_F746NG lcd;

Serial PC(USBTX, USBRX);

extern bool GetCelTemp;

extern float tempResult;
extern int soundResult;
extern int lightResult;

bool doWhile = false;

void LoadGUI()
{
    //Baud for PuTTy 9600 Standard
    PC.baud(9600);

    //Clear LCD Screen
    lcd.Clear(0xFF003538);
    
    //Border Color
    lcd.SetTextColor(LCD_COLOR_WHITE);
    
    //Top Title
    Label mainTitle(240, 5, "Eternity Squid Studios Controller II", Label::CENTER, Font16, LCD_COLOR_GREEN);
    
    //Restart Button
    Button restartBtn(370, 250, 70, 20, "Restart", Font12, LCD_COLOR_WHITE, LCD_COLOR_RED, LCD_COLOR_RED);
    
    //Adds a underline to the counter text
    Button labelBtn(1, 26, 478, 60, "___Lines___", Font16, LCD_COLOR_WHITE, 0xFF003538, 0xFF003538);
    
    //Allows you to toggle the LEDs
    Button MidBtn(1, 86, 478, 60, "Pointless", Font16, LCD_COLOR_WHITE, 0xFF003538, 0xFF003538, 0xFF003538);
    
    //Border Lines
    lcd.DrawRect(0, 25, 479, 225);

    if (!doWhile)
    {
        while (1) //Main Thread (Continued)
        {   
            //Printing to puTTy
            PC.printf("\rCurrent: %d\r", soundResult);



            //Middle button (Touch)
            if (MidBtn.Touched())
            {

            }
        
            //Goes if restartBtn is pressed
            if (restartBtn.Touched())
            {
               NVIC_SystemReset(); //System reset function
            }
        }
    }
}