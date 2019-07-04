
/**
 * main.c
 */
#include <stdint.h>
#include "stdbool.h"
#include "FreeRTOS.h"
#include "task.h"
#include "driverlib/can.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "can1.h"
#include "semphr.h"
#include"User_tasks.h"




SemaphoreHandle_t Key_Semaphore; /* Creating a Semphor */
SemaphoreHandle_t Key_Semaphore2; /* Creating a Semphor */


int main(void)
{



    Key_Semaphore = xSemaphoreCreateCounting(2, 0); /* Creating Semphor For Counting Semaphor */
    Key_Semaphore2 = xSemaphoreCreateBinary(); /* Creating Semphor For Binary Semaphor */
 /*
  * Task 1 Creation For peripherals Initialization
  */
    BaseType_t Returned;
    Returned = xTaskCreate(Preipherals_Init,"Task1", 90, NULL,4,NULL);
    /*
     * Task 2 Creation For CAN Receive  Initialization
     */

    BaseType_t Returned1;
    Returned1 = xTaskCreate(CAN_Read, "Task2", 100,NULL,3, NULL);
    /*
     * Task 3 Creation For Led On  Initialization
     */
    BaseType_t Returned2;
    Returned2 = xTaskCreate(LEDOn, "Task3", 100,  NULL, 2, NULL);
    /*
     * Task 4 Creation For   Initialization
     */
    BaseType_t Returned3;
    Returned3 = xTaskCreate(SEND_key, "Task4", 100, NULL, 1, NULL);
     /*
      * Start Scheduler
      */

    vTaskStartScheduler();
    while (1)
    {

    }
    return 0;
}


