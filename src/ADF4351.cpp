/*ADF4351.cpp
 *author: 	Nemuro
 *Date: 	2025/02/15
 *Version: 	0.1
 */

#include "ADF4351.h"

ADF4351::ADF4351(/* args */)
{
    ADF4351::reg_init();
}

ADF4351::~ADF4351()
{
}

//ADF4351 register initialization
uint8_t ADF4351::reg_init()
{
    reg0.reg0_t.CONT_BIT = 0x00;
    reg0.reg0_t.FRAC = 0x000;
    reg0.reg0_t.INT = 0x004B; //75
    reg0.reg0_t.RESERVED1 = 0x00;

    reg1.reg1_t.CONT_BIT = 0x01;
    reg1.reg1_t.MODULUS = 0x002;
    reg1.reg1_t.PHASE = 0x001;
    reg1.reg1_t.PRESCALER = 0x0;
    reg1.reg1_t.PHASE_ADJ = 0x0;
    reg1.reg1_t.RESERVED1 = 0x0;

    reg2.reg2_t.CONT_BIT = 0x02;
    reg2.reg2_t.COUNTER_RESET = 0x0;
    reg2.reg2_t.CP_THREE_STATE = 0x0;
    reg2.reg2_t.POWER_DOWN = 0x0;
    reg2.reg2_t.PD_POLARITY = 0x0; //Negative polarity if //これどっちだろう
    reg2.reg2_t.LDP = 0x1;        //intejer-N mode
    reg2.reg2_t.LDF = 0x1;        //Fractional-N mode
    reg2.reg2_t.CHARGE_PUMP_CURRENT = 0x00;
    reg2.reg2_t.DOUBLE_BUFF = 0x0;
    reg2.reg2_t.R_COUNTER = 0x001;
    reg2.reg2_t.RDIV2 = 0x0;
    reg2.reg2_t.REFERENCE_DOUBLER = 0x0;
    reg2.reg2_t.MUXOUT = 0x0;
    reg2.reg2_t.LOW_NOISE_AND_SPUR_MODE = 0x0;
    reg2.reg2_t.RESERVED1 = 0x0;

    reg3.reg3_t.CONT_BIT = 0x03;
    reg3.reg3_t.CLOCK_DIV_VALUE = 0x000;
    reg3.reg3_t.CLOCK_DIV_MODE = 0x0;
    reg3.reg3_t.CSR = 0x0;
    reg3.reg3_t.CHARGE_CANCEL = 0x0;
    reg3.reg3_t.ABP = 0x1;
    reg3.reg3_t.BAND_SELECT_CLOCK_MODE = 0x1;
    reg3.reg3_t.RESERVED1 = 0x00;

    reg4.reg4_t.CONT_BIT = 0x04;
    reg4.reg4_t.OUTPUT_POWER = 0x1;
    reg4.reg4_t.RF_OUTPUT_ENABLE = 0x1;
    reg4.reg4_t.AUX_OUTPUT_POWER = 0x1;
    reg4.reg4_t.AUX_OUTPUT_ENABLE = 0x0;
    reg4.reg4_t.AUX_OUTPUT_SELECT = 0x0;
    reg4.reg4_t.MUTE_TILL_LOCK_DETECT = 0x0;
    reg4.reg4_t.VCO_POWER_DOWN = 0x0;
    reg4.reg4_t.BAND_SELECT_CLOCK_DIVIDER_VALUE = 0x0;
    reg4.reg4_t.RF_DIVIDER_SELECT = 0x0;
    reg4.reg4_t.FEEDBACK_SELECT = 0x0;
    reg4.reg4_t.RESERVED1 = 0x00;

    reg5.reg5_t.CONT_BIT = 0x05;
    reg5.reg5_t.RESERVED1 = 0x00;
    reg5.reg5_t.RESERVED2 = 0x00;
    reg5.reg5_t.RESERVED3 = 0x00;
    reg5.reg5_t.LD_PIN_MODE = 0x0;
    reg5.reg5_t.RESERVED4 = 0x00;

    return 0;
}


// Setters
ADF4351_Error ADF4351::set_FRAC(uint16_t FRAC) {
    if (FRAC > 0xFFF) return ADF4351_INVALID_VALUE;
    reg0.reg0_t.FRAC = FRAC;
    return ADF4351_SUCCESS;
}

