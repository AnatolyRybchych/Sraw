#pragma once
#include <vector>
#include <memory>
#include <stdexcept>
#include <GL/glew.h>
#include "Window.hpp"
#include "MainWindowState.hpp"
#include "Quitable.hpp"
#include "DrawingTarget.hpp"

class App;

class MainWindow:public Window, public DrawingTarget{
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
    virtual void Redraw() const noexcept override;
    MainWindow(HINSTANCE hInstance, App &app);
    const Texture &GetCurrentStateTexture() const;
    HBITMAP CreateCurrentStateBitmap() const;
    HBITMAP CreateBgBitmap() const;
    void ClearCurrentState() noexcept;
    void MakeCurrent() const noexcept;
    void SwapBuffers() const noexcept;
    void Show();
    void Hide() const noexcept;
    virtual ~MainWindow();
};