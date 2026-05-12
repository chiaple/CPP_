#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace transport {

class ITransport {
public:
    virtual ~ITransport() = default;

    virtual void open() = 0;
    virtual void close() = 0;
    virtual bool isOpen() const = 0;
    virtual void write(const std::vector<std::uint8_t>& data) = 0;
    virtual std::vector<std::uint8_t> read(std::size_t maxBytes) = 0;
};

}  // namespace transport
