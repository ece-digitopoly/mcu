/*
 * Property.cpp
 *
 *  Created on: Sep 24, 2019
 *      Author: shankak
 */

#include "Property.h"

Property::Property(int position, int type, int cost, int mortgage_bonus, int mortgage_removal_cost, int add_house_cost, int property_rents[6], int property_set) {
	this->position = position;
	this->type = type;
	this->cost = cost;
	this->mortgage_bonus = mortgage_bonus;
	this->mortgage_removal_cost = mortgage_removal_cost;
	this->add_house_cost = add_house_cost;
	this->property_set = property_set;

	for(int i = 0; i < 6; i++){
		this->property_rents[i] = property_rents[i];
	}

	owned = false;
	mortgaged = false;
	num_houses = 0;
	station_rent = 50;
	one_utility_mult = 4;
	two_utility_mult = 10;

	current_rent = 0;
}

Property::Property(int position){
	this->position = position;
	type = -1;
	cost = 0;
	mortgage_bonus = 0;
	mortgage_removal_cost = 0;
	add_house_cost = 0;
	property_rents = {0, 0, 0, 0, 0, 0};
	owned = false;
	mortgaged = false;
	num_houses = 0;
	station_rent = 50;
	one_utility_mult = 4;
	two_utility_mult = 10;
	property_set = -1;
	current_rent = 0;
}
Property::~Property() {
	// TODO Auto-generated destructor stub
}

