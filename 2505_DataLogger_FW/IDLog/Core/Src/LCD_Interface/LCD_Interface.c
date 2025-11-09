/*
 * LCD_Interface.c
 *
 *  Created on: Nov 3, 2025
 *      Author: TITHI
 */

#include "HardwareConfig.h"


uint16_t ucDisplayRefreshCounter = DISPLAYREFRESH_LCD_OFF;
int PauseFunCounter = PAUSEFUNLOADER;
int PauseDetectDelayCounter = PAUSEDETECTDELAY;

bool bTimeRefreshDisplay = true;
bool bEnableCrossSign = false;
bool bLCD_Init = true;
bool bPauseDetectStartDelay = false;
bool bPauseFunctionON = false;
bool bDisplayMinMaxTemperatureFlag = false;
bool bTempHumidityToggleFlag = true;

typedef struct {
    unsigned char S0 : 1;
    unsigned char S1 : 1;
    unsigned char S2 : 1;
    unsigned char S3 : 1;
    unsigned char S4 : 1;
    unsigned char S5 : 1;
    unsigned char S6 : 1;
    unsigned char S7 : 1;
    unsigned char S8 : 1;
    unsigned char S9 : 1;
    unsigned char S10 : 1;

    unsigned char S11 : 1;
    unsigned char S12 : 1;
    unsigned char S13 : 1;
    unsigned char S14 : 1;
    unsigned char S15 : 1;
    unsigned char S16 : 1;
    unsigned char S17 : 1;
    unsigned char S18 : 1;
    unsigned char S19 : 1;

    unsigned char S20 : 1;
    unsigned char S21 : 1;
    unsigned char S22 : 1;
    unsigned char S23 : 1;
    unsigned char S24 : 1;
    unsigned char S25 : 1;
    unsigned char S26 : 1;
    unsigned char S27 : 1;
    unsigned char S28 : 1;
    unsigned char S29 : 1;

    unsigned char S30 : 1;
    unsigned char S31 : 1;
} RAM_ADDRESS_Bits_0to31;

typedef struct {
    unsigned char S32 : 1;
    unsigned char S33 : 1;
    unsigned char S34 : 1;
    unsigned char S35 : 1;
    unsigned char S36 : 1;
    unsigned char S37 : 1;
    unsigned char S38 : 1;
    unsigned char S39 : 1;
    unsigned char S40 : 1;
    unsigned char S41 : 1;
    unsigned char S42 : 1;
    unsigned char S43 : 1;

} RAM_ADDRESS_Bits_32to64;

typedef union{
	RAM_ADDRESS_Bits_0to31 BitGroup_1;
	uint32_t Data;
}RAM_ADDRESS_Bits_Union_bit0_to_31;

typedef union{
	RAM_ADDRESS_Bits_32to64 BitGroup_2;
	uint32_t Data;
}RAM_ADDRESS_Bits_Union_bit32_to_64;

typedef struct {
    unsigned char a : 1;
    unsigned char b : 1;
    unsigned char c : 1;
    unsigned char d : 1;
    unsigned char e : 1;
    unsigned char f : 1;
    unsigned char g : 1;
    unsigned char Unused : 1;

} SEG_Bits;

typedef union{
	SEG_Bits BitsGroup;
	uint8_t Data;
}SEG_Bits_union ;

#define MAX_CHAR_SEG 		MAX_CHAR_SEG_LINE_1 + MAX_CHAR_SEG_LINE_2
#define MAX_CHAR_SEG_LINE_1 4
#define MAX_CHAR_SEG_LINE_2 8

typedef struct {
	SEG_Bits_union SevenSegmentChar[MAX_CHAR_SEG];

}SEG_GROUP;
typedef struct {
	RAM_ADDRESS_Bits_Union_bit0_to_31 RAM0_31bit;
	RAM_ADDRESS_Bits_Union_bit32_to_64 RAM32_63bit;
}COM_Struct;

typedef struct
{
	COM_Struct COM0;
	COM_Struct COM1;
	COM_Struct COM2;
	COM_Struct COM3;
}COM_GROUP;

COM_GROUP ComGroup;
SEG_GROUP SegGroup;


typedef struct {
    unsigned char T1 : 1;   //Battery usage indication
    unsigned char T2 : 1;   //Battery usage indication
    unsigned char T3 : 1;   //Battery usage indication
    unsigned char T4 : 1;   //Battery usage indicator frame

} BAT_Bits;

typedef struct {
    unsigned char X1 : 1;       //Alarm High
    unsigned char X2 : 1;       //Negative Sign
    unsigned char X3 : 1;       //Alarm low

    unsigned char X4 : 1;       //Digit 1

} UpDownSign_Bits;

typedef struct{
    unsigned char S1 : 1;   //Alarm low 3
    unsigned char S2 : 1;   //Alarm low 2
    unsigned char S3 : 1;   //Alarm low 1
    unsigned char S4 : 1;   //Bell Icon
    unsigned char S5 : 1;   //Alarm high 3
    unsigned char S6 : 1;   //Alarm high 2
    unsigned char S7 : 1;   //Alarm high 1
    unsigned char S8 : 1;   //True sign
    unsigned char S9 : 1;   //Cross sign
}Alarm_Bits;

typedef struct {
    unsigned char S10 : 1;    //Min
    unsigned char S11 : 1;    //Max
    unsigned char S12 : 1;    //%RH
    unsigned char S13 : 1;    //Degree Ferenhit
    unsigned char S14 : 1;    //Degree Celcius
    unsigned char S15 : 1;    //Rec
	unsigned char S16 : 1;    //Pause
	unsigned char S17 : 1;    //Day
	unsigned char S18 : 1;    //Hour
	unsigned char S19: 1;     //Duration
} UNIT_Symbol_Bits;

typedef struct {
	unsigned  char P1:1;
}DP;

#pragma pack(push)  // To solve structure padding issue
#pragma pack(1)
struct {
	UpDownSign_Bits UpDownSignNotification;
	BAT_Bits BattNotification;
	Alarm_Bits Alarm_Notification;
	UNIT_Symbol_Bits UNIT_Symbol_BitsNotification;
	DP dp;
}DispSymbolGroup;
#pragma pack(pop)

DisplayElements DisplayBuffer;


