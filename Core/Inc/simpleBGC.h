/*
 * simpleBGC.h
 *
 *  Created on: Jan 8, 2025
 *      Author: patryk
 */

#ifndef INC_SIMPLEBGC_H_
#define INC_SIMPLEBGC_H_

#include "spi.h"

#define SIMPLEBGC_CS_PORT GPIOA
#define SIMPLEBGC_CS_PIN  GPIO_PIN_15

void SimpleBGC_SendReceive(uint8_t *txData, uint8_t *rxData, uint16_t length);

#endif /* INC_SIMPLEBGC_H_ */
