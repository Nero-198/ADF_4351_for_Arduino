#include "CommandHandler.h"

CommandHandler::CommandHandler(ADF4351_Arduino& device) : adf4351(device) {}

void CommandHandler::handleCommand(const String& commandLine) {
    String inputString = commandLine;
    inputString.trim();

    Serial.print("Received command: ");
    Serial.println(inputString);

    int spaceIndex = inputString.indexOf(' ');
    String command = "";    //command
    String valueStr = "";   //argument
    if (spaceIndex == -1) {
        command = inputString;
    } else {
        command = inputString.substring(0, spaceIndex);
        valueStr = inputString.substring(spaceIndex + 1);
    }

    int value = valueStr.toInt();

    ADF4351_Write_Error err = ADF4351_WRITE_ERROR;
    bool recognized = true;

    if (command.equalsIgnoreCase("INT")) {
        err = adf4351.write_INT(value);
    } else if (command.equalsIgnoreCase("FRAC")) {
        err = adf4351.write_FRAC(value);
    } else if (command.equalsIgnoreCase("MODULUS")) {
        err = adf4351.write_MODULUS(value);
    } else if (command.equalsIgnoreCase("PHASE")) {
        err = adf4351.write_PHASE(value);
    } else if (command.equalsIgnoreCase("PRESCALER")) {
        err = adf4351.write_PRESCALER((uint8_t)value);
    } else if (command.equalsIgnoreCase("PHASE_ADJ")) {
        err = adf4351.write_PHASE_ADJ((uint8_t)value);
    } else if (command.equalsIgnoreCase("COUNTER_RESET")) {
        err = adf4351.write_COUNTER_RESET((uint8_t)value);
    } else if (command.equalsIgnoreCase("CP_THREE_STATE")) {
        err = adf4351.write_CP_THREE_STATE((uint8_t)value);
    } else if (command.equalsIgnoreCase("POWER_DOWN")) {
        err = adf4351.write_POWER_DOWN((uint8_t)value);
    } else if (command.equalsIgnoreCase("PD_POLARITY")) {
        err = adf4351.write_PD_POLARITY((uint8_t)value);
    } else if (command.equalsIgnoreCase("LDP")) {
        err = adf4351.write_LDP((uint8_t)value);
    } else if (command.equalsIgnoreCase("LDF")) {
        err = adf4351.write_LDF((uint8_t)value);
    } else if (command.equalsIgnoreCase("CHARGE_PUMP_CURRENT")) {
        err = adf4351.write_CHARGE_PUMP_CURRENT((uint8_t)value);
    } else if (command.equalsIgnoreCase("DOUBLE_BUFF")) {
        err = adf4351.write_DOUBLE_BUFF((uint8_t)value);
    } else if (command.equalsIgnoreCase("R_COUNTER")) {
        err = adf4351.write_R_COUNTER(value);
    } else if (command.equalsIgnoreCase("RDIV2")) {
        err = adf4351.write_RDIV2((uint8_t)value);
    } else if (command.equalsIgnoreCase("REFERENCE_DOUBLER")) {
        err = adf4351.write_REFERENCE_DOUBLER((uint8_t)value);
    } else if (command.equalsIgnoreCase("MUXOUT")) {
        err = adf4351.write_MUXOUT((uint8_t)value);
    } else if (command.equalsIgnoreCase("LOW_NOISE_AND_SPUR_MODE")) {
        err = adf4351.write_LOW_NOISE_AND_SPUR_MODE((uint8_t)value);
    } else if (command.equalsIgnoreCase("CLOCK_DIV_VALUE")) {
        err = adf4351.write_CLOCK_DIV_VALUE(value);
    } else if (command.equalsIgnoreCase("CLOCK_DIV_MODE")) {
        err = adf4351.write_CLOCK_DIV_MODE((uint8_t)value);
    } else if (command.equalsIgnoreCase("CSR")) {
        err = adf4351.write_CSR((uint8_t)value);
    } else if (command.equalsIgnoreCase("CHARGE_CANCEL")) {
        err = adf4351.write_CHARGE_CANCEL((uint8_t)value);
    } else if (command.equalsIgnoreCase("ABP")) {
        err = adf4351.write_ABP((uint8_t)value);
    } else if (command.equalsIgnoreCase("BAND_SELECT_CLOCK_MODE")) {
        err = adf4351.write_BAND_SELECT_CLOCK_MODE((uint8_t)value);
    } else if (command.equalsIgnoreCase("OUTPUT_POWER")) {
        err = adf4351.write_OUTPUT_POWER((uint8_t)value);
    } else if (command.equalsIgnoreCase("RF_OUTPUT_ENABLE")) {
        err = adf4351.write_RF_OUTPUT_ENABLE((uint8_t)value);
    } else if (command.equalsIgnoreCase("AUX_OUTPUT_POWER")) {
        err = adf4351.write_AUX_OUTPUT_POWER((uint8_t)value);
    } else if (command.equalsIgnoreCase("AUX_OUTPUT_ENABLE")) {
        err = adf4351.write_AUX_OUTPUT_ENABLE((uint8_t)value);
    } else if (command.equalsIgnoreCase("AUX_OUTPUT_SELECT")) {
        err = adf4351.write_AUX_OUTPUT_SELECT((uint8_t)value);
    } else if (command.equalsIgnoreCase("MUTE_TILL_LOCK_DETECT")) {
        err = adf4351.write_MUTE_TILL_LOCK_DETECT((uint8_t)value);
    } else if (command.equalsIgnoreCase("VCO_POWER_DOWN")) {
        err = adf4351.write_VCO_POWER_DOWN((uint8_t)value);
    } else if (command.equalsIgnoreCase("BAND_SELECT_CLOCK_DIVIDER_VALUE")) {
        err = adf4351.write_BAND_SELECT_CLOCK_DIVIDER_VALUE((uint8_t)value);
    } else if (command.equalsIgnoreCase("RF_DIVIDER_SELECT")) {
        err = adf4351.write_RF_DIVIDER_SELECT((uint8_t)value);
    } else if (command.equalsIgnoreCase("FEEDBACK_SELECT")) {
        err = adf4351.write_FEEDBACK_SELECT((uint8_t)value);
    } else if (command.equalsIgnoreCase("LD_PIN_MODE")) {
        err = adf4351.write_LD_PIN_MODE((uint8_t)value);
    } else if (command.equalsIgnoreCase("SET_CE_HIGH")) {
        adf4351.set_CE();
        err = ADF4351_WRITE_SUCCESS;
    } else if (command.equalsIgnoreCase("SET_CE_LOW")) {
        adf4351.unset_CE();
        err = ADF4351_WRITE_SUCCESS;
    } else {
        recognized = false;
    }

    if (recognized) {
        if (err == ADF4351_WRITE_SUCCESS) {
            Serial.println("Command executed successfully.");
        } else {
            Serial.println("Command execution failed.");
        }
    } else {
        Serial.println("Unknown command.");
    }
}
