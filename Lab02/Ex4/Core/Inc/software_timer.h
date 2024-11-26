/*
 * software_timer.h
 *
 *  Created on: Nov 11, 2024
 *      Author: hoang
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_


/* Includes */
#include "tim.h"
#include "software_timer.h"

#define TIMER_CYCLE_2 1
#define COUTNER_COLON_BLINK 250
#define COUNTER_TIME_UPDATE 60000

extern int colon_flag;
extern int update_time_flag;


void timer_init();
void setTimer_colon(uint16_t duration);
void setTimer_update_time(uint16_t duration);
void displayTime();
void updateColon();
void updateTime();

#endif /* INC_SOFTWARE_TIMER_H_ */
