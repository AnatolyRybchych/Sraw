#pragma once
#include "UnicodeWindows.hpp"
#include "MonitorInfo.hpp"
#include "MainWindowStateStage.hpp"

class MainWindow;

class MainWindowState{
private:
    MainWindow *window; 
    MonitorInfo monitorInfo;
    MainWindowStateStage stage;
    HBITMAP screenshot = nullptr;
    HDC screenshotDc = nullptr;
public:
    MainWindowState(MainWindow *window, HMONITOR monitor);
    LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
    HMONITOR GetMonitor() const noexcept;
    ~MainWindowState() noexcept;
};