/*
 * software_timer.c
 *
 *  Created on: Nov 11, 2024
 *      Author: hoang
 */
#include "software_timer.h"

#include "led_7seg.h"



#define TIMER_CYCLE_2 1

int debug_led_flag = 0;
int debug_counter = 0;

int y0_led_flag = 0;
int y0_counter = 0;

int y1_led_flag = 0;
int y1_counter = 0;


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
void setTimer_debug_led(uint16_t duration){
	int timer_MUL = duration/TIMER_CYCLE_2;
	debug_counter = timer_MUL;
	debug_led_flag = 0;
}
void setTimer_y0_led(uint16_t duration){
	int timer_MUL = duration/TIMER_CYCLE_2;
	y0_counter = timer_MUL;
	y0_led_flag = 0;
}
void setTimer_y1_led(uint16_t duration){
	int timer_MUL = duration/TIMER_CYCLE_2;
	y1_counter = timer_MUL;
	y1_led_flag = 0;
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		if(debug_counter > 0){
			debug_counter--;
			if(debug_counter <= 0){
				debug_led_flag = 1;
			}
		}
		if(y0_counter > 0){
			y0_counter--;
			if(y0_counter <= 0){
				y0_led_flag = 1;
			}
		}
		if(y1_counter > 0){
			y1_counter--;
			if(y1_counter <= 0){
				y1_led_flag = 1;
			}
		}
		// 1ms interrupt here
		//led7_Scan();
	}
}
