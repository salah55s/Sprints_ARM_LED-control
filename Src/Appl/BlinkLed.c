/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  BlinkLed.c
 *        \brief  App
 *		\details: this file contains the implementaion of BlinkLed app
 *        
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "system_TM4C123.h"
#include "IntCtrl.h"
#include "Port.h"
#include "Dio.h"
#include "Gpt.h"
#include "BlinkLed.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/	

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
volatile static uint8_t flag = FALSE;
static uint32_t SetOnTime = 0;
static uint32_t SetOffTime = 0;
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef enum
{
	LED_OFF,
	LED_ON,
	STOP
}LedState;
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : void BlinkLed_Init(void)                                      
* \Description     : Initializes the Led Port pin                                
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/

void BlinkLed_Init(void)
{
	Gpt_Init(&Gpt_Cfg);
	Gpt_EnableNotification(TIMER0);
	Gpt_CallbackRegister(TIMER0,Timer0_Handler);
}
/******************************************************************************
* \Syntax          : void BlinkLed_SetOnTime(uint32_t Time)                                    
* \Description     : Set the On time in sec for LED                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Time	required time in sec 
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void BlinkLed_SetOnTime(uint32_t Time)
{
	SetOnTime = Time;
}
/******************************************************************************
* \Syntax          : void BlinkLed_SetOffTime(uint32_t Time)                                    
* \Description     : Set the Off time in sec for LED                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Time	required time in sec 
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void BlinkLed_SetOffTime(uint32_t Time)
{
	SetOffTime = Time;
}
/******************************************************************************
* \Syntax          : void BlinkLed_Start(void)                                    
* \Description     : make the LED strat blinking based on the OnTime and OffTime                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None 
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void BlinkLed_Start(void)
{
	Gpt_StartTimer(TIMER0,1); //1 *(1/USER_FREQ_HZ) = 1ms
}
/******************************************************************************
* \Syntax          : void BlinkLed_Stop(void)                                   
* \Description     : Stops the LED blinking                                 
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None 
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void BlinkLed_Stop(void)
{
	Gpt_StopTimer(TIMER0);
}
/******************************************************************************
* \Syntax          : void Timer0_Handler(void)                                   
* \Description     : This the timer handler which is called by the Timer ISR through callback function                                
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None 
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Timer0_Handler(void)
{
	flag = TRUE;
}
/******************************************************************************
* \Syntax          : void BlinkLed_Run(void)                                  
* \Description     : check for OnTime period and OffTime period and take required action to make LED blink                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : None Reentrant                                             
* \Parameters (in) : None 
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/

void BlinkLed_Run(void)
{	
	static uint32_t ms_Counter = 0;
	static uint32_t s_Counter = 0;
	static volatile uint8_t state;
	static uint32_t period = 0;
	period = SetOnTime + SetOffTime;
	if(TRUE == flag)
	{
		flag = FALSE;
		ms_Counter++;
	}
	if(ms_Counter == 1000)
	{
		ms_Counter = 0;
		s_Counter++;
	}
	if(s_Counter < SetOnTime)
	{
		state = LED_ON;
	}
	else if((s_Counter >= SetOnTime) && (s_Counter < period))
	{
		state = LED_OFF;
	}
	else if(s_Counter >= period)
	{
		s_Counter = 0;
		state = STOP;
	}
	switch(state)
	{
		case LED_OFF:
			Dio_WriteChannel(Channels[1].Channel,LOW);
			break;
		case LED_ON:
			Dio_WriteChannel(Channels[1].Channel,HIGH);
			break;
		case STOP:
			break;
		default:
			break;
	}
}
