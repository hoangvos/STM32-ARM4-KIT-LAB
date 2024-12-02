/*
 * ring_buffer.c
 *
 *  Created on: Jun 4, 2024
 *      Author: DAT
 */

#include "ring_buffer.h"

void initRingBuffer(RingBuffer *buffer) {
  buffer->head = 0;
  buffer->tail = 0;
}

int isRingBufferEmpty(RingBuffer *buffer) {
  return buffer->head == buffer->tail;
}

int isRingBufferFull(RingBuffer *buffer) {
  return (buffer->tail + 1) % BUFFER_SIZE == buffer->head;
}

void addToRingBuffer(RingBuffer *buffer, int data) {
  if (isRingBufferFull(buffer)) {
    printf("Ring buffer is full!\n");
    return;
  }

  buffer->data[buffer->tail] = data;
  buffer->tail = (buffer->tail + 1) % BUFFER_SIZE;
}

char getFromRingBuffer(RingBuffer *buffer) {
  if (isRingBufferEmpty(buffer)) {
    printf("Ring buffer is empty!\n");
    return "E";
  }

  int data = buffer->data[buffer->head];
  buffer->head = (buffer->head + 1) % BUFFER_SIZE;
  return (char)data;
}