//==============================================================================================================================================
//Function Name		: unsigned char ConverCharToSegByte(unsigned char ucByte)
//Preconditions		: None.
//                  :
//Input Parameter	: Passed Byte Value.
//Return Value		: None.
//Overview          : This function Will Convert byte value to the segment value.
//Author		    : Hardik Patel
//Date			    : 05 Apr 2024
//Revision		    : 0
//Date			    :
//===============================================================================================================================================

unsigned char ConverCharToSegByte(unsigned char ucByte)
{
    switch(ucByte)
    {
        case 0x30:
            return 0x3F;		//0

        case 0x31:
            return 0x06;		//1

        case 0x32:
            return 0x5B;		//2

        case 0x33:
            return 0x4F;		//3

        case 0x34:
            return 0x66;		//4

        case 0x35:
            return 0x6D;		//5

        case 0x36:
            return 0x7D;		//6

        case 0x37:
            return 0x07;		//7

        case 0x38:
            return 0x7F;		//8

        case 0x39:
            return 0x6F;		//9

        case 0x41:              //A
            return 0x77;

        case 0x42:              //B
            return 0x7C;

        case 0x43:              //C
            return 0x39;

        case 0x44:              //D
            return 0x5E;

        case 0x45:              //E
            return 0x79;

        case 0x46:              //F
            return 0x71;

        case 0x47:              //G
            return 0x6F;

        case 0x48:              //H
            return 0x76;

        case 0x49:              //I
            return 0x30;

        case 0x4A:              //J
            return 0x0E;

        case 0x4B:              //K
            return 0x70;

        case 0x4C:              //L
            return 0x38;

        case 0x4D:              //M
            return 0x15;

        case 0x4E:              //N
            return 0x54;

        case 0x4F:              //O
            return 0x5C;

        case 0x50:              //P
            return 0x73;

        case 0x51:              //Q
            return 0x67;

        case 0x52:              //R
            return 0x50;

        case 0x53:              //S
            return 0x6D;

        case 0x54:              //T
            return 0x78;

        case 0x55:              //U
            return 0x3E;

        case 0x56:              //V
            return 0x1C;

        case 0x57:              //W
            return 0x2A;

        case 0x59:              //y
            return 0x6E;

        case 0x5A:              //Z
            return 0x5B;

        case 0x20:              //Space
            return 0x00;

        case 0x2D:              //Dash
            return 0x40;

        case 0x00:
            return 0x00;

        default:
            return 0x3F;	   // SEND 0

    }
}

//==============================================================================================================================================
//Function Name		: void SegmentToCOM_Mapping (void)
//Preconditions		: LCD Drawing For Segment Mapping.
//                  :
//Input Parameter	:
//Return Value		: None.
//Overview          : This function Will Mapped Segment value to RAM Address.
//Author		    : Hardik Patel
//Date			    : 05 Apr 2024
//Revision		    : 0
//Date			    :
//===============================================================================================================================================

