#include "app/AppConfig.h"

#include <stdexcept>
#include <string>
#include <vector>

namespace app {
namespace {

int parseInteger(const std::string& name, const std::string& value) {
    std::size_t parsedChars = 0;
    try {
        int result = std::stoi(value, &parsedChars);
        if (parsedChars != value.size()) {
            throw std::invalid_argument("trailing characters");
        }
        return result;
    } catch (const std::exception&) {
        throw std::invalid_argument("invalid value for " + name + ": " + value);
    }
}

std::string requireValue(const std::vector<std::string>& args, std::size_t& index, const std::string& name) {
    if (index + 1 >= args.size()) {
        throw std::invalid_argument("missing value for " + name);
    }
    return args[++index];
}

void parseTransportOption(AppConfig& config, const std::vector<std::string>& args, std::size_t& index) {
    const std::string& option = args[index];
    if (option == "--device") {
        config.transport.device = requireValue(args, index, option);
    } else if (option == "--baud") {
        config.transport.baudRate = parseInteger(option, requireValue(args, index, option));
    } else {
        throw std::invalid_argument("unknown option: " + option);
    }
}

void parseCommonOptions(AppConfig& config, const std::vector<std::string>& args, std::size_t startIndex) {
    for (std::size_t index = startIndex; index < args.size(); ++index) {
        parseTransportOption(config, args, index);
    }
}

}  // namespace

//第一个AppConfig表示返回值类型，第二个AppConfig:: 表示这个函数属于 AppConfig 这个结构体。
AppConfig AppConfig::fromCommandLine(int argc, char* argv[]) {
    std::vector<std::string> args;
    args.reserve(static_cast<std::size_t>(argc));
    for (int index = 0; index < argc; ++index) {
        args.emplace_back(argv[index]);
    }
    
    AppConfig config;
    if (args.size() <= 1 || args[1] == "--help" || args[1] == "-h") {
        config.command = Command::Help;
        return config;
    }

    if (args[1] == "foc") {
        if (args.size() <= 2) {
            throw std::invalid_argument("missing foc command");
        }

        if (args[2] == "enable") {
            config.command = Command::FocEnable;
            parseCommonOptions(config, args, 3);
        } else if (args[2] == "stop") {
            config.command = Command::FocStop;
            parseCommonOptions(config, args, 3);
        } else if (args[2] == "rpm") {
            if (args.size() <= 3) {
                throw std::invalid_argument("missing rpm value");
            }
            config.command = Command::FocSetRpm;
            config.targetRpm = parseInteger("rpm", args[3]);
            parseCommonOptions(config, args, 4);
        } else {
            throw std::invalid_argument("unknown foc command: " + args[2]);
        }
        return config;
    }

    if (args[1] == "stm32") {
        if (args.size() <= 2) {
            throw std::invalid_argument("missing stm32 command");
        }

        if (args[2] == "flash") {
            if (args.size() <= 3) {
                throw std::invalid_argument("missing firmware path");
            }
            config.command = Command::Stm32Flash;
            config.firmwarePath = args[3];
            parseCommonOptions(config, args, 4);
        } else if (args[2] == "run") {
            config.command = Command::Stm32Run;
            parseCommonOptions(config, args, 3);
        } else {
            throw std::invalid_argument("unknown stm32 command: " + args[2]);
        }
        return config;
    }

    throw std::invalid_argument("unknown command group: " + args[1]);
}

std::string AppConfig::usage() {
    return
        "Usage:\n"
        "  cpp_demo --help\n"
        "  cpp_demo foc enable [--device PATH] [--baud RATE]\n"
        "  cpp_demo foc rpm <value> [--device PATH] [--baud RATE]\n"
        "  cpp_demo foc stop [--device PATH] [--baud RATE]\n"
        "  cpp_demo stm32 flash <firmware.bin> [--device PATH] [--baud RATE]\n"
        "  cpp_demo stm32 run [--device PATH] [--baud RATE]\n"
        "\n"
        "Defaults:\n"
        "  --device /dev/ttyUSB0\n"
        "  --baud 115200\n";
}

}  // namespace app
