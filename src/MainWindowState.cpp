#include "MainWindowState.hpp"
#include "MainWindow.hpp"

MainWindowState::MainWindowState(MainWindow &window, HMONITOR monitor)
    :monitorInfo(monitor), window(window){
    stage = MainWindowStateStage::CopyScreenImage;
}

void MainWindowState::GetScreenshot() noexcept{
    if(screenshotDc != nullptr) DeleteDC(screenshotDc);
    if(screenshot != nullptr) DeleteObject(screenshot);

    MONITORINFO info = monitorInfo.Get();
    int cxMonitor = info.rcMonitor.right - info.rcMonitor.left;
    int cyMonitor = info.rcMonitor.bottom - info.rcMonitor.top;

    HDC screenDc = GetDC(NULL);
    screenshotDc = CreateCompatibleDC(screenDc);

    screenshot = CreateCompatibleBitmap(screenDc, cxMonitor, cyMonitor);
    SelectObject(screenshotDc, screenshot);
    BitBlt(screenshotDc, 0, 0, cxMonitor, cyMonitor, screenDc, info.rcMonitor.left, info.rcMonitor.top, SRCCOPY);

    DeleteDC(screenDc);
    stage = MainWindowStateStage::KeepScreenSate;
    Canvas = std::unique_ptr<DrawingCanvas>(new DrawingCanvas(cxMonitor, cyMonitor, screenshot));
}

LRESULT MainWindowState::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept{
    switch (msg)
    {
    case WM_SHOWWINDOW:{
        MONITORINFO info = monitorInfo.Get();
        int cxMonitor = info.rcMonitor.right - info.rcMonitor.left;
        int cyMonitor = info.rcMonitor.bottom - info.rcMonitor.top;
        
        if(stage == MainWindowStateStage::CopyScreenImage)
            GetScreenshot();
            
        SetWindowPos(
            hWnd, HWND_TOPMOST, 
            info.rcMonitor.left, 
            info.rcMonitor.top, 
            cxMonitor, 
            cyMonitor, 
            0
        );
    } return 0;
    case WM_PAINT:{
        PAINTSTRUCT ps;
        BeginPaint(hWnd, &ps);

        Canvas->Draw();
        window.SwapBuffers();

        EndPaint(hWnd, &ps);
    } return 0;
    default: return DefWindowProcW(hWnd, msg, wParam, lParam);
    }
}


HMONITOR MainWindowState::GetMonitor() const noexcept{
    return monitorInfo.GetMonitor();
}

MainWindowState::~MainWindowState() noexcept{
    if(stage != MainWindowStateStage::CopyScreenImage){
        DeleteObject(screenshot);
        DeleteDC(screenshotDc);
    }
}