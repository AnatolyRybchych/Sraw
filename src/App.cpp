#include "App.hpp"
#include "DrawImage.hpp"
#include "MouseHighlight.hpp"
#include <iostream>
#include "UnicodeWindows.hpp"
#include "paths.hpp"
#include "GlWrappers/RenderText.hpp"
#include <shlobj.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

static BOOL SaveFileName(wchar_t *fileName, int filenameSize, const wchar_t *initialDir, const wchar_t *title, const wchar_t *filter, DWORD dwFlags){
    OPENFILENAMEW ofn;
    ZeroMemory( &ofn , sizeof( ofn));
	ofn.lStructSize = sizeof ( ofn );
	ofn.hwndOwner = NULL  ;
	ofn.lpstrFile = fileName ;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = filenameSize;
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex =1;
	ofn.lpstrFileTitle = NULL ;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = initialDir;
    ofn.lpstrTitle = title;
	ofn.Flags = dwFlags;

	return GetSaveFileNameW( &ofn );
}

static const wchar_t *DesctopDirUnicode(){
    static wchar_t path[MAX_PATH+1];
    if (SHGetSpecialFolderPathW(HWND_DESKTOP, path, CSIDL_DESKTOP, FALSE))
        return path;
    else
        return L"ERROR";
}

static void SaveHbitmapToFile(HBITMAP bmp, const wchar_t *file){
    std::string tmpDir(1000, 0);
    GetTempPathA(tmpDir.size(), tmpDir.data());
    sprintf(tmpDir.data(), "%s%s", tmpDir.c_str(), "__img__.png");

    HDC memDc = CreateCompatibleDC(NULL);
    SelectObject(memDc, bmp);

    BITMAPINFO bi;
    memset(&bi, 0, sizeof(bi));
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    GetDIBits(memDc, bmp, 0, 0, NULL, &bi, DIB_RGB_COLORS);
    int cx = bi.bmiHeader.biWidth;
    int cy = bi.bmiHeader.biHeight;

    char *bmpData = new char[cx * cy * 4];
    bi.bmiHeader.biCompression = 0;
    GetDIBits(memDc, bmp, 0, cy, bmpData, &bi, DIB_RGB_COLORS);
    DeleteDC(memDc);

    for(int i = 0; i < cx * cy; i++){
        int pixel = i * 4;
        char tmp = bmpData[pixel];
        bmpData[pixel] = bmpData[pixel +2];
        bmpData[pixel+2] = tmp;
    }

    stbi_flip_vertically_on_write(1);
    stbi_write_png(tmpDir.c_str(), cx, cy, 4, bmpData, cx * 4);


    delete[] bmpData;

    FILE *tmpFile = fopen(tmpDir.c_str(), "rb");
    FILE *newFile = _wfopen((std::wstring(file) + L".png").c_str(), L"wb");

    char *buffer = new char[1024];
    int readn = 0;
    while ((readn = fread(buffer, 1, 1024, tmpFile)) == 1024){
        fwrite(buffer, 1, readn, newFile);
    }
    fwrite(buffer, 1, readn, newFile);

    fclose(tmpFile);
    fclose(newFile);

    delete[] buffer;
}

App::App(HINSTANCE hInstance){
    this->hInstance = hInstance;
}

int App::Run(){
    Gdiplus::GdiplusStartup(&gdiToken, &startInput, NULL);

    window = new MainWindow(hInstance, *this);
    ResourceProvider::InitProvider();
    GlobalWindowInput::Init(*this);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);   
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    DrawImage::Init();
    MouseHighlight::Init();
    RenderText::InitDefaultRenderer(FileArial, ResourceProvider::GetProvider().GetRenderTextProgram());

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return msg.wParam;
}

void App::QuitApp() noexcept{
    if(MessageBoxW(window->GetHWnd(), L"Exit?", L"", MB_OKCANCEL) == IDOK)
        PostQuitMessage(0);
    else HideWindow();
}

