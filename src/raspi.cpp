#include "../inc/raspi.h"
#include "../inc/Util.h"
#include "../inc/rn4020.h"

void scrollDown(){
	uint8_t buffer[] = "{\"action\": \"scroll\", \"direction\": \"down\"}\r\n";
	HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);
}

void scrollUp(){
	uint8_t buffer[] = "{\"action\": \"scroll\", \"direction\": \"up\"}\r\n";
	HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);
}

int convertCharToInt(char ch){
	return ch - '0';
}

int sendDiceRoll(){
	uint8_t buffer[] = "{\"action\": \"dicerolling\"}";
	uint8_t sbuffer[35] = {0};

	HAL_UART_Transmit(&Util::raspi_handle, buffer, sizeof(buffer), HAL_MAX_DELAY);

	uint8_t die1_roll = get_die1_roll();
	int die1_roll_int = convertCharToInt(die1_roll);

	sprintf((char *) sbuffer, "{\"action\": \"diceroll\", \"roll\": %d}", die1_roll_int);

	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
	HAL_UART_Transmit(&Util::raspi_handle, sbuffer, sizeof(sbuffer), HAL_MAX_DELAY);
	HAL_Delay(50);
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);

	return die1_roll_int;
}
