/*ADF4351_Arduino.cpp
 *Author: Nemuro
 *Date: 2025/02/16
 *Version: 0.1
*/

#include "ADF4351_Arduino.h"
#include <SPI.h>

/**
 * @brief Construct a new adf4351 arduino::adf4351 arduino object
 * 
 * @param pin_DATA 
 * @param MUXOUT 
 * @param pin_PDBRF 
 * @param pin_CE 
 * @param pin_LE 
 * @param pin_CLK 
 * @param pin_LD 
 */
ADF4351_Arduino::ADF4351_Arduino(pin_size_t DATA_pin, pin_size_t MUXOUT_pin, pin_size_t PDBRF_pin, pin_size_t CE_pin, pin_size_t LE_pin, pin_size_t CLK_pin, pin_size_t LD_pin)
    : pin_DATA(DATA_pin), pin_MUXOUT(MUXOUT_pin), pin_PDBRF(PDBRF_pin), pin_CE(CE_pin), pin_LE(LE_pin), pin_CLK(CLK_pin), pin_LD(LD_pin)
{
    pinMode(pin_DATA, OUTPUT);
    pinMode(pin_MUXOUT, INPUT);
    pinMode(pin_PDBRF, OUTPUT);
    pinMode(pin_CE, OUTPUT);
    pinMode(pin_LE, OUTPUT);
    pinMode(pin_CLK, OUTPUT);
    pinMode(pin_LD, INPUT);
}

ADF4351_Arduino::~ADF4351_Arduino()
{
}

void ADF4351_Arduino::enable()
{
    digitalWrite(pin_CE, HIGH);
}

void ADF4351_Arduino::disable()
{
    digitalWrite(pin_CE, LOW);
}

//Write function for Arduino
ADF4351_Write_Error ADF4351_Arduino::reg_write_func(uint32_t data)
{
    digitalWrite(pin_LE, LOW); // LEをLOWに

    // 32ビットをMSBファーストでDATAピンに出力
    for (int i = 31; i >= 0; --i) {
        digitalWrite(pin_CLK, LOW);
        digitalWrite(pin_DATA, (data >> i) & 0x01);
        delayMicroseconds(1); // 必要に応じて調整
        digitalWrite(pin_CLK, HIGH);
        delayMicroseconds(1); // 必要に応じて調整
    }

    digitalWrite(pin_LE, HIGH); // LEをHIGHに

    return ADF4351_WRITE_SUCCESS;
}

ADF4351_Write_Error ADF4351_Arduino::write_reg0()
{
    reg0.reg0_t.CONT_BIT = 0x00;

    // LSB 3 ビットが 000 であることを確認
    if ((reg0.reg0_data & 0x07) != 0x00) {
        return ADF4351_WRITE_ERROR;
    }
    
    return reg_write_func(reg0.reg0_data);
}

ADF4351_Write_Error ADF4351_Arduino::write_reg1()
{
    reg1.reg1_t.CONT_BIT = 0x01;
    if ((reg1.reg1_data & 0x00000007) != 0x01)
    {
        reg1.reg1_t.CONT_BIT = 0x01;
        return ADF4351_WRITE_ERROR;
    }
    return reg_write_func(reg1.reg1_data);
}

ADF4351_Write_Error ADF4351_Arduino::write_reg2()
{
    reg2.reg2_t.CONT_BIT = 0x02;
    if ((reg2.reg2_data & 0x00000007) != 0x02)
    {
        reg2.reg2_t.CONT_BIT = 0x02;
        return ADF4351_WRITE_ERROR;
    }
    return reg_write_func(reg2.reg2_data);
}

ADF4351_Write_Error ADF4351_Arduino::write_reg3()
{
    reg3.reg3_t.CONT_BIT = 0x03;
    if ((reg3.reg3_data & 0x00000007) != 0x03)
    {
        reg3.reg3_t.CONT_BIT = 0x03;
        return ADF4351_WRITE_ERROR;
    }
    return reg_write_func(reg3.reg3_data);
}

ADF4351_Write_Error ADF4351_Arduino::write_reg4()
{
    reg4.reg4_t.CONT_BIT = 0x04;
    if ((reg4.reg4_data & 0x00000007) != 0x04)
    {
        reg4.reg4_t.CONT_BIT = 0x04;
        return ADF4351_WRITE_ERROR;
    }
    return reg_write_func(reg4.reg4_data);
}

