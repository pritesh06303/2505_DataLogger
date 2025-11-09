/*
 * BatchConfig.h
 *
 *  Created on: Nov 4, 2025
 *      Author: TITHI
 */

#ifndef SRC_BATCHCONFIG_BATCHCONFIG_H_
#define SRC_BATCHCONFIG_BATCHCONFIG_H_

#define ALARMSET            'A'
#define ALARMRESET          'R'
#define DATESETTING  		'D'
#define TIMESETTING         'T'
#define SENSORERROR         'E'
#define NORMALDATA          'N'
#define PAUSEDATA           'P'
#define START               'S'

typedef union {

    struct {
        float MenuOffsetCoefficient;
        float MenuScaleCoefficient;
    };
    uint8_t ucMenuCalibration[8];
} AUTOCALIBRATIONPARAMETER;

typedef union {

    struct {
        int16_t MenuOffsetCoefficient_Mul_10000;
        int16_t MenuScaleCoefficient_Mul_10000;
    };
    uint8_t RxCalParameter[4];
} RECIVED_CAL_PARA;

extern RECIVED_CAL_PARA recived_Cal_Byte;


#define SR_NUM_LENGHT			8
#define PRODUCT_CODE_LENGHT		6
#define VERSION_LENGHT			5
#define CRC_LENGTH				4

#pragma pack(push)  // To solve structure padding issue
#pragma pack(1)
typedef struct
{
	char SrNum[SR_NUM_LENGHT];
	char ProductCode[PRODUCT_CODE_LENGHT];
	char VersionName[VERSION_LENGHT];
    char Crc[4];
}MEI_INFO;
#pragma pack(pop)


typedef enum{
	BATCH_STOP = 0xFFFF,
	BATCH_START = 0x0,
	BATCH_PAUSE = 0x1,
}BATCH_STATUS;

typedef struct
{
    uint8_t ucSecond;
    uint8_t ucMinute;
}STOREINTERVAL_t;

#define BATCH_NAME_STR_LEN 10
#define OPERATOR_NAME_STR_LEN	10

typedef enum{
	FORMAT_DD_MM_YY = 0xFF,
	FORMAT_MM_DD_YY = 0xAA,
}DATE_TIME_FORMATE;

#pragma pack(push)  // To solve structure padding issue
#pragma pack(1)
typedef struct
{
	char BatchName[BATCH_NAME_STR_LEN];
	char OperatorName[OPERATOR_NAME_STR_LEN];
	RTCBUFFER StartTime;
	STOREINTERVAL_t StoreInterval;
	unsigned long int NoOfReadings;
	int16_t TemperatureAlarmHigh;
	int16_t TemperatureAlarmLow;
	uint8_t AlarmHighDelayHR;  //RHAlarmHigh;
	uint8_t AlarmHighDelayMN;
	uint8_t AlarmLowDelayHR;   //RHAlarmLow;
	uint8_t AlarmLowDelayMN;
	uint8_t Unit;
	uint8_t Display;
	uint8_t AlarmAcknowledgeHR;
	uint8_t AlarmAcknowledgeMN;
	BATCH_STATUS CurrentBatchStatus;
	DATE_TIME_FORMATE DateTimeFormat;
}BatchConfig_t;
#pragma pack(pop)


//#pragma pack(push)  // To solve structure padding issue
//#pragma pack(1)
typedef struct{
	MEI_INFO MEI_info;
//	RecordPartitionMetadataInfo LogPartitionMetadataInfo[MAX_LOG_TYPE];
	BatchConfig_t BatchConfig;
//	AUTOCALIBRATIONPARAMETER cal_para;
//	RTCBUFFER StoredRTC;
}DeviceConfigObj;
//#pragma pack(pop)

extern DeviceConfigObj devConfig;

void readDeviceConfigFromFlash(void);
DeviceConfigObj getDeviceConfigObj(void);

#endif /* SRC_BATCHCONFIG_BATCHCONFIG_H_ */
