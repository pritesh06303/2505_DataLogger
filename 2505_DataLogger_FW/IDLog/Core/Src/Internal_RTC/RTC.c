/*
 * RTC.c
 *
 *  Created on: Nov 4, 2025
 *      Author: TITHI
 */


#include "HardwareConfig.h"


RTCBUFFER CurrentRTC;
//RTCBUFFER StoredRTC;

//volatile int  uiStoreDataTime = 300;

bool bTimeToReadRTC = true;
int8_t ucReadRTCTime = READRTCTIME;
bool bBatchStartedFromKeyboardFlag = false;

unsigned char hex2bcd (unsigned char x)
{
    unsigned char y;
    y = (x / 10) << 4;
    y = y | (x % 10);
    return (y);
}


//==============================================================================================
//Function Name     : void SetRTC(RTCBUFFER *RTCStorage)
//Pre Conditions    :
//Input Parameters  :
//Return Value      :
//Overview          : Set Device RTC using this function.
//
//
//Author            : Hardik Patel
//Date              : 04 Nov 2025
//Revision          : 0
//Date              :
//===============================================================================================

void SetRTC(RTCBUFFER *RTCStorage)
{
	  RTC_TimeTypeDef sTime = {0};
	  RTC_DateTypeDef sDate = {0};

	  RTCStorage->DeviceRTC.ucSC = 0x00;   //Always Second Set To Zero When RTC Setting
	  /** Initialize RTC and set the Time and Date
	  */
	  sTime.Hours = hex2bcd(RTCStorage->DeviceRTC.ucHR);
	  sTime.Minutes = hex2bcd(RTCStorage->DeviceRTC.ucMN);
	  sTime.Seconds = hex2bcd(RTCStorage->DeviceRTC.ucSC);
	  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
	  sDate.Month = hex2bcd(RTCStorage->DeviceRTC.ucMM);
	  sDate.Date = hex2bcd(RTCStorage->DeviceRTC.ucDD);
	  sDate.Year = hex2bcd(RTCStorage->DeviceRTC.ucYY);

	  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
	  {
	    Error_Handler();
	  }
}


//==============================================================================================
//Function Name     : void ReadRTC(RTCBUFFER *RTCStorage)
//Pre Conditions    :
//Input Parameters  : Keyboard
//Return Value      :
//Overview          : This function will read RTC from Internal Registers.
//
//
//Author            : Hardik Patel
//Date              : 04 Nov 2025
//Revision          : 0
//Date              :
//===============================================================================================

void ReadRTC(RTCBUFFER *RTCStorage)
{
  RTC_DateTypeDef sdatestructureget;
  RTC_TimeTypeDef stimestructureget;

  /* Get the RTC current Time */
  HAL_RTC_GetTime(&hrtc, &stimestructureget, RTC_FORMAT_BIN);
  /* Get the RTC current Date */
  HAL_RTC_GetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BIN);
  /* Display time Format : hh:mm:ss */
//  sprintf((char*)showtime,"%02d:%02d:%02d",stimestructureget.Hours, stimestructureget.Minutes, stimestructureget.Seconds);

  RTCStorage->DeviceRTC.ucDD = sdatestructureget.Date;
  RTCStorage->DeviceRTC.ucMM = sdatestructureget.Month;
  RTCStorage->DeviceRTC.ucYY = sdatestructureget.Year;

  RTCStorage->DeviceRTC.ucHR = stimestructureget.Hours;
  RTCStorage->DeviceRTC.ucMN = stimestructureget.Minutes;
  RTCStorage->DeviceRTC.ucSC = stimestructureget.Seconds;
}

void ReadRTCFromInterrupt(uint8_t *RTCStorage, RTC_HandleTypeDef *hrtc_it)
{
  RTC_DateTypeDef sdatestructureget;
  RTC_TimeTypeDef stimestructureget;

  /* Get the RTC current Time */
  HAL_RTC_GetTime(hrtc_it, &stimestructureget, RTC_FORMAT_BIN);
  /* Get the RTC current Date */
  HAL_RTC_GetDate(hrtc_it, &sdatestructureget, RTC_FORMAT_BIN);
  /* Display time Format : hh:mm:ss */
//  sprintf((char*)showtime,"%02d:%02d:%02d",stimestructureget.Hours, stimestructureget.Minutes, stimestructureget.Seconds);

  RTCStorage[0] = sdatestructureget.Date;
  RTCStorage[1] = sdatestructureget.Month;
  RTCStorage[2] = sdatestructureget.Year;

  RTCStorage[3] = stimestructureget.Hours;
  RTCStorage[4] = stimestructureget.Minutes;
//  RTCStorage->DeviceRTC.ucSC = stimestructureget.Seconds;
}
