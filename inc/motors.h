#ifndef MOTORS_H_
#define MOTORS_H_

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "Profile.h"

void init_motors();
void move_piece(Profile* player, int a, int b);
void move_n_steps_x(int n);
void move_n_steps_y(int n);
#endif
