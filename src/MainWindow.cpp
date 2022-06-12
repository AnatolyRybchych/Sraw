#include "MainWindow.hpp"

LRESULT MainWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept{
    if(currState != nullptr){
        return currState->WndProc(hWnd, msg, wParam, lParam);
    }
    else{
        return DefWindowProcW(hWnd, msg, wParam, lParam);
    }
}


MainWindow::MainWindow(HINSTANCE hInstance)
    :Window(hInstance, L"WNDCLASS_MAINWINDOW", L"", 0, 0, 100, 100, WS_POPUPWINDOW){

}

MainWindow::~MainWindow(){

}

void MainWindow::Show(){
    POINT cursorPos;
    GetCursorPos(&cursorPos);

    HMONITOR monitor = MonitorFromPoint(cursorPos, MONITOR_DEFAULTTONEAREST);
    SetCurrState(monitor);

    ShowWindow(GetHWnd(), SW_SHOW);
    UpdateWindow(GetHWnd());
}

void MainWindow::SetCurrState(HMONITOR monitor){
    for(auto state:windowStates){
        if(state->GetMonitor() == monitor){
            currState = state;
            return;
        }
    }
    currState = std::shared_ptr<MainWindowState>(new MainWindowState(monitor));
    windowStates.push_back(currState);
}
