#pragma once

#include "hardware/irq.h"
#include "hardware/timer.h"

#include "io.h"

#define DYN_ALARM_NUM 0
#define STEP_DOWN_ALARM_NUM 1

#define TIMER timer_hw

#define DYN_ALARM_IRQ_NUM timer_hardware_alarm_get_irq_num(TIMER, DYN_ALARM_NUM)
#define STEP_DOWN_ALARM_IRQ_NUM                                                \
  timer_hardware_alarm_get_irq_num(TIMER, STEP_DOWN_ALARM_NUM)

void setIRQEnabled(timer_hw_t *timer, const uint8_t irqNum, const bool state);

void clearIRQ(timer_hw_t *timer, const uint8_t irqNum);

void latchInputsCallback();

void beginMoveCallback();

void stepCallback();

void stepPulseDownCallback();

void initInterrupts();