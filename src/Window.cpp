#include "Window.hpp"

LRESULT CALLBACK WindowWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
    Window *wnd = (Window*)GetWindowLongPtr(hWnd, 0);
    if(wnd != nullptr) 
        return wnd->WndProc(hWnd, msg, wParam, lParam);
    else 
        return DefWindowProc(hWnd, msg, wParam, lParam);
}

Window::Window(HINSTANCE hInstance, std::wstring className, std::wstring title, int x, int y, int width, int height, DWORD style, HWND parent, DWORD style_ex){
    WNDCLASSEX wc;
    memset(&wc, 0, sizeof(wc));
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = WindowWndProc;
    wc.lpszClassName = className.c_str();
    wc.hInstance = hInstance;
    wc.cbWndExtra = sizeof(Window*);
    wc.style = CS_VREDRAW | CS_HREDRAW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if(RegisterClassEx(&wc) == 0)
        throw std::runtime_error(std::string() + "cannot register window class, error code:" + std::to_string(GetLastError())); 
    
    hWnd = CreateWindowEx(style_ex, className.c_str(), title.c_str(), style, x, y, width, height, parent, nullptr, hInstance, nullptr);
    if(hWnd == 0)
        throw std::runtime_error((std::string() + "cannot create window, error code:" + std::to_string(GetLastError())));
    SetWindowLongPtr(hWnd, 0, (LONG_PTR)this);
}

HWND Window::GetHWnd() const noexcept{
    return hWnd;
}

Window::~Window(){
    SetWindowLongPtr(GetHWnd(), 0, 0);
    DestroyWindow(GetHWnd());
}