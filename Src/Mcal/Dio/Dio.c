/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Dio.c
 *        \brief  INPUT OUTPUT Driver
 *		\details: no configuration is needed for this driver as it is used to read and write from and to Dio oin
 *        
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Macros.h"
#include "Dio.h"
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
* \Syntax          : Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)                                      
* \Description     : Returns the value of the specified DIO channel.                                
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : ChannelId ID of DIO channel                     
* \Parameters (out): None                                                      
* \Return value:   : Dio_LevelType STD_HIGH The physical level of the corresponding 
											Pin is STD_HIGH 
										STD_LOW The physical level of the corresponding Pin is STD_LOW
*******************************************************************************/
Dio_LevelType Dio_ReadChannel(Port_ChannelType ChannelId){
	return  (Dio_LevelType)PORTDATA(ChannelId.Port+ChannelId.Pin); //GET_BIT(PortDATA(ChannelId.Port),ChannelId.Pin);
}
/******************************************************************************
* \Syntax          : void Dio_WriteChannel(Dio_ChannelType ChannelId,Dio_LevelType Level)                                     
* \Description     : Service to set a level of a channel.                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : ChannelId  ID of DIO channel   
*									 : Level      Value to be written
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Dio_WriteChannel(Port_ChannelType ChannelId,Dio_LevelType Level){
	ASSIGN_BIT(PORTDATA(ChannelId.Port),ChannelId.Pin,Level);
}
/******************************************************************************
* \Syntax          : void Port_Init(const Port_ConfigType*ConfigPtr)                                      
* \Description     : Returns the level of all channels of that port.                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : PortId  ID of DIO Port                    
* \Parameters (out): None                                                      
* \Return value:   : Dio_PortLevelType Level of all channels of that port
*******************************************************************************/
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId){
	return (Dio_PortLevelType)PORTDATA(PortId);
}
/******************************************************************************
* \Syntax          : void Port_Init(const Port_ConfigType*ConfigPtr)                                      
* \Description     : Service to set a value of the port.
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : PortId  ID of DIO Port
*									 : Level   Value to be written
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Dio_WritePort(Dio_PortType PortId,Dio_PortLevelType Level){
	PORTDATA(PortId) = Level;
}
/******************************************************************************
* \Syntax          : void Port_Init(const Port_ConfigType*ConfigPtr)                                      
* \Description     : Service to flip (change from 1 to 0 or from 0 to 1) the level 
*											of a channel and return the level of the channel after flip.                                  
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : ChannelId  ID of DIO channel                    
* \Parameters (out): None                                                      
* \Return value:   : Dio_LevelType STD_HIGH The physical level of the corresponding 
											Pin is STD_HIGH 
										STD_LOW The physical level of the corresponding Pin is STD_LOW
*******************************************************************************/
Dio_LevelType Dio_FlipChannel(Port_ChannelType ChannelId){
  Toggle_BIT(PORTDATA(ChannelId.Port),ChannelId.Pin);
	return GET_BIT(PORTDATA(ChannelId.Port),ChannelId.Pin);
}
