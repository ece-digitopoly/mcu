/*
 * Util.h
 *
 *  Created on: Nov 12, 2019
 *      Author: shankak
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

class Util {
public:
	Util();
	virtual ~Util();
	static UART_HandleTypeDef rn4020_handle;
	static UART_HandleTypeDef raspi_handle;
};

#endif /* UTIL_H_ */
