#pragma once
#include <vector>
#include <memory>
#include <stdexcept>
#include <GL/glew.h>
#include "Window.hpp"
#include "MainWindowState.hpp"
#include "Quitable.hpp"

class App;

class MainWindow:public Window{
private:
    std::vector<std::shared_ptr<MainWindowState>> windowStates;
    std::shared_ptr<MainWindowState> currState = nullptr;
    App &app;
    HGLRC glRc;
    HDC dc;
    void SetCurrState(HMONITOR monitor);
protected:
    LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept override;
public:
    MainWindow(HINSTANCE hInstance, App &app);
    void ClearCurrentState() noexcept;
    void MakeCurrent() const noexcept;
    void SwapBuffers() const noexcept;
    void Show();
    void Hide() const noexcept;
    virtual ~MainWindow();
};