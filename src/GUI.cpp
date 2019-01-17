#include "mbed.h"
#include "F746_GUI.hpp"

LCD_DISCO_F746NG lcd;

Serial PC(USBTX, USBRX);


extern bool GetCelTemp;

extern float tempResult;

extern int soundResult;
extern int lightResult;


int buildingNumber = 0;
int roomNumber = 0;

bool doWhile = false;

uint8_t tempText[10];


Thread LabelUpdateThread;


const string ToString(char * text)
{
    return (const string)text;
}

void LoadBorder()
{
    //Clear LCD Screen
    lcd.Clear(0xFF003538);
    
    //Top Title
    Label mainTitle(240, 5, "Eternity Squid Studios Controller II", Label::CENTER, Font16, LCD_COLOR_GREEN);

    //Border Lines
    lcd.DrawRect(0, 25, 479, 225);

    //Border Color
    lcd.SetTextColor(LCD_COLOR_WHITE);
}

void LoadRoomScreen()
{
    LoadBorder();

    unsigned int Width = 75, Height = 50; // Default Width & Height defined for every button they're applied to
    unsigned int X = 6, Y = 26;           // Default X & Y Axis defined for every button they're applied to

    Button Btn1(X, Y, Width, Height, "1", Font20, LCD_COLOR_RED, 0xFF003538, 0xFF003538);           // GUI Button Button, made from the GUI Library
    Button Btn2(X * 2 + 74, Y, Width, Height, "2", Font20, LCD_COLOR_RED, 0xFF003538, 0xFF003538);  // GUI Button Button, made from the GUI Library
    Button Btn3(X * 2 + 154, Y, Width, Height, "3", Font20, LCD_COLOR_RED, 0xFF003538, 0xFF003538); // GUI Button Button, made from the GUI Library

    Button Btn4(X, Y + 55, Width, Height, "4", Font20, LCD_COLOR_RED, 0xFF003538, 0xFF003538);            // GUI Button Button, made from the GUI Library
    Button Btn5(X * 2 + 74, Y + 55, Width, Height, "5", Font20, LCD_COLOR_RED, 0xFF003538, 0xFF003538);   // GUI Button Button, made from the GUI Library
    Button Btn6(X * 2 + 154, Y + +55, Width, Height, "6", Font20, LCD_COLOR_RED, 0xFF003538, 0xFF003538); // GUI Button Button, made from the GUI Library

    Button Btn7(X, Y + 110, Width, Height, "7", Font20, LCD_COLOR_RED, 0xFF003538, 0xFF003538);           // GUI Button Button, made from the GUI Library
    Button Btn8(X * 2 + 74, Y + 110, Width, Height, "8", Font20, LCD_COLOR_RED, 0xFF003538, 0xFF003538);  // GUI Button Button, made from the GUI Library
    Button Btn9(X * 2 + 154, Y + 110, Width, Height, "9", Font20, LCD_COLOR_RED, 0xFF003538, 0xFF003538); // GUI Button Button, made from the GUI Library

    while (1)
	{
		if (Btn1.Touched())
		{
			roomNumber = 1;                    // Define Building 1 as our chosen building
        }
		if (Btn2.Touched())
		{
			roomNumber = 2;                    // Define Building 2 as our chosen building
		}
		if (Btn3.Touched())
		{
			roomNumber = 3;                    // Define Building 3 as our chosen building
		}
		if (Btn4.Touched())
		{
			roomNumber = 4;                    // Define Building 4 as our chosen building
		}
		if (Btn5.Touched())
		{
			roomNumber = 5;                    // Define Building 5 as our chosen building
		}
		if (Btn6.Touched())
		{
			roomNumber = 6;                    // Define Building 6 as our chosen building
		}
		if (Btn7.Touched())
		{
			roomNumber = 7;                    // Define Building 7 as our chosen building
		}
		if (Btn8.Touched())
		{
			roomNumber = 8;                    // Define Building 8 as our chosen building
		}
		if (Btn9.Touched())
		{
			roomNumber = 9;                    // Define Building 8 as our chosen building
		}
	wait(0.1f);
}
}

