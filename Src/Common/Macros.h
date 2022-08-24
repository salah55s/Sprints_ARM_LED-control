#ifndef MACROS_H_INCLUDED
#define MACROS_H_INCLUDED

#define SET_BIT(reg,n)      reg |= ((uint32_t)1 <<n)
#define CLEAR_BIT(reg,n) reg &= (~((uint32_t)1 <<n ))
#define Toggle_BIT(reg,n) reg^=((uint32_t) 1 << n)
#define GET_BIT(reg,n)    ((reg>>n)&(uint32_t) 1)
#define BIT_IS_CLR(reg,n) !((uint32_t)1&(reg)>>n)
#define ASSIGN_BIT(reg,n,val)     reg ^= ((uint32_t)-val ^ reg) & n

#define SET_H_NIP(reg)    reg|=( 0xF0)  
#define CLR_H_NIP(reg)  reg&=(~0xF0)
#define FLIP_H_NIP(reg) reg^= 0xF0
#define GET_H_NIP(reg)    reg&=( 0xF0)>>4

#define SET_L_NIP(reg)    reg|=( 0x0F)  
#define CLR_L_NIP(reg)  reg&=(~0x0F)
#define FLIP_L_NIP(reg) reg^= 0x0F
#define GET_L_NIP(reg)    reg&=( 0x0F)

#define ASSIGN_L_NIP(reg,value)    reg=(reg&0xF0)|( 0x0F)&(value)
#define ASSIGN_H_NIP(reg,value)    reg=reg&(( 0x0F)|((value)<<(uint32_t)4))

#define MIN(x,y)  ((x)<(y)?(x):(y))
#define MAX(x,y)  ((x)>(y)?(x):(y))

#endif // MACROS_H_INCLUDED

/////////////////////macros/////////////////
