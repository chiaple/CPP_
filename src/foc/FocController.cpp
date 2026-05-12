#include "foc/FocController.h"

#include <cstdint>
#include <iostream>

namespace foc {
namespace {

constexpr std::uint8_t kFrameHeader = 0xAA;
constexpr std::uint8_t kCommandEnable = 0x01;
constexpr std::uint8_t kCommandSetRpm = 0x02;
constexpr std::uint8_t kCommandStop = 0x03;

std::vector<std::uint8_t> encodeInt32LittleEndian(int value) {
    const auto raw = static_cast<std::uint32_t>(value);
    return {
        static_cast<std::uint8_t>(raw & 0xFF),
        static_cast<std::uint8_t>((raw >> 8) & 0xFF),
        static_cast<std::uint8_t>((raw >> 16) & 0xFF),
        static_cast<std::uint8_t>((raw >> 24) & 0xFF),
    };
}

std::uint8_t xorChecksum(const std::vector<std::uint8_t>& data) {
    std::uint8_t checksum = 0;
    for (std::uint8_t byte : data) {
        checksum ^= byte;
    }
    return checksum;
}

}  // namespace

FocController::FocController(transport::ITransport& transport)
    : transport_(transport) {}

void FocController::connect() {
    if (!transport_.isOpen()) {
        transport_.open();
    }
}

void FocController::enable() {
    std::cout << "[FOC] enable motor driver\n";
    sendCommand(kCommandEnable);
}

void FocController::setTargetRpm(int rpm) {
    std::cout << "[FOC] set target speed: " << rpm << " rpm\n";
    sendCommand(kCommandSetRpm, encodeInt32LittleEndian(rpm));
}

void FocController::stop() {
    std::cout << "[FOC] stop motor\n";
    sendCommand(kCommandStop);
}

void FocController::sendCommand(std::uint8_t command, const std::vector<std::uint8_t>& payload) {
    std::vector<std::uint8_t> frame;
    frame.reserve(payload.size() + 4);
    frame.push_back(kFrameHeader);
    frame.push_back(command);
    frame.push_back(static_cast<std::uint8_t>(payload.size()));
    frame.insert(frame.end(), payload.begin(), payload.end());
    frame.push_back(xorChecksum(frame));

    transport_.write(frame);
}

}  // namespace foc
