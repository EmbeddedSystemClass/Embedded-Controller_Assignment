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

//Toggles LED
void LEDToggle()
{
    led = !led;
}

//Convert Non-constant into constant
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

    //Border Color
    lcd.SetTextColor(LCD_COLOR_WHITE);

    //Border Lines
    lcd.DrawRect(0, 25, 479, 225);
}

void LoadUpdateingLabels()
{
    //Label holding the Temperature input result
    Label TempLabel(lcd.GetXSize() / 2, 45, "", Label::CENTER, Font16, LCD_COLOR_WHITE, 0xFF003538);

    //Label holding the Light input result
    Label LightLabel(lcd.GetXSize() / 2, 105, "", Label::CENTER, Font16, LCD_COLOR_WHITE, 0xFF003538);
    //Label holding Good day / Goodnight text depending on light result
    Label LightLabelText(lcd.GetXSize() / 2, 80, "Good day", Label::CENTER, Font16, LCD_COLOR_WHITE, 0xFF003538);

    //Label holding the Sound input result
    Label SoundLabel(lcd.GetXSize() / 2, 165, "", Label::CENTER, Font16, LCD_COLOR_WHITE, 0xFF003538);
    //Label holding warning text depending on sound result
    Label SoundLabelText(lcd.GetXSize() / 2, 140, "Warning: Noice!", Label::CENTER, Font16, LCD_COLOR_WHITE, 0xFF003538);

    while(1)
    {
        if (!GetCelTemp)
        {
            //Converts and outputs Temperature result to Label in 'F
            sprintf((char *)tempText, "%2.1f'F", tempResult);
            TempLabel.Draw(ToString((char *)tempText), LCD_COLOR_RED); //Redraw Label
        }
        else
        {
            //Converts and outputs Temperature result to Label in 'C
            sprintf((char *)tempText, "%2.1f'C", tempResult);
            TempLabel.Draw(ToString((char *)tempText), LCD_COLOR_LIGHTBLUE); //Redraw Label
        }

        //Converts and outputs Light result to Label
        sprintf((char *)lightText, "%2.1f'L", lightResult);
        LightLabel.Draw(ToString((char *)lightText), LCD_COLOR_WHITE); //Redraw Label

        //Converts and outputs Sound result to Label
        sprintf((char *)soundText, "%2.0f'dB", soundResult);

        if (soundResult > 80)
        {
            SoundLabel.Draw(ToString((char *)soundText), LCD_COLOR_LIGHTRED); //Redraw Label
        }
        else if (soundResult > 60 && soundResult < 80)
        {
            SoundLabel.Draw(ToString((char *)soundText), LCD_COLOR_YELLOW); //Redraw Label
        }
        else
        {
            SoundLabel.Draw(ToString((char *)soundText), LCD_COLOR_DARKGREEN); //Redraw Label
        }

        //Updates Light Label
        if (lightResult > 150)
        {
            LightLabelText.Draw("Good day", LCD_COLOR_YELLOW); //Redraw Label
        }
        else
        {
            LightLabelText.Draw("Goodnight", LCD_COLOR_GRAY); //Redraw Label
        }

        //Updates Sound Label
        if (soundResult > 80)
        {
            //Toggles LED
            LEDToggle();
            SoundLabelText.Draw("Warning: Noise!", LCD_COLOR_LIGHTRED); //Redraw Label
        }
        else
        {
            led = 0;
            SoundLabelText.Draw("", LCD_COLOR_WHITE); //Redraw Label
        }

        wait(0.2);
    }
}

