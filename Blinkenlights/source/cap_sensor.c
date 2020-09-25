/*
 * cap_sensor.c
 *
 *  Created on: Sep 19, 2020
 *      Author: Arpit Savarkar / arpit.savarkar@colorado.edu
 *
 *  References:
 *  https://www.digikey.com/eewiki/display/microcontroller/Using+the+Capacitive+Touch+Sensor+on+the+FRDM-KL46Z
 */

#include "MKL25Z4.h"
#include "cap_sensor.h"


/* ************************************************************************
 * Code
 **************************************************************************/

/* ​ ​ @brief​ ​ Initialization of Capacitive Sensor (Clocks Gating etc) */
void CAP_Init(void) {

	// Enable clock for TSI PortB 16 and 17
		SIM->SCGC5 |= SIM_SCGC5_TSI_MASK;

		TSI0->GENCS = TSI_GENCS_OUTRGF_MASK |  // Out of range flag, set to 1 to clear
			TSI_GENCS_MODE(0U) |  // Set at 0 for capacitive sensing.  Other settings are 4 and 8 for threshold detection, and 12 for noise detection
			TSI_GENCS_REFCHRG(0U) | // 0-7 for Reference charge
			TSI_GENCS_DVOLT(0U) | // 0-3 sets the Voltage range
			TSI_GENCS_EXTCHRG(0U) | //0-7 for External charge
			TSI_GENCS_PS(0U) | // 0-7 for electrode prescaler
			TSI_GENCS_NSCN(31U) | // 0-31 + 1 for number of scans per electrode
			TSI_GENCS_TSIEN_MASK | // TSI enable bit
			TSI_GENCS_STPE_MASK | // Enables TSI in low power mode
			TSI_GENCS_EOSF_MASK ; // End of scan flag, set to 1 to clear
#ifdef DEBUG
	PRINTF("\n\r Clock Gating and Initialization of Capacitive Sensor Complete ");
#endif
}


/**
​ * ​ ​ @brief​ ​ Helper Function to return back the Value sensed by the capacitive sensor
​ *
 *
​ * ​ ​ @param​ ​ void
​ *
​ * ​ ​ @return​ ​ Scanned Value with OFFSET Subtracted
​ */
uint16_t CAP_Scan(void) {
	uint16_t scan;
//#ifdef DEBUG
//	PRINTF("\n\r Capacitive Touch Scanning with OFFSET %d: ", SCAN_OFFSET);
//#endif
		TSI0->DATA = TSI_DATA_TSICH(9U); // Using channel 9 of the TSI
		TSI0->DATA |= TSI_DATA_SWTS_MASK; // Software trigger for scan
		scan = SCAN_DATA;
		TSI0->GENCS |= TSI_GENCS_EOSF_MASK ; // Reset end of scan flag
		return scan - SCAN_OFFSET;
}
