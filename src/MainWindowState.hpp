#pragma once
#include "UnicodeWindows.hpp"
#include "MonitorInfo.hpp"

class MainWindowState{
private:
    MonitorInfo monitorInfo;
public:
    MainWindowState(HMONITOR monitor);
    LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
    HMONITOR GetMonitor() const noexcept;
};