void LoadMainScreen()
{
    //Baud for PuTTy 9600 Standard
    PC.baud(9600);

    //Posts the Building number input to serial
    PC.printf("\rBuilding: %d\r\n", buildingNumber);

    //Posts the Room number input to serial
    PC.printf("\rRoom: %d\r\n", roomNumber);

    //Draw the main border
    LoadBorder();

    //Start thread for updating labels
    LabelUpdateThread.start(LoadUpdateingLabels);
    
    //Changes the temperature unit displayed & posts the input to serial
    Button labelBtnTemp(1, 26, 478, 60, "___________", Font16, LCD_COLOR_WHITE, 0xFF003538, 0xFF003538, 0xFF003538);

    //Posts the input to serial
    Button labelBtnLight(1, 86, 478, 60, "___________", Font16, LCD_COLOR_WHITE, 0xFF003538, 0xFF003538, 0xFF003538);

    //Posts the input to serial
    Button labelBtnSound(1, 146, 478, 60, "___________", Font16, LCD_COLOR_WHITE, 0xFF003538, 0xFF003538, 0xFF003538);

    //Restart Button
    Button restartBtn(370, 251, 70, 20, "Restart", Font12, LCD_COLOR_WHITE, LCD_COLOR_RED, LCD_COLOR_RED);

    //Building number display
    uint8_t buildingText[20];
    sprintf((char *)buildingText, "Building: %d    Room: %d", buildingNumber, roomNumber);
    Label BuildingLabel(20, lcd.GetYSize() - 15, (char *)buildingText, Label::CENTER, Font12, LCD_COLOR_BLUE, 0xFF003538);

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

    uint16_t Width = 75, Height = 50; // Default Width & Height Setd for every button they're applied to
    uint16_t X = 125, Y = 50; // Default X & Y Axis Setd for every button they're applied to
    uint16_t spaceX = 15, spaceY = 20; // Default X & Y Axis Setd for every button they're applied to

    const string rooms[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

    ButtonGroup RoomGroup(X, Y, Width, Height, 9, rooms, spaceX, spaceY, 3, -1, Font24, LCD_COLOR_RED, 0xFF003538, 0xFF003538);
    while (1)
	{
		if (RoomGroup.Touched(0))
		{
			roomNumber = 1;                    //Set Room 1 as the selected room
            LoadMainScreen();
        }
		if (RoomGroup.Touched(1))
		{
			roomNumber = 2;                    //Set Room 2 as the selected room
            LoadMainScreen();
		}
		if (RoomGroup.Touched(2))
		{
			roomNumber = 3;                    //Set Room 3 as the selected room
            LoadMainScreen();
		}
		if (RoomGroup.Touched(3))
		{
			roomNumber = 4;                    //Set Room 4 as the selected room
            LoadMainScreen();
		}
		if (RoomGroup.Touched(4))
		{
			roomNumber = 5;                    //Set Room 5 as the selected room
            LoadMainScreen();
		}
		if (RoomGroup.Touched(5))
		{
			roomNumber = 6;                    //Set Room 6 as the selected room
            LoadMainScreen();
		}
		if (RoomGroup.Touched(6))
		{
			roomNumber = 7;                    //Set Room 7 as the selected room
            LoadMainScreen();
		}
		if (RoomGroup.Touched(7))
		{
			roomNumber = 8;                    //Set Room 8 as the selected room
            LoadMainScreen();
		}
		if (RoomGroup.Touched(8))
		{
			roomNumber = 9;                    //Set Room 9 as the selected room
            LoadMainScreen();
		}

    }
}

void LoadStartScreen()
{
    wait(0.2);

    LoadBorder();

    uint16_t Width = 75, Height = 50; // Default Width & Height Setd for every button they're applied to
    uint16_t X = 125, Y = 50; // Default X & Y Axis Setd for every button they're applied to
    uint16_t spaceX = 15, spaceY = 20; // Default X & Y Axis Setd for every button they're applied to

    const string buildings[] = { "1", "2", "3", "4", "5", "6", "7", "8" };

    ButtonGroup BuildingGroup(X, Y, Width, Height, 8, buildings, spaceX, spaceY, 3, -1, Font24, LCD_COLOR_RED, 0xFF003538, 0xFF003538);

    while (1)
	{
		if (BuildingGroup.Touched(0))
		{
			buildingNumber = 1;                //Set Building 1 as the selected building
            LoadRoomScreen();
		}
		if (BuildingGroup.Touched(1))
		{
			buildingNumber = 2;                //Set Building 2 as the selected building
            LoadRoomScreen();
		}
		if (BuildingGroup.Touched(2))
		{
			buildingNumber = 3;                //Set Building 3 as the selected building
            LoadRoomScreen();
		}
		if (BuildingGroup.Touched(3))
		{
			buildingNumber = 4;                //Set Building 4 as the selected building
            LoadRoomScreen();
		}
		if (BuildingGroup.Touched(4))
		{
			buildingNumber = 5;                //Set Building 5 as the selected building
            LoadRoomScreen();
		}
		if (BuildingGroup.Touched(5))
		{
			buildingNumber = 6;                //Set Building 6 as the selected building
            LoadRoomScreen();
		}
		if (BuildingGroup.Touched(6))
		{
			buildingNumber = 7;                //Set Building 7 as the selected building
            LoadRoomScreen();
		}
		if (BuildingGroup.Touched(7))
		{
			buildingNumber = 8;                //Set Building 8 as the selected building
            LoadRoomScreen();
		}

        wait(0.2);
	}
}