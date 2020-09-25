/*
 * delay.c
 *
 *  Created on: Sep 19, 2020
 *      Author: Arpit Savarkar / arpit.savarkar@colorado.edu
 */
#include "delay.h"


/**
​ * ​ ​ @brief​ ​ Busy Waiting Function upto specified Delay Limit
 *
​ * ​ ​ @param​ ​ delay_time: Delay Time in in Seconds
​ *
​ * ​ ​ @return​ ​ void
​ */
void Delay(volatile unsigned int delay_time) {
	delay_time = delay_time*1000;
	while(delay_time--) {
		;
	}
}


/**
​ * ​ ​ @brief​ ​ Busy Waiting Function , also checks if the capacitive touch sensor provides a
 *           Non Noisy value read every 100 msec
 *
​ * ​ ​ @param​ ​ delay_time: Delay Time in in milliseconds
 * ​ ​ @param​ ​ MSEC100: 100 milliseconds delay absolute value
 *   @param  val : Value from the capacitive sensor
 *   @param  LED_array : Pointer to an LED_Status Register
​ *
​ * ​ ​ @return​ ​ void
​ */
void conditional_Delay(volatile uint32_t delay_time, int MSEC100 , int* val, bool* LED_array) {

	while(delay_time-- != 0) {
		if((delay_time % MSEC100) == 0) {
			*val = CAP_Scan();
			if( (*val > NOISE_LOW) && (*val < NOISE_HIGH) ) {
				helper_COLOR(val, LED_array);
			}
		}
		else {
			;
		}
	}
}
