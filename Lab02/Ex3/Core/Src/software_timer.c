/*
 * software_timer.c
 *
 *  Created on: Nov 11, 2024
 *      Author: hoang
 */
#include "software_timer.h"

#include "led_7seg.h"



#define TIMER_CYCLE_2 1

#define COUNTER_SCAN_1HZ 500
#define COUNTER_SCAN_25HZ 20
#define COUNTER_SCAN_100HZ 5
#define COUNTER_SCAN_500HZ 1


int counter_scan = COUNTER_SCAN_500HZ;


int timer2_flag = 0;
int counter2 = 0;

/**
  * @brief  Init timer interrupt
  * @param  None
  * @retval None
  */

void timer_init(){
	HAL_TIM_Base_Start_IT(&htim2);
}

/**
  * @brief  Set duration of software timer interrupt
  * @param  duration Duration of software timer interrupt
  * @retval None
  */
void setTimer2(uint16_t duration){
	int timer_MUL = duration/TIMER_CYCLE_2;
	counter2 = timer_MUL;
	timer2_flag = 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		if(counter2 > 0){
			counter2--;
			if(counter2 <= 0){
				timer2_flag = 1;
			}
		}
		if(counter_scan > 0 ){
			counter_scan--;
			if(counter_scan <= 0){
				led7_Scan();
				counter_scan = COUNTER_SCAN_25HZ;
			}
		}

	}
}
