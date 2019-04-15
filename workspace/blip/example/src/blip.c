#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define Red_Led_GPIO_PORT_NUM                   0
#define Red_Led_GPIO_BIT_NUM                   22
#define Blue_Led_GPIO_PORT_NUM                  3
#define Blue_Led_GPIO_BIT_NUM                  26
#define Green_Led_GPIO_PORT_NUM                 3
#define Green_Led_GPIO_BIT_NUM                  25



int delay=1000;


xQueueHandle RGB_colour;
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();
	Board_LED_Set(0, false);
}
static void tx(void *pvParameters)

{
	int tx_red =0;
		xQueueSend(RGB_colour, &tx_red ,1);
}


static void rx(void *pvParameters)
{
	int rx_red;



	while(1)
			    {

			    if (xQueueReceive(RGB_colour, &rx_red , 2))
			    {
			    	Chip_GPIO_WriteDirBit(LPC_GPIO, Red_Led_GPIO_PORT_NUM, Red_Led_GPIO_BIT_NUM, 0);
			    	vTaskDelay(delay);
			     	Chip_GPIO_WriteDirBit(LPC_GPIO, Green_Led_GPIO_PORT_NUM, Green_Led_GPIO_BIT_NUM,1);
			     	vTaskDelay(delay);
			    	Chip_GPIO_WriteDirBit(LPC_GPIO, Blue_Led_GPIO_PORT_NUM, Blue_Led_GPIO_BIT_NUM,1);
			    	vTaskDelay(delay);

			    }}

}
int main(void)
{
	prvSetupHardware();

	RGB_colour = xQueueCreate(32,sizeof(int));

	xTaskCreate(tx, (signed char *) "tx",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 2UL),
				(xTaskHandle *) NULL);
	xTaskCreate(rx, (signed char *) "rx",
					configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
					(xTaskHandle *) NULL);
	vTaskStartScheduler();
	/* Should never arrive here */
	return 1;
}
