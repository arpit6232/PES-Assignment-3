/*
 * led.c
 *
 *  Created on: Sep 19, 2020
 *      Author: Arpit Savarkar (arpit.savarkar@colorado.edu)
 */


#include "led.h"


/**
​ * ​ ​ @brief​ ​ Initializes the GPIO Ports and Clock Gating and Direction of Pins
 *
​ * ​ ​ @param​ ​ void
​ *
​ * ​ ​ @return​ ​ void
​ */
void LED_Init(void) {

#ifdef DEBUG
	PRINTF("\n\r Enabling Clock for PortB and PortD");
#endif
	// Clock Signal is required to Enable Ports
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

	/* Setting the required pins as GPIO Pins */
#ifdef DEBUG
	PRINTF("\n\r Setting the Pins to be used as GPIO ");
#endif
	// Red
	PORTB->PCR[RED_LED_PIN_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_PIN_POS] |= PORT_PCR_MUX(1);

	// Green
	PORTB->PCR[GREEN_LED_PIN_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_PIN_POS] |= PORT_PCR_MUX(1);

	//Blue
	PORTD->PCR[BLUE_LED_PIN_POS] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_PIN_POS] |= PORT_PCR_MUX(1);

#ifdef DEBUG
	PRINTF("\n\r Setting the Pin direction to OUTPUT");
#endif
	/* Pin Direction to Set as Output 	*/
	PTB->PDDR |= MASK(RED_LED_PIN_POS) | MASK(GREEN_LED_PIN_POS);
	PTD->PDDR |= MASK(BLUE_LED_PIN_POS);

#ifdef DEBUG
	PRINTF("\n\r LED Initialization Successful");
#endif
}


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
void LED_Control(unsigned int red, unsigned int green, unsigned int blue) {

#ifdef DEBUG
	PRINTF("\n\r LED CHANGE STATUS LOG ; 1-> Active, 0->Disabled");
	PRINTF("\n\r RED LED : %u", red);
	PRINTF("\n\r GREEN LED : %u", green);
	PRINTF("\n\r BLUE LED : %u", blue);
#endif

	// BLue
	if(blue){
		PTD->PCOR = MASK(BLUE_LED_PIN_POS);
	}
	else {
		PTD->PSOR = MASK(BLUE_LED_PIN_POS);
	}

	// Red
	if(red){
		PTB->PCOR = MASK(RED_LED_PIN_POS);
	}
	else {
		PTB->PSOR = MASK(RED_LED_PIN_POS);
	}

	// Green
	if(green){
		PTB->PCOR = MASK(GREEN_LED_PIN_POS);
	}
	else {
		PTB->PSOR = MASK(GREEN_LED_PIN_POS);
	}

}

//void LED_TurnOFF(void) {
//	PTD->PDDR &= ~ MASK(BLUE_LED_PIN_POS);
//	PTB->PDDR &= ~ MASK(RED_LED_PIN_POS);
//	PTB->PDDR &= ~ MASK(GREEN_LED_PIN_POS);
//}


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
void LED_Startup(uint32_t sec) {
	// Red n for 500 msec

	LED_Control(RED_ON, GREEN_OFF, BLUE_OFF);
#ifdef DEBUG
	PRINTF("\n\r LED RED ON for 500 msec");
#endif
	Delay(sec/2);

	// All off for 100 msec
	LED_Control(RED_OFF, GREEN_OFF, BLUE_OFF);
#ifdef DEBUG
	PRINTF("\n\r ALL LED DISABLED for 100 msec");
#endif
	Delay(sec/10);

	// Green for 500 msec
	LED_Control(RED_OFF, GREEN_ON, BLUE_OFF);
#ifdef DEBUG
	PRINTF("\n\r LED GREEN ON for 500 msec");
#endif
	Delay(sec/2);

	// All off for 100 msec
	LED_Control(RED_OFF, GREEN_OFF, BLUE_OFF);
#ifdef DEBUG
	PRINTF("\n\r ALL LED DISABLED for 100 msec");
#endif
	Delay(sec/10);

	// Blue for 500 msec
	LED_Control(RED_OFF, GREEN_OFF, BLUE_ON);
#ifdef DEBUG
	PRINTF("\n\r LED BLUE ON for 500 msec");
#endif
	Delay(sec/2);

	// All off for 100 msec
	LED_Control(RED_OFF, GREEN_OFF, BLUE_OFF);
#ifdef DEBUG
	PRINTF("\n\r ALL LED DISABLED for 100 msec");
#endif
	Delay(sec/10);

	// White for 100 msec
	LED_Control(RED_ON, GREEN_ON, BLUE_ON);
#ifdef DEBUG
	PRINTF("\n\r LED WHITE for 100 msec");
#endif
	Delay(sec/10);

	// All off for 100 msec
	LED_Control(RED_OFF, GREEN_OFF, BLUE_OFF);
#ifdef DEBUG
	PRINTF("\n\r ALL LED DISABLED for 100 msec");
#endif
	Delay(sec/10);

	// White for 100 msec
	LED_Control(RED_ON, GREEN_ON, BLUE_ON);
#ifdef DEBUG
	PRINTF("\n\r LED WHITE for 100 msec");
#endif
	Delay(sec/10);

	// All off for 100 msec
	LED_Control(RED_OFF, GREEN_OFF, BLUE_OFF);
#ifdef DEBUG
	PRINTF("\n\r ALL LED DISABLED for 100 msec");
#endif
	Delay(sec/10);

}


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
void helper_COLOR(int* val, bool* LED_array) {

#ifdef DEBUG
	PRINTF("\n\r SLIDER VALUE: %u", *val);
#endif

	if(*val<= 20 || *val > 2000) {
		LED_Control(RED_OFF, GREEN_OFF, BLUE_OFF);
		LED_array[0] = LED_array[1] = LED_array[2] = 0;
	}
	else if (*val < 350) {
		LED_Control(RED_ON, 0 , 0);
		LED_array[0] = RED_ON;
		LED_array[1] = LED_array[2] = 0;
	}
	else if(*val < 850) {
		LED_Control(0, GREEN_ON , 0);
		LED_array[1] = GREEN_ON;
		LED_array[0] = LED_array[2] = 0;
	}
	else if(*val >= 850) {
		LED_Control(0, 0, BLUE_ON);
		LED_array[2] = BLUE_ON;
		LED_array[0] = LED_array[1] = 0;
	}
}

