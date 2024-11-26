/*
 * software_timer.c
 *
 *  Created on: Nov 11, 2024
 *      Author: hoang
 */
#include "software_timer.h"

#include "led_7seg.h"



int timer2_flag = 0;
int counter_shift = 0;

int digits[4] = {1, 2, 3, 4};

void shiftDigitsRight(){
    int lastDigit = digits[3]; // Lưu số cuối cùng
    for (int i = 3; i > 0; i--) {
        digits[i] = digits[i - 1]; // Dịch các số sang phải
    }
    digits[0] = lastDigit; // Đưa số cuối cùng lên đầu
}

void displayDigits(){
    for (int i = 0; i < 4; i++) {
        led7_SetDigit(digits[i], i, 0); // Hiển thị từng số lên từng LED
    }
}


/**
  * @brief  Init timer interrupt
  * @param  None
  * @retval None
  */

void timer_init(){
	HAL_TIM_Base_Start_IT(&htim2);
	displayDigits();
	setTimer2(COUNTER_SHIFT_DELAY);
}

/**
  * @brief  Set duration of software timer interrupt
  * @param  duration Duration of software timer interrupt
  * @retval None
  */
void setTimer2(uint16_t duration){
	int timer_MUL = duration/TIMER_CYCLE_2;
	counter_shift = timer_MUL;
	timer2_flag = 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		if(counter_shift > 0){
			counter_shift--;
			if(counter_shift <= 0){
				timer2_flag = 1;
			}
		}
		// 1ms interrupt here
		led7_Scan();
	}
}
