#include <Arduino.h>
#include "ADF4351_Arduino.h"

#define DATA_PIN 1
#define MUXOUT_PIN 2
#define PDBRF_PIN 3
#define CE_PIN 4
#define LE_PIN 5
#define CLK_PIN 6
#define LD_PIN 7


ADF4351_Arduino adf4351(DATA_PIN, MUXOUT_PIN, PDBRF_PIN, CE_PIN, LE_PIN, CLK_PIN, LD_PIN);


void setup() {
  Serial.begin(9600);
  Serial.println("ADF4351 Test Start");

  // レジスタの初期化
  if (adf4351.write_INT(75) != ADF4351_WRITE_SUCCESS) {
    Serial.println("Failed to write INT");
  } else {
    Serial.println("INT written successfully");
  }

  if (adf4351.write_FRAC(0x123) != ADF4351_WRITE_SUCCESS) {
    Serial.println("Failed to write FRAC");
  } else {
    Serial.println("FRAC written successfully");
  }

  if (adf4351.write_MODULUS(0xFFF) != ADF4351_WRITE_SUCCESS) {
    Serial.println("Failed to write MODULUS");
  } else {
    Serial.println("MODULUS written successfully");
  }
}

void loop() {
  // 繰り返し処理はここに記述
}