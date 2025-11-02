/*
 * HDC3022.h
 *
 *  Created on: Nov 1, 2025
 *      Author: TITHI
 */

#ifndef SRC_SENSOR_INTERFACE_HDC3022_H_
#define SRC_SENSOR_INTERFACE_HDC3022_H_

#define SENSORREADLOADER				  60//5
#define uSHTC_Read_Delay 				  20
#define ConfigurationRegisterCommand      0x02
#define TempAndRhMeasurementCommand       0x00
#define I2C_SlaveAddr_HDC   	0x88 // Actual Slave Address Is 0x44 and Use 7-bit Addressing Mode In Code
									 //So Slave Address Left Shift by 1-Position as Per API Requirement For Master Mode
#define MinTemp							0
#define MaxTemp							60
#define MinRH							0
#define MaxRH							100


typedef enum{Temperature = 0,Humidity}SensorType;

typedef struct{

    uint8_t ucTempAndRhDataBuffer[6];

}TemperatureData;


typedef union{

    TemperatureData TempAndHumidityData;
    uint16_t uiTempOrRHData[3];
//    uint32_t liTemperatureandRHData;

}TemperatureRHData;

extern TemperatureRHData TempAndHumidityData;
extern float fTemperatureData;
extern float fHumidityData;
extern bool bTimeToTakeSensor_Data;
extern bool bSHTC_Read_Delay ;
extern uint8_t uSHTC_Delay_counter;
extern float fAVG_Ambient;
extern float fSUM_Ambient;
extern bool bSHTC_Sensor_Open;
extern uint16_t uAVG_Couner;
extern bool bSHTC_read_complite ;
extern int32_t uSensorDateReadCounter;

//==================================================================================================================================================
//Function Name		: bool ReadDataFromHdc (void)
//Preconditions		:
//Input Parameter	:
//Return Value		: none
//Dependencies		: i2c interface
//Overview          : This function oprate SHTC3 humidity and temprature ic. need to set flag"bTimeToTakeSHTC_Data = true;" at every 1 sec from timer.
//Author			: hardik patel / rajan hingu
//Date				:21-07-2023
//Revision			: 0
//Date				:
//==================================================================================================================================================
bool ReadDataFromHdc (void);

//==================================================================================================================================================
//Function Name		: void TemperatureHumidityDataConversion (void)
//Preconditions		:
//Input Parameter	:
//Return Value		: none
//Dependencies		: i2c interface
//Overview          : This function is makes reading of temperature and RH using equations.
//Author			: hardik patel / rajan hingu
//Date				:21-07-2023
//Revision			: 0
//Date				:
//==================================================================================================================================================
void TemperatureHumidityDataConversion (void);

#endif /* SRC_SENSOR_INTERFACE_HDC3022_H_ */
