#include "../inc/play.h"
#include "../inc/properties.h"
#include "../inc/Util.h"
#include "../inc/Action.h"
#include "../inc/PropertyAction.h"
#include "../inc/rn4020.h"
#include <stdio.h>

void getPropertyAction(int position){
	Property* property = Util::properties[position];

	if(property->owned){
		if(!property->mortgaged){
			if(Util::current_player->money > property->getCurrentRent()){
				property->owner->money += property->getCurrentRent();
				Util::current_player->money -= property->getCurrentRent();
				uint8_t buffer[50] = {0};
				sprintf((char *) buffer, "{\"action\": \"update\", \"player\": %d, \"money\": -%d}\r\n", Util::current_player->number, property->getCurrentRent());
				HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);
				sprintf((char *) buffer, "{\"action\": \"update\", \"player\": %d, \"money\": %d}\r\n", property->owner->number, property->getCurrentRent());
				HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);
//				end_action = true;
			}
			else{
				uint8_t buffer[] = "{\"action\": \"dialog\", \"options\": [\"Mortgage\", \"Declare Bankruptcy\"], \"text\": \"You don't have enough funds.\"}\n";
				HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);
//				action_stack[action_stack_pointer] = this;
//				action_stack_pointer++;
				//set next action array to [MortgageAction, BankruptcyAction] (maybe initialize them too)
				//push those actions to the stack and then pop them off based on something...
//				end_action = false;
			}
		}
		else{
			uint8_t buffer[] = "{\"action\": \"dialog\", \"options\": [], \"text\": \"The property is mortgaged!\"}\n";
			HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);
//			end_action = true;
		}
	}
	else{
		uint8_t buffer[] = "{\"action\": \"dialog\", \"options\": [\"Buy\", \"Auction\"], \"text\": \"This property is unowned.\"}\r\n";
		HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);
//		action_stack[action_stack_pointer] = this;
//		action_stack_pointer++;
		//set next action array to [BuyAction, AuctionAction] (maybe initialize them too)
		//push those actions to the stack and then pop them off based on something...
//		end_action = false;
	}
}

void getBuyAction(int position){
	Property* property = Util::properties[position];

	if(Util::current_player->money <= property->cost){
		uint8_t buffer[] = "{\"action\": \"dialog\", \"options\": [\"Mortgage\", \"Pass\"], \"text\": \"You don't have enough funds.\"}\r\n";
		HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);
	}
	else{
		Util::current_player->money -= property->cost;
		property->owner = Util::current_player;
		property->owned = true;
		uint8_t buffer[] = "{\"action\": \"dialog\", \"options\": [], \"text\": \"Player X has bought the property!\"}\r\n";
		buffer[52] = Util::current_player_index + 49;
//		sprintf((char *) buffer, "{\"action\": \"dialog\", \"options\": [], \"text\": \"Player %d has bought property %d.\"}\r\n", Util::current_player_index+1, property->position);
		HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);
	}
}

void getTradeAction(int trade_state){
	if(trade_state == 1){
		//dynamically add player numbers to options
		uint8_t buffer[] = "{\"action\": \"dialog\", \"options\": [], \"text\": \"Who do you want to trade with?\"}\r\n";
		HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);
	}
}

void getNewAction(int position_index){
	int position_type = Util::properties[position_index]->type;
	if (position_type == 0){
		getPropertyAction(position_index);
	}
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

bool compareCodes(char * buffer1, char * buffer2){
	if(buffer1[0] == buffer2[0] && buffer1[1] == buffer2[1] && buffer1[2] == buffer2[2]) return true;
	return false;
}

void goToNextPlayer(int die1, int die2){
	//check for doubles
	if(die1 != die2){
		Util::current_player_index++;
		if(Util::current_player_index >= Util::max_players){
			Util::current_player_index = 0;
		}

		Util::current_player = Util::players[Util::current_player_index];
	}
}

void play(){
//	int move_successful;

	init_properties();

	uint8_t sbuffer[] = "Dice Roll: X\r\n";
	uint8_t start_message[] = "Game starting!\r\n\n";
	uint8_t player_start[] = "Player X's turn.\r\n";
	uint8_t main_phase[] = "{\"action\": \"dialog\", \"options\": [\"Trade\", \"End Turn\"], \"text\": \"What do you want to do?\"}\r\n";
	uint8_t rbuffer[3];
	uint8_t die1_roll = 0;

	HAL_UART_Transmit(&Util::raspi_handle, start_message, sizeof(start_message), HAL_MAX_DELAY);

	for(;;){
		player_start[7] = (uint8_t) (Util::current_player_index + 49);
		HAL_UART_Transmit(&Util::raspi_handle, player_start, sizeof(player_start), HAL_MAX_DELAY);
		die1_roll = get_die1_roll();
		sbuffer[11] = die1_roll;
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
		HAL_UART_Transmit(&Util::raspi_handle, sbuffer, sizeof(sbuffer), HAL_MAX_DELAY);
		HAL_Delay(50);
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);

		movePlayer(Util::current_player, ((int) die1_roll) - 48);

		getNewAction(Util::current_player->position);
		HAL_UART_Receive(&Util::raspi_handle, rbuffer, sizeof(rbuffer), HAL_MAX_DELAY);

		while(!compareCodes((char *) rbuffer, "END")){
			if(compareCodes((char *) rbuffer, "BUY")){
				getBuyAction(Util::current_player->position);
			}
			HAL_UART_Receive(&Util::raspi_handle, rbuffer, sizeof(rbuffer), HAL_MAX_DELAY);
			HAL_Delay(100);
		}

		HAL_UART_Transmit(&Util::raspi_handle, main_phase, sizeof(main_phase), HAL_MAX_DELAY);
		HAL_UART_Receive(&Util::raspi_handle, rbuffer, sizeof(rbuffer), HAL_MAX_DELAY);

		while(!compareCodes((char *) rbuffer, "END")){
			if(compareCodes((char *) rbuffer, "TR1")){
				getTradeAction(1);
			}
			HAL_UART_Receive(&Util::raspi_handle, rbuffer, sizeof(rbuffer), HAL_MAX_DELAY);
			HAL_Delay(100);
		}
		goToNextPlayer(die1_roll, 0); //supposed to be die2_roll instead of 0
	}
}
