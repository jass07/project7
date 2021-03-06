#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#define LED0_GPIO_PORT_NUM          0
#define LED0_GPIO_BIT_NUM                  22 //Red Led port
#define LED1_GPIO_PORT_NUM	3
#define LED1_GPIO_BIT_NUM			26 // Blue led port
#define LED2_GPIO_PORT_NUM			 3
#define LED2_GPIO_BIT_NUM				25 //Green led


xQueueHandle LedColour;
static void prvSetupHardware(void)
{
SystemCoreClockUpdate();
Board_Init();

}
static void vSenderTask(void *pvParameters)
{
int Red=0,Blue=1,Green=2,m=0;// r for RED color , b for Blue color, g for Green color
portTickType xCurrenttime,xTime, xt4sec=4000;
while(1){
if(m==0)
{xTime=xTaskGetTickCount();			 //store the initial tick value
m++;
}
xQueueSend(LedColour,&Red,1);
xQueueSend(LedColour,&Blue,1);
xQueueSend(LedColour,&Green,1);
xCurrenttime=xTaskGetTickCount();		// store the current tick value
if(xt4sec==xCurrenttime-xTime)	//checking if time is 4 second
{
vTaskDelay(30000);     // 30sec delay
m=0;
}} }
static void vReceiverTask(void *pvParameters)
{
char j;
while(1){
if(xQueueReceive(LedColour,&j,2))
{
vTaskDelay(2000);     // 2sec delay
if(j == 0){
//red led
Chip_GPIO_WriteDirBit(LPC_GPIO, LED0_GPIO_PORT_NUM, LED0_GPIO_BIT_NUM, true);
Chip_GPIO_WriteDirBit(LPC_GPIO, LED1_GPIO_PORT_NUM, LED1_GPIO_BIT_NUM, false);
 Chip_GPIO_WriteDirBit(LPC_GPIO, LED2_GPIO_PORT_NUM, LED2_GPIO_BIT_NUM, false);



}
else if(j == 1 ){
//Blue led
Chip_GPIO_WriteDirBit(LPC_GPIO, LED0_GPIO_PORT_NUM, LED0_GPIO_BIT_NUM, false);
Chip_GPIO_WriteDirBit(LPC_GPIO, LED1_GPIO_PORT_NUM, LED1_GPIO_BIT_NUM, true);
Chip_GPIO_WriteDirBit(LPC_GPIO, LED2_GPIO_PORT_NUM, LED2_GPIO_BIT_NUM, false);


 }
else if(j == 2 ){
//Green led
Chip_GPIO_WriteDirBit(LPC_GPIO, LED0_GPIO_PORT_NUM, LED0_GPIO_BIT_NUM, false);
Chip_GPIO_WriteDirBit(LPC_GPIO, LED1_GPIO_PORT_NUM, LED1_GPIO_BIT_NUM, false);
Chip_GPIO_WriteDirBit(LPC_GPIO, LED2_GPIO_PORT_NUM, LED2_GPIO_BIT_NUM, true);


 } } }
}
int main(void)
{
prvSetupHardware();
LedColour = xQueueCreate( 64, sizeof(int) );
xTaskCreate(vSenderTask, (signed char *) "vSenderTask",configMINIMAL_STACK_SIZE, NULL, 2,NULL);
xTaskCreate(vReceiverTask, (signed char *) "vReceiverTask",configMINIMAL_STACK_SIZE, NULL, 1,NULL);

/* Start the scheduler */
vTaskStartScheduler();
/* Should never arrive here */
return 1;
}
