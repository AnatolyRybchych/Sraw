#pragma once

#include <functional>
#include "Window.hpp"
#include <gdiplus.h>

class CutBmpWindow:public Window{
private:
    static int counter;
    std::function<void(HBITMAP bmp)> onCut;
    HBITMAP bmp;
    HDC bmpDc;
    HBITMAP bgBmp;
    HDC bg;
    HBITMAP backBufferBmp;
    HDC backBuffer;

    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;

    bool isMouseDown = false;

    int bmpCx, bmpCy;
protected:
    virtual LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept override;
public:
    CutBmpWindow(HINSTANCE hInst, HBITMAP bitmap, std::function<void(HBITMAP bmp)> onCut) noexcept;
    virtual ~CutBmpWindow() noexcept;
};