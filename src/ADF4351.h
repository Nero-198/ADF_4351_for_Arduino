/*ADF4351.h
 * author: 	Nemuro
 * Date: 	2025/02/15
 * Version: 	0.1
*/
// This file assumes Little Endian format.

#ifndef ADF4351_H
#define ADF4351_H

#include <stdint.h>

// Error status enumeration
enum ADF4351_Error {
    ADF4351_SUCCESS = 0,
    ADF4351_INVALID_VALUE,
    ADF4351_READ_ERROR
};

class ADF4351
{
private:
    uint8_t reg_init();

protected:
    union adf4351_reg0
    {
        uint32_t reg0_data;

        struct
        {
            uint32_t CONT_BIT: 3;
            uint32_t FRAC: 12;
            uint32_t INT: 16;
            uint32_t RESERVED1: 1;
        } reg0_t;
    };
    union adf4351_reg1
    {
        uint32_t reg1_data;

        struct
        {
            uint32_t CONT_BIT: 3;
            uint32_t MODULUS: 12;
            uint32_t PHASE: 12;
            uint32_t PRESCALER: 1;
            uint32_t PHASE_ADJ: 1;
            uint32_t RESERVED1: 3;
        } reg1_t;
    };
    union adf4351_reg2
    {
        uint32_t reg2_data;

        struct
        {
            uint32_t CONT_BIT: 3;
            uint32_t COUNTER_RESET: 1;
            uint32_t CP_THREE_STATE: 1;
            uint32_t POWER_DOWN: 1;
            uint32_t PD_POLARITY: 1;
            uint32_t LDP: 1;
            uint32_t LDF: 1;
            uint32_t CHARGE_PUMP_CURRENT: 4;
            uint32_t DOUBLE_BUFF: 1;
            uint32_t R_COUNTER: 10;
            uint32_t RDIV2: 1;
            uint32_t REFERENCE_DOUBLER: 1;
            uint32_t MUXOUT:3;
            uint32_t LOW_NOISE_AND_SPUR_MODE: 2;
            uint32_t RESERVED1: 1;
        } reg2_t;
    };
    union adf4351_reg3
    {
        uint32_t reg3_data;

        struct
        {
            uint32_t CONT_BIT: 3;
            uint32_t CLOCK_DIV_VALUE: 12;
            uint32_t CLOCK_DIV_MODE: 2;
            uint32_t RESERVED1: 1;
            uint32_t CSR: 1;
            uint32_t RESERVED2: 2;
            uint32_t CHARGE_CANCEL: 1;
            uint32_t ABP : 1;
            uint32_t BAND_SELECT_CLOCK_MODE: 1;
            uint32_t RESERVED3: 8;
        } reg3_t;
    };
    union adf4351_reg4
    {
        uint32_t reg4_data;

        struct
        {
            uint32_t CONT_BIT: 3;
            uint32_t OUTPUT_POWER: 2;
            uint32_t RF_OUTPUT_ENABLE: 1;
            uint32_t AUX_OUTPUT_POWER: 2;
            uint32_t AUX_OUTPUT_ENABLE: 1;
            uint32_t AUX_OUTPUT_SELECT: 1;
            uint32_t MUTE_TILL_LOCK_DETECT: 1; //"MTLD" on datasheet
            uint32_t VCO_POWER_DOWN: 1;
            uint32_t BAND_SELECT_CLOCK_DIVIDER_VALUE: 8;
            uint32_t RF_DIVIDER_SELECT: 3;
            uint32_t FEEDBACK_SELECT: 1;
            uint32_t RESERVED1: 8;
        } reg4_t;
    };
    union adf4351_reg5
    {
        uint32_t reg5_data;

        struct
        {
            uint32_t CONT_BIT: 3;
            uint32_t RESERVED1: 16;
            uint32_t RESERVED2: 2;
            uint32_t RESERVED3: 1;
            uint32_t LD_PIN_MODE: 2;
            uint32_t RESERVED4: 8;
        } reg5_t;
    };

