/*
 * BatMesure.c
 *
 *  Created on: Nov 4, 2025
 *      Author: TITHI
 */

#include "HardwareConfig.h"

float batvolt = 3.0;
//==================================================================================================================================================
//Function Name		: bool Read_Vbat_Reading(float *value)
//Preconditions		: none
//Input Parameter	: none.
//Return Value		: bool true
//Dependencies		: Battery voltage. but in schematic USB is inserted then Vbat pin voltage = USB voltage so that time mesure wrong Vbat Voltage.
//Overview          : Mesure battery voltage.
//Author			: Harik Patel
//Date				: 04 Nov 2025
//Revision			: 0
//Date				:
//==================================================================================================================================================

bool Read_Vbat_Reading(float *value)
{
	int16_t avg[8]={0};
	uint32_t sum=0;
//	uint8_t temps[10] = {0};
	float vbatread = 0.0;
	ADC_ChannelConfTypeDef sConfig = { 0 };

	sConfig.Channel = ADC_CHANNEL_VBAT;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;

	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
	HAL_ADC_Start(&hadc1);

	for(int counter=0;counter<8;counter++)
	{
		HAL_ADC_PollForConversion(&hadc1,100);

		avg[counter]= HAL_ADC_GetValue(&hadc1);
		sum = sum+avg[counter];
	}
	HAL_ADC_Stop(&hadc1);
	sum=sum>>3;
//	sci_Put_Int32bit(huart2 , sum);
	vbatread = (1.471076E-03*sum) + 1.248320E-01;

//	FloatToAscii(0, &temps[0], 7, vbatread, 2);
//	sci_PutByte(huart2,' ');
//	sci_PutByte(huart2,temps[0]);
//	sci_PutByte(huart2,temps[1]);
//	sci_PutByte(huart2,temps[2]);
//	sci_PutByte(huart2,temps[3]);
//	sci_PutByte(huart2,temps[4]);
//	sci_PutByte(huart2,temps[5]);
//	sci_PutByte(huart2,temps[6]);
//	sci_PutByte(huart2,'\r');
//	sci_PutByte(huart2,'\n');
	*value = vbatread;
	Battery_Bar_Update();
	return true;

}
