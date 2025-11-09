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
#include "HDC3022.h"
#include "Timer.h"
#include "RTC.h"
#include "EEPROM.h"
#include "LCD_Interface.h"
#include "BatchConfig.h"
#include "SleepPower.h"
#include "BatMesure.h"




extern ADC_HandleTypeDef hadc1;
extern I2C_HandleTypeDef hi2c3;
extern SPI_HandleTypeDef hspi3;
extern TIM_HandleTypeDef htim16;
extern LCD_HandleTypeDef hlcd;
extern RTC_HandleTypeDef hrtc;
#endif /* INC_HARDWARECONFIG_H_ */