    adf4351_reg0 reg0;
    adf4351_reg1 reg1;
    adf4351_reg2 reg2;
    adf4351_reg3 reg3;
    adf4351_reg4 reg4;
    adf4351_reg5 reg5;

public:
    ADF4351(/* args */);
    ~ADF4351();

    // Setters
    ADF4351_Error set_FRAC(uint16_t FRAC);
    ADF4351_Error set_INT(uint16_t INT);
    ADF4351_Error set_MODULUS(uint16_t MODULUS);
    ADF4351_Error set_PHASE(uint16_t PHASE);
    ADF4351_Error set_PRESCALER(uint8_t PRESCALER);
    ADF4351_Error set_PHASE_ADJ(uint8_t PHASE_ADJ);
    ADF4351_Error set_COUNTER_RESET(uint8_t COUNTER_RESET);
    ADF4351_Error set_CP_THREE_STATE(uint8_t CP_THREE_STATE);
    ADF4351_Error set_POWER_DOWN(uint8_t POWER_DOWN);
    ADF4351_Error set_PD_POLARITY(uint8_t PD_POLARITY);
    ADF4351_Error set_LDP(uint8_t LDP);
    ADF4351_Error set_LDF(uint8_t LDF);
    ADF4351_Error set_CHARGE_PUMP_CURRENT(uint8_t CHARGE_PUMP_CURRENT);
    ADF4351_Error set_DOUBLE_BUFF(uint8_t DOUBLE_BUFF);
    ADF4351_Error set_R_COUNTER(uint16_t R_COUNTER);
    ADF4351_Error set_RDIV2(uint8_t RDIV2);
    ADF4351_Error set_REFERENCE_DOUBLER(uint8_t REFERENCE_DOUBLER);
    ADF4351_Error set_MUXOUT(uint8_t MUXOUT);
    ADF4351_Error set_LOW_NOISE_AND_SPUR_MODE(uint8_t LOW_NOISE_AND_SPUR_MODE);
    ADF4351_Error set_CLOCK_DIV_VALUE(uint16_t CLOCK_DIV_VALUE);
    ADF4351_Error set_CLOCK_DIV_MODE(uint8_t CLOCK_DIV_MODE);
    ADF4351_Error set_CSR(uint8_t CSR);
    ADF4351_Error set_CHARGE_CANCEL(uint8_t CHARGE_CANCEL);
    ADF4351_Error set_ABP(uint8_t ABP);
    ADF4351_Error set_BAND_SELECT_CLOCK_MODE(uint8_t BAND_SELECT_CLOCK_MODE);
    ADF4351_Error set_OUTPUT_POWER(uint8_t OUTPUT_POWER);
    ADF4351_Error set_RF_OUTPUT_ENABLE(uint8_t RF_OUTPUT_ENABLE);
    ADF4351_Error set_AUX_OUTPUT_POWER(uint8_t AUX_OUTPUT_POWER);
    ADF4351_Error set_AUX_OUTPUT_ENABLE(uint8_t AUX_OUTPUT_ENABLE);
    ADF4351_Error set_AUX_OUTPUT_SELECT(uint8_t AUX_OUTPUT_SELECT);
    ADF4351_Error set_MUTE_TILL_LOCK_DETECT(uint8_t MUTE_TILL_LOCK_DETECT);
    ADF4351_Error set_VCO_POWER_DOWN(uint8_t VCO_POWER_DOWN);
    ADF4351_Error set_BAND_SELECT_CLOCK_DIVIDER_VALUE(uint8_t BAND_SELECT_CLOCK_DIVIDER_VALUE);
    ADF4351_Error set_RF_DIVIDER_SELECT(uint8_t RF_DIVIDER_SELECT);
    ADF4351_Error set_FEEDBACK_SELECT(uint8_t FEEDBACK_SELECT);
    ADF4351_Error set_LD_PIN_MODE(uint8_t LD_PIN_MODE);
    // Getters
    ADF4351_Error get_FRAC(uint16_t *FRAC);
    ADF4351_Error get_INT(uint16_t *INT);
    ADF4351_Error get_MODULUS(uint16_t *MODULUS);
    ADF4351_Error get_PHASE(uint16_t *PHASE);
    ADF4351_Error get_PRESCALER(uint8_t *PRESCALER);
    ADF4351_Error get_PHASE_ADJ(uint8_t *PHASE_ADJ);
    ADF4351_Error get_COUNTER_RESET(uint8_t *COUNTER_RESET);
    ADF4351_Error get_CP_THREE_STATE(uint8_t *CP_THREE_STATE);
    ADF4351_Error get_POWER_DOWN(uint8_t *POWER_DOWN);
    ADF4351_Error get_PD_POLARITY(uint8_t *PD_POLARITY);
    ADF4351_Error get_LDP(uint8_t *LDP);
    ADF4351_Error get_LDF(uint8_t *LDF);
    ADF4351_Error get_CHARGE_PUMP_CURRENT(uint8_t *CHARGE_PUMP_CURRENT);
    ADF4351_Error get_DOUBLE_BUFF(uint8_t *DOUBLE_BUFF);
    ADF4351_Error get_R_COUNTER(uint16_t *R_COUNTER);
    ADF4351_Error get_RDIV2(uint8_t *RDIV2);
    ADF4351_Error get_REFERENCE_DOUBLER(uint8_t *REFERENCE_DOUBLER);
    ADF4351_Error get_MUXOUT(uint8_t *MUXOUT);
    ADF4351_Error get_LOW_NOISE_AND_SPUR_MODE(uint8_t *LOW_NOISE_AND_SPUR_MODE);
    ADF4351_Error get_CLOCK_DIV_VALUE(uint16_t *CLOCK_DIV_VALUE);
    ADF4351_Error get_CLOCK_DIV_MODE(uint8_t *CLOCK_DIV_MODE);
    ADF4351_Error get_CSR(uint8_t *CSR);
    ADF4351_Error get_CHARGE_CANCEL(uint8_t *CHARGE_CANCEL);
    ADF4351_Error get_ABP(uint8_t *ABP);
    ADF4351_Error get_BAND_SELECT_CLOCK_MODE(uint8_t *BAND_SELECT_CLOCK_MODE);
    ADF4351_Error get_OUTPUT_POWER(uint8_t *OUTPUT_POWER);
    ADF4351_Error get_RF_OUTPUT_ENABLE(uint8_t *RF_OUTPUT_ENABLE);
    ADF4351_Error get_AUX_OUTPUT_POWER(uint8_t *AUX_OUTPUT_POWER);
    ADF4351_Error get_AUX_OUTPUT_ENABLE(uint8_t *AUX_OUTPUT_ENABLE);
    ADF4351_Error get_AUX_OUTPUT_SELECT(uint8_t *AUX_OUTPUT_SELECT);
    ADF4351_Error get_MUTE_TILL_LOCK_DETECT(uint8_t *MUTE_TILL_LOCK_DETECT);
    ADF4351_Error get_VCO_POWER_DOWN(uint8_t *VCO_POWER_DOWN);
    ADF4351_Error get_BAND_SELECT_CLOCK_DIVIDER_VALUE(uint8_t *BAND_SELECT_CLOCK_DIVIDER_VALUE);
    ADF4351_Error get_RF_DIVIDER_SELECT(uint8_t *RF_DIVIDER_SELECT);
    ADF4351_Error get_FEEDBACK_SELECT(uint8_t *FEEDBACK_SELECT);
    ADF4351_Error get_LD_PIN_MODE(uint8_t *LD_PIN_MODE);

    ADF4351_Error update();


};

#endif // ADF4351_H