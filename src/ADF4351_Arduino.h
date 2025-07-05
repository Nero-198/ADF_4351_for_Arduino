/*ADF4351_Arduino.h
 *Author: Nemuro
 *Date: 2025/02/16
 *Version: 0.1
*/

#ifndef ADF4351_ARDUINO_H
#define ADF4351_ARDUINO_H

#include "ADF4351.h"
#include <stdint.h>
#include <Arduino.h>
#include <SPI.h>

enum ADF4351_Write_Error
{
    ADF4351_WRITE_SUCCESS = 0,
    ADF4351_WRITE_ERROR
};

class ADF4351_Arduino : public ADF4351
{
private:
    pin_size_t pin_DATA;
    pin_size_t pin_MUXOUT;
    pin_size_t pin_PDBRF;
    pin_size_t pin_CE;
    pin_size_t pin_LE;
    pin_size_t pin_CLK;
    pin_size_t pin_LD;

public:
    // SPIClass* spiを削除
    ADF4351_Arduino(pin_size_t pin_DATA, pin_size_t pin_MUXOUT, pin_size_t pin_PDBRF, pin_size_t pin_CE, pin_size_t pin_LE, pin_size_t pin_CLK, pin_size_t pin_LD);
    ~ADF4351_Arduino();

    // デバイス有効化/無効化
    void set_CE();
    void unset_CE();
    //PDBRF RF出力の有効化/無効化
    void set_PDBRF();
    void unset_PDBRF();

    ADF4351_Write_Error output_func(uint32_t data);

    // writer register functions
    ADF4351_Write_Error write_reg0();
    ADF4351_Write_Error write_reg1();
    ADF4351_Write_Error write_reg2();
    ADF4351_Write_Error write_reg3();
    ADF4351_Write_Error write_reg4();
    ADF4351_Write_Error write_reg5();

    //setter functions but with with write_regX() functions
    ADF4351_Write_Error write_FRAC(uint16_t FRAC);
    ADF4351_Write_Error write_INT(uint16_t INT);
    ADF4351_Write_Error write_MODULUS(uint16_t MODULUS);
    ADF4351_Write_Error write_PHASE(uint16_t PHASE);
    ADF4351_Write_Error write_PRESCALER(uint8_t PRESCALER);
    ADF4351_Write_Error write_PHASE_ADJ(uint8_t PHASE_ADJ);
    ADF4351_Write_Error write_COUNTER_RESET(uint8_t COUNTER_RESET);
    ADF4351_Write_Error write_CP_THREE_STATE(uint8_t CP_THREE_STATE);
    ADF4351_Write_Error write_POWER_DOWN(uint8_t POWER_DOWN);
    ADF4351_Write_Error write_PD_POLARITY(uint8_t PD_POLARITY);
    ADF4351_Write_Error write_LDP(uint8_t LDP);
    ADF4351_Write_Error write_LDF(uint8_t LDF);
    ADF4351_Write_Error write_CHARGE_PUMP_CURRENT(uint8_t CHARGE_PUMP_CURRENT);
    ADF4351_Write_Error write_DOUBLE_BUFF(uint8_t DOUBLE_BUFF);
    ADF4351_Write_Error write_R_COUNTER(uint16_t R_COUNTER);
    ADF4351_Write_Error write_RDIV2(uint8_t RDIV2);
    ADF4351_Write_Error write_REFERENCE_DOUBLER(uint8_t REFERENCE_DOUBLER);
    ADF4351_Write_Error write_MUXOUT(uint8_t MUXOUT);
    ADF4351_Write_Error write_LOW_NOISE_AND_SPUR_MODE(uint8_t LOW_NOISE_AND_SPUR_MODE);
    ADF4351_Write_Error write_CLOCK_DIV_VALUE(uint16_t CLOCK_DIV_VALUE);
    ADF4351_Write_Error write_CLOCK_DIV_MODE(uint8_t CLOCK_DIV_MODE);
    ADF4351_Write_Error write_CSR(uint8_t CSR);
    ADF4351_Write_Error write_CHARGE_CANCEL(uint8_t CHARGE_CANCEL);
    ADF4351_Write_Error write_ABP(uint8_t ABP);
    ADF4351_Write_Error write_BAND_SELECT_CLOCK_MODE(uint8_t BAND_SELECT_CLOCK_MODE);
    ADF4351_Write_Error write_OUTPUT_POWER(uint8_t OUTPUT_POWER);
    ADF4351_Write_Error write_RF_OUTPUT_ENABLE(uint8_t RF_OUTPUT_ENABLE);
    ADF4351_Write_Error write_AUX_OUTPUT_POWER(uint8_t AUX_OUTPUT_POWER);
    ADF4351_Write_Error write_AUX_OUTPUT_ENABLE(uint8_t AUX_OUTPUT_ENABLE);
    ADF4351_Write_Error write_AUX_OUTPUT_SELECT(uint8_t AUX_OUTPUT_SELECT);
    ADF4351_Write_Error write_MUTE_TILL_LOCK_DETECT(uint8_t MUTE_TILL_LOCK_DETECT);
    ADF4351_Write_Error write_VCO_POWER_DOWN(uint8_t VCO_POWER_DOWN);
    ADF4351_Write_Error write_BAND_SELECT_CLOCK_DIVIDER_VALUE(uint8_t BAND_SELECT_CLOCK_DIVIDER_VALUE);
    ADF4351_Write_Error write_RF_DIVIDER_SELECT(uint8_t RF_DIVIDER_SELECT);
    ADF4351_Write_Error write_FEEDBACK_SELECT(uint8_t FEEDBACK_SELECT);
    ADF4351_Write_Error write_LD_PIN_MODE(uint8_t LD_PIN_MODE);
};

#endif // ADF4351_ARDUINO_H
