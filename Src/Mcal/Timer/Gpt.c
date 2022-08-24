/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Gpt.c
 *        \brief  General porpose timer Driver
 *
 *      \details  The Driver Configure All MCU timers
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Macros.h"
#include "Gpt.h"
#include "Mcu_Hw.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/	
#define	MCU_CLK							16000000UL

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
typedef void (*CallBack)(void);
static CallBack GptCallbackFunction[12] = {NULL_PTR};
static uint32_t NumOfTicksPerUserTick[12] = {0};
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void Gpt_Init(void)                                      
* \Description		 : Initializes the hardware timer module.
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ConfigPtr :Pointer to a selected configuration structure                    
* \Parameters (out): None                                                      
* \Return value:   : None

*******************************************************************************/
void Gpt_Init(const Gpt_ConfigType*ConfigPtr)
{
		//Enable CLK for Timer module
	SET_BIT(SYSCTRL->RCGCTIMER,ConfigPtr->GptChannelId);
	//1-1. Ensure the timer is disabled (GPTMCTL)
	CLEAR_BIT(TIMER_BASE(ConfigPtr->GptChannelId)->CTL,0);
	//2. Write the GPTM Configuration with a value of 0x0000.0000.
	TIMER_BASE(ConfigPtr->GptChannelId)->CFG = 0x00000000;
	//3. Configure the TnMR in (GPTMTnMR):One-Shot/Periodic
	if(GPT_MODE_SLEEP == ConfigPtr->Mode)
		SET_BIT(TIMER_BASE(ConfigPtr->GptChannelId)->TAMR,0);
	else if(GPT_MODE_NORMAL == ConfigPtr->Mode)
		SET_BIT(TIMER_BASE(ConfigPtr->GptChannelId)->TAMR,1);
	//4. Optionally configure the TnSNAPS, TnWOT, TnMTE, and TnCDIR bits in the GPTMTnMR register
	//to capture the value of the free-running timer at time-out, use an external
  //trigger to start counting, configure an additional trigger or interrupt, and count up or down.
	//GPT_COUNT_UP
	SET_BIT(TIMER_BASE(ConfigPtr->GptChannelId)->TAMR , 4);
	//to enable timerA stall for debug
	SET_BIT(TIMER_BASE(ConfigPtr->GptChannelId)->CTL,1);
	//6. If interrupts are required, set the appropriate bits in the GPTM Interrupt Mask Register(GPTMIMR).
	
	//calculate timer period
	NumOfTicksPerUserTick[ConfigPtr->GptChannelId] = MCU_CLK/(ConfigPtr->GptChannelTickFrequency);
	uint32_t ActualMaxTicks = NumOfTicksPerUserTick[ConfigPtr->GptChannelId] * ConfigPtr->GptChannelTickValueMax; 
	TIMER_BASE(ConfigPtr->GptChannelId)->TAILR = ActualMaxTicks;
/*ToDo: change timer width based on GptChannelTickValueMax which determines 
	 the number of bits that user intersted in */
}
/******************************************************************************
* \Syntax          : Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel)                                      
* \Description     : Returns the time already elapsed
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Channel :Numeric identifier of the GPT channel.                    
* \Parameters (out): None                                                      
* \Return value:   : Gpt_ValueType Elapsed timer value (in number of ticks)
*******************************************************************************/
Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel)
{
		return TIMER_BASE(Channel)->TAR/NumOfTicksPerUserTick[Channel];	 
}
/******************************************************************************
* \Syntax          : Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel)                                      
* \Description     : Returns the time remaining until the target time is reached.
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Channel :Numeric identifier of the GPT channel.                    
* \Parameters (out): None                                                      
* \Return value:   : Gpt_ValueType Remaining timer value (in number of ticks)
*******************************************************************************/
Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel)
{
	return (TIMER_BASE(Channel)->TAILR -TIMER_BASE(Channel)->TAR)/NumOfTicksPerUserTick[Channel];	 
}
/******************************************************************************
* \Syntax          : void Gpt_StartTimer(Gpt_ChannelType Channel,Gpt_ValueType Value)                                      
* \Description     : Starts a timer channel.                                                           
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Channel Numeric identifier of the GPT channel.                    
*									 : Value   Target time in number of ticks, value in ms.
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Gpt_StartTimer(Gpt_ChannelType Channel,Gpt_ValueType Value)
{
	uint32_t ActualMaxTicks = NumOfTicksPerUserTick[Channel] * Value; 
	TIMER_BASE(Channel)->TAILR = ActualMaxTicks;
	SET_BIT(TIMER_BASE(Channel)->CTL,0);//A
}
/******************************************************************************
* \Syntax          : void Gpt_StopTimer(Gpt_ChannelType Channel)                                      
* \Description     : Stops a timer channel.
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Channel  Numeric identifier of the GPT channel             
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Gpt_StopTimer(Gpt_ChannelType Channel)
{
	CLEAR_BIT(TIMER_BASE(Channel)->CTL,0); 
}
/******************************************************************************
* \Syntax          : void Gpt_EnableNotification(Gpt_ChannelType Channel)
* \Description     : Enables the interrupt notification for a channel (relevant in normal mode).                                                                            
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Channel Numeric identifier of the GPT channel.                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Gpt_EnableNotification(Gpt_ChannelType Channel)
{
	SET_BIT(TIMER_BASE(Channel)->IMR,0);//TATOIM TimeOut interrupt
}
/******************************************************************************
* \Syntax          : void Gpt_DisableNotification(Gpt_ChannelType Channel)
* \Description     : Disables the interrupt notification for a channel (relevant in normal mode).                                                                            
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Channel Numeric identifier of the GPT channel.                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Gpt_DisableNotification(Gpt_ChannelType Channel) //no notifiaction, no isr will operate
{
	CLEAR_BIT(TIMER_BASE(Channel)->IMR,0);//TATOIM TimeOut interrupt
}

/******************************************************************************
* \Syntax          : void Gpt_CallbackRegister(Gpt_ChannelType Channel,void (*InterruptHandler)(void))
* \Description     : registers the user callback which will be called by the interrupt                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Channel Numeric identifier of the GPT channel
*									 : InterruptHandler user callback function
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Gpt_CallbackRegister(Gpt_ChannelType Channel,void (*InterruptHandler)(void))
{
	GptCallbackFunction[Channel] = InterruptHandler;
}
/******************************************************************************
* \Syntax          : Std_ReturnType Gpt_GetPredefTimerValue(Gpt_PredefTimerType PredefTimer,uint32_t*TimeValuePtr)                                      
* \Description     : Shall return the current value of the GPT Predef Timer passed by PredefTimer.                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : PredefTimer           
*									 : TimeValuePtr
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
Std_ReturnType Gpt_GetPredefTimerValue(Gpt_PredefTimerType PredefTimer,uint32_t*TimeValuePtr)
{
	
}
/******************************************************************************
* \Syntax          : void Gpt_PollTimer(Gpt_ChannelType Channel)                                     
* \Description     : shows the state of the Gpt internal interrupt signal                                                                           
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Channel Numeric identifier of the GPT channel                    
* \Parameters (out): None                                                      
* \Return value:   : uint8_t true if interrupt is signaled
*******************************************************************************/
Std_ReturnType Gpt_PollTimer(Gpt_ChannelType Channel)
{
	return GET_BIT(TIMER_BASE(Channel)->RIS,0);
}

