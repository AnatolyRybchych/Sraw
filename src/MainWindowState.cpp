#include "MainWindowState.hpp"
#include "MainWindow.hpp"

MainWindowState::MainWindowState(MainWindow *window, HMONITOR monitor)
    :monitorInfo(monitor){
    stage = MainWindowStateStage::CopyScreenImage;
    this->window = window;
}

LRESULT MainWindowState::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept{
    switch (msg)
    {
    case WM_SHOWWINDOW:{
        MONITORINFO info = monitorInfo.Get();

        int cxMonitor = info.rcMonitor.right - info.rcMonitor.left;
        int cyMonitor = info.rcMonitor.bottom - info.rcMonitor.top;

        if(stage == MainWindowStateStage::CopyScreenImage){
            if(screenshotDc != nullptr) DeleteDC(screenshotDc);
            if(screenshot != nullptr) DeleteObject(screenshot);

            HDC screenDc = GetDC(NULL);
            screenshotDc = CreateCompatibleDC(screenDc);

            screenshot = CreateCompatibleBitmap(screenDc, cxMonitor, cyMonitor);
            SelectObject(screenshotDc, screenshot);
            BitBlt(screenshotDc, 0, 0, cxMonitor, cyMonitor, screenDc, info.rcMonitor.left, info.rcMonitor.top, SRCCOPY);

            DeleteDC(screenDc);
            stage = MainWindowStateStage::KeepScreenSate;
        }
        
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
        MONITORINFO info = monitorInfo.Get();

        int cxMonitor = info.rcMonitor.right - info.rcMonitor.left;
        int cyMonitor = info.rcMonitor.bottom - info.rcMonitor.top;

        PAINTSTRUCT ps;
        HDC dc = BeginPaint(hWnd, &ps);

        BitBlt(dc, 0, 0, cxMonitor, cyMonitor, screenshotDc, 0, 0, SRCCOPY);

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