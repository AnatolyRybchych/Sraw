#pragma once
#include <memory>
#include "UnicodeWindows.hpp"
#include "MonitorInfo.hpp"
#include "MainWindowStateStage.hpp"
#include "DrawingCanvas.hpp"


class MainWindow;

class MainWindowState{
private:
    MainWindow &window; 
    MonitorInfo monitorInfo;
    MainWindowStateStage stage;
    std::unique_ptr<DrawingCanvas> Canvas = nullptr;
    HBITMAP screenshot = nullptr;
    HDC screenshotDc = nullptr;
    void GetScreenshot() noexcept;
public:
    MainWindowState(MainWindow &window, HMONITOR monitor);
    LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
    HMONITOR GetMonitor() const noexcept;
    ~MainWindowState() noexcept;
};