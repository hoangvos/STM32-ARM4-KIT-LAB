/*
 * draw_graph.c
 *
 *  Created on: Nov 26, 2024
 *      Author: PC
 */

#include "draw_graph.h"

int power_buffer[POWER_BUFFER_LENGTH] = {};
int power_buffer_counter = 0;

void draw_graph() {
	int temp = sensor_GetCurrent()*sensor_GetVoltage();
	power_buffer[power_buffer_counter] = temp;
	++power_buffer_counter;
	if (power_buffer_counter == POWER_BUFFER_LENGTH)
		power_buffer_counter = 0;
	lcd_Fill(20, 0, 220, 200, WHITE);
	lcd_DrawLine(20, 100, 20, 200, RED);
	lcd_DrawLine(20, 200, 220, 200, RED);
	int x = 20;
	for (int i = power_buffer_counter + 1; i < POWER_BUFFER_LENGTH; ++i){
		lcd_DrawLine(x, 200 - power_buffer[i-1], x + 20, 200 - power_buffer[i], RED);
		x += 20;
	}
	if (x < 220) {
		lcd_DrawLine(x, 200 - power_buffer[POWER_BUFFER_LENGTH - 1], x + 20, 200 - power_buffer[0], RED);
		x += 20;
		for (int i = 0; i < power_buffer_counter - 1; ++i) {
			lcd_DrawLine(x, 200 - power_buffer[i], x + 20, 200 - power_buffer[i + 1], RED);
			x += 20;
		}
	}
}
