//GLOBALS
Profile* current_player;
int WAITING_FOR_INPUT = 1;

int getDiceRoll(){
	return 0;
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
		//send new_action -> call UART
		while(!new_action->action_complete){
			new_action = getNextAction(new_action->next_action);
			//send new_action -> call UART
		}
	}
}