void SegmentToCOM_Mapping (void)
{
	// char 1-- 1A/1B/1C/1D/1E/1F/1G
	ComGroup.COM0.RAM0_31bit.BitGroup_1.S2 = SegGroup.SevenSegmentChar[0].BitsGroup.a;
	ComGroup.COM1.RAM0_31bit.BitGroup_1.S2 = SegGroup.SevenSegmentChar[0].BitsGroup.b;
	ComGroup.COM2.RAM0_31bit.BitGroup_1.S2 = SegGroup.SevenSegmentChar[0].BitsGroup.c;
	ComGroup.COM3.RAM0_31bit.BitGroup_1.S2 = SegGroup.SevenSegmentChar[0].BitsGroup.d;
	ComGroup.COM2.RAM0_31bit.BitGroup_1.S1 = SegGroup.SevenSegmentChar[0].BitsGroup.e;
	ComGroup.COM0.RAM0_31bit.BitGroup_1.S1 = SegGroup.SevenSegmentChar[0].BitsGroup.f;
	ComGroup.COM1.RAM0_31bit.BitGroup_1.S1 = SegGroup.SevenSegmentChar[0].BitsGroup.g;

	// char 2-- 2A/2B/2C/2D/2E/2F/2G
	ComGroup.COM0.RAM0_31bit.BitGroup_1.S4 = SegGroup.SevenSegmentChar[1].BitsGroup.a;
	ComGroup.COM1.RAM0_31bit.BitGroup_1.S4 = SegGroup.SevenSegmentChar[1].BitsGroup.b;
	ComGroup.COM2.RAM0_31bit.BitGroup_1.S4 = SegGroup.SevenSegmentChar[1].BitsGroup.c;
	ComGroup.COM3.RAM0_31bit.BitGroup_1.S4 = SegGroup.SevenSegmentChar[1].BitsGroup.d;
	ComGroup.COM2.RAM0_31bit.BitGroup_1.S3 = SegGroup.SevenSegmentChar[1].BitsGroup.e;
	ComGroup.COM0.RAM0_31bit.BitGroup_1.S3 = SegGroup.SevenSegmentChar[1].BitsGroup.f;
	ComGroup.COM1.RAM0_31bit.BitGroup_1.S3 = SegGroup.SevenSegmentChar[1].BitsGroup.g;

	// char 3-- 3A/3B/3C/3D/3E/3F/3G
	ComGroup.COM0.RAM0_31bit.BitGroup_1.S6 = SegGroup.SevenSegmentChar[2].BitsGroup.a;
	ComGroup.COM1.RAM0_31bit.BitGroup_1.S6 = SegGroup.SevenSegmentChar[2].BitsGroup.b;
	ComGroup.COM2.RAM0_31bit.BitGroup_1.S6 = SegGroup.SevenSegmentChar[2].BitsGroup.c;
	ComGroup.COM3.RAM0_31bit.BitGroup_1.S6 = SegGroup.SevenSegmentChar[2].BitsGroup.d;
	ComGroup.COM2.RAM0_31bit.BitGroup_1.S5 = SegGroup.SevenSegmentChar[2].BitsGroup.e;
	ComGroup.COM0.RAM0_31bit.BitGroup_1.S5 = SegGroup.SevenSegmentChar[2].BitsGroup.f;
	ComGroup.COM1.RAM0_31bit.BitGroup_1.S5 = SegGroup.SevenSegmentChar[2].BitsGroup.g;

	// char 4-- 4A/4B/4C/4D/4E/4F/4G
	ComGroup.COM0.RAM0_31bit.BitGroup_1.S8 = SegGroup.SevenSegmentChar[3].BitsGroup.a;
	ComGroup.COM1.RAM0_31bit.BitGroup_1.S8 = SegGroup.SevenSegmentChar[3].BitsGroup.b;
	ComGroup.COM2.RAM0_31bit.BitGroup_1.S8 = SegGroup.SevenSegmentChar[3].BitsGroup.c;
	ComGroup.COM3.RAM0_31bit.BitGroup_1.S8 = SegGroup.SevenSegmentChar[3].BitsGroup.d;
	ComGroup.COM2.RAM0_31bit.BitGroup_1.S7 = SegGroup.SevenSegmentChar[3].BitsGroup.e;
	ComGroup.COM0.RAM0_31bit.BitGroup_1.S7 = SegGroup.SevenSegmentChar[3].BitsGroup.f;
	ComGroup.COM1.RAM0_31bit.BitGroup_1.S7 = SegGroup.SevenSegmentChar[3].BitsGroup.g;

	// Notifications -------------------------------------------------------------------

	ComGroup.COM0.RAM0_31bit.BitGroup_1.S10 = DispSymbolGroup.Alarm_Notification.S8;
	ComGroup.COM1.RAM0_31bit.BitGroup_1.S10 = DispSymbolGroup.Alarm_Notification.S7;
	ComGroup.COM2.RAM0_31bit.BitGroup_1.S10 = DispSymbolGroup.Alarm_Notification.S6;
	ComGroup.COM3.RAM0_31bit.BitGroup_1.S10 = DispSymbolGroup.Alarm_Notification.S5;
	ComGroup.COM0.RAM0_31bit.BitGroup_1.S11 = DispSymbolGroup.Alarm_Notification.S4;
	ComGroup.COM1.RAM0_31bit.BitGroup_1.S11 = DispSymbolGroup.Alarm_Notification.S3;
	ComGroup.COM2.RAM0_31bit.BitGroup_1.S11 = DispSymbolGroup.Alarm_Notification.S2;
	ComGroup.COM3.RAM0_31bit.BitGroup_1.S11 = DispSymbolGroup.Alarm_Notification.S1;
	ComGroup.COM3.RAM0_31bit.BitGroup_1.S13 = DispSymbolGroup.Alarm_Notification.S9;

	ComGroup.COM0.RAM0_31bit.BitGroup_1.S12 = DispSymbolGroup.BattNotification.T2;
	ComGroup.COM1.RAM0_31bit.BitGroup_1.S12 = DispSymbolGroup.BattNotification.T3;
	ComGroup.COM2.RAM0_31bit.BitGroup_1.S12 = DispSymbolGroup.BattNotification.T1;
	ComGroup.COM3.RAM0_31bit.BitGroup_1.S12 = DispSymbolGroup.BattNotification.T4;

	ComGroup.COM0.RAM0_31bit.BitGroup_1.S13 = DispSymbolGroup.UpDownSignNotification.X1;
	ComGroup.COM1.RAM0_31bit.BitGroup_1.S13 = DispSymbolGroup.UpDownSignNotification.X2;
	ComGroup.COM2.RAM0_31bit.BitGroup_1.S13 = DispSymbolGroup.UpDownSignNotification.X3;

	ComGroup.COM3.RAM0_31bit.BitGroup_1.S13 = DispSymbolGroup.UNIT_Symbol_BitsNotification.S15;
	ComGroup.COM3.RAM0_31bit.BitGroup_1.S0 = DispSymbolGroup.UNIT_Symbol_BitsNotification.S16;
	ComGroup.COM3.RAM0_31bit.BitGroup_1.S1 = DispSymbolGroup.UNIT_Symbol_BitsNotification.S17;
	ComGroup.COM3.RAM0_31bit.BitGroup_1.S3 = DispSymbolGroup.UNIT_Symbol_BitsNotification.S18;
	ComGroup.COM3.RAM0_31bit.BitGroup_1.S7 = DispSymbolGroup.UNIT_Symbol_BitsNotification.S19;

	ComGroup.COM3.RAM0_31bit.BitGroup_1.S5 = DispSymbolGroup.dp.P1;

	ComGroup.COM0.RAM0_31bit.BitGroup_1.S0 = DispSymbolGroup.UNIT_Symbol_BitsNotification.S11;
	ComGroup.COM1.RAM0_31bit.BitGroup_1.S0 = DispSymbolGroup.UNIT_Symbol_BitsNotification.S10;
	ComGroup.COM2.RAM0_31bit.BitGroup_1.S0 = DispSymbolGroup.UpDownSignNotification.X4;

	ComGroup.COM0.RAM0_31bit.BitGroup_1.S9 = DispSymbolGroup.UNIT_Symbol_BitsNotification.S14;
	ComGroup.COM1.RAM0_31bit.BitGroup_1.S9 = DispSymbolGroup.UNIT_Symbol_BitsNotification.S13;
	ComGroup.COM2.RAM0_31bit.BitGroup_1.S9 = DispSymbolGroup.UNIT_Symbol_BitsNotification.S12;
}

//==============================================================================================================================================
//Function Name		: void WriteDataOnDisplayDriver(void)
//Preconditions		:
//                  :
//Input Parameter	:
//Return Value		: None.
//Overview          : This function Will update data to Display RAM.
//Author		    : Hardik Patel
//Date			    : 05 Apr 2024
//Revision		    : 0
//Date			    :
//===============================================================================================================================================

void WriteDataOnDisplayDriver(void)
{
//	HAL_LCD_Clear(&hlcd);
    /* Clear the LCD_RAM registers */
    for ( uint8_t counter = LCD_RAM_REGISTER0; counter <= LCD_RAM_REGISTER7; counter++)
    {
      hlcd.Instance->RAM[counter] = 0;
    }

	while(1)
	{
		HAL_LCD_StateTypeDef status = HAL_LCD_GetState(&hlcd);
		if (status != HAL_LCD_STATE_BUSY)
			break;
	}

	HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER0, 0xFFFFFFFF, ComGroup.COM0.RAM0_31bit.Data);
	HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER1, 0xFFFFFFFF, ComGroup.COM0.RAM32_63bit.Data);

	HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER2, 0xFFFFFFFF, ComGroup.COM1.RAM0_31bit.Data);
	HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER3, 0xFFFFFFFF, ComGroup.COM1.RAM32_63bit.Data);

	HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER4, 0xFFFFFFFF, ComGroup.COM2.RAM0_31bit.Data);
	HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER5, 0xFFFFFFFF, ComGroup.COM2.RAM32_63bit.Data);

	HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER6, 0xFFFFFFFF, ComGroup.COM3.RAM0_31bit.Data);
	HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER7, 0xFFFFFFFF, ComGroup.COM3.RAM32_63bit.Data);

	HAL_LCD_UpdateDisplayRequest(&hlcd);
}


