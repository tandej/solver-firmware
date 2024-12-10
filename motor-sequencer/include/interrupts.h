#pragma once

#include "pico/stdlib.h"

void setIRQEnabled(timer_hw_t *timer, const uint8_t irqNum, const bool state);

void clearIRQ(timer_hw_t *timer, const uint8_t irqNum);

void latchInputsCallback();

void beginMoveCallback();

void stepCallback();

void stepPulseDownCallback();

void initInterrupts();