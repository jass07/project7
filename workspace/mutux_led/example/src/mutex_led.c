#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/*GPIO pins and bits are define */
#define Red_Led_GPIO_PORT_NUM                   0
#define Red_Led_GPIO_BIT_NUM                   22
#define Blue_Led_GPIO_PORT_NUM                  3
#define Blue_Led_GPIO_BIT_NUM                  26
#define Green_Led_GPIO_PORT_NUM                 3
#define Green_Led_GPIO_BIT_NUM                  25

//Here define Mutex named RGB

xSemaphoreHandle RGB =0 ;

/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();

	/* Initial LED0 state is off */
	Board_LED_Set(0, false);
}

/* RED LED  */

static void red(void *pvParameters)
 {
	while (1)
	{
	 if (xSemaphoreTake(RGB,1000))         //here it will take mutex with time

	 {
		Chip_GPIO_WriteDirBit(LPC_GPIO, Red_Led_GPIO_PORT_NUM, Red_Led_GPIO_BIT_NUM, 1);  //RED LED on
		Chip_GPIO_WriteDirBit(LPC_GPIO, Green_Led_GPIO_PORT_NUM, Green_Led_GPIO_BIT_NUM,0);
		Chip_GPIO_WriteDirBit(LPC_GPIO, Blue_Led_GPIO_PORT_NUM, Blue_Led_GPIO_BIT_NUM,0);
	 }
	  else
	 		{
		      xSemaphoreGive(RGB);       //here it will give back

			}
              vTaskDelay(3000);            //delay of 3 seconds

	}
}



/* GREEN LED */
static void green(void *pvParameters)
{
	while (1)
	{
		if (xSemaphoreTake(RGB ,2000))

		{
			Chip_GPIO_WriteDirBit(LPC_GPIO, Red_Led_GPIO_PORT_NUM, Red_Led_GPIO_BIT_NUM, 0);
			Chip_GPIO_WriteDirBit(LPC_GPIO, Green_Led_GPIO_PORT_NUM, Green_Led_GPIO_BIT_NUM,1);//Green LED on
			Chip_GPIO_WriteDirBit(LPC_GPIO, Blue_Led_GPIO_PORT_NUM, Blue_Led_GPIO_BIT_NUM,0);

		}
		else
				{
			       xSemaphoreGive(RGB);

				}
		         vTaskDelay(3000);
	}
}

/* BLUE LED  */
static void blue(void *pvParameters)
{


	while (1)
	{
		if (xSemaphoreTake(RGB ,1000))

		{
			Chip_GPIO_WriteDirBit(LPC_GPIO, Red_Led_GPIO_PORT_NUM, Red_Led_GPIO_BIT_NUM, 0);
			Chip_GPIO_WriteDirBit(LPC_GPIO, Blue_Led_GPIO_PORT_NUM, Blue_Led_GPIO_BIT_NUM,1);//Blue LED on
			Chip_GPIO_WriteDirBit(LPC_GPIO, Green_Led_GPIO_PORT_NUM, Green_Led_GPIO_BIT_NUM,0);


		}
		else
		{
			xSemaphoreGive(RGB);

		}

		vTaskDelay(3000);
	}
}

int main(void)
{
	prvSetupHardware();

	RGB = xSemaphoreCreateMutex();

	/* LED RED  */
	xTaskCreate(red, (signed char *) "red",
				configMINIMAL_STACK_SIZE, NULL, 3,NULL);

	/* LED BLUE */
	xTaskCreate(blue, (signed char *) "blue",
				configMINIMAL_STACK_SIZE, NULL, 2,NULL);


	/* LED GREEN */
		xTaskCreate(green, (signed char *) "green",
					configMINIMAL_STACK_SIZE, NULL, 1,NULL);

	/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}
