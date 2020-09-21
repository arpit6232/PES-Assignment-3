/*
 * delay.c
 *
 *  Created on: Sep 19, 2020
 *      Author: root
 */
#include "MKL25Z4.h"

void Delay(volatile uint32_t delay_time) {
	while(delay_time--) {
		;
	}
}

void new_Delay(unsigned int delay_time) {
	delay_time = delay_time*1000;
	while(delay_time--) {
//		while(delay_time--)
		;
	}
}
