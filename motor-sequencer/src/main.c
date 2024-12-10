#include "hardware/gpio.h"
#include "pico/stdlib.h"

#include "interrupts.h"
#include "io.h"

#include <stdio.h>

volatile uint8_t stepIndex = 0;

// returns whether the value referenced by the pointer `deltaTimeUS` is
// valid. A `false` should be interpreted as the end of a step sequence.
bool sampleStep(const bool isFullMagnitude, uint8_t *deltaTimeUS) {
  *deltaTimeUS = 0;

  // TODO
  return false;
}

int main() {
  stdio_init_all();

  initAllGPIOs();

  initInterrupts();

  while (true)
    ;
}