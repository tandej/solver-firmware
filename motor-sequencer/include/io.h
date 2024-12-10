#pragma once

#include "hardware/gpio.h"

#define INPUT_DIR_PIN (uint8_t)0
#define INPUT_MAG_PIN (uint8_t)1
#define INPUT_MS0_PIN (uint8_t)2
#define INPUT_MS1_PIN (uint8_t)3
#define INPUT_SYNC_PIN (uint8_t)4

#define INPUTS                                                                 \
  (uint8_t[]) {                                                                \
    INPUT_DIR_PIN, INPUT_MAG_PIN, INPUT_MS0_PIN, INPUT_MS1_PIN, INPUT_SYNC_PIN \
  }

#define OUTPUT_EN1_PIN (uint8_t)5
#define OUTPUT_EN2_PIN (uint8_t)6
#define OUTPUT_EN3_PIN (uint8_t)7
#define OUTPUT_STEP_PIN (uint8_t)8
#define OUTPUT_DIR_PIN (uint8_t)9

#define OUTPUTS                                                                \
  (uint8_t[]) {                                                                \
    OUTPUT_EN1_PIN, OUTPUT_EN2_PIN, OUTPUT_EN3_PIN, OUTPUT_STEP_PIN,           \
        OUTPUT_DIR_PIN                                                         \
  }

void batchInitGPIOs(const uint8_t pins[], const size_t numIOs,
                    const bool pullup, const bool setAsInput);

void initAllGPIOs();