#include "MainWindowState.hpp"
#include "MainWindow.hpp"

MainWindowState::MainWindowState(MainWindow &window, HMONITOR monitor, Quitable &quitable, const DrawingTarget &drawingTarget)
    :monitorInfo(monitor), window(window), quitable(quitable), drawingTarget(drawingTarget){
    stage = MainWindowStateStage::CopyScreenImage;
}

const Texture &MainWindowState::GetStateTexture() const noexcept{
    return canvas->GetCurrentState();
}

const Texture &MainWindowState::GetBgTexture() const noexcept{
    return canvas->GetBackground();
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
    canvas = std::unique_ptr<DrawingCanvas>(new DrawingCanvas(*screenshot.get(), quitable, drawingTarget, cxMonitor, cyMonitor));
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
    } return 0;
    case WM_MOUSEMOVE:{
        if(canvas){
            if(canvas->OnMouseMove(LOWORD(lParam), HIWORD(lParam)))InvalidateRect(window.GetHWnd(), nullptr, false);
        }
    }return 0;
    case WM_LBUTTONDOWN:{
        if(canvas){
            if(canvas->OnLMouseDown(LOWORD(lParam), HIWORD(lParam)))InvalidateRect(window.GetHWnd(), nullptr, false);
        }
    }return 0;
    case WM_LBUTTONUP:{
        if(canvas){
            if(canvas->OnLMouseUp(LOWORD(lParam), HIWORD(lParam)))InvalidateRect(window.GetHWnd(), nullptr, false);
        }
    }return 0;
    case WM_RBUTTONDOWN:{
        if(canvas){
            if(canvas->OnRMouseDown(LOWORD(lParam), HIWORD(lParam)))InvalidateRect(window.GetHWnd(), nullptr, false);
        }
    }return 0;
    case WM_RBUTTONUP:{
        if(canvas){
            if(canvas->OnRMouseUp(LOWORD(lParam), HIWORD(lParam)))InvalidateRect(window.GetHWnd(), nullptr, false);
        }
    }return 0;
    case WM_KEYDOWN:{
        if(canvas){
            if(canvas->OnkeyDown(wParam, (lParam & 0xffff0000) >> 16))InvalidateRect(window.GetHWnd(), nullptr, false);
        }
    }return 0;
    case WM_KEYUP:{
        if(canvas){
            if(canvas->Onkeyup(wParam)) InvalidateRect(window.GetHWnd(), nullptr, false);
        }
    }return 0;
    case WM_UNICHAR:
    case WM_CHAR:{
        if(canvas){
            wchar_t ch[] = {(wchar_t)wParam, 0,};
            if(canvas->OnTextInput(std::wstring(ch))) InvalidateRect(window.GetHWnd(), nullptr, false);
        }
    }return 0;
    case WM_PAINT:{
        glClear(GL_COLOR_BUFFER_BIT);
        PAINTSTRUCT ps;
        BeginPaint(hWnd, &ps);
        if(canvas){
            canvas->Draw();
        }
        window.SwapBuffers();
        EndPaint(hWnd, &ps);
    } return 0;
    case WM_MOUSEWHEEL:{
        if(canvas){
            if(GET_WHEEL_DELTA_WPARAM(wParam) > 0){
                if(canvas->OnScrollDown())InvalidateRect(window.GetHWnd(), nullptr, false);
            }
            else{
                if(canvas->OnScrollUp())InvalidateRect(window.GetHWnd(), nullptr, false);
            }
        }
    }return 0;
    default: return DefWindowProcW(hWnd, msg, wParam, lParam);
    }
}


HMONITOR MainWindowState::GetMonitor() const noexcept{
    return monitorInfo.GetMonitor();
}

MainWindowState::~MainWindowState() noexcept{
}