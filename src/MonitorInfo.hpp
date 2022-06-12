#pragma once
#include "UnicodeWindows.hpp"

class MonitorInfo{
    HMONITOR monitor;
public:
    MonitorInfo(HMONITOR monitor) noexcept;
    MONITORINFO Get() const noexcept;
    HMONITOR GetMonitor() const noexcept;
};
