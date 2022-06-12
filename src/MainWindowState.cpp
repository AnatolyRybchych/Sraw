#include "MainWindowState.hpp"

MainWindowState::MainWindowState(HMONITOR monitor){
    this->monitor = monitor;
}

LRESULT MainWindowState::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept{
    switch (msg)
    {
    default: return DefWindowProcW(hWnd, msg, wParam, lParam);
    }
}


HMONITOR MainWindowState::GetMonitor() const noexcept{
    return monitor;
}
