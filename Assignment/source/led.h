/*
 * led.h
 *
 *  Created on: Sep 19, 2020
 *      Author: root
 */

#ifndef LED_H_
#define LED_H_

#include "delay.h"
#include "MKL25Z4.h"
#include <stdbool.h>
#include <stdint.h>

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
void LED_Init(void);
void LED_Control(unsigned int red, unsigned int green, unsigned int blue);
void LED_Toggle(unsigned int red, unsigned int green, unsigned int blue);
void LED_Startup(uint32_t sec);
void LED_Flash(uint32_t sec);
void LED_TurnOFF(void);
void helper_COLOR(int* val, bool* LED_array);

#endif /* LED_H_ */