//==============================================================================================================================================
//Function Name		: void updateNotification(NotificationGroup notification, DisplayType ViewType, DISP_NOTIFICATION_CONTROL send)
//Preconditions		:
//                  :
//Input Parameter	:
//Return Value		: None.
//Overview          : This function Will Update Notification On LCD.
//Author		    : Hardik Patel
//Date			    : 05 Apr 2024
//Revision		    : 0
//Date			    :
//===============================================================================================================================================

void updateNotification(NotificationGroup notification, DisplayType ViewType, DISP_NOTIFICATION_CONTROL send)
{
	switch((uint32_t)notification)
	{
	case DISP_SYMBOL_BATTERY_0:
		DisplayBuffer.Notification.Battery.Type = ViewType;
		break;

	case DISP_SYMBOL_BATTERY_1:
		DisplayBuffer.Notification.Battery.Type = ViewType;
		break;

	case DISP_SYMBOL_BATTERY_2:
		DisplayBuffer.Notification.Battery.Type = ViewType;
		break;

	case DISP_SYMBOL_BATTERY_3:
		DisplayBuffer.Notification.Battery.Type = ViewType;
		break;

	case DISP_SYMBOL_NEGAT_SIGN:
		if (ViewType)
			DispSymbolGroup.UpDownSignNotification.X2 = 1;
		else
			DispSymbolGroup.UpDownSignNotification.X2 = 0;
		break;

	case DISP_SYMBOL_ALARM_HIGH:
		if (ViewType)
			DispSymbolGroup.UpDownSignNotification.X1 = 1;
		else
			DispSymbolGroup.UpDownSignNotification.X1 = 0;
		break;

	case DISP_SYMBOL_ALARM_LOW:
		if (ViewType)
			DispSymbolGroup.UpDownSignNotification.X3 = 1;
		else
			DispSymbolGroup.UpDownSignNotification.X3 = 0;
		break;

	case DISP_SYMBOL_DIGIT_ONE:
		if (ViewType)
		{
			DispSymbolGroup.UpDownSignNotification.X4 = 1;
		}
		else
		{
			DispSymbolGroup.UpDownSignNotification.X4 = 0;
		}
		break;

	case DISP_SYMBOL_BELL:
		if (ViewType)
			DispSymbolGroup.Alarm_Notification.S4 = 1;
		else
			DispSymbolGroup.Alarm_Notification.S4 = 0;
		break;

	case DISP_SYMBOL_DAY:
		if (ViewType)
			DispSymbolGroup.UNIT_Symbol_BitsNotification.S17 = 1;
		else
			DispSymbolGroup.UNIT_Symbol_BitsNotification.S17 = 0;
		break;

	case DISP_SYMBOL_DUR:
		if (ViewType)
			DispSymbolGroup.UNIT_Symbol_BitsNotification.S19 = 1;
		else
			DispSymbolGroup.UNIT_Symbol_BitsNotification.S19 = 0;
		break;

	case DISP_SYMBOL_BATCH_RUN:
		if (ViewType)
			DispSymbolGroup.UNIT_Symbol_BitsNotification.S15 = 1;
		else
			DispSymbolGroup.UNIT_Symbol_BitsNotification.S15 = 0;
		break;

	case DISP_SYMBOL_BATCH_PAUSE:
		if (ViewType)
			DispSymbolGroup.UNIT_Symbol_BitsNotification.S16 = 1;
		else
			DispSymbolGroup.UNIT_Symbol_BitsNotification.S16 = 0;
		break;

	case DISP_SYMBOL_MIN:
		if (ViewType)
			DispSymbolGroup.UNIT_Symbol_BitsNotification.S10 = 1;
		else
			DispSymbolGroup.UNIT_Symbol_BitsNotification.S10 = 0;
		break;

	case DISP_SYMBOL_MAX:
		if (ViewType)
			DispSymbolGroup.UNIT_Symbol_BitsNotification.S11 = 1;
		else
			DispSymbolGroup.UNIT_Symbol_BitsNotification.S11 = 0;
		break;

	case DISP_SYMBOL_RH:
		if (ViewType)
			DispSymbolGroup.UNIT_Symbol_BitsNotification.S12 = 1;
		else
			DispSymbolGroup.UNIT_Symbol_BitsNotification.S12 = 0;
		break;

	case DISP_SYMBOL_DEG_FERE:
		if (ViewType)
			DispSymbolGroup.UNIT_Symbol_BitsNotification.S13 = 1;
		else
			DispSymbolGroup.UNIT_Symbol_BitsNotification.S13 = 0;
		break;

	case DISP_SYMBOL_DEG_CEL:
		if (ViewType)
			DispSymbolGroup.UNIT_Symbol_BitsNotification.S14 = 1;
		else
			DispSymbolGroup.UNIT_Symbol_BitsNotification.S14 = 0;
		break;

	case DISP_SYMBOL_TRUE:
		if (ViewType)
		{
			DispSymbolGroup.Alarm_Notification.S8 = 1;
		}
		else
		{
			DispSymbolGroup.Alarm_Notification.S8 = 0;
		}
		break;

	case DISP_SYMBOL_CROSS:
		if (ViewType)
		{
			DispSymbolGroup.Alarm_Notification.S9 = 1;
		}
		else
		{
			DispSymbolGroup.Alarm_Notification.S9 = 0;
		}
		break;

	case DIP_SYSMBOL_DP1:
		if (ViewType)
			DispSymbolGroup.dp.P1 = 1;
		else
			DispSymbolGroup.dp.P1 = 0;
		break;

	case DIP_SYSMBOL_CLEAR_ALL:
		memset(&DispSymbolGroup.UpDownSignNotification,0,sizeof(DispSymbolGroup.UpDownSignNotification));
		memset(&DispSymbolGroup.BattNotification,0,sizeof(DispSymbolGroup.BattNotification));
		memset(&DispSymbolGroup.Alarm_Notification,0,sizeof(DispSymbolGroup.Alarm_Notification));
		memset(&DispSymbolGroup.UNIT_Symbol_BitsNotification,0,sizeof(DispSymbolGroup.UNIT_Symbol_BitsNotification));
		memset(&DispSymbolGroup.dp,0,sizeof(DispSymbolGroup.dp));
		memset(&SegGroup,0,sizeof(SegGroup));

		DisplayBuffer.Notification.Bell = OFF;

		break;

	case DIP_SYSMBOL_UPDATE_ALL:
		DisplayBuffer.Notification.Battery.Bar = 0x00F0;
		memset(&DispSymbolGroup,0xFF,sizeof(DispSymbolGroup));
		memset(&SegGroup,0xFF,sizeof(SegGroup));
		DispSymbolGroup.Alarm_Notification.S1 = 0;
		DispSymbolGroup.Alarm_Notification.S2 = 0;
		DispSymbolGroup.Alarm_Notification.S3 = 0;
		DispSymbolGroup.Alarm_Notification.S5 = 0;
		DispSymbolGroup.Alarm_Notification.S6 = 0;
		DispSymbolGroup.Alarm_Notification.S7 = 0;
		DispSymbolGroup.Alarm_Notification.S8 = 0;
		DispSymbolGroup.Alarm_Notification.S9 = 0;
		DispSymbolGroup.UNIT_Symbol_BitsNotification.S16 = 0;
		DispSymbolGroup.UNIT_Symbol_BitsNotification.S17 = 0;
		DispSymbolGroup.UNIT_Symbol_BitsNotification.S18 = 0;
		DispSymbolGroup.UNIT_Symbol_BitsNotification.S19 = 0;
		break;

	case DISP_SYMBOL_GROUP_1:
		memset(&DispSymbolGroup.BattNotification,0,sizeof(DispSymbolGroup.BattNotification));
		break;

	case DISP_SYMBOL_GROUP_2:
		memset(&DispSymbolGroup.UpDownSignNotification,0,sizeof(DispSymbolGroup.UpDownSignNotification));
		break;

	case DISP_SYMBOL_GROUP_3:
		memset(&DispSymbolGroup.Alarm_Notification,0,sizeof(DispSymbolGroup.Alarm_Notification));
		break;

	case DISP_SYMBOL_GROUP_4:
		memset(&DispSymbolGroup.UNIT_Symbol_BitsNotification,0,sizeof(DispSymbolGroup.UNIT_Symbol_BitsNotification));
		break;

	case DISP_SYMBOL_GROUP_5:
		memset(&DispSymbolGroup.dp,0,sizeof(DispSymbolGroup.dp));
		break;
	}


	if (send == UPDATE_DISPLAY)
	{
		SegmentToCOM_Mapping();
		WriteDataOnDisplayDriver();
	}
}


