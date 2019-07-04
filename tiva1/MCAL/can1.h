/*
 * can_init.h
 *
 *  Created on: Jul 3, 2019
 *      Author: AVE-LAP-44
 */

#ifndef CAN1_H_
#define CAN1_H_
#include <stdint.h>
#include "stdbool.h"
#include "driverlib/can.h"
#include "driverlib/pin_map.h"


#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
void CAN_init1(void);

uint8_t CAN_recieve (uint8_t bufferno);

void CAN_SEND (uint8_t data_put);
#endif /* CAN1_H_ */
