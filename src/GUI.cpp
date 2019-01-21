#include "mbed.h"
#include "F746_GUI.hpp"

LCD_DISCO_F746NG lcd;

Serial PC(USBTX, USBRX);
DigitalOut led(D2);


extern bool GetCelTemp;

extern float tempResult;
extern float soundResult;
extern float lightResult;


int buildingNumber = 0;
int roomNumber = 0;

bool doWhile = false;

uint8_t tempText[10];
uint8_t lightText[10];
uint8_t soundText[10];


Thread LabelUpdateThread;


void LEDToggle()
{
    led = !led;
}

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

void LoadUpdateingLabels()
{
    Label TempLabel(lcd.GetXSize() / 2, 45, "", Label::CENTER, Font16, LCD_COLOR_WHITE, 0xFF003538);

    Label LightLabel(lcd.GetXSize() / 2, 105, "", Label::CENTER, Font16, LCD_COLOR_WHITE, 0xFF003538);
    Label LightLabelText(lcd.GetXSize() / 2, 80, "Good day", Label::CENTER, Font16, LCD_COLOR_WHITE, 0xFF003538);

    Label SoundLabel(lcd.GetXSize() / 2, 165, "", Label::CENTER, Font16, LCD_COLOR_WHITE, 0xFF003538);
    Label SoundLabelText(lcd.GetXSize() / 2, 140, "Warning: Noice!", Label::CENTER, Font16, LCD_COLOR_WHITE, 0xFF003538);

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

        sprintf((char *)lightText, "%2.1f'L", lightResult);
        LightLabel.Draw(ToString((char *)lightText), LCD_COLOR_WHITE);

        sprintf((char *)soundText, "%2.0f'dB", soundResult);
        SoundLabel.Draw(ToString((char *)soundText), LCD_COLOR_WHITE);

        if (lightResult > 150)
        {
            LightLabelText.Draw("Good day", LCD_COLOR_WHITE);
        }
        else
        {
            LightLabelText.Draw("Goodnight", LCD_COLOR_WHITE);
        }

        if (soundResult > 80)
        {
            LEDToggle();
            SoundLabelText.Draw("Warning: Noice!", LCD_COLOR_WHITE);
        }
        else
        {
            led = 0;
            SoundLabelText.Draw("", LCD_COLOR_WHITE);
        }

        wait(0.2);
    }
}

void LoadMainScreen()
{
    //Baud for PuTTy 9600 Standard
    PC.baud(9600);

    PC.printf("\rBuilding: %d\r\n", buildingNumber);
    PC.printf("\rRoom: %d\r\n", roomNumber);

    LoadBorder();

    //Start thread for updating labels
    LabelUpdateThread.start(LoadUpdateingLabels);
    
    //Adds a underline to the counter text
    Button labelBtnTemp(1, 26, 478, 60, "___________", Font16, LCD_COLOR_WHITE, 0xFF003538, 0xFF003538, 0xFF003538);

    //Allows you to toggle the LEDs
    Button labelBtnLight(1, 86, 478, 60, "___________", Font16, LCD_COLOR_WHITE, 0xFF003538, 0xFF003538, 0xFF003538);

    Button labelBtnSound(1, 146, 478, 60, "___________", Font16, LCD_COLOR_WHITE, 0xFF003538, 0xFF003538, 0xFF003538);

    //Restart Button
    Button restartBtn(370, 251, 70, 20, "Restart", Font12, LCD_COLOR_WHITE, LCD_COLOR_RED, LCD_COLOR_RED);

    //Building number display
    uint8_t buildingText[20];
    sprintf((char *)buildingText, "Building: %d", buildingNumber);
    Label BuildingLabel(20, lcd.GetYSize() - 15, (char *)buildingText, Label::CENTER, Font12, LCD_COLOR_BLUE, 0xFF003538);

    //Room number display
    uint8_t RoomText[20];
    sprintf((char *)RoomText, "Room: %d", roomNumber);
    Label RoomLabel(120, lcd.GetYSize() - 15, (char *)RoomText, Label::CENTER, Font12, LCD_COLOR_BLUE, 0xFF003538);

    wait(2.0);

    while (1) //Main Thread (Continued)
    {
        //Temperature button (Touch)
        if (labelBtnTemp.Touched())
        {
            GetCelTemp = !GetCelTemp; // Selects the Temperature unit, if true then 'C else 'F

            if (!GetCelTemp)
            {
                //Prints Teperature input to serial in 'C
                PC.printf("\rTemp: %2.1f'C\r\n", tempResult);
            }
            else
            {
                //Prints Teperature input to serial in 'F
                PC.printf("\rTemp: %2.1f'F\r\n", tempResult);
            }

            wait(2.0); //Waits after button press
        }

        //Light button (Touch)
        if (labelBtnLight.Touched())
        {
            //Prints Light input to serial
            PC.printf("\rLight: %2.1f'L\r\n", lightResult);
            wait(2.0); //Waits after button press
        }

        //Sound button (Touch)
        if (labelBtnSound.Touched())
        {
            //Prints Sound input to serial
            PC.printf("\rSound: %2.0f'dB\r\n", soundResult);
            wait(2.0); //Waits after button press
        }
    
        //Goes if restartBtn is pressed
        if (restartBtn.Touched())
        {
            NVIC_SystemReset(); //System reset function
        }
    }
}

