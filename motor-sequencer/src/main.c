#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const uint INPUT_DIR_PIN = 0;
const uint INPUT_MAG_PIN = 1;
const uint INPUT_MS0_PIN = 2;
const uint INPUT_MS1_PIN = 3;
const uint INPUT_SYNC_PIN = 4;

const uint OUTPUT_EN0_PIN = 5;
const uint OUTPUT_EN1_PIN = 6;
const uint OUTPUT_EN2_PIN = 7;
const uint OUTPUT_STEP_PIN = 8;
const uint OUTPUT_DIR_PIN = 9;

// set all as outputs if `setAsInput` is false, and all as pulled down if
// `pullup` is false
void batchInitGPIOs(uint pins[], size_t numIOs, bool pullup, bool setAsInput) {
  for (uint i = 0; i < numIOs; i++) {
    gpio_init(pins[i]);
    gpio_set_dir(pins[i], !setAsInput);
    gpio_set_pulls(pins[i], pullup, !pullup);
  }
}

int main() {
  stdio_init_all();

  batchInitGPIOs((uint[]){INPUT_DIR_PIN, INPUT_MAG_PIN, INPUT_MS0_PIN,
                          INPUT_MS1_PIN, INPUT_SYNC_PIN},
                 5, false, true);
  batchInitGPIOs((uint[]){OUTPUT_EN0_PIN, OUTPUT_EN1_PIN, OUTPUT_EN2_PIN,
                          OUTPUT_STEP_PIN, OUTPUT_DIR_PIN},
                 5, false, false);

  printf("Hello, world!\n");
  return 0;
}