//==============================================================================================================================================
//Function Name		: void updateDayMarker(bool *Marker, uint16_t NumOfDay)
//Preconditions		:
//                  :
//Input Parameter	:
//Return Value		: None.
//Overview          : This function Will Update day Marker On LCD.
//Author		    : Hardik Patel
//Date			    : 05 Apr 2024
//Revision		    : 0
//Date			    :
//===============================================================================================================================================

//void updateDayMarker(bool *Marker, uint16_t NumOfDay)
//{
//	if (NumOfDay > MAX_HISTORY_DAY)
//		return;
//
//	uint16_t day = 0;
//
//	for (day = 0; day < NumOfDay ; day++)
//		DispSymbolGroup.DayMarkerBuffer[day] = Marker[day];
//
////	SegmentToCOM_Mapping();
////
////	WriteDataOnDisplayDriver();
//
//}

//void ResetDayMarker(void)
//{
//	memset(&DispSymbolGroup.DayMarkerBuffer,0,sizeof(DispSymbolGroup.DayMarkerBuffer));
//}


//==============================================================================================================================================
//Function Name		: void updateDisplay(uint8_t line, char *str)
//Preconditions		:
//                  :
//Input Parameter	:
//Return Value		: None.
//Overview          : This function Will Update Data To LCD according Line Number.
//Author		    : Hardik Patel
//Date			    : 05 Apr 2024
//Revision		    : 0
//Date			    :
//===============================================================================================================================================

void updateDisplay(uint8_t line, char *str)
{
	uint8_t Loop = 0;
	unsigned char c = 0;

	if(line > 2 || line == 0)
		return;

	for (Loop = 0; Loop < 8/*strlen(str)*/; Loop++)
	{
		if (line == 1)
		{
			if (MAX_CHAR_SEG_LINE_1 == Loop)
				break;
		}
		else
		{
			if (MAX_CHAR_SEG_LINE_2 == Loop)
				break;
		}

		if(DisplayBuffer.Line[1].strng[Loop] == ':')
		{
			updateNotification(DIP_SYSMBOL_DP1, 1,UPDATE_RAM_VARIBLES_ONLY);
			c = 0x00;
		}
		else
			c = ConverCharToSegByte(str[Loop]);

		if (line == 2)
			SegGroup.SevenSegmentChar[Loop + 4].Data = c;
		else
			SegGroup.SevenSegmentChar[Loop].Data = c;
	}

//	SegmentToCOM_Mapping();
//	WriteDataOnDisplayDriver();
}


//==============================================================================================================================================
//Function Name		: void ConvertDataToDigits (int data, unsigned char *Buffer)
//Preconditions		:
//                  :
//Input Parameter	:
//Return Value		: None.
//Overview          : This function Will Convert data to digit for temperature update.
//Author		    : Hardik Patel
//Date			    : 05 Apr 2024
//Revision		    : 0
//Date			    :
//===============================================================================================================================================

void ConvertDataToDigits (int data, unsigned char *Buffer)
{
    data = ((int) (data % 1000));
    Buffer[0] =  ((int) (data / 100) + 0x30);
    data = ((int) (data % 100));
    Buffer[1] =  ((int) (data / 10) + 0x30);
    Buffer[2] =  ((int) (data % 10) + 0x30);
}


//==============================================================================================================================================
//Function Name		: void UpdateDataOnLcd(int iDataDisplay)
//Preconditions		:
//                  :
//Input Parameter	:
//Return Value		: None.
//Overview          : This function Will Update Data ON LCD.
//Author		    : Hardik Patel
//Date			    : 05 Apr 2024
//Revision		    : 0
//Date			    :
//===============================================================================================================================================

