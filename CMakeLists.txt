cmake_minimum_required(VERSION 3.16)

project(CPPDemo VERSION 0.1.0 LANGUAGES CXX)

add_executable(cpp_demo
    app/main.cpp
    src/app/AppConfig.cpp
    src/app/CommandRunner.cpp
    src/foc/FocController.cpp
    src/stm32/Stm32FirmwareUpdater.cpp
    src/transport/SerialPort.cpp
)

target_compile_features(cpp_demo PRIVATE cxx_std_17)

target_include_directories(cpp_demo
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(cpp_demo PRIVATE /W4)
else()
    target_compile_options(cpp_demo PRIVATE -Wall -Wextra -Wpedantic)
endif()
