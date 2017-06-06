#pragma once

#include <string>
#include <iostream>

#include "conf.h"

namespace logging
{
    bool init(conf& conf_file);
    void destroy();
    void log(const std::string& message, bool verbose);
    void set_verbose(bool verbose);
    std::ostream& get();
}
