/*
 * HDC3022.c
 *
 *  Created on: Nov 1, 2025
 *      Author: TITHI
 */

#include "HardwareConfig.h"


static enum {

   DataWriteMode =0,
   DataReadMode,

}DataStatusMode = DataWriteMode ;

uint8_t ucDataWriteBufferhdc[5] = {0};
uint8_t ucDataReadBufferhdc[6] = {0};
float fTemperatureData = 0;
float fHumidityData = 0;
float fTemperatureDataInFahrenheit =0;
float fAVG_Ambient = 0;
float fSUM_Ambient = 0;
uint16_t uAVG_Couner = 0;
bool bTimeToTakeSensor_Data = true;
bool bSHTC_Read_Delay = false;
bool bSHTC_Sensor_Open = false;
bool bSHTC_read_complite = false;
uint8_t uSHTC_Delay_counter = uSHTC_Read_Delay;

int32_t uSensorDateReadCounter = SENSORREADLOADER;

TemperatureRHData TempAndHumidityData;

//==================================================================================================================================================
//Function Name		: bool ReadDataFromHdc (void)
//Preconditions		:
//Input Parameter	:
//Return Value		: none
//Dependencies		: i2c interface
//Overview          : This function oprate SHTC3 humidity and temprature ic. need to set flag"bTimeToTakeSHTC_Data = true;" at every 1 sec from timer.
//Author			: hardik patel
//Date				:21-07-2023
//Revision			: 0
//Date				:
//==================================================================================================================================================

bool ReadDataFromHdc (void)
{
	switch(DataStatusMode)
	{

		case DataWriteMode:
		{
			if(bSHTC_Read_Delay == false)
			{
				ucDataWriteBufferhdc[0] = 0x24;
				ucDataWriteBufferhdc[1] = 0x00;

				if( HAL_I2C_Master_Transmit(&hi2c3,I2C_SlaveAddr_HDC ,(uint8_t *)ucDataWriteBufferhdc,2,20) == HAL_OK)
				{
					bSHTC_Sensor_Open = false;
					bSHTC_Read_Delay = true;
					uSHTC_Delay_counter = uSHTC_Read_Delay;
					DataStatusMode = DataReadMode;
				}
				else
				{
					bSHTC_Sensor_Open = true;
					bTimeToTakeSensor_Data = false;
					bSHTC_read_complite = true;
//					sci_PutByte(huart4, 'N');
//					sci_PutByte(huart4, 'O');
//					sci_PutByte(huart4, 'K');
//					sci_PutByte(huart4, ' ');
//					sci_PutByte(huart4, 'T');
//					sci_PutByte(huart4, ' ');
//					sci_PutByte(huart4, ',');
				}
			}
			break;
		}
		case DataReadMode:
		{
			if(bSHTC_Read_Delay == false)
			{
				HAL_I2C_Master_Receive(&hi2c3,I2C_SlaveAddr_HDC,(uint8_t *)ucDataReadBufferhdc,6,10);

				TempAndHumidityData.TempAndHumidityData.ucTempAndRhDataBuffer[1] = ucDataReadBufferhdc[0];
				TempAndHumidityData.TempAndHumidityData.ucTempAndRhDataBuffer[0] = ucDataReadBufferhdc[1];
				TempAndHumidityData.TempAndHumidityData.ucTempAndRhDataBuffer[2] = ucDataReadBufferhdc[4];
				TempAndHumidityData.TempAndHumidityData.ucTempAndRhDataBuffer[3] = ucDataReadBufferhdc[3];

				TemperatureHumidityDataConversion();
//				TemperatureToPercentageConversion ();
				DataStatusMode = DataWriteMode;
				bSHTC_read_complite = true;

//				sci_PutByte(huart4, 'O');
//				sci_PutByte(huart4, 'K');
//				sci_PutByte(huart4, ' ');
//				sci_PutByte(huart4, 'T');
//				sci_PutByte(huart4, ' ');
//				sci_PutByte(huart4, ',');
			}
			break;
		}

		default:
		{
		   DataStatusMode = DataWriteMode;
		   break;
		}
	}
	return true;
}


//==================================================================================================================================================
//Function Name		: void TemperatureHumidityDataConversion (void)
//Preconditions		:
//Input Parameter	:
//Return Value		: none
//Dependencies		: i2c interface
//Overview          : This function is makes reading of temperature and RH using equations.
//Author			: hardik patel
//Date				:21-07-2023
//Revision			: 0
//Date				:
//==================================================================================================================================================

void TemperatureHumidityDataConversion (void)
{
	fTemperatureData = (float)((((float)TempAndHumidityData.uiTempOrRHData[0]/65535)*175)-45);
//	fTemperatureData =  ( (fTemperatureData * cal_para.MenuScaleCoefficient[0] ) + cal_para.MenuOffsetCoefficient[0] );

	fHumidityData = (float)((((float)TempAndHumidityData.uiTempOrRHData[1])/65535)*100);
//	fHumidityData =  ((fHumidityData * cal_para.MenuScaleCoefficient[1] ) + (cal_para.MenuOffsetCoefficient[1] ));

	TemperatureToPercentageConversion();
	HumidityToPercentageConversion();
}




