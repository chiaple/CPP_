#pragma once

#include "transport/ITransport.h"

#include <string>

namespace stm32 {

class Stm32FirmwareUpdater {
public:
    explicit Stm32FirmwareUpdater(transport::ITransport& transport);

    void flash(const std::string& firmwarePath);
    void runApplication();

private:
    void writeLine(const std::string& line);

    transport::ITransport& transport_;
};

}  // namespace stm32
