/*
 * traffic_light_control.c
 *
 *  Created on: Nov 12, 2024
 *      Author: PC
 */

#include "traffic_light_control.h"

TrafficLightState traffic_light_state = INIT;

/*
 * 0: red
 * 1: amber
 * 2: green
 */
int traffic_light_time_buffer[3] = {RED_TIME_DEFAULT, AMBER_TIME_DEFAULT, GREEN_TIME_DEFAULT};
int traffic_light_time_buffer_next[3] = {RED_TIME_DEFAULT, AMBER_TIME_DEFAULT, GREEN_TIME_DEFAULT};
int traffic_light_time_buffer_temp[3] = {RED_TIME_DEFAULT, AMBER_TIME_DEFAULT, GREEN_TIME_DEFAULT};

int time_counter_x, time_counter_y;

void controlTrafficLight(){
  switch (traffic_light_state) {
    case INIT:
      lcd_Clear(BROWN);
      lcd_Fill(0, 0, 240, 40, WHITE);
      lcd_StrCenter(0, 8, "NORMAL", RED, WHITE, 24, 1);
      traffic_light_state = NORMAL_RED_GREEN;
      traffic_light_display_state = XRED_YGREEN;
      time_counter_x = traffic_light_time_buffer[0];
      time_counter_y = traffic_light_time_buffer[2];
      --time_counter_x;
	  --time_counter_y;
      setTimer(1, TRAFFIC_LIGHT_TIME);
      break;
    case NORMAL_RED_GREEN:
      if(button_count[0] == 1){
    	++button_count[0];
    	lcd_Fill(0, 0, 240, 40, WHITE);
    	lcd_StrCenter(0, 8, "MODIFICATION", RED, WHITE, 24, 1);
    	traffic_light_state = MODIFY_RED;
    	traffic_light_display_state = XRED;
	    setTimer(0, LED_BLINK_TIME);
      } else {
		if(timer_flag[1] == 1){
		  setTimer(1, TRAFFIC_LIGHT_TIME);
		  if(time_counter_y <= 0){
			  lcd_Fill(0, 0, 240, 40, WHITE);
			  lcd_StrCenter(0, 8, "NORMAL", RED, WHITE, 24, 1);
			traffic_light_state = NORMAL_RED_AMBER;
			traffic_light_display_state = XRED_YAMBER;
			time_counter_y = traffic_light_time_buffer[1];
		  }
		  --time_counter_x;
		  --time_counter_y;
		}
      }
      break;
    case NORMAL_RED_AMBER:
      if(button_count[0] == 1){
    	  ++button_count[0];
    	lcd_Fill(0, 0, 240, 40, WHITE);
    	lcd_StrCenter(0, 8, "MODIFICATION", RED, WHITE, 24, 1);
      	traffic_light_state = MODIFY_RED;
      	traffic_light_display_state = XRED;
		setTimer(0, LED_BLINK_TIME);
      } else {
		if(timer_flag[1] == 1){
		  setTimer(1, TRAFFIC_LIGHT_TIME);
		  if(time_counter_y <= 0){
			  lcd_Fill(0, 0, 240, 40, WHITE);
			  lcd_StrCenter(0, 8, "NORMAL", RED, WHITE, 24, 1);
			traffic_light_state = NORMAL_GREEN_RED;
			traffic_light_display_state = XGREEN_YRED;
			time_counter_x = traffic_light_time_buffer[2];
			time_counter_y = traffic_light_time_buffer[0];
		  }
		  --time_counter_x;
		  --time_counter_y;
		}
      }
      break;
    case NORMAL_GREEN_RED:
      if(button_count[0] == 1){
    	  ++button_count[0];
    	lcd_Fill(0, 0, 240, 40, WHITE);
    	lcd_StrCenter(0, 8, "MODIFICATION", RED, WHITE, 24, 1);
      	traffic_light_state = MODIFY_RED;
      	traffic_light_display_state = XRED;
		setTimer(0, LED_BLINK_TIME);
      } else {
		if(timer_flag[1] == 1){
		  setTimer(1, TRAFFIC_LIGHT_TIME);
		  if(time_counter_x <= 0){
			  lcd_Fill(0, 0, 240, 40, WHITE);
			  lcd_StrCenter(0, 8, "NORMAL", RED, WHITE, 24, 1);
			traffic_light_state = NORMAL_AMBER_RED;
			traffic_light_display_state = XAMBER_YRED;
			time_counter_x = traffic_light_time_buffer[1];
		  }
		  --time_counter_x;
		  --time_counter_y;
		}
      }
      break;
    case NORMAL_AMBER_RED:
      if(button_count[0] == 1){
    	  ++button_count[0];
    	lcd_Fill(0, 0, 240, 40, WHITE);
    	lcd_StrCenter(0, 8, "MODIFICATION", RED, WHITE, 24, 1);
      	traffic_light_state = MODIFY_RED;
      	traffic_light_display_state = XRED;
      	setTimer(0, LED_BLINK_TIME);
      } else {
		if(timer_flag[1] == 1){
		  setTimer(1, TRAFFIC_LIGHT_TIME);
		  if(time_counter_x <= 0){
			  lcd_Fill(0, 0, 240, 40, WHITE);
			  lcd_StrCenter(0, 8, "NORMAL", RED, WHITE, 24, 1);
			traffic_light_state = NORMAL_RED_GREEN;
			traffic_light_display_state = XRED_YGREEN;
			time_counter_x = traffic_light_time_buffer[0];
			time_counter_y = traffic_light_time_buffer[2];
		  }
		  --time_counter_x;
		  --time_counter_y;
		}
      }
      break;
    case MODIFY_RED:
      if(button_count[0] == 1){
    	  ++button_count[0];
    	lcd_Fill(0, 0, 240, 40, WHITE);
    	lcd_StrCenter(0, 8, "MODIFICATION", RED, WHITE, 24, 1);
      	traffic_light_state = MODIFY_GREEN;
      	traffic_light_display_state = XGREEN;
      } else {
		if(timer_flag[0] == 1){
		  setTimer(0, LED_BLINK_TIME);
		  if (traffic_light_display_state == XRED)
			traffic_light_display_state = YRED;
		  else
			traffic_light_display_state = XRED;
		}
		if(button_count[1] == 1){
			++button_count[1];
		  ++traffic_light_time_buffer_temp[0];
		  if(traffic_light_time_buffer_temp[0] > TIME_LIGHT_MAX)
			traffic_light_time_buffer_temp[0] = TIME_LIGHT_MIN;
		}
		if(button_count[2] == 1){
			++button_count[2];
		  traffic_light_time_buffer_next[0] = traffic_light_time_buffer_temp[0];
		}
//		lcd_Fill(0, 40, 240, 40, WHITE);
		lcd_ShowIntNum(100, 48, traffic_light_time_buffer_temp[0], 2, RED, WHITE, 24);
      }
      break;
    case MODIFY_GREEN:
      if(button_count[0] == 1){
    	  ++button_count[0];
    	lcd_Fill(0, 0, 240, 40, WHITE);
    	lcd_StrCenter(0, 8, "MODIFICATION", RED, WHITE, 24, 1);
      	traffic_light_state = MODIFY_AMBER;
      	traffic_light_display_state = XAMBER;
      } else {
		if(timer_flag[0] == 1){
		  setTimer(0, LED_BLINK_TIME);
		  if (traffic_light_display_state == XGREEN)
			traffic_light_display_state = YGREEN;
		  else
			traffic_light_display_state = XGREEN;
		}
		if(button_count[1] == 1){
			++button_count[1];
		  ++traffic_light_time_buffer_temp[2];
		  if(traffic_light_time_buffer_temp[2] > TIME_LIGHT_MAX)
			traffic_light_time_buffer_temp[2] = TIME_LIGHT_MIN;
		}
		if(button_count[2] == 1){
			++button_count[2];
		  traffic_light_time_buffer_next[2] = traffic_light_time_buffer_temp[2];
		}
//		lcd_Fill(0, 40, 240, 40, WHITE);
		lcd_ShowIntNum(100, 48, traffic_light_time_buffer_temp[2], 2, RED, WHITE, 24);
      }
      break;
    case MODIFY_AMBER:
	  if(button_count[0] == 1){
		  ++button_count[0];
		lcd_Fill(0, 0, 240, 40, WHITE);
		lcd_StrCenter(0, 8, "MODIFICATION", RED, WHITE, 24, 1);
		traffic_light_state = MODIFY_ERROR;
		traffic_light_display_state = NONE;
	  } else {
		if(timer_flag[0] == 1){
		  setTimer(0, LED_BLINK_TIME);
		  if (traffic_light_display_state == XAMBER)
			traffic_light_display_state = YAMBER;
		  else
			traffic_light_display_state = XAMBER;
		}
		if(button_count[1] == 1){
			++button_count[1];
		  ++traffic_light_time_buffer_temp[1];
		  if(traffic_light_time_buffer_temp[1] > TIME_LIGHT_MAX)
			traffic_light_time_buffer_temp[1] = TIME_LIGHT_MIN;
		}
		if(button_count[2] == 1){
			++button_count[2];
		  traffic_light_time_buffer_next[1] = traffic_light_time_buffer_temp[1];
		}
//		lcd_Fill(0, 40, 240, 40, WHITE);
		lcd_ShowIntNum(100, 48, traffic_light_time_buffer_temp[1], 2, RED, WHITE, 24);
	  }
	  break;
    case MODIFY_ERROR:
      if(traffic_light_time_buffer_next[0] == traffic_light_time_buffer_next[1] + traffic_light_time_buffer_next[2]){
		traffic_light_time_buffer[0] = traffic_light_time_buffer_next[0];
		traffic_light_time_buffer[1] = traffic_light_time_buffer_next[1];
		traffic_light_time_buffer[2] = traffic_light_time_buffer_next[2];
      }
      traffic_light_time_buffer_temp[0] = traffic_light_time_buffer[0];
      traffic_light_time_buffer_temp[1] = traffic_light_time_buffer[1];
      traffic_light_time_buffer_temp[2] = traffic_light_time_buffer[2];

      traffic_light_time_buffer_next[0] = traffic_light_time_buffer[0];
	  traffic_light_time_buffer_next[1] = traffic_light_time_buffer[1];
	  traffic_light_time_buffer_next[2] = traffic_light_time_buffer[2];
      lcd_Clear(BROWN);
      lcd_Fill(0, 0, 240, 40, WHITE);
      lcd_StrCenter(0, 8, "NORMAL", RED, WHITE, 24, 1);
      traffic_light_state = NORMAL_RED_GREEN;
      traffic_light_display_state = XRED_YGREEN;
      time_counter_x = traffic_light_time_buffer[0];
      time_counter_y = traffic_light_time_buffer[2];
      --time_counter_x;
      --time_counter_y;
      setTimer(1, TRAFFIC_LIGHT_TIME);
      break;
    default:
      break;
  }
  displayTrafficLight();
}
