#pragma once

#include "hardware/gpio.h"

#define INPUT_DIR_PIN 0
#define INPUT_MAG_PIN 1
#define INPUT_MS0_PIN 2
#define INPUT_MS1_PIN 3
#define INPUT_SYNC_PIN 4

#define INPUTS                                                                 \
  (uint8_t[]) {                                                                \
    INPUT_DIR_PIN, INPUT_MAG_PIN, INPUT_MS0_PIN, INPUT_MS1_PIN, INPUT_SYNC_PIN \
  }

#define OUTPUT_EN1_PIN 5
#define OUTPUT_EN2_PIN 6
#define OUTPUT_EN3_PIN 7
#define OUTPUT_STEP_PIN 8
#define OUTPUT_DIR_PIN 9

#define OUTPUTS                                                                \
  (uint8_t[]) {                                                                \
    OUTPUT_EN1_PIN, OUTPUT_EN2_PIN, OUTPUT_EN3_PIN, OUTPUT_STEP_PIN,           \
        OUTPUT_DIR_PIN                                                         \
  }

void batchInitGPIOs(const uint8_t pins[], const size_t numIOs,
                    const bool pullup, const bool setAsInput);

void initAllGPIOs();