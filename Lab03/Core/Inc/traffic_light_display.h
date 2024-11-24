/*
 * traffic_light_display.h
 *
 *  Created on: Nov 14, 2023
 *      Author: Nguyuyen
 */

#ifndef INC_TRAFFIC_LIGHT_DISPLAY_H_
#define INC_TRAFFIC_LIGHT_DISPLAY_H_

#include "lcd.h"

typedef enum
{
  NONE = 0,
  XRED_YGREEN = 1,
  XRED_YAMBER = 2,
  XGREEN_YRED = 3,
  XAMBER_YRED = 4,
  XRED = 5,
  XAMBER = 6,
  XGREEN = 7,
  YRED = 8,
  YAMBER = 9,
  YGREEN = 10
} TrafficLightDisplayState;

extern TrafficLightDisplayState traffic_light_display_state;

void redXOn();
void amberXOn();
void greenXOn();
void redYOn();
void amberYOn();
void greenYOn();
void redOff();
void amberOff();
void greenOff();
void displayTrafficLight();

#endif /* INC_TRAFFIC_LIGHT_DISPLAY_H_ */
