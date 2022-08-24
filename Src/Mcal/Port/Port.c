/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Port.c
 *        \brief  General perpose input output driver Driver
 *
 *      \details  The Driver Configure All MCU pins
 *                Enable Port pin
 *								Read and Write on Port pin
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Macros.h"
#include "Port.h"
#include "Mcu_Hw.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/	

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

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
* \Syntax          : void Port_Init(const Port_ConfigType*ConfigPtr)                                      
* \Description     : Initializes the Port Driver module.                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : ConfigPtr: pointer to user configurations                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Port_Init(const Port_ConfigType*ConfigPtr)
{
	
	if(NULL_PTR == ConfigPtr)
	{
//		printf("error");
		ConfigPtr = Channels; //defualt
	}
	for(uint8_t i=0;i<DIO_CONFIGURED_CHANNLES;i++)
	{
			/*Enable Clocking for the Port*/

			SET_BIT(SYSCTRL->RCGCPORT,(ConfigPtr[i].Channel.Port));
			/*TODO:add interrupt handling if needed*/
		
			/*Setting Direction*/
			if( DIRECTION_OUTPUT == (ConfigPtr[i].Direction))
				SET_BIT(GPIO_BASE(ConfigPtr[i].Channel.Port)->DIR,ConfigPtr[i].Channel.Pin);
			//				SET_BIT(PORTDIR(ConfigPtr[i].Channel.Port),ConfigPtr[i].Channel.Pin);
			else if(DIRECTION_INPUT == (ConfigPtr[i].Direction))
					CLEAR_BIT(GPIO_BASE(ConfigPtr[i].Channel.Port)->DIR,ConfigPtr[i].Channel.Pin);
			//CLEAR_BIT(PORTDIR(ConfigPtr[i].Channel.Port),ConfigPtr[i].Channel.Pin);
			/*Setting Alternate Function*/
			if(ConfigPtr[i].Mode == SPECIAL_MODE)
			{
				/*TODO: Alternate Functions PortAFSEL & PortPCTL PMCx Bit Field Encoding*/
				PORTAFSEL(ConfigPtr[i].Channel.Port) |= SPECIAL_MODE;
				PORTPCTL(ConfigPtr[i].Channel.Port);/* TODO: config this register*/
			}
			/*Setting Attach Output Current*/
			if(ConfigPtr[i].Current == R2R)
			{
				SET_BIT(GPIO_BASE(ConfigPtr[i].Channel.Port)->DR2R,ConfigPtr[i].Channel.Pin);
				//SET_BIT(PORTDR2R(ConfigPtr[i].Channel.Port),ConfigPtr[i].Channel.Pin);
			}
			else if(ConfigPtr[i].Current == R4R)
			{
				SET_BIT(GPIO_BASE(ConfigPtr[i].Channel.Port)->DR4R,ConfigPtr[i].Channel.Pin);
				//SET_BIT(PORTDR4R(ConfigPtr[i].Channel.Port),ConfigPtr[i].Channel.Pin);
			}
			else if(ConfigPtr[i].Current == R8R)
			{
				SET_BIT(GPIO_BASE(ConfigPtr[i].Channel.Port)->DR8R,ConfigPtr[i].Channel.Pin);
				//SET_BIT(PORTDR8R(ConfigPtr[i].Channel.Port),ConfigPtr[i].Channel.Pin);
			}
			/*Setting Attach Resistor*/
			if(ConfigPtr[i].Attach == PULL_DOWN)
			{
				SET_BIT(GPIO_BASE(ConfigPtr[i].Channel.Port)->PDR,ConfigPtr[i].Channel.Pin);
				//SET_BIT(PORTPDR(ConfigPtr[i].Channel.Port),ConfigPtr[i].Channel.Pin);
			}
			else if(ConfigPtr[i].Attach == PULL_UP)
			{
				SET_BIT(GPIO_BASE(ConfigPtr[i].Channel.Port)->PUR,ConfigPtr[i].Channel.Pin);
				//SET_BIT(PORTPUR(ConfigPtr[i].Channel.Port),ConfigPtr[i].Channel.Pin);
			}
			else if((ConfigPtr[i].Attach) == OPEN_DRAIN)
			{
				SET_BIT(GPIO_BASE(ConfigPtr[i].Channel.Port)->ODR,ConfigPtr[i].Channel.Pin);
				//SET_BIT(PORTODR(ConfigPtr[i].Channel.Port),ConfigPtr[i].Channel.Pin);
			}
			/* Enable Port */
			SET_BIT(GPIO_BASE(ConfigPtr[i].Channel.Port)->DEN,ConfigPtr[i].Channel.Pin);
			//SET_BIT(PORTDEN(ConfigPtr[i].Channel.Port),ConfigPtr[i].Channel.Pin);
		}	
}

/**********************************************************************************************************************
 *  END OF FILE: Port.c
 *********************************************************************************************************************/
