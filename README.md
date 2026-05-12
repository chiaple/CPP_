# CPPDemo

Portable Linux C++ control program for a STM32-based FOC driver board.

This project is the future Linux-board side of the system. It will run on an
embedded Linux board, talk to the STM32 FOC application during normal operation,
and talk to the STM32 bootloader when updating firmware.

## Build

```bash
cmake --preset Debug
cmake --build --preset Debug
```

## Commands

```bash
./build/Debug/cpp_demo --help
./build/Debug/cpp_demo foc enable --device /dev/ttyUSB0 --baud 115200
./build/Debug/cpp_demo foc rpm 300 --device /dev/ttyUSB0
./build/Debug/cpp_demo foc stop --device /dev/ttyUSB0
./build/Debug/cpp_demo stm32 flash firmware/main_app.bin --device /dev/ttyUSB0
./build/Debug/cpp_demo stm32 run --device /dev/ttyUSB0
```

## Layout

- `app/`: executable entry point
- `include/app`, `src/app`: command-line parsing and command dispatch
- `include/transport`, `src/transport`: serial/CAN/USB communication layer
- `include/foc`, `src/foc`: FOC driver board control interface
- `include/stm32`, `src/stm32`: STM32 bootloader and firmware update interface
- `build/`: generated CMake/Ninja files, ignored by Git

`SerialPort` is currently a simulator that prints bytes. Replace it with a real
POSIX serial implementation before running on the final Linux board.
