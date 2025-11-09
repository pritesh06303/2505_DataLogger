/*
 * LCD_Interface.h
 *
 *  Created on: Nov 3, 2025
 *      Author: TITHI
 */

#ifndef SRC_LCD_INTERFACE_LCD_INTERFACE_H_
#define SRC_LCD_INTERFACE_LCD_INTERFACE_H_

#define DISPLAYREFRESH_LCD_OFF  5  //Refresh Time In Sec
#define DISPLAYREFRESH_LCD_ON  10  //Refresh Time In Sec
#define GET_TEMP_COUNTER  60
#define TEMP_MEASUREONUSBCONNECT  5
//#define SPEED_GET_TEMP_COUNTER  2
#define PAUSEDETECTDELAY 5
#define PAUSEFUNLOADER  900

extern int PauseFunCounter;
extern int PauseDetectDelayCounter;
extern uint16_t ucDisplayRefreshCounter;
extern bool bTimeRefreshDisplay;
extern bool bEnableCrossSign;
extern bool bLCD_Init;
extern bool bPauseDetectStartDelay;
extern bool bPauseFunctionON;
extern bool bDisplayMinMaxTemperatureFlag;
extern bool bTempHumidityToggleFlag;

typedef  enum{
	DISP_SYMBOL_BATTERY_0 = 0,
	DISP_SYMBOL_BATTERY_1,
	DISP_SYMBOL_BATTERY_2,
	DISP_SYMBOL_BATTERY_3,
	DISP_SYMBOL_GROUP_1,

	DISP_SYMBOL_NEGAT_SIGN,
	DISP_SYMBOL_ALARM_HIGH,
	DISP_SYMBOL_ALARM_LOW,
	DISP_SYMBOL_DIGIT_ONE,
	DISP_SYMBOL_GROUP_2,

//	DISP_SYMBOL_HR_GLASS,
//	DISP_SYMBOL_USB,
	DISP_SYMBOL_ALARM_LOW3,
	DISP_SYMBOL_ALARM_LOW2,
	DISP_SYMBOL_ALARM_LOW1,
	DISP_SYMBOL_BELL,
	DISP_SYMBOL_ALARM_HIGH3,
	DISP_SYMBOL_ALARM_HIGH2,
	DISP_SYMBOL_ALARM_HIGH1,
	DISP_SYMBOL_TRUE,
	DISP_SYMBOL_CROSS,
	DISP_SYMBOL_GROUP_3,

	DISP_SYMBOL_MIN,
	DISP_SYMBOL_MAX,
	DISP_SYMBOL_RH,
	DISP_SYMBOL_DEG_FERE,
	DISP_SYMBOL_DEG_CEL,
	DISP_SYMBOL_BATCH_RUN,
	DISP_SYMBOL_BATCH_PAUSE,
	DISP_SYMBOL_DAY,
	DISP_SYMBOL_HOUR,
	DISP_SYMBOL_DUR,
//	DISP_SYMBOL_CALENDER,
//	DISP_SYMBOL_CLOCK,
	DISP_SYMBOL_GROUP_4,

	DIP_SYSMBOL_DP1,
	DISP_SYMBOL_GROUP_5,

	DIP_SYSMBOL_CLEAR_ALL,
	DIP_SYSMBOL_UPDATE_ALL
}NotificationGroup;

typedef  enum{
	UPDATE_DISPLAY = 0,
	UPDATE_RAM_VARIBLES_ONLY
}DISP_NOTIFICATION_CONTROL;

typedef enum{
    ON=0,
    OFF,
    BLINK
}DisplayType;

void updateNotification(NotificationGroup notification, DisplayType type, DISP_NOTIFICATION_CONTROL send);
void updateDayMarker(bool *Marker, uint16_t NumOfDay);
void ResetDayMarker(void);
void updateDisplay(uint8_t line, char *str);

typedef enum {
	Celcius = 0,
	Fahrenheit
}DISP_UNIT;

//typedef struct {
//    char strng[8];
//}Line_t;
//
//typedef struct {
//    Line_t Line[2];
//}DisplayElements;

typedef enum{
    CROSS=0,
    CHECK
}AlarmType;

typedef enum{
    CELCIUS=0,
    FEHRENHEIT,
    RH
}UnitType;

typedef enum{
    ALRMLOW=0,
    ALRMHIGH,
    NoAlrm
}AlrmHiLo;

typedef enum{
    RECORD=0,
    PAUSE,
    STOP
}RecType;

typedef struct {
    int Bar;
    DisplayType Type;
}Battery_t;

typedef struct {
    int Bar;
    DisplayType Type;
}WiFi_t;

typedef struct {
    AlarmType Alrm_Status;
    DisplayType Type;
}Alrm_Status_t;

typedef struct {
    UnitType Unit;
    DisplayType Type;
}UnitType_t;

typedef struct {
    AlrmHiLo AlrmType;
    DisplayType Type;
}AlrmType_t;

typedef struct {
    RecType RecStatus;
    DisplayType Type;
}RecType_t;

#pragma pack(push)  // To solve structure padding issue
#pragma pack(1)
typedef struct {
    Battery_t Battery;
    DisplayType Bell;
    Alrm_Status_t AlarmStatus;
    DisplayType Day;
//    DisplayType Calendar;
//    DisplayType Clock;
    DisplayType Duration;
    DisplayType S9;
    DisplayType S10;
    DisplayType S11;
    DisplayType S12;
    DisplayType MIN;
    DisplayType MAX;
    RecType_t RecStatus_t;
    UnitType_t Unit;
    AlrmType_t AlrmTypeHiLo_t;
}Notification_t;
#pragma pack(pop)

#pragma pack(push)  // To solve structure padding issue
#pragma pack(1)
typedef struct {
    char strng[8];
    DisplayType Type[8];
    bool BlinkChar[8];
}Line_t;
#pragma pack(pop)

#pragma pack(push)  // To solve structure padding issue
#pragma pack(1)
typedef struct {
    Notification_t Notification;
    Line_t Line[2];
}DisplayElements;
#pragma pack(pop)

extern DisplayElements DisplayBuffer;



extern int DateTimeDisplayToggleFlag;
extern bool isSystemOnUsbPower;
void UpdateDataOnLcd(int iDataDisplay);
void UpdateSymbolsOnLCD(void);
void UpdateDisplay(void);
void RefreshDisplay(void);
//void MinMaxAndPauseDetection(void);
void ConvertDataToDigits (int data, unsigned char *Buffer);

#endif /* SRC_LCD_INTERFACE_LCD_INTERFACE_H_ */
