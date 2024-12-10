#include "interrupts.h"

#include "io.h"

#include "hardware/irq.h"
#include "hardware/timer.h"

#define DYN_ALARM_NUM 0
#define STEP_DOWN_ALARM_NUM 1

#define TIMER timer_hw

#define DYN_ALARM_IRQ_NUM timer_hardware_alarm_get_irq_num(TIMER, DYN_ALARM_NUM)
#define STEP_DOWN_ALARM_IRQ_NUM                                                \
  timer_hardware_alarm_get_irq_num(TIMER, STEP_DOWN_ALARM_NUM)

volatile bool latchedMagnitudeIsFull = true;
volatile bool latchedDirIsPositive = true;
volatile uint8_t latchedMotorSelect = 0b00;

volatile uint8_t stepCounter = 0;

void setIRQEnabled(timer_hw_t *timer, const uint8_t irqNum, const bool state) {
  if (state) {
    hw_set_bits(&timer->inte, 1 << irqNum);
  } else {
    hw_clear_bits(&timer->inte, 1 << irqNum);
  }
  irq_set_enabled(irqNum, state);
}

void clearIRQ(timer_hw_t *timer, const uint8_t irqNum) {
  hw_set_bits(&timer->intr, 1 << irqNum);
}

void latchInputsCallback() {
  latchedMagnitudeIsFull = gpio_get(INPUT_MAG_PIN);
  latchedDirIsPositive = gpio_get(INPUT_DIR_PIN);

  latchedMotorSelect =
      (gpio_get(INPUT_MS1_PIN) << 1) + (gpio_get(INPUT_MS1_PIN));

  setIRQEnabled(TIMER, DYN_ALARM_IRQ_NUM, false);
  setIRQEnabled(TIMER, STEP_DOWN_ALARM_IRQ_NUM, false);
}

void beginMoveCallback() {
  setIRQEnabled(TIMER, DYN_ALARM_IRQ_NUM, true);
  setIRQEnabled(TIMER, STEP_DOWN_ALARM_IRQ_NUM, true);
}

void stepCallback() {}

void stepDownCallback() {}

void stepPulseDownCallback() {}

void initInterrupts() {
  gpio_set_irq_enabled_with_callback(INPUT_SYNC_PIN, GPIO_IRQ_EDGE_FALL, true,
                                     &latchInputsCallback);

  irq_set_exclusive_handler(DYN_ALARM_IRQ_NUM, &stepCallback);
  irq_set_exclusive_handler(STEP_DOWN_ALARM_IRQ_NUM, &stepPulseDownCallback);
}