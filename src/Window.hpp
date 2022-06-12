#pragma once
#include <string>
#include <stdexcept>

#include "UnicodeWindows.hpp"

LRESULT CALLBACK WindowWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class Window{
    friend LRESULT CALLBACK WindowWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
    HWND hWnd;
protected:
    virtual LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept = 0;
public:
    Window(HINSTANCE hInstance, std::wstring className, std::wstring title, int x, int y, int width, int height, DWORD style, HWND parent = nullptr, DWORD style_ex = 0);
    HWND GetHWnd() const noexcept;

    virtual ~Window();
};