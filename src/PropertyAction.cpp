/*
 * PropertyAction.cpp
 *
 *  Created on: Sep 23, 2019
 *      Author: shankak
 */

#include "PropertyAction.h"
#include "global_vars.h"
//list of possible next_actions!! Have a global option_selected variable
//Look at that option_selected variable and traverse list

//MAYBE MAINTAIN A STACK OF ACTIONS TO COMPLETE??
//Stack makes sense. It will rerun the previous action after popping off.
//For example, after sending a mortgage action, it will pop that off and rerun the property action to pay off player
//If not enough funds, it will send the same 2 actions (mortgage and bankruptcy) back to user.

PropertyAction::PropertyAction(int position) {
	Property* property = PROPERTIES[position];

	if(property->owned){
		if(!property->mortgaged){
			if(current_player->money > property->getCurrentRent()){
				property->owner->money += property->getCurrentRent();
				current_player->money -= property->getCurrentRent();
				end_action = true;
			}
			else{
				uint8_t buffer[] = "{\"action\": \"dialog\", \"options\": [\"Mortgage\", \"Declare Bankruptcy\"], \"text\": \"You don't have enough funds.\"}\n";
				HAL_UART_Transmit(&s_UARTHandle, buffer, sizeof(buffer), HAL_MAX_DELAY);
				action_stack[action_stack_pointer] = this;
				action_stack_pointer++;
				//set next action array to [MortgageAction, BankruptcyAction] (maybe initialize them too)
				//push those actions to the stack and then pop them off based on something...
				end_action = false;
			}
		}
		else{
			uint8_t buffer[] = "{\"action\": \"dialog\", \"options\": [], \"text\": \"The property is mortgaged!\"}\n";
			HAL_UART_Transmit(&s_UARTHandle, buffer, sizeof(buffer), HAL_MAX_DELAY);
			end_action = true;
		}
	}
	else{
		uint8_t buffer[] = "{\"action\": \"dialog\", \"options\": [\"Buy\", \"Auction\"], \"text\": \"This property is unowned.\"}\n";
		HAL_UART_Transmit(&s_UARTHandle, buffer, sizeof(buffer), HAL_MAX_DELAY);
		action_stack[action_stack_pointer] = this;
		action_stack_pointer++;
		//set next action array to [BuyAction, AuctionAction] (maybe initialize them too)
		//push those actions to the stack and then pop them off based on something...
		end_action = false;
	}
}

PropertyAction::~PropertyAction() {
	// TODO Auto-generated destructor stub
}

