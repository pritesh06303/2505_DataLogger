/*
 * SleepPower.c
 *
 *  Created on: Nov 4, 2025
 *      Author: TITHI
 */

#include "HardwareConfig.h"


bool bUart_Timer_init = false;
uint8_t uRemain_Battery = 0;

float volt_bands[4][2] = {{ 3.5 , 2.7},
						  {2.7 , 2.6},
						  {2.6 , 2.5},
						  {2.5 , 0.0}};

////==================================================================================================================================================
////Function Name		: bool SystemClock_Config_1Mhz(void)
////Preconditions		: USB is not connected.
////Input Parameter	: none.
////Return Value		: stutus of 1 Mhz freq.
////Overview          : This function initialize 1 Mhz MSI frequncy for low power consuption.
////Author			:
////Date				:
////Revision			: 0
////Date				:
////==================================================================================================================================================
//
//bool SystemClock_Config_1Mhz(void)
//{
//	bool result = true;
//
//  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
//  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
//  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
//
//
//  /** Configure the main internal regulator output voltage
//  */
//  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure LSE Drive Capability
//  */
//  HAL_PWR_EnableBkUpAccess();
//  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
//
//  /** Initializes the RCC Oscillators according to the specified parameters
//  * in the RCC_OscInitTypeDef structure.
//  */
//  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE
//                              |RCC_OSCILLATORTYPE_MSI;
//  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
//  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
//  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
//  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
//  RCC_OscInitStruct.MSICalibrationValue = 0;
//  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_4;
//  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
//  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Initializes the CPU, AHB and APB buses clocks
//  */
//  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
//                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
//  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
//  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
//  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
//
//  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//
//  return result;
//
//}
//
//
////==================================================================================================================================================
////Function Name		: void PowerDownUp(uint8_t Powermode)
////Preconditions		: USB is not connected.
////Input Parameter	: Deep sleep power mode and sleep power mode.
////Return Value		: stutus of 1 Mhz freq.
////Overview          : This function will intruct to controller for goes to deep sleep mode or sleep mode.
////Author			:
////Date				:
////Revision			: 0
////Date				:
////==================================================================================================================================================
//
//void PowerDownUp(uint8_t Powermode)
//{
//
//	//================ Deinit Modules===================================================//
////	GPIO_InitTypeDef GPIO_InitStructure;
//	  /* Configure all GPIO port pins in Analog Input mode (floating input trigger OFF) */
//	  /* Note: Debug using ST-Link is not possible during the execution of this   */
//	  /*       example because communication between ST-link and the device       */
//	  /*       under test is done through UART. All GPIO pins are disabled (set   */
//	  /*       to analog input mode) including  UART I/O pins.           */
//	if(devConfig.BatchConfig.Display == OFF)
//	{
//		if((uDisplay_On_Counter == 0) && (bLCD_Init == true))
//		{
//			HAL_LCD_Clear(&hlcd);
//			HAL_LCD_DeInit(&hlcd);
//			bLCD_Init = false;
//
//		}
//	}
//
//	HAL_SuspendTick();
//
//	PowerDown_GPIO_Deinit();
//
///* ### - 4 - Enter in Stop mode ########################################### */
//	if(Powermode == DEEP_SLEEP_POWER)
//	{
//		HAL_RTC_DeInit(&hrtc);
//		HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
//
//		__HAL_RCC_PWR_CLK_ENABLE();
//		HAL_PWR_EnableBkUpAccess();
//		/* Disable all used wakeup sources: WKUP pin */
////		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
//		HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN1);
//		HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN2);
//		HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN3);
//
//		  /* Clear wake up Flag */
//	//	  __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WUF3);
//
//		/* Enable wakeup pin WKUP2 */
//		HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN2_HIGH);
//
//		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WUF2);
//
//		HAL_PWREx_EnterSHUTDOWNMode();
//	}
//	else
//		HAL_PWREx_EnterSTOP2Mode(PWR_STOPENTRY_WFI);
//
//
////================ Init Modules===================================================//
//
//	SystemReInit();
//	HAL_ResumeTick();
//}
//
////==================================================================================================================================================
////Function Name		: bool USB_EnableDisableControl(int start)
////Preconditions		: Need to inser USB.
////Input Parameter	: Enable or Desable.
////Return Value		: Status of USB driver.
////Overview          : This function will initialize or de-initialize USB function or drivers or change Keybord debaunce time at 1 Mhz or 48 Mhz.
////Author			:
////Date				:
////Revision			: 0
////Date				:
////==================================================================================================================================================
//
//bool USB_EnableDisableControl(int start)
//{
//	extern USBD_HandleTypeDef hUsbDeviceFS;
//	if (start == ENABLE)
//	{
//		Uart_TimerControl(start);
//		Usb_GPIO_Control(start);
//		ADC_InitDeInitControl(start);
//		__HAL_RCC_USB_OTG_FS_RELEASE_RESET();
////		if(devConfig.BatchConfig.Display == ON)
////		{
//			ucDisplayRefreshTime = DISPLAYREFRESH_LCD_OFF;
//			bTimeRefreshDisplay = true;
////		}
//		 DISCRETETIMEOUTCOUNTER = 10  ;
//		 CONTINIOUSTIMEOUTCOUNTER = 50  ;
//		 DEBOUNCETIMEOUTCOUNTER = 10  ;
//		 SCANKEYBOARDDELAY = 5 ;
//		if (USBD_Start(&hUsbDeviceFS) != USBD_OK)
//		{
////			ErrorLogInFlash(ERR_USB_START);
//			Error_Handler();
//			return false;
//		}
//	}
//	else
//	{
//		Uart_TimerControl(start);
//		Usb_GPIO_Control(start);
//		ADC_InitDeInitControl(start);
//		__HAL_RCC_USB_OTG_FS_FORCE_RESET();
//		 DISCRETETIMEOUTCOUNTER  = 1  ;
//		 CONTINIOUSTIMEOUTCOUNTER = 5  ;
//		 DEBOUNCETIMEOUTCOUNTER  = 1  ;
//		 SCANKEYBOARDDELAY   = 1 ;
//		if (USBD_Stop(&hUsbDeviceFS) != USBD_OK)
//		{
////			ErrorLogInFlash(ERR_USB_STOP);
//			Error_Handler();
//			return false;
//		}
//	}
//	return true;
//}
//
//
////==================================================================================================================================================
////Function Name		: void Usb_GPIO_Control(int state)
////Preconditions		: none.
////Input Parameter	: Enable or Desable.
////Return Value		: none.
////Overview          : This function will initialize or de-initialize USB GPIOs.
////Author			:
////Date				:
////Revision			: 0
////Date				:
////==================================================================================================================================================
//
//void Usb_GPIO_Control(int state)
//{
//	GPIO_InitTypeDef GPIO_InitStruct;
//
//	if (state == ENABLE)
//	{
////		__HAL_RCC_GPIOC_CLK_ENABLE();
////		__HAL_RCC_GPIOA_CLK_ENABLE();
//		/**USB_OTG_FS GPIO Configuration
//		PC9     ------> USB_OTG_FS_NOE
//		PA11     ------> USB_OTG_FS_DM
//		PA12     ------> USB_OTG_FS_DP
//		*/
//		GPIO_InitStruct.Pin = GPIO_PIN_9;
//		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//		GPIO_InitStruct.Pull = GPIO_NOPULL;
//		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//		GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
//		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
//
//		GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
//		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//		GPIO_InitStruct.Pull = GPIO_NOPULL;
//		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//		GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
//		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//	}
//	else
//	{
//		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_9);
//		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);
//	}
//}
//
//
//
////==================================================================================================================================================
////Function Name		: void Uart_TimerControl(int state)
////Preconditions		: none.
////Input Parameter	: Enable or Desable.
////Return Value		: none.
////Overview          : This function will initialize or de-initialize UART and Timer peripherals.
////Author			:
////Date				:
////Revision			: 0
////Date				:
////==================================================================================================================================================
//
//void Uart_TimerControl(int state)
//{
//	if ((state == ENABLE) && (devConfig.BatchConfig.CurrentBatchStatus == BATCH_STOP))
//	{
//		HAL_UART_Init(&huart2);
//		HAL_TIM_Base_Init(&htim2);
//		HAL_TIM_Base_Start_IT(&htim2);
//		sci_Recive_Init();
//	}
//	else
//	{
//		for(int l=0 ; l<20 ; l++)
//			Recive_uart2[l] = 0;
//
//		bCalibrationMenu_On = false;
//
//		HAL_UART_Abort_IT(&huart2);
//		HAL_UART_DeInit(&huart2);
//		HAL_TIM_Base_Stop_IT(&htim2);
//		HAL_TIM_Base_DeInit(&htim2);
//		bUart_Timer_init = false;
//	}
//}
//
//
//
////==================================================================================================================================================
////Function Name		: void ADC_InitDeInitControl(int state)
////Preconditions		: none.
////Input Parameter	: Enable or Desable.
////Return Value		: none.
////Overview          : This function will initialize or de-initialize ADC peripherals.
////Author			:
////Date				:
////Revision			: 0
////Date				:
////==================================================================================================================================================
//
//void ADC_InitDeInitControl(int state)
//{
//    GPIO_InitTypeDef GPIO_InitStruct = {0};
//	if (state == ENABLE)
//	{
////		HAL_GPIO_WritePin(S1_POS_M_GPIO_Port, S1_POS_M_Pin, GPIO_PIN_RESET);
////		/*Configure GPIO pins : S1_POS_M_Pin */
////		GPIO_InitStruct.Pin = S1_POS_M_Pin;
////		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
////		GPIO_InitStruct.Pull = GPIO_NOPULL;
////		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
////		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
////		SystemClock_Config_1Mhz();
//		HAL_ADC_Init(&hadc1);
//	}
//	else
//	{
////		HAL_GPIO_WritePin(S1_POS_M_GPIO_Port ,S1_POS_M_Pin , GPIO_PIN_SET );
////		HAL_GPIO_DeInit(S1_POS_M_GPIO_Port, S1_POS_M_Pin);
//		HAL_ADC_DeInit(&hadc1);
//	}
//}
//
//
//typedef enum{
//	SleepMode = 0,
//	Set1MhzSystemFrq,
//	Set48MhzSystemFrq,
//	NoSystemFrq
//}PowerMode;
//
//PowerMode CurrentPowerMode = NoSystemFrq;
//PowerMode OldPowerMode = NoSystemFrq;
//
//HAL_TickFreqTypeDef uwTickFreq1 = HAL_TICK_FREQ_DEFAULT;  /* 1KHz */
//
////bool isDeviceOnUSBPower( GPIO_PinState *PinState)
////{
////	static enum
////	{
////		GET_POWER_STAT = 0,
////		WAIT_USB_DEBOUNCE
////	}PowerState = GET_POWER_STAT;
////	static uint32_t tickstart = 0;
////	static GPIO_PinState OldPowerState;
////	switch(PowerState)
////	{
////	case GET_POWER_STAT:
////		OldPowerState = HAL_GPIO_ReadPin(VbusSense_GPIO_Port,VbusSense_Pin);
////		tickstart = HAL_GetTick();
////		PowerState = WAIT_USB_DEBOUNCE;
////		break;
////	case WAIT_USB_DEBOUNCE:
////		if (HAL_GetTick() > tickstart + 5)
////		{
////			if ( OldPowerState == HAL_GPIO_ReadPin(VbusSense_GPIO_Port,VbusSense_Pin))
////			{
////				*PinState = OldPowerState;
////				PowerState = GET_POWER_STAT;
////				return true;;
////			}
////			PowerState = GET_POWER_STAT;
////		}
////		break;
////	}
////
////return false;
////}
//
//
////==================================================================================================================================================
////Function Name		: bool isDeviceOnUSBPower( GPIO_PinState *PinState)
////Preconditions		: none.
////Input Parameter	: none.
////Return Value		: USB Detect Pin state.
////Overview          : This function will detect USB connected or not connected.
////Author			:
////Date				:
////Revision			: 0
////Date				:
////==================================================================================================================================================
//
//bool isDeviceOnUSBPower( GPIO_PinState *PinState)
//{
//	*PinState = HAL_GPIO_ReadPin(VbusSense_GPIO_Port,VbusSense_Pin);
//
//	if(*PinState == 1)
//		return true;
//	else
//		return false;
//}
//
//
////==================================================================================================================================================
////Function Name		: bool PowerManager(bool bFlagForceSleep)
////Preconditions		: none.
////Input Parameter	: none.
////Return Value		: none.
////Overview          : This function will manage frequncy switch sequnce.
////Author			:
////Date				:
////Revision			: 0
////Date				:
////==================================================================================================================================================
//
//bool PowerManager(bool bFlagForceSleep)
//{
//	GPIO_PinState usbPower;
//
////	if (!isDeviceOnUSBPower(&usbPower))
////		return false;
//	isDeviceOnUSBPower(&usbPower);
//
//	if (usbPower == GPIO_PIN_RESET)
//	{
//		isSystemOnUsbPower = false;
//		CurrentPowerMode = Set1MhzSystemFrq;
//
//		if((bFlagForceSleep) && (OldPowerMode != Set48MhzSystemFrq))
//			CurrentPowerMode = SleepMode;
//	}
//	else
//	{
//		isSystemOnUsbPower = true;
//		CurrentPowerMode = Set48MhzSystemFrq;
//	}
//
//	switch (CurrentPowerMode)
//	{
//		case SleepMode:
//		{
//			if(devConfig.BatchConfig.Display == OFF)
//			{
//				if(uDisplay_On_Counter == 0)
//				{
//					if((bFlagTimeToDeepSleep == true) && (devConfig.BatchConfig.CurrentBatchStatus == BATCH_STOP))
//					{
//						PowerDownUp(DEEP_SLEEP_POWER);
//					}
//					else
//					{
//						if((bTimeToDisplayHistoryDataFlag == false) && (bDeviceMenuExecutedByUserFlag == false))
//							PowerDownUp(SLEEP_POWER);
//					}
//				}
//			}
//			else
//			{
//				if(bDeviceMenuExecutedByUserFlag == false)
//				{
//					if((bFlagTimeToDeepSleep == true) && (devConfig.BatchConfig.CurrentBatchStatus == BATCH_STOP))
//					{
//						PowerDownUp(DEEP_SLEEP_POWER);
//					}
//					else
//					{
//						if((KeyStatus.Key[0].ucKeys != 0) && (bTimeToDisplayHistoryDataFlag == false) && (bDeviceMenuExecutedByUserFlag == false))
//							PowerDownUp(SLEEP_POWER);
//					}
//				}
//			}
//			return true;
//		}
//		case Set1MhzSystemFrq:
//		{
//			if (OldPowerMode != CurrentPowerMode)
//			{
//				USB_EnableDisableControl(DISABLE);
////				__HAL_RCC_USB_OTG_FS_FORCE_RESET();
//				SystemClock_Config_1Mhz();
//				// Set 1MHz
//				OldPowerMode = CurrentPowerMode;
//			}
//			return true;
//		}
//		case Set48MhzSystemFrq:
//		{
//			if (OldPowerMode != CurrentPowerMode)
//			{
//				// Set 48MHz
//				SystemClock_Config();
//				USB_EnableDisableControl(ENABLE);
////				__HAL_RCC_USB_OTG_FS_RELEASE_RESET();
//				MX_USB_DEVICE_Init();
//
//				OldPowerMode = CurrentPowerMode;
//			}
//			return true;
//		}
//		case NoSystemFrq:
//			return true;
//	}
//	return false;
//}
//
//
////==================================================================================================================================================
////Function Name		: void PowerDown_GPIO_Deinit(void)
////Preconditions		: none.
////Input Parameter	: none.
////Return Value		: none..
////Overview          : This function will Deinit GPIOs before controller gois to sleep.
////Author			:
////Date				:
////Revision			: 0
////Date				:
////==================================================================================================================================================
//
//void PowerDown_GPIO_Deinit(void)
//{
//
////	HAL_GPIO_DeInit(GPIOC, GPIO_PIN_9);
////	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);
//
//	 HAL_GPIO_WritePin(HB_LED_GPIO_Port, HB_LED_Pin , GPIO_PIN_RESET);
//	 HAL_GPIO_DeInit(HB_LED_GPIO_Port, HB_LED_Pin);
//
////	 HAL_GPIO_WritePin(S1_POS_M_GPIO_Port ,S1_POS_M_Pin , GPIO_PIN_SET );
////	 HAL_GPIO_DeInit(S1_POS_M_GPIO_Port, S1_POS_M_Pin);
//
////	 HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
////	 HAL_GPIO_DeInit(BUZZER_GPIO_Port, BUZZER_Pin);
//
//	 HAL_GPIO_DeInit(FUNCTION_KEY_GPIO_Port, FUNCTION_KEY_Pin);
////	 HAL_GPIO_DeInit(S1_NEG_M_GPIO_Port, S1_NEG_M_Pin);
//	 HAL_GPIO_DeInit(VbusSense_GPIO_Port, VbusSense_Pin);
//
//	 HAL_GPIO_DeInit(ENTER_KEY_GPIO_Port, ENTER_KEY_Pin);
//	 HAL_GPIO_DeInit(UP_KEY_GPIO_Port, UP_KEY_Pin);
////	 HAL_GPIO_DeInit(SensorDetect_GPIO_Port, SensorDetect_Pin);
//
//
//}


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

void Battery_Bar_Update(void)
{
	if(batvolt<= volt_bands[0][0] && batvolt > volt_bands[0][1])
	{
		uRemain_Battery = Bat_three_Bar;
	}
	else if(batvolt<= volt_bands[1][0] && batvolt > volt_bands[1][1])
	{
		uRemain_Battery = Bat_Two_Bar;
	}
	else if(batvolt<= volt_bands[2][0] && batvolt > volt_bands[2][1])
	{
		uRemain_Battery = Bat_One_Bar;
	}
	else if(batvolt<= volt_bands[3][0] && batvolt > volt_bands[3][1])
	{
		uRemain_Battery = Emty_Bar;
	}
}
