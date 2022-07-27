#pragma once
#include <memory>
#include <GL/glew.h>
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
    std::unique_ptr<Texture> screenshot;
    std::unique_ptr<DrawingCanvas> canvas = nullptr;
    Quitable &quitable;

    void GetScreenshot() noexcept;
public:
    MainWindowState(MainWindow &window, HMONITOR monitor, Quitable &quitable);
    LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
    HMONITOR GetMonitor() const noexcept;
    ~MainWindowState() noexcept;
};