/*
 * Main_App.c
 *
 *  Created on: Oct 30, 2025
 *      Author: TITHI
 */

#include "HardwareConfig.h"


void MainAppInit(void)
{
	uint8_t txData[20] = "Hello EEPROM!";
	uint8_t rxData[20];

    // Write string
//    EEPROM_WritePage(0x000000, txData, sizeof(txData));

    // Read back
    EEPROM_ReadData(0x000000, rxData, sizeof(txData));

	HAL_TIM_Base_Start_IT(&htim16);

}



void MainAppWhileFunction (void)
{
	/*-------------Sensor Reading--------------*/
	if(bTimeToTakeSensor_Data == true)
	{
		ReadDataFromHdc ();

		if(bSHTC_read_complite == true)
		{
//			Serial_Debug();
			bSHTC_read_complite = false;
			bTimeToTakeSensor_Data = false;
		}
	}

	if(bTimeRefreshDisplay == true)
	{
		UpdateDisplay();
		RefreshDisplay();
		bTimeRefreshDisplay = false;
	}

}

