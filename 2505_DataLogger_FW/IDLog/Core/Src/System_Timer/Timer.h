/*
 * Timer.h
 *
 *  Created on: Nov 1, 2025
 *      Author: TITHI
 */

#ifndef SRC_SYSTEM_TIMER_TIMER_H_
#define SRC_SYSTEM_TIMER_TIMER_H_

extern bool bSensor_Read ;
extern bool bOne_Secend_Timer_Flag;
extern bool b50ms_Flag ;
extern bool b400ms_Falg_var;

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
void App_TimerHandler(void);

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
void TimerInterrupt_1mSec_CallingFunction(void);


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
void TimerInterrupt_10mSec_CallingFunction(void);

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
void TimerInterrupt_500mSec_CallingFunction(void);

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
void TimerInterrupt_1Sec_CallingFunction(void);

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
void TimerInterrupt_5Sec_CallingFunction(void);

#endif /* SRC_SYSTEM_TIMER_TIMER_H_ */
