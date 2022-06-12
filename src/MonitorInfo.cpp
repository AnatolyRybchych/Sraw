#include "MonitorInfo.hpp"


MonitorInfo::MonitorInfo(HMONITOR monitor) noexcept{
    this->monitor = monitor;
}

MONITORINFO MonitorInfo::Get() const noexcept{
    MONITORINFO info;
    memset(&info, 0, sizeof(info));
    info.cbSize = sizeof(info);
    GetMonitorInfoW(monitor, &info);
    return info;
}

HMONITOR MonitorInfo::GetMonitor() const noexcept{
    return monitor;
}
