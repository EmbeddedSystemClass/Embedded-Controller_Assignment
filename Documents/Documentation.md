# Eternity Squid Studios Embedded Controller II:

(Created: 14-Jan-2019) by: Kristian Kraken Sarka Nielsen

### Used libraries:

    - mbed-os: v15.11 from 16/jan/2019
    - F746_GUI: from 09/mar/2018
    - Grvoe_Temperature: from 06/aug/2018


### Hardware:

    - 1x DISCO-F746G (STM32F746G-DISCO MB1191B)
    - 1x Grove Base Shield v1.3
    - 1x Grove LED socket kit v1.5
    - 1x Grove Temperature Sensor v1.2
    - 1x Grove Light Sensor v1.2
    - 1x Grove Sound Sensor v1.6
    - 1x USB-A to mini USB-B Cable 0.25M
    - 4x Danyang 26AWG (4 color) 4pin signal cabel 0.25M


### Functions:

    - Sensor with label to display converted results for Light
    - Sensor with label to display converted results for Temperature
    - Sensor with label to display converted results for Sound
    - Button for output of converted result from Light sensor to serial
    - Button for output of converted result from Temperature sensor to serial
    - Button for output of converted result from Sound sensor to serial
    - Label for display of selected Building & Room
    - A button that makes the program restart


### General User Interface:

    - Building selection page:
        - A title in the top of the sceen
        - A rectangle acting as a screen border
        - 8x Selection button

    - Room selection page:
        - A title in the top of the sceen
        - A rectangle acting as a screen border
        - 9x Selection button

    - Unit display page:
        - A title in the top of the sceen
        - A rectangle acting as a screen border
        - A Label displaying the Temperature sensor convertion result
            - Text color change with the different value types ('C & 'F)
            - A Button that outpu the displayed result to serial
        - A Label displaying the Light sensor convertion result
            - A Button that outpu the displayed result to serial
        - A Label displaying the Sound sensor convertion result
            - A Button that outpu the displayed result to serial
        - A Label saying good day and goodnight depending on Light sensor result
        - A Label warning about noise depending on Sound sensor sensor result
        - A Label displaying the selected Building & room numbers
        - a restart button at the bottom right of the screen


### Connections:

    - DISCO-F746G (STM32F746G-DISCO MB1191B)
        - PWR: PC via (USB-A to mini USB-B Cable 0.25M)
        - IO (input/output) pins: Grove Base Shield v1.3

    - Grove Base Shield v1.3
        - D2: Grove LED socket kit v1.5
        - A0: Grove Light Sensor v1.2
        - A1: Grove Temperature Sensor v1.2
        - A2: Grove Sound Sensor v1.6