#include "CutBmpWindow.hpp"

#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int CutBmpWindow::counter = 0;

LRESULT CutBmpWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept{
    switch (msg){
    case WM_PAINT:{
        PAINTSTRUCT ps;
        HDC dc = BeginPaint(hWnd, &ps);

        RECT clientRect;
        GetClientRect(hWnd, &clientRect);
        
        BitBlt(backBuffer, 0, 0, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top, bg, 0, 0, SRCCOPY);
        BitBlt(backBuffer, MIN(x1, x2), MIN(y1, y2), MAX(x1, x2) - MIN(x1, x2), MAX(y1, y2) - MIN(y1, y2), bmpDc, MIN(x1, x2), MIN(y1, y2), SRCCOPY);

        BitBlt(dc, 0, 0, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top, backBuffer, 0, 0, SRCCOPY);

        EndPaint(hWnd, &ps);
    }return 0;
    case WM_ERASEBKGND:{

    }return 1;
    case WM_RBUTTONDOWN:
    case WM_LBUTTONDOWN:{
        isMouseDown = true;
        x1 = x2 = LOWORD(lParam);
        y1 = y2 = HIWORD(lParam);
        InvalidateRect(hWnd, NULL, 0);
    }return 0;
    case WM_MOUSEMOVE:{
        if(isMouseDown){
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, 0);
        }
    }return 0;
    case WM_RBUTTONUP:
    case WM_LBUTTONUP:{
        if(isMouseDown){
            ShowWindow(hWnd, SW_HIDE);
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            
            HDC screenDc = GetDC(NULL);
            HDC memDc = CreateCompatibleDC(screenDc);
            HBITMAP result = CreateCompatibleBitmap(screenDc, MAX(x1, x2) - MIN(x1, x2), MAX(y1, y2) - MIN(y1, y2));
            SelectObject(memDc, result);
            RECT r = {
                0, 0, 100, 100
            };
            FillRect(memDc, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));

            BitBlt(memDc, 0, 0, MAX(x1, x2) - MIN(x1, x2), MAX(y1, y2) - MIN(y1, y2), bmpDc, MIN(x1, x2), MIN(y1, y2), SRCCOPY);
            onCut(result);

            DeleteObject(result);
            DeleteDC(memDc);
        }
    }return 0;
    default:
        return DefWindowProcW(hWnd, msg, wParam, lParam);
    }
}

static int CursorPosX() noexcept{
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    return cursorPos.x;
}

static int CursorPosY() noexcept{
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    return cursorPos.y;
}

CutBmpWindow::CutBmpWindow(HINSTANCE hInst, HBITMAP bitmap, std::function<void(HBITMAP bmp)> onCut) noexcept
:Window(hInst, (std::wstring(L"WndClassCutBmp") + std::to_wstring(counter++)).c_str(), L"Cut image", CursorPosX(), CursorPosY(), 100, 100, WS_POPUPWINDOW | WS_SYSMENU, nullptr, WS_EX_TOPMOST){
    BITMAP bitmapHdr;
    GetObject(bitmap, sizeof(bitmapHdr), &bitmapHdr);
    bmpCx = bitmapHdr.bmWidth;
    bmpCy = bitmapHdr.bmHeight;

    this->onCut = onCut;
    bmpDc = CreateCompatibleDC(NULL);
    bmp = (HBITMAP)CopyImage(bitmap, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
    bg = CreateCompatibleDC(NULL);
    bgBmp = (HBITMAP)CopyImage(bitmap, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
    SelectObject(bmpDc, bmp);
    SelectObject(bg, bgBmp);

    Gdiplus::Graphics g(bg);
    Gdiplus::SolidBrush b(Gdiplus::Color(120, 170, 170, 255));
    g.FillRectangle(&b, 0, 0, bmpCx, bmpCy);

    backBufferBmp = (HBITMAP)CopyImage(bgBmp, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
    backBuffer = CreateCompatibleDC(NULL);
    SelectObject(backBuffer, backBufferBmp);

    ShowWindow(GetHWnd(), SW_MAXIMIZE);
}

CutBmpWindow::~CutBmpWindow() noexcept{
    DeleteObject(bmp);
    DeleteDC(bmpDc);
    DeleteObject(bg);
    DeleteDC(bg);
    DeleteObject(backBufferBmp);
    DeleteDC(backBuffer);
}