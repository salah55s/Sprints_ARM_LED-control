/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Platform_Types.h
 *       Module:  -
 *
 *  Description:  Contains types that dependent on platform - CortexM4     
 *  
 *********************************************************************************************************************/
#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define WORD_LENGTH_BITS      32u
#define WORD_LENGTH_BYTES     4u
#define MSB_FIRST             0u    /* big endian bit ordering */
#define LSB_FIRST        1u    /* little endian bit ordering */

#define HIGH_BYTE_FIRST  0u    /* big endian byte ordering */
#define LOW_BYTE_FIRST   1u    /* little endian byte ordering */

#ifndef TRUE
   #define TRUE   1u
#endif

#ifndef FALSE
   #define FALSE  0u
#endif

#define ENABLE    1u
#define DISABLE   0u

#define CPU_BIT_ORDER    LSB_FIRST        /*little endian bit ordering*/
#define CPU_BYTE_ORDER   LOW_BYTE_FIRST   /*little endian byte ordering*/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef unsigned char         boolean;       /*        TRUE .. FALSE           */

typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;

    /* exact-width unsigned integer types */
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;

typedef float                 float32;
typedef double                float64;

#ifdef PLATFORM_SUPPORT_SINT64_UINT64 /*Valid only for gnu and C99 */
typedef signed    long long  sint64;   /* -9223372036854775808 .. 9223372036854775807      */
typedef unsigned  long long  uint64;   /*                    0 .. 18446744073709551615     */
#endif

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

 
#endif  /* PLATFORM_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
