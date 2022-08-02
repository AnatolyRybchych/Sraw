#pragma once
#include <memory>
#include <GL/glew.h>
#include "UnicodeWindows.hpp"
#include "MonitorInfo.hpp"
#include "MainWindowStateStage.hpp"
#include "DrawingCanvas.hpp"
#include "DrawingTarget.hpp"


class MainWindow;

class MainWindowState{
private:
    MainWindow &window; 
    MonitorInfo monitorInfo;
    MainWindowStateStage stage;
    std::unique_ptr<Texture> screenshot;
    std::unique_ptr<DrawingCanvas> canvas = nullptr;
    Quitable &quitable;
    const DrawingTarget &drawingTarget;
    

    void GetScreenshot() noexcept;
public:
    const Texture &GetStateTexture() const noexcept;
    const Texture &GetBgTexture() const noexcept;
    MainWindowState(MainWindow &window, HMONITOR monitor, Quitable &quitable, const DrawingTarget &drawingTarget);
    LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
    HMONITOR GetMonitor() const noexcept;
    ~MainWindowState() noexcept;
};