void LoadRoomScreen()
{
    wait(0.2);

    LoadBorder();

    uint16_t Width = 75, Height = 50; // Default Width & Height defined for every button they're applied to
    uint16_t X = 6, Y = 50; // Default X & Y Axis defined for every button they're applied to
    uint16_t spaceX = 15, spaceY = 20; // Default X & Y Axis defined for every button they're applied to

    const string rooms[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

    ButtonGroup RoomGroup(X, Y, Width, Height, 9, rooms, spaceX, spaceY, 2, -1, Font24, LCD_COLOR_RED, 0xFF003538, 0xFF003538);
    while (1)
	{
		if (RoomGroup.Touched(0))
		{
			roomNumber = 1;                    //Define Room 1 as the selected room
            LoadMainScreen();
        }
		if (RoomGroup.Touched(1))
		{
			roomNumber = 2;                    //Define Room 2 as the selected room
            LoadMainScreen();
		}
		if (RoomGroup.Touched(2))
		{
			roomNumber = 3;                    //Define Room 3 as the selected room
            LoadMainScreen();
		}
		if (RoomGroup.Touched(3))
		{
			roomNumber = 4;                    //Define Room 4 as the selected room
            LoadMainScreen();
		}
		if (RoomGroup.Touched(4))
		{
			roomNumber = 5;                    //Define Room 5 as the selected room
            LoadMainScreen();
		}
		if (RoomGroup.Touched(5))
		{
			roomNumber = 6;                    //Define Room 6 as the selected room
            LoadMainScreen();
		}
		if (RoomGroup.Touched(6))
		{
			roomNumber = 7;                    //Define Room 7 as the selected room
            LoadMainScreen();
		}
		if (RoomGroup.Touched(7))
		{
			roomNumber = 8;                    //Define Room 8 as the selected room
            LoadMainScreen();
		}
		if (RoomGroup.Touched(8))
		{
			roomNumber = 9;                    //Define Room 9 as the selected room
            LoadMainScreen();
		}

    }
}

void LoadStartScreen()
{
    wait(0.2);

    LoadBorder();

    uint16_t Width = 75, Height = 50; // Default Width & Height defined for every button they're applied to
    uint16_t X = 6, Y = 50;           // Default X & Y Axis defined for every button they're applied to
    uint16_t spaceX = 15, spaceY = 20;           // Default X & Y Axis defined for every button they're applied to

    const string buildings[] = { "1", "2", "3", "4", "5", "6", "7", "8" };

    ButtonGroup BuildingGroup(X, Y, Width, Height, 8, buildings, spaceX, spaceY, 2, -1, Font24, LCD_COLOR_RED, 0xFF003538, 0xFF003538);

    while (1)
	{
		if (BuildingGroup.Touched(0))
		{
			buildingNumber = 1;                //Define Building 1 as the selected building
            LoadRoomScreen();
		}
		if (BuildingGroup.Touched(1))
		{
			buildingNumber = 2;                //Define Building 2 as the selected building
            LoadRoomScreen();
		}
		if (BuildingGroup.Touched(2))
		{
			buildingNumber = 3;                //Define Building 3 as the selected building
            LoadRoomScreen();
		}
		if (BuildingGroup.Touched(3))
		{
			buildingNumber = 4;                //Define Building 4 as the selected building
            LoadRoomScreen();
		}
		if (BuildingGroup.Touched(4))
		{
			buildingNumber = 5;                //Define Building 5 as the selected building
            LoadRoomScreen();
		}
		if (BuildingGroup.Touched(5))
		{
			buildingNumber = 6;                //Define Building 6 as the selected building
            LoadRoomScreen();
		}
		if (BuildingGroup.Touched(6))
		{
			buildingNumber = 7;                //Define Building 7 as the selected building
            LoadRoomScreen();
		}
		if (BuildingGroup.Touched(7))
		{
			buildingNumber = 8;                //Define Building 8 as the selected building
            LoadRoomScreen();
		}

        wait(0.2);
	}
}