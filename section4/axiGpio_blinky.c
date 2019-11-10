/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "sleep.h"
#include "xgpio.h"

#define REG(address) *(volatile unsigned int*)(address)

#define GPIO_BASE (0x41200000) /* XPAR_AXI_GPIO_0_BASEADDR */
#define GPIO_DATA (GPIO_BASE + 0x0000)
#define GPIO_TRI (GPIO_BASE + 0x0004)


int main()
{
    init_platform();

    print("Hello World\n\r");

//    /************* Register Control *****************/
//    /*Set all of 4 pins (LEDS) as output*/
//    REG(GPIO_TRI) = 0x00;
//
//    while(1){
//    	/* Set all of 4 pins (LEDS) as High */
//    	REG(GPIO_DATA) = 0x0F;
//    	sleep(1);
//    	/* Set all of 4 pins (LEDs) as Low */
//    	REG(GPIO_DATA) = 0x00;
//    	sleep(1);
//    }
//    /************* Register Control *****************/

    /************* API Driver Control *****************/
    XGpio instXGpio;
    XGpio_Initialize(&instXGpio, XPAR_AXI_GPIO_0_DEVICE_ID);

    /* Set all of 4 pins(LEDS) as output */
    XGpio_SetDataDirection(&instXGpio,1,0);

    while(1){
    	/*Set all of 4 pins(LEDs) as High*/
    	XGpio_DiscreteWrite(&instXGpio,1,0x0F);
    	sleep(1);
    	/*Set all of 4 pins(LEDs) as Low*/
    	XGpio_DiscreteWrite(&instXGpio,1,0x00);
    	sleep(1);
    }
    /************* API Driver Control *****************/


    cleanup_platform();
    return 0;
}
