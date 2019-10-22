/*
 * PropertyAction.cpp
 *
 *  Created on: Sep 23, 2019
 *      Author: shankak
 */

#include "PropertyAction.h"

//list of possible next_actions!! Have a global option_selected variable
//Look at that option_selected variable and traverse list

//MAYBE MAINTAIN A STACK OF ACTIONS TO COMPLETE??
//Stack makes sense. It will rerun the previous action after popping off.
//For example, after sending a mortgage action, it will pop that off and rerun the property action to pay off player
//If not enough funds, it will send the same 2 actions (mortgage and bankruptcy) back to user.

PropertyAction::PropertyAction(int position) {
	Property* property = PROPERTIES[position];
	//check details of property
		//if owned
			//if not mortgaged
				//if enough money
					//transfer funds, set action to send dialog that it happened #END OF ACTION
				//if not
					//set action to send dialog with options to mortgage or declare bankruptcy
					//set next action array to [MortgageAction, BankruptcyAction] (maybe initialize them too)
			//if mortgaged
				//set action to send dialog with mortgaged text #END OF ACTION
		//if not
			//set action to send dialog with options to buy given property
			//set next action array to [BuyAction, AuctionAction] (leave out auction for now, just to make life easier)


}

PropertyAction::~PropertyAction() {
	// TODO Auto-generated destructor stub
}

