/*
 * Util.cpp
 *
 *  Created on: Nov 12, 2019
 *      Author: shankak
 */

#include "Util.h"

Util::Util() {
	// TODO Auto-generated constructor stub

}

Util::~Util() {
	// TODO Auto-generated destructor stub
}

UART_HandleTypeDef Util::rn4020_handle;
UART_HandleTypeDef Util::raspi_handle;
Property* Util::properties[40];
Profile* Util::players[4];
Profile* Util::current_player;
uint8_t Util::rx_buffer[3] = {0};
bool Util::rx_done = false;
int Util::current_player_index = 0;
int Util::max_players = 4;
int Util::rx_buf_index = 0;
bool Util::action_complete = false;