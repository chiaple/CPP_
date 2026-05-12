#include "app/AppConfig.h"
#include "app/CommandRunner.h"

#include <exception>
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        const app::AppConfig config = app::AppConfig::fromCommandLine(argc, argv);
        return app::CommandRunner::run(config);
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << "\n\n"
                  << app::AppConfig::usage();
        return 1;
    }
}
