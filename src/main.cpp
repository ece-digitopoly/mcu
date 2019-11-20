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
#include "../inc/motors.h"
			
extern "C" {
	void TIM4_IRQHandler (void){
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
		TIM4 -> SR &= ~TIM_SR_CC2IF;
		TIM4 -> SR &= ~TIM_SR_UIF;
	}

	void TIM3_IRQHandler (void){
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_4);
		TIM3 -> SR &= ~TIM_SR_CC1IF;
		TIM3 -> SR &= ~TIM_SR_UIF;
	}
	void EXTI9_5_IRQHandler(void)
	{
		if (!HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_5)) {
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
					scrollUp();
		}
		else if (!HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_6)) {
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
					scrollDown();
				}
		else if (!HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_7)) {
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
			click();
		}
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
	}
}
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

	//Motor 1 is the second pin and motor 2 is the first
	//Motor Enables
	GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	//Motor Steps
	GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	//Motor Dirs
	GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	//Electromagnet Transistor
	GPIO_InitStruct.Pin = GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

//	 TESTING FUNCTION
	GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

static void tim3_init(void){
	TIM_HandleTypeDef htim3;

	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};

	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 899; // 4 kHz (hwclk/((psc + 1)*(arr + 1)))
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 9;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

	if (HAL_TIM_OC_Init(&htim3) != HAL_OK){
		Error_Handler();
	}
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_OC1REF;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK){
    	Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_OC_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK){
    	Error_Handler();
    }
    if (HAL_TIM_Base_Start_IT(&htim3) != HAL_OK){
    	Error_Handler();
    }
    if (HAL_TIM_OC_Start(&htim3, TIM_CHANNEL_1) != HAL_OK){
    	Error_Handler();
    }

// 	HAL_TIM_MspPostInit(&htim3);

}

static void tim4_init(void){
	TIM_HandleTypeDef htim4;

	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};

	htim4.Instance = TIM4;
	htim4.Init.Prescaler = 899;
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim4.Init.Period = 9;
	htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_OC_Init(&htim4) != HAL_OK){
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_OC2REF;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK){
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_OC_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2) != HAL_OK){
		Error_Handler();
	}
	if (HAL_TIM_Base_Start_IT(&htim4) != HAL_OK){
		Error_Handler();
	}
	if (HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_2) != HAL_OK){
		Error_Handler();
	}
//  HAL_TIM_MspPostInit(&htim4);
}





void init_tim(){
	HAL_NVIC_SetPriority(TIM4_IRQn, 1, 1);
	HAL_NVIC_EnableIRQ(TIM4_IRQn);

	HAL_NVIC_SetPriority(TIM3_IRQn, 1, 1);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);

	tim4_init();
	tim3_init();
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


bool compareCodes2(char * buffer1, char * buffer2){
	if(buffer1[0] == buffer2[0] && buffer1[1] == buffer2[1] && buffer1[2] == buffer2[2]) return true;
	return false;
}

int main(void)
{
	HAL_Init();

	SystemClock_Config(); //Use internal clock

	__USART1_CLK_ENABLE();
	__USART2_CLK_ENABLE();
	__GPIOA_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();
	__GPIOC_CLK_ENABLE();
	__TIM3_CLK_ENABLE();
	__TIM4_CLK_ENABLE();


	init_gpio();
	init_uart();
	init_tim();
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(SysTick_IRQn);

	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 1);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

//	init_dice();
	init_players();
	init_motors();

//	play();

//	move_n_steps_x(1);



//	uint8_t buffer1[] = "{\"action\": \"click\"}";
//	HAL_UART_Transmit(&Util::raspi_handle, buffer1, sizeof(buffer1), HAL_MAX_DELAY);
//	HAL_Delay (3000);
//
//	uint8_t buffer2[] = "{\"action\": \"scroll\", \"direction\": \"down\"}";
//	HAL_UART_Transmit(&Util::raspi_handle, buffer2, sizeof(buffer2), HAL_MAX_DELAY);
//	HAL_Delay (1000);
//	HAL_UART_Transmit(&Util::raspi_handle, buffer2, sizeof(buffer2), HAL_MAX_DELAY);
//	HAL_Delay (1000);
//	HAL_UART_Transmit(&Util::raspi_handle, buffer2, sizeof(buffer2), HAL_MAX_DELAY);
//	HAL_Delay (1000);
//
//	uint8_t buffer3[] = "{\"action\": \"click\"}";
//	HAL_UART_Transmit(&Util::raspi_handle, buffer3, sizeof(buffer3), HAL_MAX_DELAY);
//	HAL_Delay (3000);

	uint8_t rbuffer[3];
	HAL_UART_Receive(&Util::raspi_handle, rbuffer, sizeof(rbuffer), 100);

	while(!compareCodes2((char *) rbuffer, "STR"))
	{
//		if(compareCodes2((char *) rbuffer, "STR")){
//			HAL_Delay (2000);
//			break;
//		}
//		HAL_Delay (500);
		HAL_UART_Receive(&Util::raspi_handle, rbuffer, sizeof(rbuffer), 100);
	}

	uint8_t buffer4[] = "{\"action\": \"dicerolling\"}";
	HAL_UART_Transmit(&Util::raspi_handle, buffer4, sizeof(buffer4), HAL_MAX_DELAY);
	HAL_Delay (2000);

	uint8_t buffer5[] = "{\"action\": \"diceroll\", \"roll\": \"3\"}";
	HAL_UART_Transmit(&Util::raspi_handle, buffer5, sizeof(buffer5), HAL_MAX_DELAY);
	HAL_Delay (2000);

	uint8_t buffer6[] = "{\"action\": \"dialog\", \"options\": [\"Buy\", \"Ignore\"], \"text\": \"This property is unowned.\"}";
	HAL_UART_Transmit(&Util::raspi_handle, buffer6, sizeof(buffer6), HAL_MAX_DELAY);
//	HAL_Delay (2000);

	move_piece(1, 4);

	HAL_Delay (1000);
	uint8_t buffer7[] = "{\"action\": \"piecemoved\"}";
	HAL_UART_Transmit(&Util::raspi_handle, buffer7, sizeof(buffer7), HAL_MAX_DELAY);
	HAL_Delay (500);

//	uint8_t rbuffer[3];
	HAL_UART_Receive(&Util::raspi_handle, rbuffer, sizeof(rbuffer), HAL_MAX_DELAY);


			while(1){
				if(compareCodes2((char *) rbuffer, "BUY")){
					uint8_t buffer8[] = "{\"action\": \"update\", \"property\": \"3\", \"player\": \"0\", \"text\": \"This property is unowned.\"}";
					HAL_UART_Transmit(&Util::raspi_handle, buffer8, sizeof(buffer8), HAL_MAX_DELAY);
					HAL_Delay (500);
					uint8_t buffer9[] = "{\"action\": \"update\", \"player\": \"0\", \"money\": \"1400\"}";
					HAL_UART_Transmit(&Util::raspi_handle, buffer9, sizeof(buffer9), HAL_MAX_DELAY);
					break;
				}
				HAL_UART_Receive(&Util::raspi_handle, rbuffer, sizeof(rbuffer), HAL_MAX_DELAY);
				HAL_Delay(100);
			}


//	HAL_Delay (2000);


	for(;;){
//		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
//		HAL_Delay(500);
	}
}

