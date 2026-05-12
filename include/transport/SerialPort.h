#pragma once

#include "transport/ITransport.h"

#include <string>

namespace transport {

class SerialPort : public ITransport {
public:
    SerialPort(std::string device, int baudRate);
    ~SerialPort() override;

    SerialPort(const SerialPort&) = delete;
    SerialPort& operator=(const SerialPort&) = delete;
    SerialPort(SerialPort&&) = default;
    SerialPort& operator=(SerialPort&&) = default;

    void open() override;
    void close() override;
    bool isOpen() const override;
    void write(const std::vector<std::uint8_t>& data) override;
    std::vector<std::uint8_t> read(std::size_t maxBytes) override;

private:
    std::string device_;
    int baudRate_;
    bool opened_ = false;
};

}  // namespace transport
