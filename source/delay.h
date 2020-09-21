/*
 * delay.h
 *
 *  Created on: Sep 19, 2020
 *      Author: Arpit Savarkar (arpit.savarkar@colorado.edu)
 */

#ifndef DELAY_H_
#define DELAY_H_

static const int delayLoopUp[4] =
{
		// 500, 1000, 2000, 3000 mSec
		312500, 625000, 900000, 1200000
};

static const int delay100MSECLoopUp[4] =
{
		// 500, 1000, 2000, 3000 mSec
		62500, 62500, 40000, 333334
};

extern void Delay(volatile uint32_t delay_time);
extern void new_Delay(unsigned int delay_time);
extern void optimized_Delay(volatile uint32_t delay_time);

#endif /* DELAY_H_ */
