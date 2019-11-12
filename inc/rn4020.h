#ifndef RN4020_H_
#define RN4020_H_

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void init_rn4020();
void init_dice();
uint8_t get_die1_roll();

#endif
