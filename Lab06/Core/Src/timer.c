/*
 * timer.c
 *
 *  Created on: Nov 12, 2024
 *      Author: PC
 */

#include "timer.h"

/*
 * timer0: blink led
 * timer1: traffic light
 * timer2: read button
 */
int timer_counter[TIMER_NUMBER];
int timer_flag[TIMER_NUMBER];

void initTimer() {
	HAL_TIM_Base_Start_IT(&htim2);
	setTimer(0, COLON_BLINK_TIME);
	setTimer(1, ONE_MINUTE_TIME);
	setTimer(2, BUTTON_READING_TIME);
	setTimer(3, DEBUG_LED_TIME);
	setTimer(4, GET_DATA_TIME);
}

void setTimer(int index, int duration){
  timer_counter[index] = duration / TIME_CYCLE;
  timer_flag[index] = 0;
}
void runTimer(){
  for(int i = 0; i < TIMER_NUMBER; ++i){
    if(timer_counter[i] > 0){
      --timer_counter[i];
      if(timer_counter[i] == 0)
	    timer_flag[i] = 1;
    }
  }
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
  runTimer();
  led7_Scan();
}
