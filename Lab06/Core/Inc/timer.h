/*
 * timer.h
 *
 *  Created on: Nov 12, 2024
 *      Author: PC
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "tim.h"

#define TIME_CYCLE 1
#define TIMER_NUMBER 5

#define COLON_BLINK_TIME 250
#define ONE_MINUTE_TIME 1000
#define BUTTON_READING_TIME 50
#define DEBUG_LED_TIME 500
#define GET_DATA_TIME 5000

extern int timer_counter[TIMER_NUMBER];
extern int timer_flag[TIMER_NUMBER];

void initTimer();
void setTimer(int index, int duration);
void runTimer();

#endif /* INC_TIMER_H_ */
