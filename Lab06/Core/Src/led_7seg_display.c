/*
 * led_7seg_display.c
 *
 *  Created on: Nov 26, 2024
 *      Author: PC
 */

#include "led_7seg_display.h"

int hour;
int minute;
int colon_status = 0;

void updateColon(){
	colon_status = !colon_status;
		led7_SetColon(colon_status);
}
void updateTime(){
	minute = ds3231_min;
	hour = ds3231_hours;
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
