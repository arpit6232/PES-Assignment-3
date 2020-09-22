/*
 * cap_sensor.h
 *
 *  Created on: Sep 19, 2020
 *      Author: root
 */

#ifndef CAP_SENSOR_H_
#define CAP_SENSOR_H_

#include "MKL25Z4.h"
#include <stdint.h>


/* ************************************************************************
 * Macros
 **************************************************************************/
#define SCAN_OFFSET 588  // Offset for scan range
#define SCAN_DATA TSI0->DATA & 0xFFFF // Accessing the bits held in TSI0_DATA_TSICNT

/* ************************************************************************
 * Prototypes
 **************************************************************************/

void CAP_Init(void);
uint16_t CAP_Scan(void);
int32_t CAP_poll(void);
void helper_CAP_Scan(volatile uint16_t val);

#endif /* CAP_SENSOR_H_ */
