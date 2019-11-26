#include "../inc/play.h"
#include "../inc/properties.h"
#include "../inc/Util.h"
#include "../inc/Action.h"
#include "../inc/PropertyAction.h"
#include "../inc/rn4020.h"
#include "../inc/raspi.h"
#include "../inc/motors.h"
#include <stdio.h>
#include <stdlib.h>

void getPropertyAction(int position){
	Property* property = Util::properties[position];

	if(property->owned){
		if(!property->mortgaged){
			if(Util::current_player->money > property->getCurrentRent()){
				property->owner->money += property->getCurrentRent();
				Util::current_player->money -= property->getCurrentRent();
				uint8_t buffer[60] = {0};
				sprintf((char *) buffer, "{\"action\": \"update\", \"player\": \"%d\", \"money\": \"%d\"}\r\n", Util::current_player->number - 1, Util::current_player->money);
				HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);
				HAL_Delay (100);
				sprintf((char *) buffer, "{\"action\": \"update\", \"player\": \"%d\", \"money\": \"%d\"}\r\n", property->owner->number - 1, property->owner->money);
				HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);
				HAL_Delay(100);
				Util::action_complete = true;
			}
			else{
				uint8_t buffer[] = "{\"action\": \"dialog\", \"options\": [\"Mortgage\", \"Declare Bankruptcy\"], \"text\": \"You don't have enough funds.\"}\n";
				HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);
			}
		}
		else{
			uint8_t buffer[] = "{\"action\": \"dialog\", \"options\": [], \"text\": \"The property is mortgaged!\"}\n";
			HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);
			Util::action_complete = true;
		}
	}
	else{
		uint8_t buffer[] = "{\"action\": \"dialog\", \"options\": [\"Buy\", \"Ignore\"], \"text\": \"This property is unowned.\"}\r\n";
		HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);
	}
}

void getBuyAction(int position){
	Property* property = Util::properties[position];

	if(Util::current_player->money <= property->cost){
		uint8_t buffer[] = "{\"action\": \"dialog\", \"options\": [\"Mortgage\", \"Ignore\"], \"text\": \"You don't have enough funds.\"}\r\n";
		HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);
	}
	else{
		Util::current_player->money -= property->cost;
		property->owner = Util::current_player;
		property->owned = true;
		uint8_t buffer[105];
        sprintf((char*) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"property\": \"%d\", \"text\": \"Player X has bought the property!\"}\r\n", Util::current_player_index, position);
		HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);
		HAL_Delay (100);
		sprintf((char*) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
		HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);
		Util::action_complete = true;
	}
}

void getTradeAction(int trade_state){
	if(trade_state == 1){
		//dynamically add player numbers to options
		uint8_t buffer[] = "{\"action\": \"dialog\", \"options\": [], \"text\": \"Who do you want to trade with?\"}\r\n";
		HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);
	}
}

int getNearestUtility(){
	if(Util::current_player->position < 12) return 12;
	return 28;
}

int getNearestRailroad(){
	uint8_t buffer[105];
	if(Util::current_player->position < 5) return 5;
	else if(Util::current_player->position < 15) return 15;
	else if(Util::current_player->position < 25) return 25;
	else if(Util::current_player->position >= 35){
		Util::current_player->money += 200;
		sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
		return 5;
	}
	return 35;
}

void movePieceMiddle(int a){
	int new_position = Util::current_player->position + a;
	if (new_position > 39){
		new_position -= 39;
	}

//	int move_successful;
	move_piece(Util::current_player, Util::current_player->position, new_position);
	//Error handling for move

	Util::current_player->position = new_position;
}

