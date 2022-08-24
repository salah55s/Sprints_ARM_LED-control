/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Dio_Cfg.h
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef Dio_CFG_H
#define Dio_CFG_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Port.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* Number of the configured Dio Channels */
#define DIO_CONFIGURED_CHANNLES              (5U)

/* Channel Index in the array of structures in Dio_PBcfg.c */
#define DioConf_LED1_CHANNEL        PIN1
#define DioConf_LED2_CHANNEL        PIN2
#define DioConf_LED3_CHANNEL        PIN3
#define DioConf_SW1_CHANNEL         PIN4
#define DioConf_SW2_CHANNEL         PIN0

/* DIO Configured Port ID's  */
#define DioConf_LED1_PORT                PORTF
#define DioConf_LED2_PORT                PORTF
#define DioConf_LED3_PORT                PORTF
#define DioConf_SW1_PORT                 PORTF
#define DioConf_SW2_PORT                 PORTF

/* DIO Configured Channel ID's */
//#define DioConf_LED1_CHANNEL_NUM             (Dio_ChannelType)1 /* Pin 1 in PORTF */
//#define DioConf_SW1_CHANNEL_NUM              (Dio_ChannelType)4 /* Pin 4 in PORTF */


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*typedef struct Dio_ConfigType
{
	Port_ConfigType Channels[DIO_CONFIGURED_CHANNLES];
} Dio_ConfigType;
*/
 
#endif  /* Dio_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Dio_Cfg.h
 *********************************************************************************************************************/
