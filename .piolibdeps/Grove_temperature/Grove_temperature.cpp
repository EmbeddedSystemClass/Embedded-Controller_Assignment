
/**
 ******************************************************************************
 * @file    Grove_temperature.cpp
 * @author  Toyomasa Watarai
 * @version V1.0.0
 * @date    6 Aug 2018
 * @brief   Seeed grove temperature sensor class implementation
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

#include "Grove_temperature.h"

Grove_temperature::Grove_temperature(PinName ain)
    : _ain(ain)
{
}

Grove_temperature::~Grove_temperature()
{
}

float Grove_temperature::getTemperature()
{
    const int B = 4275;               // B value of the thermistor
    const int R0 = 100000;            // R0 = 100k

    float R = 1.0f/_ain.read() - 1.0f;
    R = R0*R;

    float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15; // convert to temperature via datasheet
    return temperature;
}