void UpdateDataOnLcd(int iDataDisplay)
{
    int cDataDisplay = 0;
    unsigned char ucDisplayBuffer[4] = {0};

//	DeviceConfigObj devConfig = getDeviceConfigObj();
    if(bTempHumidityToggleFlag)
    {
		if(devConfig.BatchConfig.Unit == Celcius)
		{
			updateNotification(DISP_SYMBOL_DEG_CEL, 1,UPDATE_RAM_VARIBLES_ONLY);
			updateNotification(DISP_SYMBOL_DEG_FERE, 0,UPDATE_RAM_VARIBLES_ONLY);
		}
		else if(devConfig.BatchConfig.Unit == Fahrenheit)
		{
			iDataDisplay = (iDataDisplay*9/5)+3200;
			updateNotification(DISP_SYMBOL_DEG_CEL, 0,UPDATE_RAM_VARIBLES_ONLY);
			updateNotification(DISP_SYMBOL_DEG_FERE, 1,UPDATE_RAM_VARIBLES_ONLY);
		}
    }
    else
    {
    	updateNotification(DISP_SYMBOL_RH, 1,UPDATE_RAM_VARIBLES_ONLY);
    }

    ////update reading
//    cDataDisplay = (int) ((iDataDisplay / 10));  //Display Resolution is 2 digit after decimal point so comment this line
    cDataDisplay = (int) (iDataDisplay);

    if((cDataDisplay > 19999) || (cDataDisplay < -19999))
    {
        cDataDisplay = (int) ((cDataDisplay / 10));
    }

    if(cDataDisplay < 0)
    {
    	updateNotification(DISP_SYMBOL_NEGAT_SIGN, 1,UPDATE_RAM_VARIBLES_ONLY);   //On Negative sign
        cDataDisplay = -(cDataDisplay);
    }
    else
    	updateNotification(DISP_SYMBOL_NEGAT_SIGN, 0,UPDATE_RAM_VARIBLES_ONLY); //Off Negative sign

    if((cDataDisplay/10000) > 0)
    {
    	updateNotification(DISP_SYMBOL_DIGIT_ONE, 1,UPDATE_RAM_VARIBLES_ONLY);    //On half digit
        cDataDisplay = ((int) (cDataDisplay % 1000));
    }
    else
    	updateNotification(DISP_SYMBOL_DIGIT_ONE, 0,UPDATE_RAM_VARIBLES_ONLY);    //Off half digit


//    if (AlarmStatusHigh || AlarmStatusLow)
//    {
//    	updateNotification(DISP_SYMBOL_BELL, 1,UPDATE_RAM_VARIBLES_ONLY);    //Off half digit
//    }

    ucDisplayBuffer[0] = (int) (cDataDisplay / 1000) + 0x30;
    ConvertDataToDigits(cDataDisplay,&ucDisplayBuffer[1]);
    updateNotification(DIP_SYSMBOL_DP1, 1,UPDATE_RAM_VARIBLES_ONLY); // finally send all symbols save in ram variables so we call UPDATE_DISPLAY
    updateDisplay(1,(char *) ucDisplayBuffer);
}

