#pragma once

#include "app/AppConfig.h"

namespace app {

class CommandRunner {
public:
    static int run(const AppConfig& config);
};

}  // namespace app
