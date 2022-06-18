#include "MainWindowState.hpp"
#include "MainWindow.hpp"

MainWindowState::MainWindowState(MainWindow &window, HMONITOR monitor)
    :monitorInfo(monitor), window(window){
    stage = MainWindowStateStage::CopyScreenImage;
}

void MainWindowState::GetScreenshot() noexcept{
    MONITORINFO info = monitorInfo.Get();
    int cxMonitor = info.rcMonitor.right - info.rcMonitor.left;
    int cyMonitor = info.rcMonitor.bottom - info.rcMonitor.top;

    HDC screenDc = GetDC(NULL);
    HDC screenshotDc = CreateCompatibleDC(screenDc);
    HBITMAP screenshotBmp = CreateCompatibleBitmap(screenDc, cxMonitor, cyMonitor);
        SelectObject(screenshotDc, screenshotBmp);
        BitBlt(screenshotDc, 0, 0, cxMonitor, cyMonitor, screenDc, info.rcMonitor.left, info.rcMonitor.top, SRCCOPY);

        screenshot = std::unique_ptr<Texture>(new Texture(screenshotBmp));
    DeleteObject(screenshotBmp);
    DeleteDC(screenshotDc);
    DeleteDC(screenDc);

    stage = MainWindowStateStage::KeepScreenSate;
    canvas = std::unique_ptr<DrawingCanvas>(new DrawingCanvas(*screenshot.get()));
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

        canvas->OnShow(cxMonitor, cyMonitor);
    } return 0;
    case WM_PAINT:{
        PAINTSTRUCT ps;
        BeginPaint(hWnd, &ps);

        glClear(GL_COLOR_BUFFER_BIT);
        canvas->Draw();
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
}