/******************************************************************************
* \Syntax          : void Gpt_ClrFlag(Gpt_ChannelType Channel)                                    
* \Description     : used to clear the status bits of interrupt                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Channel Numeric identifier of the GPT channel                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Gpt_ClrFlag(Gpt_ChannelType Channel)
{
	uint32_t u32status = TIMER_BASE(Channel)->MIS;
	SET_BIT(TIMER_BASE(Channel)->ICR,u32status>>1);
}
/******************************************************************************
* \Syntax          : void TIMER0A_Handler(void)                                      
* \Description     : The interrupt routine                                                                              
* \Sync\Async      : Asynchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Non                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void TIMER0A_Handler(void)
{
	Gpt_ClrFlag(0);
	if(NULL_PTR != GptCallbackFunction[0])
	{
		GptCallbackFunction[0]();
	}
}
void TIMER1A_Handler(void)
{
	Gpt_ClrFlag(1);
	if(NULL_PTR == GptCallbackFunction[1])
	{
		GptCallbackFunction[1]();
	}
}
void TIMER2A_Handler(void)
{
	Gpt_ClrFlag(2);
	if(NULL_PTR == GptCallbackFunction[2])
	{
		GptCallbackFunction[2]();
	}
}
void TIMER3A_Handler(void)
{
	Gpt_ClrFlag(3);
	if(NULL_PTR == GptCallbackFunction[3])
	{
		GptCallbackFunction[3]();
	}
}
void TIMER4A_Handler(void)
{
	Gpt_ClrFlag(4);
	if(NULL_PTR == GptCallbackFunction[4])
	{
		GptCallbackFunction[4]();
	}
}
void TIMER5A_Handler(void)
{
	Gpt_ClrFlag(5);
	if(NULL_PTR == GptCallbackFunction[5])
	{
		GptCallbackFunction[5]();
	}
}
void WTIMER0A_Handler(void)
{
	Gpt_ClrFlag(6);
	if(NULL_PTR == GptCallbackFunction[6])
	{
		GptCallbackFunction[6]();
	}
}
void WTIMER1A_Handler(void)
{
	Gpt_ClrFlag(0);
	if(NULL_PTR == GptCallbackFunction[0])
	{
		GptCallbackFunction[0]();
	}
}
void WTIMER2A_Handler(void)
{
	Gpt_ClrFlag(0);
	if(NULL_PTR == GptCallbackFunction[0])
	{
		GptCallbackFunction[0]();
	}
}
void WTIMER3A_Handler(void)
{
	Gpt_ClrFlag(0);
	if(NULL_PTR == GptCallbackFunction[0])
	{
		GptCallbackFunction[0]();
	}
}
void WTIMER4A_Handler(void)
{
	Gpt_ClrFlag(0);
	if(NULL_PTR == GptCallbackFunction[0])
	{
		GptCallbackFunction[0]();
	}
}
void WTIMER5A_Handler(void)
{
	Gpt_ClrFlag(0);
	if(NULL_PTR == GptCallbackFunction[0])
	{
		GptCallbackFunction[0]();
	}
}
/**********************************************************************************************************************
 *  END OF FILE: Gpt.c
 *********************************************************************************************************************/
