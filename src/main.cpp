/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "../inc/Util.h"
#include "../inc/rn4020.h"
#include "../inc/raspi.h"
#include "../inc/play.h"
			
void Error_Handler(){
	for(;;);
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

void init_gpio(){
	GPIO_InitTypeDef GPIO_InitStruct;

	//Setup UART2
	/*Configure GPIO pins : PA2 PA3 */
	GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	//Setup UART1
	/*Configure GPIO pins : PA9 PA10 */
	GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	//Light LED1
	/*Configure GPIO pin : PB2 */
	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void init_uart(){
	//UART1 = RN4020
	//UART2 = Raspberry Pi

	Util::raspi_handle.Instance	 	 	 = USART2;
	Util::raspi_handle.Init.BaudRate	 = 115200;
	Util::raspi_handle.Init.WordLength 	 = UART_WORDLENGTH_8B;
	Util::raspi_handle.Init.StopBits	 = UART_STOPBITS_1;
	Util::raspi_handle.Init.Parity	     = UART_PARITY_NONE;
	Util::raspi_handle.Init.HwFlowCtl	 = UART_HWCONTROL_NONE;
	Util::raspi_handle.Init.Mode	   	 = UART_MODE_TX_RX;

	if (HAL_UART_Init(&Util::raspi_handle) != HAL_OK)
		asm("bkpt 255");

	Util::rn4020_handle.Instance	 	 = USART1;
	Util::rn4020_handle.Init.BaudRate	 = 115200;
	Util::rn4020_handle.Init.WordLength  = UART_WORDLENGTH_8B;
	Util::rn4020_handle.Init.StopBits	 = UART_STOPBITS_1;
	Util::rn4020_handle.Init.Parity	     = UART_PARITY_NONE;
	Util::rn4020_handle.Init.HwFlowCtl	 = UART_HWCONTROL_NONE;
	Util::rn4020_handle.Init.Mode	   	 = UART_MODE_TX_RX;

	if (HAL_UART_Init(&Util::rn4020_handle) != HAL_OK)
		asm("bkpt 255");
}

void init_players(){
	//initialize players array as well
	Util::max_players = 2;
	for(int i = 0; i < Util::max_players; i++){
		Util::players[i] = new Profile(i + 1);
	}
	Util::current_player = Util::players[0];
}

int main(void)
{
	HAL_Init();

	SystemClock_Config(); //Use internal clock

	__USART1_CLK_ENABLE();
	__USART2_CLK_ENABLE();
	__GPIOA_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();

	init_gpio();
	init_uart();

//	init_dice();
	init_players();

	play();

	uint8_t sbuffer[] = "Dice Roll: X\r\n";
	uint8_t dice_roll = 0;

	for(;;){
		dice_roll = get_die1_roll();
		sbuffer[11] = dice_roll;
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
		HAL_UART_Transmit(&Util::raspi_handle, sbuffer, sizeof(sbuffer), HAL_MAX_DELAY);
		HAL_Delay(50);
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
	}
}
