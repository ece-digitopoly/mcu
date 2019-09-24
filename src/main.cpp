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
#include "Profile.h"
#include "Action.h"
#include "PropertyAction.h"
#include "Property.h"

static UART_HandleTypeDef s_UARTHandle;
int calls = 0;
int ifs = 0;
int elses = 0;

void scrollUp();
void scrollDown();
void click();
void buyProperty();
void Error_Handler() {
	for (;;);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_0)
    {
    	ifs++;
    }
    else
	{
    	elses++;
    }
}

void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */
    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)){
    	click();
    }
//  HAL_Delay(50);
    /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_IRQn 1 */

  /* USER CODE END EXTI0_IRQn 1 */
}

void EXTI1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */
    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1))
    	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8);
//  HAL_Delay(50);
    /* USER CODE END EXTI0_IRQn 0 */
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  /* USER CODE BEGIN EXTI0_IRQn 1 */

  /* USER CODE END EXTI0_IRQn 1 */
}

static int mouseScrollBack;
static int mouseScrollForth;
static int mouseIsScrollingBack;
static int mouseIsScrollingForth;

void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */
    int pe7 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7);
    int pe8 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_8);

    if ((pe7 && pe8 && !mouseIsScrollingForth)) {
    	scrollUp();
    	mouseIsScrollingBack = 1;
    }
	else if (pe7 && !pe8 && !mouseIsScrollingBack) {
		scrollDown();
		mouseIsScrollingForth = 1;
	}
	else if (pe7 && pe8) {
		mouseIsScrollingForth = 0;
	}
	else if (pe7 && !pe8) {
		mouseIsScrollingBack = 0;
	}
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
}


void scrollDown(){
	uint8_t buffer[] = "{\"action\": \"scroll\", \"direction\": \"down\"}\n";
	HAL_UART_Transmit(&s_UARTHandle, buffer, sizeof(buffer), HAL_MAX_DELAY);
}

void scrollUp(){
	uint8_t buffer[] = "{\"action\": \"scroll\", \"direction\": \"up\"}\n";
	HAL_UART_Transmit(&s_UARTHandle, buffer, sizeof(buffer), HAL_MAX_DELAY);
}


void click(){
	uint8_t buffer[] = "{\"action\": \"click\"}\n";
	HAL_UART_Transmit(&s_UARTHandle, buffer, sizeof(buffer), HAL_MAX_DELAY);
}


void buyProperty(){
	uint8_t buffer[] = "{\"action\": \"buy\", \"player\": \"2\", \"property\": \"3\"}\n";
	HAL_UART_Transmit(&s_UARTHandle, buffer, sizeof(buffer), HAL_MAX_DELAY);
}

ADC_HandleTypeDef hadc1;
static void MX_ADC1_Init(void);
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.NbrOfDiscConversion = 0;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.EOCSelection = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  sConfig.Channel = ADC_CHANNEL_11;
  sConfig.Rank = 2;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

void config_ext_channel_ADC(uint32_t channel, int val)
{
  ADC_ChannelConfTypeDef sConfig = {0};

  sConfig.Channel = channel;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;

  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
}



int main(){
	HAL_Init();

	__USART2_CLK_ENABLE();
	__GPIOA_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();
	__GPIOE_CLK_ENABLE();

	/* Set pin as input */
	GPIO_InitTypeDef GPIO_InitStruct;

	/*Configure GPIO pin : PB0 */
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins : PC0 PC1 */
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	GPIO_InitStruct.Alternate = GPIO_AF0_ADC123_IN0;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pin : PE9 */
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/*Configure GPIO pins : PA2 PA3 */
	GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	MX_ADC1_Init();

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

	s_UARTHandle.Instance	 	 = USART2;
	s_UARTHandle.Init.BaudRate	 = 115200;
	s_UARTHandle.Init.WordLength = UART_WORDLENGTH_8B;
	s_UARTHandle.Init.StopBits	 = UART_STOPBITS_1;
	s_UARTHandle.Init.Parity	 = UART_PARITY_NONE;
	s_UARTHandle.Init.HwFlowCtl	 = UART_HWCONTROL_NONE;
	s_UARTHandle.Init.Mode	   	 = UART_MODE_TX_RX;

	if (HAL_UART_Init(&s_UARTHandle) != HAL_OK)
		asm("bkpt 255");

	HAL_Delay(1000);
	scrollDown();
	HAL_Delay(1000);
	scrollDown();
	HAL_Delay(100);
	scrollDown();
	HAL_Delay(100);
	scrollDown();
	HAL_Delay(100);
	scrollDown();
	HAL_Delay(100);
	scrollDown();
	HAL_Delay(1000);
	scrollUp();
	HAL_Delay(100);
	scrollUp();
	HAL_Delay(100);
	scrollUp();
	HAL_Delay(100);
	scrollUp();
	HAL_Delay(100);
	scrollUp();
	HAL_Delay(1000);
	click();

	uint32_t g_ADCValue;
	int x_g_MeasurementNumber;
	int y_g_MeasurementNumber;

	HAL_ADC_Start(&hadc1);
	for (;;) {
		config_ext_channel_ADC(ADC_CHANNEL_10, 10);
		if (HAL_ADC_PollForConversion(&hadc1, 1000) == HAL_OK)
		{
		    g_ADCValue = HAL_ADC_GetValue(&hadc1);
		    x_g_MeasurementNumber++;
		}

		config_ext_channel_ADC(ADC_CHANNEL_11, 11);
		if (HAL_ADC_PollForConversion(&hadc1, 1000) == HAL_OK)
		{
			g_ADCValue = HAL_ADC_GetValue(&hadc1);
			y_g_MeasurementNumber++;
		}
	}

	return 0;
}

