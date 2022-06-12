#pragma once
#include "UnicodeWindows.hpp"

class MainWindowState{
private:
    HMONITOR monitor;
public:
    MainWindowState(HMONITOR monitor);
    LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
    HMONITOR GetMonitor() const noexcept;
};