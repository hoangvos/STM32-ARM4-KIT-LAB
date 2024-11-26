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
#define COUNTER_SHIFT_DELAY 1000

extern int timer2_flag;
extern int counter_shift;


void timer_init();
void setTimer2(uint16_t duration);
void shiftDigitsRight();
void displayDigits();

#endif /* INC_SOFTWARE_TIMER_H_ */
