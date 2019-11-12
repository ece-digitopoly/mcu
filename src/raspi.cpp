#include "../inc/raspi.h"
#include "../inc/Util.h"

void scrollDown(){
	uint8_t buffer[] = "{\"action\": \"scroll\", \"direction\": \"down\"}\r\n";
	HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);
}

void scrollUp(){
	uint8_t buffer[] = "{\"action\": \"scroll\", \"direction\": \"up\"}\r\n";
	HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);
}
