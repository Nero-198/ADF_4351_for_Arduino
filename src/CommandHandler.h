#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <Arduino.h>
#include "ADF4351_Arduino.h"

class CommandHandler {
private:
    ADF4351_Arduino& adf4351;

public:
    CommandHandler(ADF4351_Arduino& device);

    // シリアルからのコマンド文字列を受け取り解析・実行する
    void handleCommand(const String& commandLine);
};

#endif // COMMAND_HANDLER_H
