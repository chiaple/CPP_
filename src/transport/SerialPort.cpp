#include "transport/SerialPort.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <utility>

namespace transport {

SerialPort::SerialPort(std::string device, int baudRate)
    : device_(std::move(device)), baudRate_(baudRate) {}

SerialPort::~SerialPort() {
    close();
}

void SerialPort::open() {
    if (device_.empty()) {
        throw std::invalid_argument("serial device path is empty");
    }

    opened_ = true;
    std::cout << "[Serial] open " << device_ << " @ " << baudRate_ << " baud\n";
}

void SerialPort::close() {
    if (!opened_) {
        return;
    }

    opened_ = false;
    std::cout << "[Serial] close " << device_ << '\n';
}

bool SerialPort::isOpen() const {
    return opened_;
}

void SerialPort::write(const std::vector<std::uint8_t>& data) {
    if (!opened_) {
        throw std::runtime_error("serial port is not open");
    }

    std::cout << "[Serial] write";
    for (std::uint8_t byte : data) {
        std::cout << ' ' << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<int>(byte);
    }
    std::cout << std::dec << std::setfill(' ') << '\n';
}

std::vector<std::uint8_t> SerialPort::read(std::size_t maxBytes) {
    if (!opened_) {
        throw std::runtime_error("serial port is not open");
    }

    std::cout << "[Serial] read up to " << maxBytes << " bytes\n";
    return {};
}

}  // namespace transport