/**
 * @brief set INT value
 * 
 * @param INT 
 * @return ADF4351_Error 
 * @details range is depends on the prescaler value
 * @details if prescaler is 0(4/5), INT range is 23-65535
 * @details if prescaler is 1(8/9), INT range is 75-65535
 */
ADF4351_Error ADF4351::set_INT(uint16_t INT) {
    if (INT > 0xFFFF) return ADF4351_INVALID_VALUE;
    if (reg1.reg1_t.PRESCALER == 0)
    {
        if (INT < 23) return ADF4351_INVALID_VALUE;
    }
    else
    {
        if (INT < 75) return ADF4351_INVALID_VALUE;
    }
    reg0.reg0_t.INT = INT;
    return ADF4351_SUCCESS;
}

/**
 * @brief set MODULUS value
 * 
 * @param MODULUS 
 * @return ADF4351_Error 
 * @details range is 2-4095
 */
ADF4351_Error ADF4351::set_MODULUS(uint16_t MODULUS) {
    if (MODULUS > 0xFFF) return ADF4351_INVALID_VALUE;
    if (MODULUS < 2) return ADF4351_INVALID_VALUE;
    reg1.reg1_t.MODULUS = MODULUS;
    return ADF4351_SUCCESS;
}

/**
 * @brief  
 * 
 * @param PHASE 
 * @return ADF4351_Error 
 * @details range is 0-4095
 * @details recommended value is 1
 */
