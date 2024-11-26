/*
 * software_timer.c
 *
 *  Created on: Nov 11, 2024
 *      Author: hoang
 */
#include "software_timer.h"

#include "led_7seg.h"



int colon_flag = 0;
int counter_colon = 0;

int update_time_flag = 0;
int counter_update_time = 0;

int hour = 12;
int minute = 34;
int colon_status = 0;

void updateTime(){
	minute++;
	if(minute >= 60){
		minute = 0;
		hour++;
		if(hour > 24){
			hour = 0;
		}
	}
	setTimer_update_time(COUNTER_TIME_UPDATE);
}
void updateColon(){
	colon_status = !colon_status;
	led7_SetColon(colon_status);
	setTimer_colon(COUTNER_COLON_BLINK);
}

void displayTime(){
    int hour_tens = hour / 10;
    int hour_units = hour % 10;
    int minute_tens = minute / 10;
    int minute_units = minute % 10;
    led7_SetDigit(hour_tens, 0, 0);
    led7_SetDigit(hour_units, 1, 0);
    led7_SetDigit(minute_tens, 2, 0);
    led7_SetDigit(minute_units, 3, 0);
}


/**
  * @brief  Init timer interrupt
  * @param  None
  * @retval None
  */

void timer_init(){
	HAL_TIM_Base_Start_IT(&htim2);
	setTimer_colon(COUTNER_COLON_BLINK);
	setTimer_update_time(COUNTER_TIME_UPDATE);
	displayTime();
}

/**
  * @brief  Set duration of software timer interrupt
  * @param  duration Duration of software timer interrupt
  * @retval None
  */
void setTimer_colon(uint16_t duration){
	int timer_MUL = duration/TIMER_CYCLE_2;
	counter_colon = timer_MUL;
	colon_flag = 0;
}
void setTimer_update_time(uint16_t duration){
	int timer_MUL = duration/TIMER_CYCLE_2;
	counter_update_time = timer_MUL;
	update_time_flag = 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		if(counter_colon > 0){
			counter_colon--;
			if(counter_colon <= 0){
				colon_flag = 1;
			}
		}
		if(counter_update_time > 0){
			counter_update_time--;
			if(counter_update_time <= 0){
				update_time_flag = 1;
			}
		}
		// 1ms interrupt here
		led7_Scan();
	}
}
