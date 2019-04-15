/*
===============================================================================
 Name        : led.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif
#define Red_Led_GPIO_PORT_NUM                   0
#define Red_Led_GPIO_BIT_NUM                   22
#define Blue_Led_GPIO_PORT_NUM                  3
#define Blue_Led_GPIO_BIT_NUM                  26
#define Green_Led_GPIO_PORT_NUM                 3
#define Green_Led_GPIO_BIT_NUM                  25
#include <cr_section_macros.h>

void Delay_time();
int main(void)
{
#if defined (__USE_LPCOPEN)
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
   Board_Init();

#endif
#endif
    while(1)
    {
    	Chip_GPIO_WriteDirBit(LPC_GPIO, Red_Led_GPIO_PORT_NUM, Red_Led_GPIO_BIT_NUM,true);
    	Chip_GPIO_WriteDirBit(LPC_GPIO, Blue_Led_GPIO_PORT_NUM, Blue_Led_GPIO_BIT_NUM, true);
    	Chip_GPIO_WriteDirBit(LPC_GPIO, Green_Led_GPIO_PORT_NUM, Green_Led_GPIO_BIT_NUM, true);
    	Delay_time();
    	Chip_GPIO_WriteDirBit(LPC_GPIO, Red_Led_GPIO_PORT_NUM, Red_Led_GPIO_BIT_NUM, false);
    	Chip_GPIO_WriteDirBit(LPC_GPIO, Blue_Led_GPIO_PORT_NUM, Blue_Led_GPIO_BIT_NUM, false);
    	Delay_time();
    	Chip_GPIO_WriteDirBit(LPC_GPIO, Green_Led_GPIO_PORT_NUM, Green_Led_GPIO_BIT_NUM,false);
    	Chip_GPIO_WriteDirBit(LPC_GPIO, Red_Led_GPIO_PORT_NUM, Red_Led_GPIO_BIT_NUM,true);
    	Delay_time();
    	Chip_GPIO_WriteDirBit(LPC_GPIO, Red_Led_GPIO_PORT_NUM, Red_Led_GPIO_BIT_NUM,false);
    	Chip_GPIO_WriteDirBit(LPC_GPIO, Blue_Led_GPIO_PORT_NUM, Blue_Led_GPIO_BIT_NUM, true);
    	Delay_time();
    	Chip_GPIO_WriteDirBit(LPC_GPIO, Blue_Led_GPIO_PORT_NUM, Blue_Led_GPIO_BIT_NUM, false);
    }

    return 0 ;
}
void Delay_time()
   {
   	int i;
   	for(i=0;i<=4500000;i++);
   }
