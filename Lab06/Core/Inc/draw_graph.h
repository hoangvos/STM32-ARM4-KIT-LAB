/*
 * draw_graph.h
 *
 *  Created on: Nov 26, 2024
 *      Author: PC
 */

#ifndef INC_DRAW_GRAPH_H_
#define INC_DRAW_GRAPH_H_

#include "sensor.h"
#include "lcd.h"

#define POWER_BUFFER_LENGTH 11

extern int power_buffer[POWER_BUFFER_LENGTH];
extern int power_buffer_counter;

void draw_graph();

#endif /* INC_DRAW_GRAPH_H_ */
