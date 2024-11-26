/*
 * traffic_light_display.c
 *
 *  Created on: Nov 14, 2023
 *      Author: Nguyuyen
 */

#include "traffic_light_display.h"

TrafficLightDisplayState traffic_light_display_state = NONE;
TrafficLightDisplayState traffic_light_display_state_pre = YGREEN;

void redXOn() {
  lcd_DrawCircle(90, 110, RED, 20, 1);
  lcd_DrawCircle(30, 170, WHITE, 20, 1);
}
void amberXOn() {
  lcd_DrawCircle(150, 110, YELLOW, 20, 1);
  lcd_DrawCircle(30, 230, WHITE, 20, 1);
}
void greenXOn() {
  lcd_DrawCircle(210, 110, GREEN, 20, 1);
  lcd_DrawCircle(30, 290, WHITE, 20, 1);
}
void redYOn() {
  lcd_DrawCircle(90, 110, WHITE, 20, 1);
  lcd_DrawCircle(30, 170, RED, 20, 1);
}
void amberYOn() {
  lcd_DrawCircle(150, 110, WHITE, 20, 1);
  lcd_DrawCircle(30, 230, YELLOW, 20, 1);
}
void greenYOn() {
  lcd_DrawCircle(210, 110, WHITE, 20, 1);
  lcd_DrawCircle(30, 290, GREEN, 20, 1);
}
void redOff() {
  lcd_DrawCircle(90, 110, WHITE, 20, 1);
  lcd_DrawCircle(30, 170, WHITE, 20, 1);
}
void amberOff() {
  lcd_DrawCircle(150, 110, WHITE, 20, 1);
  lcd_DrawCircle(30, 230, WHITE, 20, 1);
}
void greenOff() {
  lcd_DrawCircle(210, 110, WHITE, 20, 1);
  lcd_DrawCircle(30, 290, WHITE, 20, 1);
}

void displayTrafficLight(){
  if (traffic_light_display_state == traffic_light_display_state_pre)
	  return;
  traffic_light_display_state_pre = traffic_light_display_state;
  switch (traffic_light_display_state) {
    case NONE:
      redOff();
      amberOff();
      greenOff();
	  break;
    case XRED_YGREEN:
	  lcd_Clear(WHITE);
	  redXOn();
	  amberOff();
	  greenYOn();
      break;
    case XRED_YAMBER:
      redXOn();
      amberYOn();
      greenOff();
      break;
    case XGREEN_YRED:
      greenXOn();
      amberOff();
      redYOn();
      break;
    case XAMBER_YRED:
      greenOff();
      amberXOn();
      redYOn();
      break;
    case XRED:
      redXOn();
      amberOff();
      greenOff();
      break;
    case XAMBER:
      redOff();
      amberXOn();
      greenOff();
      break;
    case XGREEN:
      redOff();
      amberOff();
      greenXOn();
      break;
    case YRED:
	  redYOn();
	  amberOff();
	  greenOff();
	  break;
	case YAMBER:
	  redOff();
	  amberYOn();
	  greenOff();
	  break;
	case YGREEN:
	  redOff();
	  amberOff();
	  greenYOn();
	  break;
    default:
      break;
  }
}
