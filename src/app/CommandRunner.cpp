#include "app/CommandRunner.h"

#include "foc/FocController.h"
#include "stm32/Stm32FirmwareUpdater.h"
#include "transport/SerialPort.h"

#include <iostream>

namespace app {
namespace {

transport::SerialPort makeSerialPort(const TransportConfig& config) {
    return transport::SerialPort(config.device, config.baudRate);
}

}  // namespace

int CommandRunner::run(const AppConfig& config) {
    if (config.command == Command::Help) {
        std::cout << AppConfig::usage();
        return 0;
    }

    transport::SerialPort serial = makeSerialPort(config.transport);

    switch (config.command) {
    case Command::FocEnable: {
        foc::FocController motor(serial);
        motor.connect();
        motor.enable();
        return 0;
    }
    case Command::FocSetRpm: {
        foc::FocController motor(serial);
        motor.connect();
        motor.setTargetRpm(config.targetRpm);
        return 0;
    }
    case Command::FocStop: {
        foc::FocController motor(serial);
        motor.connect();
        motor.stop();
        return 0;
    }
    case Command::Stm32Flash: {
        stm32::Stm32FirmwareUpdater updater(serial);
        updater.flash(config.firmwarePath);
        return 0;
    }
    case Command::Stm32Run: {
        stm32::Stm32FirmwareUpdater updater(serial);
        updater.runApplication();
        return 0;
    }
    case Command::Help:
        break;
    }

    std::cout << AppConfig::usage();
    return 0;
}

}  // namespace app