void getChanceAction(int ccc_id){
	uint8_t buffer[105];
	int nearest_utility_pos = getNearestUtility();
	int nearest_railroad_pos = getNearestRailroad();
	switch(ccc_id){
	case 0: //Advance to Go.
		movePieceMiddle(0);
		Util::current_player->money += 200;
		sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
		break;
	case 1: //Advance to Illinois Ave. If you pass Go, collect $200.
		if(Util::current_player->position > 24){
			Util::current_player->money += 200;
			sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
		}
		movePieceMiddle(24);
		getPropertyAction(24);
		break;
	case 2: //Advance to St. Charles Place. If you pass Go, collect $200.
		if(Util::current_player->position > 11){
			Util::current_player->money += 200;
			sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
		}
		movePieceMiddle(11);
		getPropertyAction(11);
		break;
	case 3: //Advance token to nearest Utility. If unowned, you may buy it from the Bank.
	    getPropertyAction(nearest_utility_pos);
		break;
	case 4: //Advance token to the nearest Railroad. If Railroad is unowned, you may buy it from the Bank.
		getPropertyAction(nearest_railroad_pos);
	    break;
	case 5: //Bank pays you dividend of $50.
		Util::current_player->money += 50;
		sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
	    break;
	case 6: //Go Back Three Spaces.
		movePieceMiddle(Util::current_player->position - 3);
		getPropertyAction(Util::current_player->position);
	    break;
	case 7: //Go to Jail. Go directly to Jail. Do not pass GO, do not collect $200.
		movePieceMiddle(10);
		//DO JAIL THINGS
	    break;
	case 8: //Make general repairs on all your property: For each house pay $25, For each hotel  $100.
	    break;
	case 9: //Get dividends of $15.
		Util::current_player->money += 15;
		sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
	    break;
	case 10: //Take a trip to Reading Railroad.  If you pass Go, collect $200.
		if(Util::current_player->position > 5){
			Util::current_player->money += 200;
			sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
		}
		movePieceMiddle(5);
		getPropertyAction(5);
	    break;
	case 11: //Take a walk on the Boardwalk. Advance token to Boardwalk.
		movePieceMiddle(39);
		getPropertyAction(39);
	    break;
	case 12: //You have been elected Chairman of the Board. Get bonus of $50.
		Util::current_player->money += 50;
		sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
		break;
	case 13: //Your building loan matures. Receive $150.
		Util::current_player->money += 150;
		sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
	    break;
	case 14: //You have won a crossword competition. Collect $100
		Util::current_player->money += 100;
		sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
	    break;
	}
	Util::action_complete = true;
}

void getCCAction(int ccc_id){
	uint8_t buffer[105];
	int nearest_utility_pos = getNearestUtility();
	int nearest_railroad_pos = getNearestRailroad();
	switch(ccc_id){
	case 0: //Advance to Go.
		movePieceMiddle(0);
		Util::current_player->money += 200;
		sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
		break;
	case 1: //Bank error in your favor. Collect $200.
		Util::current_player->money += 200;
		sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
		break;
	case 2: //No Doctor's fees. Get $50.
		Util::current_player->money += 50;
		sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
		break;break;
	case 3: //From sale of stock you get $50.
		Util::current_player->money += 50;
		sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
		break;
	case 4: //Go to Jail. Go directly to jail. Do not pass Go, Do not collect $200.
		movePieceMiddle(10);
		//DO JAIL THINGS
	    break;
	case 5: //Grand Opera Night. Collect $50 for opening night seats.
		Util::current_player->money += 50;
		sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
	    break;
	case 6: //Holiday Fund matures. Receive $100.
		Util::current_player->money += 100;
		sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
	    break;
	case 7: //Income tax refund. Collect $20.
		Util::current_player->money += 20;
		sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
	    break;
	case 8: //It is your birthday. Collect $10
		Util::current_player->money += 10;
		sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
	    break;
	case 9: //Life insurance matures – Collect $100
		Util::current_player->money += 100;
		sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
	    break;
	case 10: //No Hospital Fees. Get $50.
		Util::current_player->money += 50;
		sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
	    break;
	case 11: //No School fees. Get $50.
		Util::current_player->money += 50;
		sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
	    break;
	case 12: //Receive $25 consultancy fee.
		Util::current_player->money += 25;
		sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
	    break;
	case 13: //You have won second prize in a beauty contest. Collect $10.
		Util::current_player->money += 10;
		sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
	    break;
	case 14: //You inherit $100
		Util::current_player->money += 100;
		sprintf((char *) buffer, "{\"action\": \"update\", \"player\":\"%d\", \"money\": \"%d\"}\r\n", Util::current_player_index, Util::current_player->money);
	    break;
	}
	Util::action_complete = true;
}
void getNewAction(int position_index, int ccc_id){
	int position_type = Util::properties[position_index]->type;
	switch(position_type){
	case 0: //Property
	case 1: //Railroad
	case 2: //Utility
		getPropertyAction(position_index);
		break;
	case 3: //Chance
		getChanceAction(ccc_id);
		break;
	case 4: //Community Chest
		getCCAction(ccc_id);
		break;

	}
}

int moveMotors(int old_position, int new_position){
	return 1;
}

