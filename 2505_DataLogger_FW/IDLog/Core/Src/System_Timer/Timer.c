/*
 * Timer.c
 *
 *  Created on: Nov 1, 2025
 *      Author: TITHI
 */

#include "HardwareConfig.h"

#define ONEMILLISECONDLOADER           1
#define TENMILLISECONDLOADER           10// 10
#define FIVEHUNDREDMILLISECONDLOADER   50  // 2000
#define ONESECONDLOADER                1000
#define FIVESECONDLOADER               5000

uint32_t uiOneMilliSecondLocalISRInterruptCounter           =     ONEMILLISECONDLOADER;
uint32_t uiTenMilliSecondLocalISRInterruptCounter           =     TENMILLISECONDLOADER;
uint32_t uiFiveHundredMilliSecondLocalISRInterruptCounter   =     FIVEHUNDREDMILLISECONDLOADER;
uint32_t uiOneSecondLocalISRInterruptCounter                =     ONESECONDLOADER;
uint32_t uiFiveSecondLocalISRInterruptCounter               =     FIVESECONDLOADER;

bool bOne_Secend_Timer_Flag = false;
bool b50ms_Flag = false;
//bool bSensor_DataReadFlag = false;
//==================================================================================================================================================
//Function Name		: void App_TimerHandler(void)
//Preconditions		: call this function on 250uS tick.
//Input Parameter	:
//Return Value		: none
//Dependencies		: Timer interrupt.
//Overview          : This function ganerate 1mS , 10 mS , 500 mS , 1 Sec and 5 Sec tick.
//Author			: hardik patel
//Date				:
//Revision			: 0
//Date				:
//==================================================================================================================================================

void App_TimerHandler(void)
{

    /* 1mSec Local ISR Interrupt*/
    uiOneMilliSecondLocalISRInterruptCounter--;
    if(uiOneMilliSecondLocalISRInterruptCounter <=  0)
    {
        TimerInterrupt_1mSec_CallingFunction();
        uiOneMilliSecondLocalISRInterruptCounter =  ONEMILLISECONDLOADER;
    }

    /* 10mSec Local ISR Interrupt*/
    uiTenMilliSecondLocalISRInterruptCounter--;
    if(uiTenMilliSecondLocalISRInterruptCounter <=  0)
    {
        TimerInterrupt_10mSec_CallingFunction();
        uiTenMilliSecondLocalISRInterruptCounter =  TENMILLISECONDLOADER;
    }

    /* 500mSec Local ISR Interrupt*/
    uiFiveHundredMilliSecondLocalISRInterruptCounter--;
    if(uiFiveHundredMilliSecondLocalISRInterruptCounter <= 0)
    {
        TimerInterrupt_500mSec_CallingFunction();
        uiFiveHundredMilliSecondLocalISRInterruptCounter =   FIVEHUNDREDMILLISECONDLOADER;
    }

    /* 1Sec Local ISR Interrupt*/
    uiOneSecondLocalISRInterruptCounter--;
    if(uiOneSecondLocalISRInterruptCounter <=  0)
    {
        TimerInterrupt_1Sec_CallingFunction();
        uiOneSecondLocalISRInterruptCounter =  ONESECONDLOADER;
    }

    /* 5Sec Local ISR Interrupt*/
    uiFiveSecondLocalISRInterruptCounter--;
    if(uiFiveSecondLocalISRInterruptCounter <=  0)
    {
        TimerInterrupt_5Sec_CallingFunction();
        uiFiveSecondLocalISRInterruptCounter =  FIVESECONDLOADER;
    }
}

//==================================================================================================================================================
//Function Name		: void TimerInterrupt_1mSec_CallingFunction(void)
//Preconditions		:
//Input Parameter	:
//Return Value		: none
//Dependencies		: Timer interrupt.
//Overview          : This function call at every 1 mS.
//Author			:
//Date				:
//Revision			: 0
//Date				:
//==================================================================================================================================================

void TimerInterrupt_1mSec_CallingFunction(void)
{
//	b1mSflag_for_serial = true;
	if(bSHTC_Read_Delay == true)
	{
		uSHTC_Delay_counter--;
		if(uSHTC_Delay_counter == 0)
		{
			bSHTC_Read_Delay = false;
		}
	}

//	b400ms_Falg_var ++;
//	if(b400ms_Falg_var == 100)
//	{
//		b400ms_Falg = true;
//
//	}

}

//==================================================================================================================================================
//Function Name		: void TimerInterrupt_10mSec_CallingFunction(void)
//Preconditions		:
//Input Parameter	:
//Return Value		: none
//Dependencies		: Timer interrupt.
//Overview          : This function call at every 10 mS.
//Author			:
//Date				:
//Revision			: 0
//Date				:
//==================================================================================================================================================

void TimerInterrupt_10mSec_CallingFunction(void)
{
//	bOne_Secend_Timer_Flag = 	true;
}

//==================================================================================================================================================
//Function Name		: void TimerInterrupt_500mSec_CallingFunction(void)
//Preconditions		:
//Input Parameter	:
//Return Value		: none
//Dependencies		: Timer interrupt.
//Overview          : This function call at every 500 mS.
//Author			:
//Date				:
//Revision			: 0
//Date				:
//==================================================================================================================================================
void TimerInterrupt_500mSec_CallingFunction(void)
{
	b50ms_Flag = true;
}

//==================================================================================================================================================
//Function Name		: void TimerInterrupt_1Sec_CallingFunction(void)
//Preconditions		:
//Input Parameter	:
//Return Value		: none
//Dependencies		: Timer interrupt.
//Overview          : This function call at every 1 Sec.
//Author			:
//Date				:
//Revision			: 0
//Date				:
//==================================================================================================================================================
void TimerInterrupt_1Sec_CallingFunction(void)
{
//	bTimeRefreshDisplay = true; //this flag define temporary for testing

	uSensorDateReadCounter--;
	if(uSensorDateReadCounter <= 0)
	{
		uSensorDateReadCounter = SENSORREADLOADER;
		bTimeToTakeSensor_Data = true;
	}

	ucDisplayRefreshCounter--;
	if(ucDisplayRefreshCounter <= 0)
	{
		ucDisplayRefreshCounter = DISPLAYREFRESH_LCD_OFF;
		bTimeRefreshDisplay = true;
	}

	bOne_Secend_Timer_Flag = true;

	HAL_GPIO_TogglePin(HB_LED_GPIO_Port,HB_LED_Pin);
}

//==================================================================================================================================================
//Function Name		: void TimerInterrupt_5Sec_CallingFunction(void)
//Preconditions		:
//Input Parameter	:
//Return Value		: none
//Dependencies		: Timer interrupt.
//Overview          : This function call at every 5 Sec.
//Author			:
//Date				:
//Revision			: 0
//Date				:
//==================================================================================================================================================
void TimerInterrupt_5Sec_CallingFunction(void)
{


}
