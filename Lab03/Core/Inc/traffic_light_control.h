/*
 * traffic_light_control.h
 *
 *  Created on: Nov 12, 2024
 *      Author: PC
 */

#ifndef INC_TRAFFIC_LIGHT_CONTROL_H_
#define INC_TRAFFIC_LIGHT_CONTROL_H_

#include "timer.h"
#include "button.h"
#include "traffic_light_display.h"

#define RED_TIME_DEFAULT 5
#define AMBER_TIME_DEFAULT 2
#define GREEN_TIME_DEFAULT 3

#define TIME_LIGHT_MAX 99
#define TIME_LIGHT_MIN 1

#define SWITCH_MODE_BUTTON 0
#define INCREASE_BUTTON 1
#define CONFIRM_BUTTON 2

typedef enum
{
  INIT = 0,
  NORMAL_RED_GREEN = 1,
  NORMAL_RED_AMBER = 2,
  NORMAL_GREEN_RED = 3,
  NORMAL_AMBER_RED = 4,
  MODIFY_RED = 5,
  MODIFY_GREEN = 6,
  MODIFY_AMBER = 7,
  MODIFY_ERROR = 8
} TrafficLightState;

extern int traffic_light_time_buffer[3];
extern int traffic_light_time_buffer_next[3];
extern int traffic_light_time_buffer_temp[3];
extern int time_counter_x, time_counter_y;
extern TrafficLightState traffic_light_state;

void controlTrafficLight();

#endif /* INC_TRAFFIC_LIGHT_CONTROL_H_ */