int DateTimeDisplayToggleFlag = false;
bool isSystemOnUsbPower = false;
void UpdateSymbolsOnLCD(void)
{
//	char DispRTC[9] = {0};
	/* Update all display symbol variables using UPDATE_RAM_VARIBLES_ONLY
	 * and lastly call UPDATE_DISPLAY to send all symbols on LCD
	 */

	//clear relative symbols
	updateNotification(DISP_SYMBOL_GROUP_1, 0, UPDATE_RAM_VARIBLES_ONLY);
	updateNotification(DISP_SYMBOL_GROUP_3, 0, UPDATE_RAM_VARIBLES_ONLY);
	updateNotification(DISP_SYMBOL_GROUP_4, 0, UPDATE_RAM_VARIBLES_ONLY);
	updateNotification(DISP_SYMBOL_GROUP_5, 0, UPDATE_RAM_VARIBLES_ONLY);

//	DeviceConfigObj devConfig = getDeviceConfigObj();

	if(bTempHumidityToggleFlag)
	{
		if(devConfig.BatchConfig.Unit == Celcius)
		{
			updateNotification(DISP_SYMBOL_DEG_CEL, 1,UPDATE_RAM_VARIBLES_ONLY);
	//		updateNotification(DISP_SYMBOL_DEG_FERE, 0,UPDATE_RAM_VARIBLES_ONLY);
		}
		else if(devConfig.BatchConfig.Unit == Fahrenheit)
		{
	//		updateNotification(DISP_SYMBOL_DEG_CEL, 0,UPDATE_RAM_VARIBLES_ONLY);
			updateNotification(DISP_SYMBOL_DEG_FERE, 1,UPDATE_RAM_VARIBLES_ONLY);
		}
	}
	else
	{
		updateNotification(DISP_SYMBOL_RH, 1,UPDATE_RAM_VARIBLES_ONLY);
	}

	if (devConfig.BatchConfig.CurrentBatchStatus == BATCH_START)
	{
//		updateDisplay(2,DispRTC);

//		updateNotification(DISP_SYMBOL_BATCH_RUN, 1, UPDATE_RAM_VARIBLES_ONLY);
//		if((AlarmStatusHigh) || (AlarmStatusLow))
//		{
//			DisplayBuffer.Notification.Bell = ON;
//			updateNotification(DISP_SYMBOL_BELL, 1, UPDATE_RAM_VARIBLES_ONLY);
//		}

		if(bEnableCrossSign == true)
		{
//			updateNotification(DISP_SYMBOL_TRUE, 0, UPDATE_RAM_VARIBLES_ONLY);
//			updateNotification(DISP_SYMBOL_CROSS, 1, UPDATE_RAM_VARIBLES_ONLY);
		}
		else
		{
//			updateNotification(DISP_SYMBOL_CROSS, 0, UPDATE_RAM_VARIBLES_ONLY);
//			updateNotification(DISP_SYMBOL_TRUE, 1, UPDATE_RAM_VARIBLES_ONLY);
		}
	}
	else
	{
//		updateNotification(DISP_SYMBOL_HR_GLASS, 1, UPDATE_RAM_VARIBLES_ONLY);
	}

	if (devConfig.BatchConfig.CurrentBatchStatus == BATCH_PAUSE)
	{
		updateNotification(DISP_SYMBOL_BATCH_PAUSE, 1, UPDATE_RAM_VARIBLES_ONLY);
	}

//	if (HighAlarmByte)
//	{
////		updateNotification(DISP_SYMBOL_MAX, 1, UPDATE_RAM_VARIBLES_ONLY);
//		updateNotification(DISP_SYMBOL_ALARM_HIGH, 1, UPDATE_RAM_VARIBLES_ONLY);
//	}
//	if (LowAlarmByte)
//	{
////		updateNotification(DISP_SYMBOL_MIN, 1, UPDATE_RAM_VARIBLES_ONLY);
//		updateNotification(DISP_SYMBOL_ALARM_LOW, 1, UPDATE_RAM_VARIBLES_ONLY);
//	}

//	if (isSystemOnUsbPower)
//	{
//		DisplayBuffer.Notification.USB = ON;
//		updateNotification(DISP_SYMBOL_USB, 1, UPDATE_RAM_VARIBLES_ONLY);
//	}
//	else
//	{
//		DisplayBuffer.Notification.USB = OFF;
//		updateNotification(DISP_SYMBOL_USB, 0, UPDATE_RAM_VARIBLES_ONLY);
//	}

	DisplayBuffer.Notification.Battery.Type = ON;
	DisplayBuffer.Notification.Battery.Bar = 0x0080;    //Battery Outer Box

	if(uRemain_Battery == Bat_One_Bar)
	{
		DisplayBuffer.Notification.Battery.Bar = 0x0090;
		updateNotification(DISP_SYMBOL_BATTERY_0, ON, UPDATE_RAM_VARIBLES_ONLY);
		updateNotification(DISP_SYMBOL_BATTERY_1, OFF, UPDATE_RAM_VARIBLES_ONLY);
		updateNotification(DISP_SYMBOL_BATTERY_2, OFF, UPDATE_RAM_VARIBLES_ONLY);
	}
	if(uRemain_Battery == Bat_Two_Bar)
	{
		DisplayBuffer.Notification.Battery.Bar = 0x00B0;
		updateNotification(DISP_SYMBOL_BATTERY_0, ON, UPDATE_RAM_VARIBLES_ONLY);
		updateNotification(DISP_SYMBOL_BATTERY_1, ON, UPDATE_RAM_VARIBLES_ONLY);
		updateNotification(DISP_SYMBOL_BATTERY_2, OFF, UPDATE_RAM_VARIBLES_ONLY);
	}


	if(uRemain_Battery == Bat_three_Bar)
	{
		DisplayBuffer.Notification.Battery.Bar = 0x00F0;
		updateNotification(DISP_SYMBOL_BATTERY_0, ON, UPDATE_RAM_VARIBLES_ONLY);
		updateNotification(DISP_SYMBOL_BATTERY_1, ON, UPDATE_RAM_VARIBLES_ONLY);
		updateNotification(DISP_SYMBOL_BATTERY_2, ON, UPDATE_RAM_VARIBLES_ONLY);
	}


	// finally send all symbols save in ram variables so we call UPDATE_DISPLAY
	updateNotification(DISP_SYMBOL_BATTERY_3, ON, UPDATE_RAM_VARIBLES_ONLY);
}


void UpdateDisplay(void)
{
    uint8_t ucTempHour = 0;
    uint8_t ucTempMin = 0;
    static bool bTimeToDisplayMaxTemperature = false;

//	if((devConfig.BatchConfig.CurrentBatchStatus == BATCH_STOP) && (bTimeToDisplayErrorMsgFlag == false))
//	{
//		updateNotification(DISP_SYMBOL_HR_GLASS, 1, UPDATE_RAM_VARIBLES_ONLY);
//
//		//Seconds are not shown on display so we have to show 10 till counter reach on 9 and we have to show 9 till couter reach on 8 and so no. So we added 60 count extra only for diplay purpose
//		CalculateAlarmDurationFromSeconds(iBatchStartDelayCounter + 60, &ucTempHour, &ucTempMin);
//
//        ConvertDataToDigits(ucTempHour,(uint8_t *) &DisplayBuffer.Line[1].strng[3]);
//        ConvertDataToDigits(ucTempMin,(uint8_t *) &DisplayBuffer.Line[1].strng[6]);
//        DisplayBuffer.Line[1].strng[0] = 0x00;
//        DisplayBuffer.Line[1].strng[1] = 0x00;
//        DisplayBuffer.Line[1].strng[2] = 0x00;
//        DisplayBuffer.Line[1].strng[5] = ':';
//        updateDisplay(2,DisplayBuffer.Line[1].strng);
//	}
//	else
	{
//        if(bTimeToDisplayErrorMsgFlag == true)   //When Sensor Is Not Connected at That Time Error Message Shown On Display
//        {
//        	updateNotification(DIP_SYSMBOL_CLEAR_ALL, 0, UPDATE_RAM_VARIBLES_ONLY);
//        	DisplayBuffer.Notification.Battery.Type = OFF;
//
//			DisplayBuffer.Line[0].strng[0] = 'E';
//			DisplayBuffer.Line[0].strng[1] = 'R';
//			DisplayBuffer.Line[0].strng[2] = 'R';
//			DisplayBuffer.Line[0].strng[3] = 0x00;
//
//			updateNotification(DISP_SYMBOL_CROSS, 1, UPDATE_RAM_VARIBLES_ONLY); //Cross mark will be displayed when error condition generated
//	        updateDisplay(1,DisplayBuffer.Line[0].strng);
//            if(bPauseFunctionON == false)   //If recording is in pause condition, then pause counter should be displayed on 1st row
//                return;
//        }
//
//		if(bPauseFunctionON == true)
//		{
//			//Seconds are not shown on display so we have to show 10 till counter reach on 9 and we have to show 9 till couter reach on 8 and so no. So we added 60 count extra only for diplay purpose
//			CalculateAlarmDurationFromSeconds(PauseFunCounter + 60, &ucTempHour, &ucTempMin);
//
//	        ConvertDataToDigits(ucTempHour,(uint8_t *) &DisplayBuffer.Line[1].strng[3]);
//	        ConvertDataToDigits(ucTempMin,(uint8_t *) &DisplayBuffer.Line[1].strng[6]);
//	        DisplayBuffer.Line[1].strng[0] = 0x00;
//	        DisplayBuffer.Line[1].strng[1] = 0x00;
//	        DisplayBuffer.Line[1].strng[2] = 0x00;
//	        DisplayBuffer.Line[1].strng[5] = ':';
//	    	UpdateSymbolsOnLCD();
//	    	UpdateDataOnLcd(CurrentTempData);
//	        updateDisplay(2,DisplayBuffer.Line[1].strng);
//			updateNotification(DISP_SYMBOL_HR_GLASS, 1, UPDATE_RAM_VARIBLES_ONLY);
//			updateNotification(DISP_SYMBOL_BATCH_PAUSE, 1, UPDATE_RAM_VARIBLES_ONLY);
//			updateNotification(DISP_SYMBOL_BATCH_RUN, 0, UPDATE_RAM_VARIBLES_ONLY);
//			return;
//		}

        if(bDisplayMinMaxTemperatureFlag)
        {
//            DisplayBuffer.Notification.RecStatus_t.Type = OFF;
            if(bTimeToDisplayMaxTemperature)
            {
                bTimeToDisplayMaxTemperature = false;
                bDisplayMinMaxTemperatureFlag = false;
                DisplayBuffer.Notification.MAX = ON;
                DisplayBuffer.Notification.MIN = OFF;
            	UpdateSymbolsOnLCD();
//            	UpdateDataOnLcd(iMaxTemperature);
            	updateNotification(DISP_SYMBOL_MAX, 1,UPDATE_RAM_VARIBLES_ONLY);
            	updateNotification(DISP_SYMBOL_MIN, 0,UPDATE_RAM_VARIBLES_ONLY);
    			updateNotification(DISP_SYMBOL_BATCH_RUN, 0, UPDATE_RAM_VARIBLES_ONLY);
                return;
            }
            else
            {

                bTimeToDisplayMaxTemperature = true;
                DisplayBuffer.Notification.MIN = ON;
                DisplayBuffer.Notification.MAX = OFF;
            	UpdateSymbolsOnLCD();
//            	UpdateDataOnLcd(iMinTemperature);
            	updateNotification(DISP_SYMBOL_MIN, 1,UPDATE_RAM_VARIBLES_ONLY);
            	updateNotification(DISP_SYMBOL_MAX, 0,UPDATE_RAM_VARIBLES_ONLY);
    			updateNotification(DISP_SYMBOL_BATCH_RUN, 0, UPDATE_RAM_VARIBLES_ONLY);
                return;
            }
        }
	}
	UpdateSymbolsOnLCD();

	if(bTempHumidityToggleFlag)
	{
		UpdateDataOnLcd(CurrentTempData);
		bTempHumidityToggleFlag = false;
	}
	else
	{
		UpdateDataOnLcd(CurrentRHData);
		bTempHumidityToggleFlag = true;
	}
}

