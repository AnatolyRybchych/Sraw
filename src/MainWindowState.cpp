#include "MainWindowState.hpp"

MainWindowState::MainWindowState(HMONITOR monitor)
    :monitorInfo(monitor){

}

LRESULT MainWindowState::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept{
    switch (msg)
    {
    case WM_SHOWWINDOW:{
        MONITORINFO info = monitorInfo.Get();
        
        SetWindowPos(
            hWnd, HWND_TOPMOST, 
            info.rcMonitor.left, 
            info.rcMonitor.top, 
            info.rcMonitor.right - info.rcMonitor.left, 
            info.rcMonitor.bottom - info.rcMonitor.top, 
            0
        );
    } return 0;
    default: return DefWindowProcW(hWnd, msg, wParam, lParam);
    }
}


HMONITOR MainWindowState::GetMonitor() const noexcept{
    return monitorInfo.GetMonitor();
}
