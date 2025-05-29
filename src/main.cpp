#include <Arduino.h>
#include "ADF4351_Arduino.h"
#include "CommandHandler.h"

#define DATA_PIN 31
#define MUXOUT_PIN 27
#define PDBRF_PIN 25
#define CE_PIN 34
#define LE_PIN 32
#define CLK_PIN 29
#define LD_PIN 26

ADF4351_Arduino adf4351(DATA_PIN, MUXOUT_PIN, PDBRF_PIN, CE_PIN, LE_PIN, CLK_PIN, LD_PIN);
CommandHandler cmdHandler(adf4351);

void setup() {
  Serial.begin(9600);
  Serial.println("ADF4351 Test Start");

  adf4351.enable(); // デバイス有効化
delay(1000); // デバイスが安定するまで待機

/*
  // SPIの初期化
  SPI.begin();
  SPI.setDataMode(SPI_MODE0); // CPOL=0, CPHA=0
  SPI.setBitOrder(MSBFIRST); // MSBファースト
  SPI.setClockDivider(SPI_CLOCK_DIV8); // クロック分周比を設定（必要に応じて調整）
*/

  // ADF4351の初期化
  adf4351.output_func(0x00000000); // 初期状態で全てのレジスタをクリア
  delay(10);

//初期化
adf4351.write_INT(48); // INT値を48に設定
adf4351.write_FRAC(200); // FRAC値を200に設定
adf4351.write_MODULUS(2500); // MODULUS値を1000に設定
adf4351.write_REFERENCE_DOUBLER(0); // 参照倍増器を無効化
adf4351.write_R_COUNTER(1); // Rカウンタを1に設定
adf4351.write_RDIV2(0); // RDIV2を無効化

}

void loop() {
  static String inputString = "";
  static bool stringComplete = false;

  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n' || inChar == '\r') {
      if (inputString.length() > 0) {
        stringComplete = true;
      }
    } else {
      inputString += inChar;
    }
  }

  if (stringComplete) {
    cmdHandler.handleCommand(inputString);
    inputString = "";
    stringComplete = false;
  }
}
