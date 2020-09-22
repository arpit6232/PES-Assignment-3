/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    Blinkenlights.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "led.h"
#include "delay.h"
#include "cap_sensor.h"
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

/* ************************************************************************
 * Definitions
 **************************************************************************/

//#define sec  6000000
#define SEC  5000

static enum {ST_ON, ST_OFF, ST_TSI, ST_DEAD} next_state = ST_ON;
// ---------------------------------------------------------------------

/* ************************************************************************
 * Prototypes
 **************************************************************************/

/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

//#ifdef DEBUG
//    PRINTF("\n\r Debug Mode");
//#endif

    /* Initialize the LED Pins as OUTPUT Pins */
    LED_Init();
    CAP_Init();
    // Initially Clear all the LED Bits on Ports
    LED_Control(0, 0, 0);
    int val = 0;
    // Startup Pattern
    // Set LED RED on for 500 Sec
    LED_Startup(SEC);
    bool LED_Status[3] = {RED_ON, GREEN_ON, BLUE_ON};


    for(int i=0 ; ; i++) {
    	if(i == 4) {
    		i = 0;
    	}
		if( next_state == ST_ON) {
			PRINTF("\n\r State ON");
			LED_Control(LED_Status[0], LED_Status[1] , LED_Status[2]);

			conditional_Delay(delayLoopUp[i], delay100MSECLoopUp[i], &val, LED_Status);
			next_state = ST_OFF;
		}
		if (next_state == ST_OFF) {
			PRINTF("\n\r State OFF");
			LED_Control(0,0,0);
			Delay(SEC/2);
			next_state = ST_ON;
		}
    }

    // End of Main
    return 0 ;
}


void conditional_Delay(volatile uint32_t delay_time, int MSEC100 , int* val, bool* LED_array) {

	while(delay_time-- != 0) {
		if((delay_time % MSEC100) == 0) {
			*val = CAP_Scan();
			if( (*val > 25) && (*val < 60000) ) {
				helper_COLOR(val, LED_array);
			}
		}
		else {
			;
		}
	}
}



