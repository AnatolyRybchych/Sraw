#pragma once
#include <vector>
#include <memory>
#include "Window.hpp"
#include "MainWindowState.hpp"

class MainWindow:public Window{
private:
    std::vector<std::shared_ptr<MainWindowState>> windowStates;
    std::shared_ptr<MainWindowState> currState = nullptr;

    void SetCurrState(HMONITOR monitor);
protected:
    LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept override;
public:
    MainWindow(HINSTANCE hInstance);
    void Show();
    virtual ~MainWindow();
};