/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Port_Types.h
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef Port_Types_H
#define Port_Types_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Dio_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
//#define CONFIGURED_PINS			5 /*< Size of config array */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#define Port_PinType		uint8_t

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum
{
	NORMAL_MODE =0,
	SPECIAL_MODE =1
}Port_PinModeType;
typedef enum
{
	DIRECTION_INPUT =0,
	DIRECTION_OUTPUT =1
}Port_PinDirectionType;
typedef enum
{
	PULL_UP =0,
	PULL_DOWN ,
	OPEN_DRAIN
}PortPinInternalAttach;
typedef enum
{
	R2R,
	R4R,
	R8R
}PortPinOutputCurrent;


typedef struct
{
	Dio_PortType Port;
	Dio_ChannelType Pin;
}Port_ChannelType;
typedef struct
{
	Port_PinModeType Mode;
	Dio_LevelType Value;
	PortPinOutputCurrent Current;
	PortPinInternalAttach Attach;
	Port_PinDirectionType Direction;
	Port_ChannelType Channel;
}Port_ConfigType;
 

#endif  /* Port_Types_H */

/**********************************************************************************************************************
 *  END OF FILE: Port_Types.h
 *********************************************************************************************************************/