void App::HideWindow() noexcept{
    window->Hide();
}

void App::HideWindowAndResoreState() noexcept{
    HideWindow();
    window->ClearCurrentState();
}

static void DrawBitmapToAnother(HBITMAP src, HBITMAP dst){
    HDC srcDc = CreateCompatibleDC(NULL);
    HDC dstDc = CreateCompatibleDC(NULL);

    SelectObject(srcDc, src);
    SelectObject(dstDc, dst);

    BITMAP bmpSrc;
    BITMAP bmpDst;
    GetObjectA(src, sizeof(bmpSrc), &bmpSrc);
    GetObjectA(dst, sizeof(bmpDst), &bmpDst);

    int x = 0;
    int y = 0;
    int cx = MAX(bmpSrc.bmWidth, bmpDst.bmWidth);
    int cy = MAX(bmpSrc.bmHeight, bmpDst.bmHeight);

    BLENDFUNCTION bl;
    bl.BlendOp = AC_SRC_OVER;
    bl.BlendFlags = 0;
    bl.SourceConstantAlpha = 255;
    bl.AlphaFormat = AC_SRC_ALPHA;

    AlphaBlend(dstDc, x, y, cx, cy, srcDc, x, y, cx, cy, bl);
    

    DeleteDC(srcDc);
    DeleteDC(dstDc);
}

void App::HideWindowSaveStateToFile() noexcept{
    HideWindow();
    HBITMAP state = window->CreateCurrentStateBitmap(); 
    HBITMAP bg = window->CreateBgBitmap(); 
    DrawBitmapToAnother(state, bg);

    cutBmpWindow = std::unique_ptr<CutBmpWindow>(new CutBmpWindow(hInstance, bg, std::bind(SaveCutedImageToFile, this, std::placeholders::_1)));
    DeleteObject(state);  
    DeleteObject(bg);  
}

void App::HideWindowCopyStateToClipboard() noexcept{
    HideWindow();
    HBITMAP state = window->CreateCurrentStateBitmap();
    HBITMAP bg = window->CreateBgBitmap(); 
    DrawBitmapToAnother(state, bg);

    cutBmpWindow = std::unique_ptr<CutBmpWindow>(new CutBmpWindow(hInstance, bg, std::bind(CopyCutedImageToClipboard, this, std::placeholders::_1)));
    DeleteObject(state);
}

void App::SaveCutedImageToFile(HBITMAP bmp) noexcept{    
    std::wstring fileName(1000, 0);
    if(SaveFileName(fileName.data(), fileName.size(), DesctopDirUnicode(), L"save image", L"png file (*.png), *.png", OFN_PATHMUSTEXIST)){
        SaveHbitmapToFile(bmp, fileName.c_str());
    }
}

void App::CopyCutedImageToClipboard(HBITMAP bmp) noexcept{
    OpenClipboard(window->GetHWnd());
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, bmp);
    CloseClipboard();
    
}

bool App::OnKeyboardHookLL(KeyboardMessages message, KBDLLHOOKSTRUCT *args) noexcept{
    static bool control = false;
    static bool win = false;

    if(args->vkCode == VK_ESCAPE){
        window->Hide();
        return true;
    }

    if(message == KeyboardMessages::KeyDown || message == KeyboardMessages::SysKeyDown){
        if(args->vkCode == VK_LCONTROL) control = true;
        else if(args->vkCode == VK_LWIN) win = true;
    }
    else if(message == KeyboardMessages::KeyUp || message == KeyboardMessages::SysKeyUp){
        if(args->vkCode == VK_LCONTROL) control = false;
        else if(args->vkCode == VK_LWIN) win = false;
    }

    if(control && win && (args->vkCode == VK_LCONTROL || args->vkCode == VK_LWIN)){
        if(IsWindowVisible(window->GetHWnd()))window ->Hide();
        else
            window->Show();
        win = false;
            control = false;
    }

    return true;
}
