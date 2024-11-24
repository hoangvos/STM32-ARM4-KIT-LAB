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
	setTimer(0, LED_BLINK_TIME);
	setTimer(1, TRAFFIC_LIGHT_TIME);
	setTimer(2, BUTTON_READING_TIME);
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
}