void RefreshDisplay (void)
{
//    int temp=0;
//    int temp1=0;
//    char TempArr1[8] = {0};
//    char TempArr2[8] = {0};
//    if(bDisplayOnFlag == FALSE) //If device in sleep mode and display is off then no need to run this function
//        return;

    if(DisplayBuffer.Notification.Battery.Type == BLINK)    //If battery low then battery outer box need to blink, other bars should be off
    {
    	DispSymbolGroup.BattNotification.T4 = ~DispSymbolGroup.BattNotification.T4;
        DispSymbolGroup.BattNotification.T1 = 0;
        DispSymbolGroup.BattNotification.T2 = 0;
        DispSymbolGroup.BattNotification.T3 = 0;
    }
    else if(DisplayBuffer.Notification.Battery.Type == ON)
    {
        switch(DisplayBuffer.Notification.Battery.Bar)
        {
            case 0x0080:    //battery low
                DispSymbolGroup.BattNotification.T1 = 0;
                DispSymbolGroup.BattNotification.T2 = 0;
                DispSymbolGroup.BattNotification.T3 = 0;
                DispSymbolGroup.BattNotification.T4 = 1;   //Outer box of battery
                break;
            case 0x0090:
                DispSymbolGroup.BattNotification.T1 = 1;
                DispSymbolGroup.BattNotification.T2 = 0;
                DispSymbolGroup.BattNotification.T3 = 0;
                DispSymbolGroup.BattNotification.T4 = 1;
                break;
            case 0x00B0:
                DispSymbolGroup.BattNotification.T1 = 1;
                DispSymbolGroup.BattNotification.T2 = 1;
                DispSymbolGroup.BattNotification.T3 = 0;
                DispSymbolGroup.BattNotification.T4 = 1;
                break;
            case 0x00F0:    //Battery full
                DispSymbolGroup.BattNotification.T1 = 1;
                DispSymbolGroup.BattNotification.T2 = 1;
                DispSymbolGroup.BattNotification.T3 = 1;
                DispSymbolGroup.BattNotification.T4 = 1;
                break;
        }
    }
    else
    {
        DispSymbolGroup.BattNotification.T1 = 0;
        DispSymbolGroup.BattNotification.T2 = 0;
        DispSymbolGroup.BattNotification.T3 = 0;
        DispSymbolGroup.BattNotification.T4 = 0;
    }

	SegmentToCOM_Mapping();
	WriteDataOnDisplayDriver();
}


//void MinMaxAndPauseDetection(void)
//{
//	uint8_t Fun_Key = 0;
//	uint8_t Up_Key = 0;
//
//	Fun_Key = KeyStatus.Key[0].ucKeys;
//	Up_Key = KeyStatus.Key[1].ucKeys;
//
//    if((Fun_Key == 0) && (Up_Key == 0) && !bDeviceMenuExecutedByUserFlag && (bTimeToDisplayErrorMsgFlag == false))  //Min/Max Display On LCD and pause function detection.
//    {
//        if((!bDisplayMinMaxTemperatureFlag) && (!bPauseFunctionON))
//        {
//            bDisplayMinMaxTemperatureFlag = true;
////            bTimeToDisplayDate = true;
//        }
//
//        if(devConfig.BatchConfig.CurrentBatchStatus == BATCH_START)
//        	bPauseDetectStartDelay = true;
//    }
//    else
//    {
//        bPauseDetectStartDelay = false;
//        PauseDetectDelayCounter = PAUSEDETECTDELAY;
//    }
//}

