/*
 * led.h
 *
 *  Created on: Sep 19, 2020
 *      Author: root
 */

#ifndef LED_H_
#define LED_H_

/* ************************************************************************
 * Definitions
 **************************************************************************/

#define RED_LED_PIN_POS (18)
#define GREEN_LED_PIN_POS (19)
#define BLUE_LED_PIN_POS (1)

#define MASK(x) (1UL << (x))

/* ************************************************************************
 * Prototypes
 **************************************************************************/
void LED_Init(void);
void LED_Control(unsigned int red, unsigned int green, unsigned int blue);
void LED_Toggle(unsigned int red, unsigned int green, unsigned int blue);
void LED_Startup(uint32_t sec);
void LED_Flash(uint32_t sec);
void LED_TurnOFF(void);

#endif /* LED_H_ */
