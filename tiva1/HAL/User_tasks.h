/*
 * User_tasks.h
 *
 *  Created on: Jul 3, 2019
 *      Author: AVE-LAP-44
 */

#ifndef USER_TASKS_H_
#define USER_TASKS_H_
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

void Preipherals_Init(void * pvParameters);
void CAN_Read(void * pvParameters);
void LEDOn(void * pvParameters);
void SEND_key(void * pvParameters);
#endif /* USER_TASKS_H_ */
