/*
 * User_tasks.c
 *
 *  Created on: Jul 3, 2019
 *      Author: AVE-LAP-44
 */
#include "User_tasks.h"
extern SemaphoreHandle_t Key_Semaphore; /*this semaphore already created in the main */

extern SemaphoreHandle_t Key_Semaphore2; /*this semaphore already created in the main */
void Preipherals_Init(void * pvParameters)
{

    /* Enable Port F */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    /*
     Check if the peripheral access is enabled.
     */
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
        ;

    /*
     Enable the GPIO pin for the LED (PF3).  Set the direction as output, and
     enable the GPIO pin for digital function.
     */
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3); /* Self Test -> Indication That Reciever Work Successfully  */
    /*
     Enable the GPIO pin for the LED (PF3).  Set the direction as output, and
     enable the GPIO pin for digital function.
     */

    /* Call Can Initialization */
    CAN_init1();
/*  Send first time only  */
    CAN_SEND(20);
    /* Suspend */

    vTaskSuspend(NULL);
}

/*
 * it's a Task To Receive From CAN BUS
 */
void CAN_Read(void * pvParameters)
{

    uint8_t recieved = 0; /* it's a variable to Store Received data */
    while (1)
    {
        if ( uxSemaphoreGetCount(Key_Semaphore2) == 0) /* Returns the count of a semaphore */
        {

            recieved = CAN_recieve(1); /* Store the received value*/
            if (recieved == 10)
            {

                xSemaphoreGive(Key_Semaphore); /* To give semaphore to counting semaphore after Receiving a Message On the CAN Bus*/
                xSemaphoreGive(Key_Semaphore2); /* To give semaphore to binary semaphore after Receiving a Message On the CAN Bus*/

                recieved = 0; /* Set it back to zero after giving the semaphore*/
            }
        }
        vTaskDelay(10); /* OS Delay*/
    }
}
/*
 * it's a Task To Turn the Led On
 */
void LEDOn(void * pvParameters)
{

    while (1)
    {

        if ( uxSemaphoreGetCount(Key_Semaphore) == 1) /* Returns the count of a semaphore */
        {

            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3); /* Turn The Led On */
            vTaskDelay(100);         /* OS Delay */
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0); /* Turn The Led OFF */

            xSemaphoreGive(Key_Semaphore); /* After Toggleing The Led give semaphore  */

        }
        vTaskDelay(40); /* OS Delay*/
    }

}
/*
 * it's a Task To Send Token On CAN BUS
 */
void SEND_key(void * pvParameters)
{

    while (1)
    {
        if ( uxSemaphoreGetCount(Key_Semaphore) == 2) /* Returns the count of a semaphore */
        {

            CAN_SEND(20);

            xSemaphoreTake(Key_Semaphore, (TickType_t ) 10); /* To Take semaphore from counting semaphore */
            xSemaphoreTake(Key_Semaphore, (TickType_t ) 10); /* To Take semaphore from counting semaphore */
            xSemaphoreTake(Key_Semaphore2, (TickType_t ) 10); /* To Take semaphore from Binary semaphore */

        }
        vTaskDelay(40); /* OS Delay*/
    }

}

