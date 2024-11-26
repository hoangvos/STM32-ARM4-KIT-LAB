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

extern int debug_led_flag;
extern int y0_led_flag;
extern int y1_led_flag;

void timer_init();
void setTimer_debug_led(uint16_t duration);
void setTimer_y0_led(uint16_t duration);
void setTimer_y1_led(uint16_t duration);


#endif /* INC_SOFTWARE_TIMER_H_ */
