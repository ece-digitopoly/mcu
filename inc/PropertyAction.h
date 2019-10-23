/*
 * PropertyAction.h
 *
 *  Created on: Sep 23, 2019
 *      Author: shankak
 */

#ifndef PROPERTYACTION_H_
#define PROPERTYACTION_H_

#include "Action.h"

class PropertyAction: public Action {
public:
	PropertyAction(int);
	virtual ~PropertyAction();
};

#endif /* PROPERTYACTION_H_ */
