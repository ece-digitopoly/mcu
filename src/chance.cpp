#include "../inc/chance.h"
#include "../inc/Util.h"

void getChanceAction(int num){
	switch(num){
	case 0:
		uint8_t buffer[] = "{\"action\": \"chance\", \"text\": \"Advance to GO. Collect $200.\"}\r\n";
		HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);
		Util::current_player->money += 200;
	}
}
