/*
 * delay.c
 *
 *  Created on: Sep 19, 2020
 *      Author: root
 */
#include "delay.h"

void Delay(volatile unsigned int delay_time) {
	delay_time = delay_time*1000;
	while(delay_time--) {
		;
	}
}
