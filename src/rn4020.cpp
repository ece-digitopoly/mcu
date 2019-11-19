#include "../inc/rn4020.h"
#include "../inc/Util.h"

void init_rn4020(){
	//Set mode as central
	//	unsigned char buffer1[] = "SR,80000000";
	//	buffer1[11] = '\r';
	//	HAL_UART_Transmit(&s_UART1Handle, buffer1, sizeof(buffer1), HAL_MAX_DELAY);
	////	HAL_Delay(1000);
	//	HAL_UART_Receive(&s_UART1Handle, rbuffer, sizeof(rbuffer), HAL_MAX_DELAY);
	//	HAL_Delay(1000);

		//Reboot
	//	uint8_t buffer2[] = "R,1";
	//
	//	HAL_UART_Transmit(&s_UART1Handle, buffer2, sizeof(buffer2), HAL_MAX_DELAY);
	HAL_Delay(5000);
}

void init_dice(){
	//Connect to Die 1
	uint8_t sbuffer[] = "E,1,DE1030E87B1D";
	sbuffer[16] = '\r';

	uint8_t rbuffer[3];
	uint8_t status[] = "Connecting to Die 1\r\n";
	uint8_t connected[] = "Connected to Die 1!\r\n";

	do{
		HAL_UART_Transmit(&Util::raspi_handle, status, sizeof(status), HAL_MAX_DELAY);
		HAL_UART_Transmit(&Util::rn4020_handle, sbuffer, sizeof(sbuffer), HAL_MAX_DELAY);
		HAL_UART_Receive(&Util::rn4020_handle, rbuffer, sizeof(rbuffer), HAL_MAX_DELAY);
		HAL_Delay(1000);
	} while(rbuffer[0] == 'E'); //look for not aok

	HAL_UART_Transmit(&Util::raspi_handle, connected, sizeof(connected), HAL_MAX_DELAY);
}

uint8_t get_die1_roll(){
	HAL_Delay(3000);
	return 49;
	uint8_t sbuffer[] = "CURV,2A19";
	sbuffer[9] = '\r';

	uint8_t obuffer[5];
	//Read value
	HAL_UART_Transmit(&Util::rn4020_handle, sbuffer, sizeof(sbuffer), HAL_MAX_DELAY);
	//Receive value
	HAL_UART_Receive(&Util::rn4020_handle, obuffer, sizeof(obuffer), HAL_MAX_DELAY);
	HAL_Delay(10);

	//Check if err. If so, have a while loop to restart connection.
	//Send a message to Pi that we're restarting connection with die X
	return obuffer[4];

}
