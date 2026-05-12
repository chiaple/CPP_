#include "stm32/Stm32FirmwareUpdater.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace stm32 {

Stm32FirmwareUpdater::Stm32FirmwareUpdater(transport::ITransport& transport)
    : transport_(transport) {}

void Stm32FirmwareUpdater::flash(const std::string& firmwarePath) {
    std::ifstream firmware(firmwarePath, std::ios::binary | std::ios::ate);
    if (!firmware) {
        throw std::runtime_error("cannot open firmware file: " + firmwarePath);
    }

    if (!transport_.isOpen()) {
        transport_.open();
    }

    const auto firmwareSize = firmware.tellg();

    std::cout << "[STM32] prepare firmware update\n";
    std::cout << "[STM32] firmware: " << firmwarePath
              << " (" << firmwareSize << " bytes)\n";
    std::cout << "[STM32] bootloader protocol is not implemented yet\n";
}

void Stm32FirmwareUpdater::runApplication() {
    if (!transport_.isOpen()) {
        transport_.open();
    }

    std::cout << "[STM32] request jump to application\n";
    writeLine("APP");
}

void Stm32FirmwareUpdater::writeLine(const std::string& line) {
    std::vector<std::uint8_t> bytes(line.begin(), line.end());
    bytes.push_back('\r');
    bytes.push_back('\n');
    transport_.write(bytes);
}

}  // namespace stm32