void LoadStartScreen()
{
    LoadBorder();

    unsigned int Width = 75, Height = 50; // Default Width & Height defined for every button they're applied to
    unsigned int X = 6, Y = 26;           // Default X & Y Axis defined for every button they're applied to

    Button Btn1(X, Y, Width, Height, "1", Font24, LCD_COLOR_RED, 0xFF003538, 0xFF003538);           // GUI Button Button, made from the GUI Library
    Button Btn2(X * 2 + 74, Y, Width, Height, "2", Font24, LCD_COLOR_RED, 0xFF003538, 0xFF003538);  // GUI Button Button, made from the GUI Library
    Button Btn3(X * 2 + 154, Y, Width, Height, "3", Font24, LCD_COLOR_RED, 0xFF003538, 0xFF003538); // GUI Button Button, made from the GUI Library
    Button Btn4(X * 2 + 234, Y, Width, Height, "4", Font24, LCD_COLOR_RED, 0xFF003538, 0xFF003538); // GUI Button Button, made from the GUI Library

    Button Btn5(X, Y + 55, Width, Height, "5", Font24, LCD_COLOR_RED, 0xFF003538, 0xFF003538);           // GUI Button Button, made from the GUI Library
    Button Btn6(X * 2 + 74, Y + 55, Width, Height, "6", Font24, LCD_COLOR_RED, 0xFF003538, 0xFF003538);  // GUI Button Button, made from the GUI Library
    Button Btn7(X * 2 + 154, Y + 55, Width, Height, "7", Font24, LCD_COLOR_RED, 0xFF003538, 0xFF003538); // GUI Button Button, made from the GUI Library
    Button Btn8(X * 2 + 234, Y + 55, Width, Height, "8", Font24, LCD_COLOR_RED, 0xFF003538, 0xFF003538); // GUI Button Button, made from the GUI Library

    while (1)
	{
		if (Btn1.Touched())
		{
			buildingNumber = 1;                // Define Building 1 as our chosen building
            LoadRoomScreen();
		}
		if (Btn2.Touched())
		{
			buildingNumber = 2;                // Define Building 2 as our chosen building
            LoadRoomScreen();
		}
		if (Btn3.Touched())
		{
			buildingNumber = 3;                // Define Building 3 as our chosen building
            LoadRoomScreen();
		}
		if (Btn4.Touched())
		{
			buildingNumber = 4;                // Define Building 4 as our chosen building
            LoadRoomScreen();
		}
		if (Btn5.Touched())
		{
			buildingNumber = 5;                // Define Building 5 as our chosen building
            LoadRoomScreen();
		}
		if (Btn6.Touched())
		{
			buildingNumber = 6;                // Define Building 6 as our chosen building
            LoadRoomScreen();
		}
		if (Btn7.Touched())
		{
			buildingNumber = 7;                // Define Building 7 as our chosen building
            LoadRoomScreen();
		}
		if (Btn8.Touched())
		{
			buildingNumber = 8;                // Define Building 8 as our chosen building
            LoadRoomScreen();
		}
	}
}

void LoadUpdateingLabels()
{
    Label TempLabel(lcd.GetXSize() / 2, 45, "", Label::CENTER, Font16, LCD_COLOR_WHITE, 0xFF003538);

    while(1)
    {
        if (!GetCelTemp)
        {
            sprintf((char *)tempText, "%2.1f'F", tempResult);
            TempLabel.Draw(ToString((char *)tempText), LCD_COLOR_RED);
        }
        else
        {
            sprintf((char *)tempText, "%2.1f'C", tempResult);
            TempLabel.Draw(ToString((char *)tempText), LCD_COLOR_BLUE);
        }
        wait(0.2);
    }
}

void LoadMainScreen()
{
    //Baud for PuTTy 9600 Standard
    PC.baud(9600);

    LoadBorder();

    LabelUpdateThread.start(LoadUpdateingLabels);
    
    //Adds a underline to the counter text
    Button labelBtn(1, 26, 478, 60, "___________", Font16, LCD_COLOR_WHITE, 0xFF003538, 0xFF003538, 0xFF003538);

    //Allows you to toggle the LEDs
    Button MidBtn(1, 86, 478, 60, "Life Is Pointless", Font16, LCD_COLOR_WHITE, 0xFF003538, 0xFF003538, 0xFF003538);

    //Restart Button
    Button restartBtn(370, 250, 70, 20, "Restart", Font12, LCD_COLOR_WHITE, LCD_COLOR_RED, LCD_COLOR_RED);

    while (1) //Main Thread (Continued)
    {
        //Middle button (Touch)
        if (labelBtn.Touched())
        {
            GetCelTemp = !GetCelTemp;
        }
    
        //Goes if restartBtn is pressed
        if (restartBtn.Touched())
        {
            NVIC_SystemReset(); //System reset function
        }
    }
}