ADF4351_Error ADF4351::set_PHASE(uint16_t PHASE) {
    if (PHASE > 0xFFF) return ADF4351_INVALID_VALUE;
    reg1.reg1_t.PHASE = PHASE;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param PRESCALER 
 * @return ADF4351_Error 
 * @details 0: 4/5, 1: 8/9
 */
ADF4351_Error ADF4351::set_PRESCALER(uint8_t PRESCALER) {
    if (PRESCALER > 1) return ADF4351_INVALID_VALUE;
    reg1.reg1_t.PRESCALER = PRESCALER;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param PHASE_ADJ 
 * @return ADF4351_Error 
 * @details 0: disabled, 1: enabled
 */
ADF4351_Error ADF4351::set_PHASE_ADJ(uint8_t PHASE_ADJ) {
    if (PHASE_ADJ > 1) return ADF4351_INVALID_VALUE;
    reg1.reg1_t.PHASE_ADJ = PHASE_ADJ;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param COUNTER_RESET 
 * @return ADF4351_Error 
 * @details 0: disabled, 1: enabled
 */
ADF4351_Error ADF4351::set_COUNTER_RESET(uint8_t COUNTER_RESET) {
    if (COUNTER_RESET > 1) return ADF4351_INVALID_VALUE;
    reg2.reg2_t.COUNTER_RESET = COUNTER_RESET;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param CP_THREE_STATE 
 * @return ADF4351_Error 
 * @details charge pump output three-state control
 * @details 0: normal operation, 1: three-state
 */
ADF4351_Error ADF4351::set_CP_THREE_STATE(uint8_t CP_THREE_STATE) {
    if (CP_THREE_STATE > 1) return ADF4351_INVALID_VALUE;
    reg2.reg2_t.CP_THREE_STATE = CP_THREE_STATE;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param POWER_DOWN 
 * @return ADF4351_Error 
 * @details 0: normal operation, 1: power down
 * @details if power down, the device will be in a low power state, 
 * @details - synthesizer counter is force to load state.
 * @details - VCO is powered down
 * @details - charge pump is in three-state
 * @details - digital lock detect is reset
 * @details - RFout buffer is disabled
 * @details - register is active and can be load and latch new values
 */
ADF4351_Error ADF4351::set_POWER_DOWN(uint8_t POWER_DOWN) {
    if (POWER_DOWN > 1) return ADF4351_INVALID_VALUE;
    reg2.reg2_t.POWER_DOWN = POWER_DOWN;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param PD_POLARITY 
 * @return ADF4351_Error 
 * @details Phase detector polarity select
 * @details 0: negative polarity, 1: positive polarity
 */
ADF4351_Error ADF4351::set_PD_POLARITY(uint8_t PD_POLARITY) {
    if (PD_POLARITY > 1) return ADF4351_INVALID_VALUE;
    reg2.reg2_t.PD_POLARITY = PD_POLARITY;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param LDP 
 * @return ADF4351_Error 
 * @details Lock detect precision
 * @details 0: 10ns, 1: 6ns
 */
ADF4351_Error ADF4351::set_LDP(uint8_t LDP) {
    if (LDP > 1) return ADF4351_INVALID_VALUE;
    reg2.reg2_t.LDP = LDP;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param LDF 
 * @return ADF4351_Error 
 * @details Lock detect function
 * @details 0: FRAC_N mode, 1: INT_N mode
 */
ADF4351_Error ADF4351::set_LDF(uint8_t LDF) {
    if (LDF > 1) return ADF4351_INVALID_VALUE;
    reg2.reg2_t.LDF = LDF;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param CHARGE_PUMP_CURRENT 
 * @return ADF4351_Error 
 * @details Charge pump current setting
 * @details 0x0: 0.31mA, 0x1: 0.63mA, 0x2: 0.94mA, 0x3: 1.25mA, 0x4: 1.56mA, 0x5: 1.88mA, 0x6: 2.19mA, 0x7: 2.50mA, 0x8: 2.81mA, 0x9: 3.13mA, 0xA: 3.44mA, 0xB: 3.75mA, 0xC: 4.06mA, 0xD: 4.38mA, 0xE: 4.69mA, 0xF: 5.00mA
 */
ADF4351_Error ADF4351::set_CHARGE_PUMP_CURRENT(uint8_t CHARGE_PUMP_CURRENT) {
    if (CHARGE_PUMP_CURRENT > 0xF) return ADF4351_INVALID_VALUE;
    reg2.reg2_t.CHARGE_PUMP_CURRENT = CHARGE_PUMP_CURRENT;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param DOUBLE_BUFF 
 * @return ADF4351_Error 
 * @details 0: disabled, 1: enabled
 */
ADF4351_Error ADF4351::set_DOUBLE_BUFF(uint8_t DOUBLE_BUFF) {
    if (DOUBLE_BUFF > 1) return ADF4351_INVALID_VALUE;
    reg2.reg2_t.DOUBLE_BUFF = DOUBLE_BUFF;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param R_COUNTER 
 * @return ADF4351_Error 
 * @details range is 1-1023
 */
ADF4351_Error ADF4351::set_R_COUNTER(uint16_t R_COUNTER) {
    if (R_COUNTER > 0x3FF) return ADF4351_INVALID_VALUE;
    if (R_COUNTER < 1) return ADF4351_INVALID_VALUE;
    reg2.reg2_t.R_COUNTER = R_COUNTER;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param RDIV2 
 * @return ADF4351_Error 
 * @details 0: disabled, 1: enabled
 */
ADF4351_Error ADF4351::set_RDIV2(uint8_t RDIV2) {
    if (RDIV2 > 1) return ADF4351_INVALID_VALUE;
    reg2.reg2_t.RDIV2 = RDIV2;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param REFERENCE_DOUBLER 
 * @return ADF4351_Error 
 * @details 0: disabled, 1: enabled
 */
ADF4351_Error ADF4351::set_REFERENCE_DOUBLER(uint8_t REFERENCE_DOUBLER) {
    if (REFERENCE_DOUBLER > 1) return ADF4351_INVALID_VALUE;
    reg2.reg2_t.REFERENCE_DOUBLER = REFERENCE_DOUBLER;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param MUXOUT 
 * @return ADF4351_Error 
 * @details 0: three-state output, 1: DVDD, 2: DGND, 3: R counter output, 4: N divider output, 5: analog lock detect, 6: digital lock detect, 7: reserved
 */
ADF4351_Error ADF4351::set_MUXOUT(uint8_t MUXOUT) {
    if (MUXOUT > 0x7) return ADF4351_INVALID_VALUE;
    reg2.reg2_t.MUXOUT = MUXOUT;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param LOW_NOISE_AND_SPUR_MODE 
 * @return ADF4351_Error 
 * @details 0: low noise mode, 1: reserved, 2: reserved, 3: low spur mode
 */
ADF4351_Error ADF4351::set_LOW_NOISE_AND_SPUR_MODE(uint8_t LOW_NOISE_AND_SPUR_MODE) {
    if (LOW_NOISE_AND_SPUR_MODE > 0x3) return ADF4351_INVALID_VALUE;
    reg2.reg2_t.LOW_NOISE_AND_SPUR_MODE = LOW_NOISE_AND_SPUR_MODE;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param CLOCK_DIV_VALUE 
 * @return ADF4351_Error 
 * @details range is 0-4095
 */
ADF4351_Error ADF4351::set_CLOCK_DIV_VALUE(uint16_t CLOCK_DIV_VALUE) {
    if (CLOCK_DIV_VALUE > 0xFFF) return ADF4351_INVALID_VALUE;
    reg3.reg3_t.CLOCK_DIV_VALUE = CLOCK_DIV_VALUE;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param CLOCK_DIV_MODE 
 * @return ADF4351_Error 
 * @details 0: off, 1: fast lock enable, 2:resync enable, 3: reserved
 */
ADF4351_Error ADF4351::set_CLOCK_DIV_MODE(uint8_t CLOCK_DIV_MODE) {
    if (CLOCK_DIV_MODE > 0x3) return ADF4351_INVALID_VALUE;
    reg3.reg3_t.CLOCK_DIV_MODE = CLOCK_DIV_MODE;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param CSR 
 * @return ADF4351_Error 
 * @details 0: CSR disabled, 1: CSR enabled
 */
ADF4351_Error ADF4351::set_CSR(uint8_t CSR) {
    if (CSR > 1) return ADF4351_INVALID_VALUE;
    reg3.reg3_t.CSR = CSR;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param CHARGE_CANCEL 
 * @return ADF4351_Error 
 * @details 0: disabled, 1: enabled
 */
ADF4351_Error ADF4351::set_CHARGE_CANCEL(uint8_t CHARGE_CANCEL) {
    if (CHARGE_CANCEL > 1) return ADF4351_INVALID_VALUE;
    reg3.reg3_t.CHARGE_CANCEL = CHARGE_CANCEL;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param ABP 
 * @return ADF4351_Error 
 * @details ANTI BACKLASH PULSE WIDTH
 * @details 0: 6ns(FRAC-n), 1: 3ns(INT-n)
 */
ADF4351_Error ADF4351::set_ABP(uint8_t ABP) {
    if (ABP > 1) return ADF4351_INVALID_VALUE;
    reg3.reg3_t.ABP = ABP;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param BAND_SELECT_CLOCK_MODE 
 * @return ADF4351_Error 
 * @details 0: low, 1: high
 */
ADF4351_Error ADF4351::set_BAND_SELECT_CLOCK_MODE(uint8_t BAND_SELECT_CLOCK_MODE) {
    if (BAND_SELECT_CLOCK_MODE > 1) return ADF4351_INVALID_VALUE;
    reg3.reg3_t.BAND_SELECT_CLOCK_MODE = BAND_SELECT_CLOCK_MODE;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param OUTPUT_POWER 
 * @return ADF4351_Error 
 * @details 0: -4dBm, 1: -1dBm, 2: +2dBm, 3: +5dBm
 */
ADF4351_Error ADF4351::set_OUTPUT_POWER(uint8_t OUTPUT_POWER) {
    if (OUTPUT_POWER > 0x3) return ADF4351_INVALID_VALUE;
    reg4.reg4_t.OUTPUT_POWER = OUTPUT_POWER;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param RF_OUTPUT_ENABLE 
 * @return ADF4351_Error 
 * @details 0: RF output disabled, 1: RF output enabled
 */
ADF4351_Error ADF4351::set_RF_OUTPUT_ENABLE(uint8_t RF_OUTPUT_ENABLE) {
    if (RF_OUTPUT_ENABLE > 1) return ADF4351_INVALID_VALUE;
    reg4.reg4_t.RF_OUTPUT_ENABLE = RF_OUTPUT_ENABLE;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param AUX_OUTPUT_POWER 
 * @return ADF4351_Error 
 * @details 0: -4dBm, 1: -1dBm, 2: +2dBm, 3: +5dBm
 */
ADF4351_Error ADF4351::set_AUX_OUTPUT_POWER(uint8_t AUX_OUTPUT_POWER) {
    if (AUX_OUTPUT_POWER > 0x3) return ADF4351_INVALID_VALUE;
    reg4.reg4_t.AUX_OUTPUT_POWER = AUX_OUTPUT_POWER;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param AUX_OUTPUT_ENABLE 
 * @return ADF4351_Error 
 * @details 0: AUX output disabled, 1: AUX output enabled
 */
ADF4351_Error ADF4351::set_AUX_OUTPUT_ENABLE(uint8_t AUX_OUTPUT_ENABLE) {
    if (AUX_OUTPUT_ENABLE > 1) return ADF4351_INVALID_VALUE;
    reg4.reg4_t.AUX_OUTPUT_ENABLE = AUX_OUTPUT_ENABLE;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param AUX_OUTPUT_SELECT 
 * @return ADF4351_Error 
 * @details 0: divided output 1: fundamental output
 */
ADF4351_Error ADF4351::set_AUX_OUTPUT_SELECT(uint8_t AUX_OUTPUT_SELECT) {
    if (AUX_OUTPUT_SELECT > 1) return ADF4351_INVALID_VALUE;
    reg4.reg4_t.AUX_OUTPUT_SELECT = AUX_OUTPUT_SELECT;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param MUTE_TILL_LOCK_DETECT 
 * @return ADF4351_Error 
 * @details 0: MUTE disabled, 1: MUTE enabled
 */
ADF4351_Error ADF4351::set_MUTE_TILL_LOCK_DETECT(uint8_t MUTE_TILL_LOCK_DETECT) {
    if (MUTE_TILL_LOCK_DETECT > 1) return ADF4351_INVALID_VALUE;
    reg4.reg4_t.MUTE_TILL_LOCK_DETECT = MUTE_TILL_LOCK_DETECT;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param VCO_POWER_DOWN 
 * @return ADF4351_Error 
 * @details 0: VCO normal operation, 1: VCO power down
 */
ADF4351_Error ADF4351::set_VCO_POWER_DOWN(uint8_t VCO_POWER_DOWN) {
    if (VCO_POWER_DOWN > 1) return ADF4351_INVALID_VALUE;
    reg4.reg4_t.VCO_POWER_DOWN = VCO_POWER_DOWN;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param BAND_SELECT_CLOCK_DIVIDER_VALUE 
 * @return ADF4351_Error 
 * @details range is 1-255
 */
ADF4351_Error ADF4351::set_BAND_SELECT_CLOCK_DIVIDER_VALUE(uint8_t BAND_SELECT_CLOCK_DIVIDER_VALUE) {
    if (BAND_SELECT_CLOCK_DIVIDER_VALUE > 0xFF) return ADF4351_INVALID_VALUE;
    if (BAND_SELECT_CLOCK_DIVIDER_VALUE < 1) return ADF4351_INVALID_VALUE;
    reg4.reg4_t.BAND_SELECT_CLOCK_DIVIDER_VALUE = BAND_SELECT_CLOCK_DIVIDER_VALUE;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param RF_DIVIDER_SELECT 
 * @return ADF4351_Error 
 * @details 0: 1/1, 1: 1/2, 2: 1/4, 3: 1/8, 4: 1/16, 5: 1/32, 6: 1/64
 */
ADF4351_Error ADF4351::set_RF_DIVIDER_SELECT(uint8_t RF_DIVIDER_SELECT) {
    if (RF_DIVIDER_SELECT > 0x7) return ADF4351_INVALID_VALUE;
    reg4.reg4_t.RF_DIVIDER_SELECT = RF_DIVIDER_SELECT;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param FEEDBACK_SELECT 
 * @return ADF4351_Error 
 * @details 0: divided, 1: fundamental
 */
ADF4351_Error ADF4351::set_FEEDBACK_SELECT(uint8_t FEEDBACK_SELECT) {
    if (FEEDBACK_SELECT > 1) return ADF4351_INVALID_VALUE;
    reg4.reg4_t.FEEDBACK_SELECT = FEEDBACK_SELECT;
    return ADF4351_SUCCESS;
}

/**
 * @brief
 * 
 * @param LD_PIN_MODE 
 * @return ADF4351_Error 
 * @details 0: low, 1: digital lock detect, 2: low, 3: high
 */
ADF4351_Error ADF4351::set_LD_PIN_MODE(uint8_t LD_PIN_MODE) {
    if (LD_PIN_MODE > 0x3) return ADF4351_INVALID_VALUE;
    reg5.reg5_t.LD_PIN_MODE = LD_PIN_MODE;
    return ADF4351_SUCCESS;
}

// Getters

/**
 * @brief Get FRAC value
 * 
 * @param FRAC Pointer to store FRAC value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_FRAC(uint16_t *FRAC) {
    if (!FRAC) return ADF4351_READ_ERROR;
    *FRAC = reg0.reg0_t.FRAC;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get INT value
 * 
 * @param INT Pointer to store INT value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_INT(uint16_t *INT) {
    if (!INT) return ADF4351_READ_ERROR;
    *INT = reg0.reg0_t.INT;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get MODULUS value
 * 
 * @param MODULUS Pointer to store MODULUS value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_MODULUS(uint16_t *MODULUS) {
    if (!MODULUS) return ADF4351_READ_ERROR;
    *MODULUS = reg1.reg1_t.MODULUS;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get PHASE value
 * 
 * @param PHASE Pointer to store PHASE value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_PHASE(uint16_t *PHASE) {
    if (!PHASE) return ADF4351_READ_ERROR;
    *PHASE = reg1.reg1_t.PHASE;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get PRESCALER value
 * 
 * @param PRESCALER Pointer to store PRESCALER value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_PRESCALER(uint8_t *PRESCALER) {
    if (!PRESCALER) return ADF4351_READ_ERROR;
    *PRESCALER = reg1.reg1_t.PRESCALER;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get PHASE_ADJ value
 * 
 * @param PHASE_ADJ Pointer to store PHASE_ADJ value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_PHASE_ADJ(uint8_t *PHASE_ADJ) {
    if (!PHASE_ADJ) return ADF4351_READ_ERROR;
    *PHASE_ADJ = reg1.reg1_t.PHASE_ADJ;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get COUNTER_RESET value
 * 
 * @param COUNTER_RESET Pointer to store COUNTER_RESET value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_COUNTER_RESET(uint8_t *COUNTER_RESET) {
    if (!COUNTER_RESET) return ADF4351_READ_ERROR;
    *COUNTER_RESET = reg2.reg2_t.COUNTER_RESET;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get CP_THREE_STATE value
 * 
 * @param CP_THREE_STATE Pointer to store CP_THREE_STATE value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_CP_THREE_STATE(uint8_t *CP_THREE_STATE) {
    if (!CP_THREE_STATE) return ADF4351_READ_ERROR;
    *CP_THREE_STATE = reg2.reg2_t.CP_THREE_STATE;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get POWER_DOWN value
 * 
 * @param POWER_DOWN Pointer to store POWER_DOWN value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_POWER_DOWN(uint8_t *POWER_DOWN) {
    if (!POWER_DOWN) return ADF4351_READ_ERROR;
    *POWER_DOWN = reg2.reg2_t.POWER_DOWN;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get PD_POLARITY value
 * 
 * @param PD_POLARITY Pointer to store PD_POLARITY value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_PD_POLARITY(uint8_t *PD_POLARITY) {
    if (!PD_POLARITY) return ADF4351_READ_ERROR;
    *PD_POLARITY = reg2.reg2_t.PD_POLARITY;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get LDP value
 * 
 * @param LDP Pointer to store LDP value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_LDP(uint8_t *LDP) {
    if (!LDP) return ADF4351_READ_ERROR;
    *LDP = reg2.reg2_t.LDP;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get LDF value
 * 
 * @param LDF Pointer to store LDF value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_LDF(uint8_t *LDF) {
    if (!LDF) return ADF4351_READ_ERROR;
    *LDF = reg2.reg2_t.LDF;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get CHARGE_PUMP_CURRENT value
 * 
 * @param CHARGE_PUMP_CURRENT Pointer to store CHARGE_PUMP_CURRENT value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_CHARGE_PUMP_CURRENT(uint8_t *CHARGE_PUMP_CURRENT) {
    if (!CHARGE_PUMP_CURRENT) return ADF4351_READ_ERROR;
    *CHARGE_PUMP_CURRENT = reg2.reg2_t.CHARGE_PUMP_CURRENT;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get DOUBLE_BUFF value
 * 
 * @param DOUBLE_BUFF Pointer to store DOUBLE_BUFF value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_DOUBLE_BUFF(uint8_t *DOUBLE_BUFF) {
    if (!DOUBLE_BUFF) return ADF4351_READ_ERROR;
    *DOUBLE_BUFF = reg2.reg2_t.DOUBLE_BUFF;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get R_COUNTER value
 * 
 * @param R_COUNTER Pointer to store R_COUNTER value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_R_COUNTER(uint16_t *R_COUNTER) {
    if (!R_COUNTER) return ADF4351_READ_ERROR;
    *R_COUNTER = reg2.reg2_t.R_COUNTER;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get RDIV2 value
 * 
 * @param RDIV2 Pointer to store RDIV2 value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_RDIV2(uint8_t *RDIV2) {
    if (!RDIV2) return ADF4351_READ_ERROR;
    *RDIV2 = reg2.reg2_t.RDIV2;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get REFERENCE_DOUBLER value
 * 
 * @param REFERENCE_DOUBLER Pointer to store REFERENCE_DOUBLER value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_REFERENCE_DOUBLER(uint8_t *REFERENCE_DOUBLER) {
    if (!REFERENCE_DOUBLER) return ADF4351_READ_ERROR;
    *REFERENCE_DOUBLER = reg2.reg2_t.REFERENCE_DOUBLER;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get MUXOUT value
 * 
 * @param MUXOUT Pointer to store MUXOUT value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_MUXOUT(uint8_t *MUXOUT) {
    if (!MUXOUT) return ADF4351_READ_ERROR;
    *MUXOUT = reg2.reg2_t.MUXOUT;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get LOW_NOISE_AND_SPUR_MODE value
 * 
 * @param LOW_NOISE_AND_SPUR_MODE Pointer to store LOW_NOISE_AND_SPUR_MODE value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_LOW_NOISE_AND_SPUR_MODE(uint8_t *LOW_NOISE_AND_SPUR_MODE) {
    if (!LOW_NOISE_AND_SPUR_MODE) return ADF4351_READ_ERROR;
    *LOW_NOISE_AND_SPUR_MODE = reg2.reg2_t.LOW_NOISE_AND_SPUR_MODE;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get CLOCK_DIV_VALUE value
 * 
 * @param CLOCK_DIV_VALUE Pointer to store CLOCK_DIV_VALUE value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_CLOCK_DIV_VALUE(uint16_t *CLOCK_DIV_VALUE) {
    if (!CLOCK_DIV_VALUE) return ADF4351_READ_ERROR;
    *CLOCK_DIV_VALUE = reg3.reg3_t.CLOCK_DIV_VALUE;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get CLOCK_DIV_MODE value
 * 
 * @param CLOCK_DIV_MODE Pointer to store CLOCK_DIV_MODE value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_CLOCK_DIV_MODE(uint8_t *CLOCK_DIV_MODE) {
    if (!CLOCK_DIV_MODE) return ADF4351_READ_ERROR;
    *CLOCK_DIV_MODE = reg3.reg3_t.CLOCK_DIV_MODE;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get CSR value
 * 
 * @param CSR Pointer to store CSR value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_CSR(uint8_t *CSR) {
    if (!CSR) return ADF4351_READ_ERROR;
    *CSR = reg3.reg3_t.CSR;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get CHARGE_CANCEL value
 * 
 * @param CHARGE_CANCEL Pointer to store CHARGE_CANCEL value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_CHARGE_CANCEL(uint8_t *CHARGE_CANCEL) {
    if (!CHARGE_CANCEL) return ADF4351_READ_ERROR;
    *CHARGE_CANCEL = reg3.reg3_t.CHARGE_CANCEL;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get ABP value
 * 
 * @param ABP Pointer to store ABP value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_ABP(uint8_t *ABP) {
    if (!ABP) return ADF4351_READ_ERROR;
    *ABP = reg3.reg3_t.ABP;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get BAND_SELECT_CLOCK_MODE value
 * 
 * @param BAND_SELECT_CLOCK_MODE Pointer to store BAND_SELECT_CLOCK_MODE value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_BAND_SELECT_CLOCK_MODE(uint8_t *BAND_SELECT_CLOCK_MODE) {
    if (!BAND_SELECT_CLOCK_MODE) return ADF4351_READ_ERROR;
    *BAND_SELECT_CLOCK_MODE = reg3.reg3_t.BAND_SELECT_CLOCK_MODE;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get OUTPUT_POWER value
 * 
 * @param OUTPUT_POWER Pointer to store OUTPUT_POWER value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_OUTPUT_POWER(uint8_t *OUTPUT_POWER) {
    if (!OUTPUT_POWER) return ADF4351_READ_ERROR;
    *OUTPUT_POWER = reg4.reg4_t.OUTPUT_POWER;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get RF_OUTPUT_ENABLE value
 * 
 * @param RF_OUTPUT_ENABLE Pointer to store RF_OUTPUT_ENABLE value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_RF_OUTPUT_ENABLE(uint8_t *RF_OUTPUT_ENABLE) {
    if (!RF_OUTPUT_ENABLE) return ADF4351_READ_ERROR;
    *RF_OUTPUT_ENABLE = reg4.reg4_t.RF_OUTPUT_ENABLE;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get AUX_OUTPUT_POWER value
 * 
 * @param AUX_OUTPUT_POWER Pointer to store AUX_OUTPUT_POWER value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_AUX_OUTPUT_POWER(uint8_t *AUX_OUTPUT_POWER) {
    if (!AUX_OUTPUT_POWER) return ADF4351_READ_ERROR;
    *AUX_OUTPUT_POWER = reg4.reg4_t.AUX_OUTPUT_POWER;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get AUX_OUTPUT_ENABLE value
 * 
 * @param AUX_OUTPUT_ENABLE Pointer to store AUX_OUTPUT_ENABLE value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_AUX_OUTPUT_ENABLE(uint8_t *AUX_OUTPUT_ENABLE) {
    if (!AUX_OUTPUT_ENABLE) return ADF4351_READ_ERROR;
    *AUX_OUTPUT_ENABLE = reg4.reg4_t.AUX_OUTPUT_ENABLE;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get AUX_OUTPUT_SELECT value
 * 
 * @param AUX_OUTPUT_SELECT Pointer to store AUX_OUTPUT_SELECT value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_AUX_OUTPUT_SELECT(uint8_t *AUX_OUTPUT_SELECT) {
    if (!AUX_OUTPUT_SELECT) return ADF4351_READ_ERROR;
    *AUX_OUTPUT_SELECT = reg4.reg4_t.AUX_OUTPUT_SELECT;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get MUTE_TILL_LOCK_DETECT value
 * 
 * @param MUTE_TILL_LOCK_DETECT Pointer to store MUTE_TILL_LOCK_DETECT value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_MUTE_TILL_LOCK_DETECT(uint8_t *MUTE_TILL_LOCK_DETECT) {
    if (!MUTE_TILL_LOCK_DETECT) return ADF4351_READ_ERROR;
    *MUTE_TILL_LOCK_DETECT = reg4.reg4_t.MUTE_TILL_LOCK_DETECT;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get VCO_POWER_DOWN value
 * 
 * @param VCO_POWER_DOWN Pointer to store VCO_POWER_DOWN value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_VCO_POWER_DOWN(uint8_t *VCO_POWER_DOWN) {
    if (!VCO_POWER_DOWN) return ADF4351_READ_ERROR;
    *VCO_POWER_DOWN = reg4.reg4_t.VCO_POWER_DOWN;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get BAND_SELECT_CLOCK_DIVIDER_VALUE value
 * 
 * @param BAND_SELECT_CLOCK_DIVIDER_VALUE Pointer to store BAND_SELECT_CLOCK_DIVIDER_VALUE value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_BAND_SELECT_CLOCK_DIVIDER_VALUE(uint8_t *BAND_SELECT_CLOCK_DIVIDER_VALUE) {
    if (!BAND_SELECT_CLOCK_DIVIDER_VALUE) return ADF4351_READ_ERROR;
    *BAND_SELECT_CLOCK_DIVIDER_VALUE = reg4.reg4_t.BAND_SELECT_CLOCK_DIVIDER_VALUE;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get RF_DIVIDER_SELECT value
 * 
 * @param RF_DIVIDER_SELECT Pointer to store RF_DIVIDER_SELECT value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_RF_DIVIDER_SELECT(uint8_t *RF_DIVIDER_SELECT) {
    if (!RF_DIVIDER_SELECT) return ADF4351_READ_ERROR;
    *RF_DIVIDER_SELECT = reg4.reg4_t.RF_DIVIDER_SELECT;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get FEEDBACK_SELECT value
 * 
 * @param FEEDBACK_SELECT Pointer to store FEEDBACK_SELECT value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_FEEDBACK_SELECT(uint8_t *FEEDBACK_SELECT) {
    if (!FEEDBACK_SELECT) return ADF4351_READ_ERROR;
    *FEEDBACK_SELECT = reg4.reg4_t.FEEDBACK_SELECT;
    return ADF4351_SUCCESS;
}

/**
 * @brief Get LD_PIN_MODE value
 * 
 * @param LD_PIN_MODE Pointer to store LD_PIN_MODE value
 * @return ADF4351_Error 
 */
ADF4351_Error ADF4351::get_LD_PIN_MODE(uint8_t *LD_PIN_MODE) {
    if (!LD_PIN_MODE) return ADF4351_READ_ERROR;
    *LD_PIN_MODE = reg5.reg5_t.LD_PIN_MODE;
    return ADF4351_SUCCESS;
}