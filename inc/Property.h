/*
 * Property.h
 *
 *  Created on: Sep 24, 2019
 *      Author: shankak
 *  	Fields: int position
 *  			int type
 *  			int cost
 *  			bool owned
 *  			bool mortgaged
 *  			int num_houses
 *  			int mortgage_bonus
 *  			int mortgage_removal_cost
 *  			int add_house_cost
 *  			int property_rents[6]
 *  			int station_rent = 50
 *  			int one_utility_mult = 4
 *  			int two_utility_mult = 10
 *  			int property_set
 */

#ifndef PROPERTY_H_
#define PROPERTY_H_

#include "Profile.h"

class Property {
public:
	int position;
	int type;
	int cost;
	bool owned;
	bool mortgaged;
	int num_houses;
	int mortgage_bonus;
	int mortgage_removal_cost;
	int add_house_cost;
	int property_rents[6];
	int station_rent;
	int one_utility_mult;
	int two_utility_mult;
	int property_set;
	Profile* owner;

	Property(int, int, int, int, int, int, int property_rents[6], int);
	Property(int position);
	Property(int position, int type);
	virtual ~Property();

	int getCurrentRent();
private:
	int current_rent;
};

#endif /* PROPERTY_H_ */
