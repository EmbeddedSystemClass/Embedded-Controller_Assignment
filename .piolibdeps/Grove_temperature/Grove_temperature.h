/**
 ******************************************************************************
 * @file    Grove_temperature.h
 * @author  Toyomasa Watarai
 * @version V1.0.0
 * @date    6 Aug 2018
 * @brief   This file contains the class of a grove temperature sensor with AnalogIn interface
 ******************************************************************************
 * @attention
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef MBED_GROVE_TEMPERATURE_H
#define MBED_GROVE_TEMPERATURE_H

#include "mbed.h"

/**  Interface for controlling grove temerature sensor
 *
 * @code
 * #include "mbed.h"
 * #include "Grove_temperature.h"
 *
 * Serial pc(USBTX, USBRX);
 * Grove_temperature temp(A4);
 *
 * int main() {
 *
 *     while(1) {
 *         pc.printf("%2.2f degC\n", sensor.getTemperature());
 *         wait(1);
 *     }
 * }
 *
 * @endcode
 */

/** Grove_temperature class
 *
 *  Grove_temperature: A library to correct data using Seeed Grove temperature sensor device
 *
 */
class Grove_temperature
{
public:

    /** Create a Grove_temperature instance
     *  which is connected to specified AnalogIn pins
     *
     * @param ain AnalogIn pin
     */
    Grove_temperature(PinName ain);

    /** Destructor of Grove_temperature
     */
    virtual ~Grove_temperature();


    /** Read the current temperature value (degree Celsius) from Grove temperature sensor
     *
     * @return Temperature value (degree Celsius)
     */
    float getTemperature(void);


private:

    AnalogIn    _ain;

};

#endif // MBED_GROVE_TEMPERATURE_H
