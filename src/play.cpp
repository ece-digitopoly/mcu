#include "Profile.h"
#include "Action.h"
#include "PropertyAction.h"
#include "global_vars.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
//GLOBALS

void movePlayer(Profile* player, int dice_roll);

int getDiceRoll(){
	return 2;
}

int moveMotors(int old_position, int new_position){
	return 1;
}

void movePlayer(Profile* player, int dice_roll){
	int new_position = player->position + dice_roll;
	if (new_position > 39){
		new_position -= 39;
	}

	int move_successful;
	move_successful = moveMotors(player->position, new_position);
	//Error handling for move

	player->position = new_position;
}

Action* getNewAction(int position_index){
	int position_type = PROPERTIES[position_index]->type;
	Action* new_action;
	if (position_type == 0){
		new_action = new PropertyAction(position_index);
	}
	return new_action;
}

void play(){
	int dice_roll, move_successful;
	initProperties();

	while (true){
		dice_roll = getDiceRoll(); //Check case for doubles

		movePlayer(current_player, dice_roll);

		Action *new_action = getNewAction(current_player->position);
		HAL_Delay(1000);

		//send user data to pi
	}
}
