#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "Profile.h"
#include "Action.h"
#include "Property.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

static UART_HandleTypeDef s_UARTHandle;
static Property* PROPERTIES[40];
static int option_selected;
static int option_upper;
static int option_lower;


static Profile* current_player;

static int WAITING_FOR_INPUT = 1;
static int action_stack_pointer = 0;
static int ACTION_STACK_LIMIT = 5;

static Action* action_stack[5]; //FIX THIS TO USE ACTION_STACK_LIMIT

void initProperties();

#endif /* GLOBAL_H_ */
