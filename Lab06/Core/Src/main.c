/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "timer.h"
#include "button.h"
#include "buzzer.h"
#include "sensor.h"
#include "ds3231.h"
#include "uart.h"
#include "led_7seg_display.h"
#include "draw_graph.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void system_init();
void test_LedDebug();
void test_Buzzer();
void test_Adc();
void test_Uart();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_FSMC_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
  MX_I2C1_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_TIM13_Init();
  /* USER CODE BEGIN 2 */
  system_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  lcd_Clear(BLACK);
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if (timer_flag[3] == 1) {
	  	  setTimer(3, DEBUG_LED_TIME);
	  	  HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
	  	}
	  if (timer_flag[0] == 1) {
		  setTimer(0, COLON_BLINK_TIME);
		  updateColon();
	  }
	  if (timer_flag[1] == 1) {
		  setTimer(1, ONE_MINUTE_TIME);
		  updateTime();
		  displayTime();
	  }
	  	if (timer_flag[2] == 1) {
	  	  setTimer(2, BUTTON_READING_TIME);
	  	  button_Scan();
	  	  test_Adc();
	  	  test_Buzzer();
	  	  ds3231_ReadTime();
	  	  test_Uart();
	  	}
	  	if (timer_flag[4] == 1) {
	  		setTimer(4, GET_DATA_TIME);
	  		draw_graph();
	  	}
  }
  /* USER CODE END 3 */
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
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void system_init() {
  initTimer();
  button_init();
  lcd_init();
  sensor_init();
  buzzer_init();
  displayTime();
  uart_init_rs232();
}

////// -------- ///////

uint8_t count_led_debug = 0;

uint8_t isButtonUp()
{
    if (button_count[3] == 1)
        return 1;
    else
        return 0;
}

uint8_t isButtonDown()
{
    if (button_count[7] == 1)
        return 1;
    else
        return 0;
}

uint8_t isButtonRight()
{
    if (button_count[11] == 1)
        return 1;
    else
        return 0;
}

uint8_t count_adc = 0;

void test_Adc(){
	count_adc = (count_adc + 1)%20;
	if(count_adc == 0){
		sensor_Read();
//		lcd_ShowStr(10, 220, "Power:", RED, BLACK, 16, 0);
//		lcd_ShowFloatNum(130, 220,sensor_GetVoltage()*sensor_GetCurrent(), 4, RED, BLACK, 16);
//
//		lcd_ShowStr(10, 240, "Voltage:", RED, BLACK, 16, 0);
//		lcd_ShowFloatNum(130, 240,sensor_GetVoltage(), 4, RED, BLACK, 16);
//
//		lcd_ShowStr(10, 260, "Current", RED, BLACK, 16, 0);
//		lcd_ShowFloatNum(130, 260, sensor_GetCurrent(), 4, RED, BLACK, 16);


//		lcd_ShowStr(10, 100, "Power:", RED, BLACK, 16, 0);
//		lcd_ShowFloatNum(130, 100,sensor_GetVoltage()*sensor_GetCurrent(), 4, RED, BLACK, 16);
//
//		lcd_ShowStr(10, 120, "Light:", RED, BLACK, 16, 0);
//		lcd_ShowIntNum(130, 120, sensor_GetLight(), 4, RED, BLACK, 16);
//
//		lcd_ShowStr(10, 140, "Temperature:", RED, BLACK, 16, 0);
//		lcd_ShowFloatNum(130, 140, sensor_GetTemperature(), 4, RED, BLACK, 16);
//
//		lcd_ShowStr(10, 160, "Humidity:", RED, BLACK, 16, 0);
//		lcd_ShowFloatNum(130, 160, (float)sensor_GetPotentiometer()*100.0/4095, 4, RED, BLACK, 16);
	}
}

void test_Buzzer(){
	if(isButtonUp()){
		buzzer_SetVolume(50);
	}

	if(isButtonDown()){
		buzzer_SetVolume(0);
	}

	if(isButtonRight()){
		buzzer_SetVolume(25);
	}

}
void test_Uart(){
  if(button_count[12] == 1){
	uart_Rs232SendNum(ds3231_hours);
    uart_Rs232SendString(":");
    uart_Rs232SendNum(ds3231_min);
    uart_Rs232SendString(":");
    uart_Rs232SendNum(ds3231_sec);
    uart_Rs232SendString("\n");

    uart_Rs232SendString("Power:");
	uart_Rs232SendNumPercent(sensor_GetVoltage()*sensor_GetCurrent()*100);
	uart_Rs232SendString("\n");

    uart_Rs232SendString("Light:");
	uart_Rs232SendNum(sensor_GetLight());
	uart_Rs232SendString("\n");

	uart_Rs232SendString("Temperature:");
	uart_Rs232SendNumPercent(sensor_GetTemperature()*100);
	uart_Rs232SendString("\n");

	uart_Rs232SendString("Humidity:");
	uart_Rs232SendNumPercent(sensor_GetPotentiometer()*100.0/4095*100);
	uart_Rs232SendString("\n");
	uart_Rs232SendString("------\n");
  }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
