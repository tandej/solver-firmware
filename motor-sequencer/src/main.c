#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/timer.h"
#include "pico/stdlib.h"
#include <stdio.h>

#define DYN_ALARM_NUM 0
#define STEP_DOWN_ALARM_NUM 1

#define TIMER timer_hw

#define DYN_ALARM_IRQ_NUM timer_hardware_alarm_get_irq_num(TIMER, DYN_ALARM_NUM)
#define STEP_DOWN_ALARM_IRQ_NUM                                                \
  timer_hardware_alarm_get_irq_num(TIMER, STEP_DOWN_ALARM_NUM)

const uint INPUT_DIR_PIN = 0;
const uint INPUT_MAG_PIN = 1;
const uint INPUT_MS0_PIN = 2;
const uint INPUT_MS1_PIN = 3;
const uint INPUT_SYNC_PIN = 4;

const uint INPUTS[] = {INPUT_DIR_PIN, INPUT_MAG_PIN, INPUT_MS0_PIN,
                       INPUT_MS1_PIN, INPUT_SYNC_PIN};

const uint OUTPUT_EN1_PIN = 5;
const uint OUTPUT_EN2_PIN = 6;
const uint OUTPUT_EN3_PIN = 7;
const uint OUTPUT_STEP_PIN = 8;
const uint OUTPUT_DIR_PIN = 9;

const uint OUTPUTS[] = {OUTPUT_EN1_PIN, OUTPUT_EN2_PIN, OUTPUT_EN3_PIN,
                        OUTPUT_STEP_PIN, OUTPUT_DIR_PIN};

volatile bool latchedMagnitudeIsFull = true;
volatile bool latchedDirIsPositive = true;
volatile uint latchedMotorSelect = 0b00;

// set all as outputs if `setAsInput` is false, and all as pulled down if
// `pullup` is false
void batchInitGPIOs(const uint pins[], const size_t numIOs, const bool pullup,
                    const bool setAsInput) {
  for (uint i = 0; i < numIOs; i++) {
    gpio_init(pins[i]);
    gpio_set_dir(pins[i], !setAsInput);
    gpio_set_pulls(pins[i], pullup, !pullup);
  }
}

void setIRQEnabled(timer_hw_t *timer, uint irqNum, bool state) {
  if (state) {
    hw_set_bits(&timer->inte, 1 << irqNum);
  } else {
    hw_clear_bits(&timer->inte, 1 << irqNum);
  }
  irq_set_enabled(irqNum, state);
}

void clearIRQ(timer_hw_t *timer, uint irqNum) {
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

int main() {
  stdio_init_all();

  batchInitGPIOs(INPUTS, sizeof(INPUTS), false, true);
  batchInitGPIOs(OUTPUTS, sizeof(OUTPUTS), false, false);

  gpio_set_irq_enabled_with_callback(INPUT_SYNC_PIN, GPIO_IRQ_EDGE_FALL, true,
                                     &latchInputsCallback);

  while (1) {
  };
}