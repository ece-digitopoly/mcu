/*
 * Profile.h
 *
 *  Created on: Sep 23, 2019
 *      Author: shankak
 */

#ifndef PROFILE_H_
#define PROFILE_H_

class Profile {
public:
	int position;//will also have num utilities and num stations
	int money;
	int number;
	Profile(int);
	virtual ~Profile();
};

#endif /* PROFILE_H_ */