void movePlayer(Profile* player, int dice_roll, int ccc_id){
	int new_position = player->position + dice_roll;
	if (new_position > 39){
		new_position -= 39;
		uint8_t sbuffer[80] = {0};
		Util::current_player->money += 200;
		sprintf((char *) sbuffer, "{\"action\": \"update\", \"player\": \"%d\", \"money\": \"%d\"}\r\n", Util::current_player->number - 1, Util::current_player->money);
		HAL_UART_Transmit(&Util::raspi_handle, sbuffer, sizeof(sbuffer), HAL_MAX_DELAY);
	}

	uint8_t sbuffer[70] = {0};
	sprintf((char *) sbuffer, "{\"action\": \"diceroll\", \"roll\": %d, \"position\": %d, \"ccc_id\": %d}", dice_roll, new_position, ccc_id);
	HAL_UART_Transmit(&Util::raspi_handle, sbuffer, sizeof(sbuffer), HAL_MAX_DELAY);
	HAL_Delay(1000);

//	int move_successful;
	move_piece(player, player->position, new_position);
	//Error handling for move

	player->position = new_position;
}

bool compareCodes(char * buffer1, char * buffer2){
	bool eval = buffer1[0] == buffer2[0] && buffer1[1] == buffer2[1] && buffer1[2] == buffer2[2];
	return eval;
}

void goToNextPlayer(int die1, int die2){
	//check for doubles
	if(die1 != die2){ //Not doing doubles at the moment
		Util::current_player_index++;
		if(Util::current_player_index >= Util::max_players){
			Util::current_player_index = 0;
		}

		Util::current_player = Util::players[Util::current_player_index];
	}
}

void play(){
	init_properties();

	uint8_t main_phase[] = "{\"action\": \"dialog\", \"options\": [\"Trade\", \"Manage Properties\", \"End Turn\"], \"text\": \"What do you want to do?\"}\r\n";
	uint8_t piece_moved[] = "{\"action\": \"piecemoved\"}";
	uint8_t rbuffer[3];
	int dice_roll = 0;

	for (;;){
		while (!Util::rx_done);
		Util::rx_done = false;

		if(compareCodes((char *) Util::rx_buffer, "STR")){
			break;
		}
		HAL_Delay(100);
	}

	for(;;){
		HAL_Delay(1500);
		dice_roll = 0;

		//Send dicerolling and dice_roll actions
		while (dice_roll <= 0 || dice_roll > 12)
			dice_roll = sendDiceRoll();

		int ccc_id = rand() % 15;
		while(ccc_id == 7 || ccc_id == 8){
			ccc_id = rand() % 15;
		}
		//Move player to new spot
		movePlayer(Util::current_player, dice_roll, ccc_id);

		HAL_UART_Transmit(&Util::raspi_handle, piece_moved, sizeof(piece_moved), HAL_MAX_DELAY);
		HAL_Delay (500);

		getNewAction(Util::current_player->position, ccc_id);
		HAL_Delay (500);
		//Send piecemoved action


		while(!Util::action_complete){
			while (!Util::rx_done);
			Util::rx_done = false;

			if (compareCodes((char *) Util::rx_buffer, "BUY")){
				getBuyAction(Util::current_player->position);
			}
			else if (compareCodes((char *) Util::rx_buffer, "IGN")){
				break;
			}
//			HAL_UART_Receive(&Util::raspi_handle, rbuffer, sizeof(rbuffer), HAL_MAX_DELAY);
			HAL_Delay(100);
		}

		HAL_Delay (100);

		HAL_UART_Transmit(&Util::raspi_handle, main_phase, sizeof(main_phase), HAL_MAX_DELAY);
//		HAL_UART_Receive(&Util::raspi_handle, rbuffer, sizeof(rbuffer), HAL_MAX_DELAY);


		Util::action_complete = false;

		while(!Util::action_complete){
			while (!Util::rx_done);
			Util::rx_done = false;
			if(compareCodes((char *) Util::rx_buffer, "EPT")){
				goToNextPlayer(1, 0); //supposed to be die2_roll instead of 0
				uint8_t end_buffer[37];
				sprintf ((char *) end_buffer, "{\"action\": \"endturn\", \"player\": \"%d\"}", Util::current_player_index);
				HAL_UART_Transmit(&Util::raspi_handle, end_buffer, sizeof(end_buffer), HAL_MAX_DELAY);
				break;
			}
			HAL_Delay (100);
		}
	}
}
