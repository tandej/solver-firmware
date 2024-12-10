#include "io.h"

// set all as outputs if `setAsInput` is false, and all as pulled down if
// `pullup` is false
void batchInitGPIOs(const uint8_t pins[], const size_t numIOs,
                    const bool pullup, const bool setAsInput) {
  for (uint8_t i = 0; i < numIOs; i++) {
    gpio_init(pins[i]);
    gpio_set_dir(pins[i], !setAsInput);
    gpio_set_pulls(pins[i], pullup, !pullup);
  }
}

void initAllGPIOs() {
  batchInitGPIOs(INPUTS, sizeof(INPUTS), false, true);
  batchInitGPIOs(OUTPUTS, sizeof(OUTPUTS), false, false);
}