ADF4351_Write_Error ADF4351_Arduino::write_reg5()
{
    reg5.reg5_t.CONT_BIT = 0x05;
    if ((reg5.reg5_data & 0x00000007) != 0x05)
    {
        reg5.reg5_t.CONT_BIT = 0x05;
        return ADF4351_WRITE_ERROR;
    }
    return reg_write_func(reg5.reg5_data);
}



ADF4351_Write_Error ADF4351_Arduino::write_FRAC(uint16_t FRAC) {
    if (set_FRAC(FRAC) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg0();
}

ADF4351_Write_Error ADF4351_Arduino::write_INT(uint16_t INT) {
    if (set_INT(INT) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg0();
}



ADF4351_Write_Error ADF4351_Arduino::write_MODULUS(uint16_t MODULUS) {
    if (set_MODULUS(MODULUS) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg1();
}

ADF4351_Write_Error ADF4351_Arduino::write_PHASE(uint16_t PHASE) {
    if (set_PHASE(PHASE) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg1();
}

ADF4351_Write_Error ADF4351_Arduino::write_PRESCALER(uint8_t PRESCALER) {
    if (set_PRESCALER(PRESCALER) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg1();
}

ADF4351_Write_Error ADF4351_Arduino::write_PHASE_ADJ(uint8_t PHASE_ADJ) {
    if (set_PHASE_ADJ(PHASE_ADJ) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg1();
}

ADF4351_Write_Error ADF4351_Arduino::write_COUNTER_RESET(uint8_t COUNTER_RESET) {
    if (set_COUNTER_RESET(COUNTER_RESET) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg2();
}

ADF4351_Write_Error ADF4351_Arduino::write_CP_THREE_STATE(uint8_t CP_THREE_STATE) {
    if (set_CP_THREE_STATE(CP_THREE_STATE) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg2();
}

ADF4351_Write_Error ADF4351_Arduino::write_POWER_DOWN(uint8_t POWER_DOWN) {
    if (set_POWER_DOWN(POWER_DOWN) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg2();
}

ADF4351_Write_Error ADF4351_Arduino::write_PD_POLARITY(uint8_t PD_POLARITY) {
    if (set_PD_POLARITY(PD_POLARITY) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg2();
}

ADF4351_Write_Error ADF4351_Arduino::write_LDP(uint8_t LDP) {
    if (set_LDP(LDP) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg2();
}

ADF4351_Write_Error ADF4351_Arduino::write_LDF(uint8_t LDF) {
    if (set_LDF(LDF) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg2();
}

ADF4351_Write_Error ADF4351_Arduino::write_CHARGE_PUMP_CURRENT(uint8_t CHARGE_PUMP_CURRENT) {
    if (set_CHARGE_PUMP_CURRENT(CHARGE_PUMP_CURRENT) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg2();
}

ADF4351_Write_Error ADF4351_Arduino::write_DOUBLE_BUFF(uint8_t DOUBLE_BUFF) {
    if (set_DOUBLE_BUFF(DOUBLE_BUFF) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg2();
}

ADF4351_Write_Error ADF4351_Arduino::write_R_COUNTER(uint16_t R_COUNTER) {
    if (set_R_COUNTER(R_COUNTER) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg2();
}

ADF4351_Write_Error ADF4351_Arduino::write_RDIV2(uint8_t RDIV2) {
    if (set_RDIV2(RDIV2) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg2();
}

ADF4351_Write_Error ADF4351_Arduino::write_REFERENCE_DOUBLER(uint8_t REFERENCE_DOUBLER) {
    if (set_REFERENCE_DOUBLER(REFERENCE_DOUBLER) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg2();
}

ADF4351_Write_Error ADF4351_Arduino::write_MUXOUT(uint8_t MUXOUT) {
    if (set_MUXOUT(MUXOUT) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg2();
}

ADF4351_Write_Error ADF4351_Arduino::write_LOW_NOISE_AND_SPUR_MODE(uint8_t LOW_NOISE_AND_SPUR_MODE) {
    if (set_LOW_NOISE_AND_SPUR_MODE(LOW_NOISE_AND_SPUR_MODE) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg2();
}

ADF4351_Write_Error ADF4351_Arduino::write_CLOCK_DIV_VALUE(uint16_t CLOCK_DIV_VALUE) {
    if (set_CLOCK_DIV_VALUE(CLOCK_DIV_VALUE) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg3();
}

ADF4351_Write_Error ADF4351_Arduino::write_CLOCK_DIV_MODE(uint8_t CLOCK_DIV_MODE) {
    if (set_CLOCK_DIV_MODE(CLOCK_DIV_MODE) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg3();
}

ADF4351_Write_Error ADF4351_Arduino::write_CSR(uint8_t CSR) {
    if (set_CSR(CSR) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg3();
}

ADF4351_Write_Error ADF4351_Arduino::write_CHARGE_CANCEL(uint8_t CHARGE_CANCEL) {
    if (set_CHARGE_CANCEL(CHARGE_CANCEL) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg3();
}

ADF4351_Write_Error ADF4351_Arduino::write_ABP(uint8_t ABP) {
    if (set_ABP(ABP) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg3();
}

ADF4351_Write_Error ADF4351_Arduino::write_BAND_SELECT_CLOCK_MODE(uint8_t BAND_SELECT_CLOCK_MODE) {
    if (set_BAND_SELECT_CLOCK_MODE(BAND_SELECT_CLOCK_MODE) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg3();
}

ADF4351_Write_Error ADF4351_Arduino::write_OUTPUT_POWER(uint8_t OUTPUT_POWER) {
    if (set_OUTPUT_POWER(OUTPUT_POWER) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg4();
}

ADF4351_Write_Error ADF4351_Arduino::write_RF_OUTPUT_ENABLE(uint8_t RF_OUTPUT_ENABLE) {
    if (set_RF_OUTPUT_ENABLE(RF_OUTPUT_ENABLE) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg4();
}

ADF4351_Write_Error ADF4351_Arduino::write_AUX_OUTPUT_POWER(uint8_t AUX_OUTPUT_POWER) {
    if (set_AUX_OUTPUT_POWER(AUX_OUTPUT_POWER) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg4();
}

ADF4351_Write_Error ADF4351_Arduino::write_AUX_OUTPUT_ENABLE(uint8_t AUX_OUTPUT_ENABLE) {
    if (set_AUX_OUTPUT_ENABLE(AUX_OUTPUT_ENABLE) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg4();
}

ADF4351_Write_Error ADF4351_Arduino::write_AUX_OUTPUT_SELECT(uint8_t AUX_OUTPUT_SELECT) {
    if (set_AUX_OUTPUT_SELECT(AUX_OUTPUT_SELECT) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg4();
}

ADF4351_Write_Error ADF4351_Arduino::write_MUTE_TILL_LOCK_DETECT(uint8_t MUTE_TILL_LOCK_DETECT) {
    if (set_MUTE_TILL_LOCK_DETECT(MUTE_TILL_LOCK_DETECT) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg4();
}

ADF4351_Write_Error ADF4351_Arduino::write_VCO_POWER_DOWN(uint8_t VCO_POWER_DOWN) {
    if (set_VCO_POWER_DOWN(VCO_POWER_DOWN) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg4();
}

ADF4351_Write_Error ADF4351_Arduino::write_BAND_SELECT_CLOCK_DIVIDER_VALUE(uint8_t BAND_SELECT_CLOCK_DIVIDER_VALUE) {
    if (set_BAND_SELECT_CLOCK_DIVIDER_VALUE(BAND_SELECT_CLOCK_DIVIDER_VALUE) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg4();
}

ADF4351_Write_Error ADF4351_Arduino::write_RF_DIVIDER_SELECT(uint8_t RF_DIVIDER_SELECT) {
    if (set_RF_DIVIDER_SELECT(RF_DIVIDER_SELECT) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg4();
}

ADF4351_Write_Error ADF4351_Arduino::write_FEEDBACK_SELECT(uint8_t FEEDBACK_SELECT) {
    if (set_FEEDBACK_SELECT(FEEDBACK_SELECT) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg4();
}

ADF4351_Write_Error ADF4351_Arduino::write_LD_PIN_MODE(uint8_t LD_PIN_MODE) {
    if (set_LD_PIN_MODE(LD_PIN_MODE) != ADF4351_SUCCESS) 
    {
        return ADF4351_WRITE_ERROR;
    }
    return write_reg5();
}
