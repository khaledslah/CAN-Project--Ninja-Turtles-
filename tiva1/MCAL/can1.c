/*
 * can.c
 *
 *  Created on: Jul 3, 2019
 *      Author: AVE-LAP-44
 */

#include "can1.h"

void CAN_init1(void)
{
    /* Enable the GPIOB peripheral*/

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);


    /*   Wait for the GPIOB module to be ready.
    */
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
    {
    }
    GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    /*
      Enable CAN0 functionality on GPIO Port B pins 5 and 4
    */
    GPIOPinConfigure(GPIO_PB4_CAN0RX);
    GPIOPinConfigure(GPIO_PB5_CAN0TX);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_CAN0))
    {
    }

    CANInit(CAN0_BASE); /* Call CAN0 Initializaion Function */
    CANBitRateSet(CAN0_BASE,SysCtlClockGet(),1000000);
    CANEnable(CAN0_BASE);
}

uint8_t CAN_recieve (uint8_t bufferno)
{
    uint32_t CAN_status=0;
    uint8_t data=0;
    tCANMsgObject OBJ1 = { 0x400, 0x7F8, MSG_OBJ_USE_ID_FILTER, bufferno, &data };

    CANMessageSet(CAN0_BASE, 1, &OBJ1, MSG_OBJ_TYPE_RX);
    while(!(CAN_status & CAN_STATUS_RXOK))
                  CAN_status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
    CANMessageGet(CAN0_BASE, 1, &OBJ1, true);
    return data;
}

void CAN_SEND (uint8_t data_put)
{
    tCANMsgObject sMsgObjectTx;
        uint8_t pui8BufferOut = data_put;


        /*
         Configure and start transmit of message object.
         */
        sMsgObjectTx.ui32MsgID = 0x400;
        sMsgObjectTx.ui32Flags = 0;
        sMsgObjectTx.ui32MsgLen = 1;
        sMsgObjectTx.pui8MsgData = &pui8BufferOut;




             CANMessageSet(CAN0_BASE, 1, &sMsgObjectTx, MSG_OBJ_TYPE_TX);



}
