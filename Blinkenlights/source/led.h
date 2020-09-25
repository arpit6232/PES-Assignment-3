/*
 * led.h
 *
 *  Created on: Sep 19, 2020
 *      Author: Arpit Savarkar / arpit.savarkar@colorado.edu
 */

#ifndef LED_H_
#define LED_H_

#include "delay.h"
#include "MKL25Z4.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "fsl_debug_console.h"

/* ************************************************************************
 * Definitions
 **************************************************************************/

#define RED_LED_PIN_POS (18)
#define GREEN_LED_PIN_POS (19)
#define BLUE_LED_PIN_POS (1)

#define MASK(x) (1UL << (x))

#define RED_ON 1
#define RED_OFF 0
#define BLUE_ON 1
#define BLUE_OFF 0
#define GREEN_ON 1
#define GREEN_OFF 0
/* ************************************************************************
 * Prototypes
 **************************************************************************/

/**
​ * ​ ​ @brief​ ​ Initializes the GPIO Ports and Clock Gating and Direction of Pins
 *
​ * ​ ​ @param​ ​ void
​ *
​ * ​ ​ @return​ ​ void
​ */
void LED_Init(void);

/**
​ * ​ ​ @brief​ ​ Clears and Sets the bits required for Digital On/Off of LEDs
​ *
​ * ​ ​ PCOR -> Clears Bit for the set Mask Pin (Active Low)
 *   PSOR -> Sets Bit for the set Mask Pin
 *
​ * ​ ​ @param​ ​ red: Boolean 1 to set High, 0 to set Low for Red Led
 * ​ ​ @param​ ​ green: Boolean 1 to set High, 0 to set Low for Green Led
 * ​ ​ @param​ ​ blue: Boolean 1 to set High, 0 to set Low for Blue Led
​ *
​ * ​ ​ @return​ ​ void
​ */
void LED_Control(unsigned int red, unsigned int green, unsigned int blue);

/**
​ * ​ ​ @brief​ ​ Implement Startup Routine
​ *
​ * ​ ​ Implements the following routine
 *    RED for 500 msec, OFF for 100 msec,
 * 	  GREEN for 500 msec, OFF for 100 msec,
 *	  BLUE for 500 msec, OFF for 100 msec
 *	  WHITE (that is, RED, GREEN, and BLUE all on) for 100 msec, OFF for 100 msec
 *    WHITE for 100 msec, OFF for 100 MSEC
 *
​ * ​ ​ @param​ ​ sec : ​ Delay period
​ *
​ * ​ ​ @return​ ​ void
​ */
void LED_Startup(uint32_t sec);


//void LED_Flash(uint32_t sec);
//void LED_TurnOFF(void);

/**
​ * ​ ​ @brief​ ​ Helper Function to Set the LED's based on Input of Helper Function
​ *
​ * ​ ​ Given a value as an input from the Capacitive Sensor it Sets the LED Status array
 *   to the desired config
 *
​ * ​ ​ @param​ ​ val : ​ Value with OFFSET from the capacitive Sensor
 *   @param  LED_array : LED Status Array
​ *
​ * ​ ​ @return​ ​ void
​ */
void helper_COLOR(int* val, bool* LED_array);

#endif /* LED_H_ */
