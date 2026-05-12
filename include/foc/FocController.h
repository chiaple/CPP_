#pragma once

#include "transport/ITransport.h"

#include <cstdint>
#include <vector>

namespace foc {

class FocController {
public:
    explicit FocController(transport::ITransport& transport);

    void connect();
    void enable();
    void setTargetRpm(int rpm);
    void stop();

private:
    void sendCommand(std::uint8_t command, const std::vector<std::uint8_t>& payload = {});

    transport::ITransport& transport_;
};

}  // namespace foc
