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

extern int timer2_flag;

void timer_init();
void setTimer2(uint16_t duration);


#endif /* INC_SOFTWARE_TIMER_H_ */
