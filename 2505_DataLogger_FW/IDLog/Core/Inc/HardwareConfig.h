/*
 * HardwareConfig.h
 *
 *  Created on: Oct 30, 2025
 *      Author: TITHI
 */

#ifndef INC_HARDWARECONFIG_H_
#define INC_HARDWARECONFIG_H_

#include <stdlib.h>
#include <stdbool.h>
#include "string.h"
#include "stdio.h"
#include "main.h"
#include "math.h"

#include "Main_App.h"
#include "Timer.h"
#include "HDC3022.h"
#include "EEPROM.h"



extern ADC_HandleTypeDef hadc1;
extern I2C_HandleTypeDef hi2c3;
extern SPI_HandleTypeDef hspi3;
extern TIM_HandleTypeDef htim16;
#endif /* INC_HARDWARECONFIG_H_ */
