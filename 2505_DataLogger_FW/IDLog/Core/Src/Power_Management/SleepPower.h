/*
 * SleepPower.h
 *
 *  Created on: Nov 4, 2025
 *      Author: TITHI
 */

#ifndef SRC_POWER_MANAGEMENT_SLEEPPOWER_H_
#define SRC_POWER_MANAGEMENT_SLEEPPOWER_H_

#define SLEEP_POWER  		0xFF
#define DEEP_SLEEP_POWER  	0xAA

static enum {
   Bat_three_Bar = 0,
   Bat_Two_Bar,
   Bat_One_Bar,
   Emty_Bar,
}Battery_Bar = Bat_three_Bar;

extern uint8_t uRemain_Battery;
extern bool bUart_Timer_init;

void SystemReInit(void);

//==================================================================================================================================================
//Function Name		: void PowerDown_GPIO_Deinit(void)
//Preconditions		: none.
//Input Parameter	: none.
//Return Value		: none..
//Overview          : This function will Deinit GPIOs before controller gois to sleep.
//Author			:
//Date				:
//Revision			: 0
//Date				:
//==================================================================================================================================================

void PowerDown_GPIO_Deinit(void);

//==================================================================================================================================================
//Function Name		: bool PowerManager(bool bFlagForceSleep)
//Preconditions		: none.
//Input Parameter	: none.
//Return Value		: none.
//Overview          : This function will manage frequncy switch sequnce.
//Author			:
//Date				:
//Revision			: 0
//Date				:
//==================================================================================================================================================

bool PowerManager(bool bFlagForceSleep);

//==================================================================================================================================================
//Function Name		: bool isDeviceOnUSBPower( GPIO_PinState *PinState)
//Preconditions		: none.
//Input Parameter	: none.
//Return Value		: USB Detect Pin state.
//Overview          : This function will detect USB connected or not connected.
//Author			:
//Date				:
//Revision			: 0
//Date				:
//==================================================================================================================================================

bool isDeviceOnUSBPower( GPIO_PinState *PinState);

//==================================================================================================================================================
//Function Name		: bool USB_EnableDisableControl(int start)
//Preconditions		: Need to inser USB.
//Input Parameter	: Enable or Desable.
//Return Value		: Status of USB driver.
//Overview          : This function will initialize or de-initialize USB function or drivers or change Keybord debaunce time at 1 Mhz or 48 Mhz.
//Author			:
//Date				:
//Revision			: 0
//Date				:
//==================================================================================================================================================

bool USB_EnableDisableControl(int start);

//==================================================================================================================================================
//Function Name		: void Usb_GPIO_Control(int state)
//Preconditions		: none.
//Input Parameter	: Enable or Desable.
//Return Value		: none.
//Overview          : This function will initialize or de-initialize USB GPIOs.
//Author			:
//Date				:
//Revision			: 0
//Date				:
//==================================================================================================================================================

void Usb_GPIO_Control(int state);

//==================================================================================================================================================
//Function Name		: void Uart_TimerControl(int state)
//Preconditions		: none.
//Input Parameter	: Enable or Desable.
//Return Value		: none.
//Overview          : This function will initialize or de-initialize UART and Timer peripherals.
//Author			:
//Date				:
//Revision			: 0
//Date				:
//==================================================================================================================================================

void Uart_TimerControl(int state);

//==================================================================================================================================================
//Function Name		: void ADC_InitDeInitControl(int state)
//Preconditions		: none.
//Input Parameter	: Enable or Desable.
//Return Value		: none.
//Overview          : This function will initialize or de-initialize ADC peripherals.
//Author			:
//Date				:
//Revision			: 0
//Date				:
//==================================================================================================================================================

void ADC_InitDeInitControl(int state);

//==================================================================================================================================================
//Function Name		: bool SystemClock_Config_1Mhz(void)
//Preconditions		: USB is not connected.
//Input Parameter	: none.
//Return Value		: stutus of 1 Mhz freq.
//Overview          : This function initialize 1 Mhz MSI frequncy for low power consuption.
//Author			:
//Date				:
//Revision			: 0
//Date				:
//==================================================================================================================================================

bool SystemClock_Config_1Mhz(void);

//==================================================================================================================================================
//Function Name		: void Battery_Bar_Update(void)
//Preconditions		: none
//Input Parameter	:
//Return Value		: none
//Dependencies		: Battery Voltage Vbat.
//Overview          : this function update battery voltage % and if battery bar stage change then update battery remain day.
//Author			:
//Date				:
//Revision			: 0
//Date				:
//==================================================================================================================================================

void Battery_Bar_Update(void);

#endif /* SRC_POWER_MANAGEMENT_SLEEPPOWER_H_ */
