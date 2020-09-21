/*
 * led.c
 *
 *  Created on: Sep 19, 2020
 *      Author: Arpit Savarkar (arpit.savarkar@colorado.edu)
 */

#include "MKL25Z4.h"
#include "led.h"
#include "delay.h"


void LED_Init(void) {

//#ifdef DEBUG
//	PRINTF("\n\r Enabling Clock for PortB and PortD");
//#endif
	// Clock Signal is required to Enable Ports
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

	/* Setting the required pins as GPIO Pins */
//#ifdef DEBUG
//	PRINTF("\n\r Setting the Pins to be used as GPIO ");
//#endif
	// Red
	PORTB->PCR[RED_LED_PIN_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_PIN_POS] |= PORT_PCR_MUX(1);

	// Green
	PORTB->PCR[GREEN_LED_PIN_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_PIN_POS] |= PORT_PCR_MUX(1);

	//Blue
	PORTB->PCR[BLUE_LED_PIN_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[BLUE_LED_PIN_POS] |= PORT_PCR_MUX(1);
//#ifdef DEBUG
//	PRINTF("\n\r Setting the Pin direction to OUTPUT");
//#endif
	/* Pin Direction to Set as Output 	*/
	PTB->PDDR |= MASK(RED_LED_PIN_POS) | MASK(GREEN_LED_PIN_POS);
	PTD->PDDR |= MASK(BLUE_LED_PIN_POS);

//#ifdef DEBUG
//	PRINTF("\n\r LED Initialization Successful");
//#endif
	// THe Above Pins can be used ot store Outputs
}


void LED_Control(unsigned int red, unsigned int green, unsigned int blue) {

//#ifdef DEBUG
//	PRINTF("\n\r In Control Function");
//#endif

	// BLue
	if(blue){
//#ifdef DEBUG
//	PRINTF("\n\r LED Blue OFF");
//#endif
		PTD->PCOR = MASK(BLUE_LED_PIN_POS);
	}
	else {
//#ifdef DEBUG
//	PRINTF("\n\r LED Blue ON");
//#endif
		PTD->PSOR = MASK(BLUE_LED_PIN_POS);
	}

	// Red
	if(red){
//#ifdef DEBUG
//	PRINTF("\n\r LED RED OFF");
//#endif
		PTB->PCOR = MASK(RED_LED_PIN_POS);
	}
	else {
//#ifdef DEBUG
//	PRINTF("\n\r LED RED ON");
//#endif
		PTB->PSOR = MASK(RED_LED_PIN_POS);
	}

	// Green
	if(green){
//#ifdef DEBUG
//	PRINTF("\n\r LED GREEN ON");
//#endif
		PTB->PCOR = MASK(GREEN_LED_PIN_POS);
	}
	else {
//#ifdef DEBUG
//	PRINTF("\n\r LED GREEN OFF");
//#endif
		PTB->PSOR = MASK(GREEN_LED_PIN_POS);
	}

}

void LED_TurnOFF(void) {
	PTD->PDDR &= ~ MASK(BLUE_LED_PIN_POS);
	PTB->PDDR &= ~ MASK(RED_LED_PIN_POS);
	PTB->PDDR &= ~ MASK(GREEN_LED_PIN_POS);
}

void LED_Startup(uint32_t sec) {
	// Red n for 500 msec

	LED_Control(1,0,0);
//#ifdef DEBUG
//	PRINTF("\n\r LED RED ON for 500 msec");
//#endif
	new_Delay(sec/2);

	// All off for 100 msec
	LED_Control(0,0,0);
//#ifdef DEBUG
//	PRINTF("\n\r LED OFF for 100 msec");
//#endif
	new_Delay(sec/10);

	// Green for 500 msec
	LED_Control(0,1,0);
//#ifdef DEBUG
//	PRINTF("\n\r LED GREEN ON for 500 msec");
//#endif
	new_Delay(sec/2);

	// All off for 100 msec
	LED_Control(0,0,0);
//#ifdef DEBUG
//	PRINTF("\n\r LED OFF for 100 msec");
//#endif
	new_Delay(sec/10);

	// Blue for 500 msec
	LED_Control(0,0,1);
//#ifdef DEBUG
//	PRINTF("\n\r LED BLUE ON for 500 msec");
//#endif
	new_Delay(sec/2);

	// All off for 100 msec
	LED_Control(0,0,0);
//#ifdef DEBUG
//	PRINTF("\n\r LED OFF for 100 msec");
//#endif
	new_Delay(sec/10);

	// White for 100 msec
	LED_Control(1,1,1);
//#ifdef DEBUG
//	PRINTF("\n\r LED WHITE for 100 msec");
//#endif
	new_Delay(sec/10);

	// All off for 100 msec
	LED_Control(0,0,0);
//#ifdef DEBUG
//	PRINTF("\n\r LED OFF for 100 msec");
//#endif
	new_Delay(sec/10);

	// White for 100 msec
	LED_Control(1,1,1);
//#ifdef DEBUG
//	PRINTF("\n\r LED WHITE for 100 msec");
//#endif
	new_Delay(sec/10);

	// All off for 100 msec
	LED_Control(0,0,0);
//#ifdef DEBUG
//	PRINTF("\n\r LED OFF for 100 msec");
//#endif
	new_Delay(sec/10);

}

//void LED_Flash(uint32_t sec) {
//
//	// All ON for 500 msec
//	LED_Control(1,1,1);
//	Delay(sec/2);
//
//	// All off for 500 msec
//	LED_Control(0,0,0);
//	Delay(sec/2);
//
//	// ALL for 1000 msec
//	LED_Control(1,1,1);
//	Delay(sec);
//
//	// All off for 500 msec
//	LED_Control(0,0,0);
//	Delay(sec/2);
//
//	// ALL for 2000 msec
//	LED_Control(1,1,1);
//	Delay(2*sec);
//
//	// All off for 500 msec
//	LED_Control(0,0,0);
//	Delay(sec/2);
//
//	// ALL for 3000 msec
//	LED_Control(1,1,1);
//	Delay(3*sec);
//
//	// All off for 500 msec
//	LED_Control(0,0,0);
//	Delay(sec/2);
//}}

