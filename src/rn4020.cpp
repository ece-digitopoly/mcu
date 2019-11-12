#include "../inc/rn4020.h"
#include "../inc/Util.h"

void init_ble_uart(){
	GPIO_InitTypeDef GPIO_InitStruct;

	//Setup UART2
	/*Configure GPIO pins : PA2 PA3 */
	GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	Util::raspi_handle.Instance	 	 = USART2;
	Util::raspi_handle.Init.BaudRate	 = 115200;
	Util::raspi_handle.Init.WordLength = UART_WORDLENGTH_8B;
	Util::raspi_handle.Init.StopBits	 = UART_STOPBITS_1;
	Util::raspi_handle.Init.Parity	 = UART_PARITY_NONE;
	Util::raspi_handle.Init.HwFlowCtl	 = UART_HWCONTROL_NONE;
	Util::raspi_handle.Init.Mode	   	 = UART_MODE_TX_RX;

	if (HAL_UART_Init(&Util::raspi_handle) != HAL_OK)
		asm("bkpt 255");

	//Setup UART1
	/*Configure GPIO pins : PA9 PA10 */
	GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	Util::rn4020_handle.Instance	 	 = USART1;
	Util::rn4020_handle.Init.BaudRate	 = 115200;
	Util::rn4020_handle.Init.WordLength = UART_WORDLENGTH_8B;
	Util::rn4020_handle.Init.StopBits	 = UART_STOPBITS_1;
	Util::rn4020_handle.Init.Parity	 = UART_PARITY_NONE;
	Util::rn4020_handle.Init.HwFlowCtl	 = UART_HWCONTROL_NONE;
	Util::rn4020_handle.Init.Mode	   	 = UART_MODE_TX_RX;

	if (HAL_UART_Init(&Util::rn4020_handle) != HAL_OK)
		asm("bkpt 255");
}
