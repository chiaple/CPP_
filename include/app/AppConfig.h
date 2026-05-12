#pragma once

#include <string>

namespace app {

enum class Command {
    Help,
    FocEnable,
    FocSetRpm,
    FocStop,
    Stm32Flash,
    Stm32Run,
};

struct TransportConfig {
    std::string device = "/dev/ttyUSB0";
    int baudRate = 115200;
};

struct AppConfig {
    Command command = Command::Help;
    TransportConfig transport;
    int targetRpm = 0;
    std::string firmwarePath;

    //函数fromCommandLine返回值AppConfig
    static AppConfig fromCommandLine(int argc, char* argv[]);
    static std::string usage();
};

}  // namespace app
