/*
 * led_7seg_display.h
 *
 *  Created on: Nov 26, 2024
 *      Author: PC
 */

#ifndef INC_LED_7SEG_DISPLAY_H_
#define INC_LED_7SEG_DISPLAY_H_

#include "led_7seg.h"
#include "ds3231.h"

extern int hour;
extern int minute;
extern int colon_status;

void updateColon();
void updateTime();
void displayTime();

#endif /* INC_LED_7SEG_DISPLAY_H_ */
