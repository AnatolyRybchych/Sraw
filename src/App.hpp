#pragma once

#include "MainWindow.hpp"
#include "GlobalWindowInput.hpp"
#include "Quitable.hpp"
#include "CutBmpWindow.hpp"
#include <gdiplus.h>
#include "ResourceProvider.hpp"

class App: public KeyboardLowLevelHandler, public Quitable{
private:
    HINSTANCE hInstance;
    MainWindow *window;

    Gdiplus::GdiplusStartupInput startInput;
    ULONG_PTR gdiToken;

    std::unique_ptr<CutBmpWindow> cutBmpWindow = nullptr;
public:
    virtual void QuitApp() noexcept override;
    virtual void HideWindow() noexcept override;
    virtual void HideWindowAndResoreState() noexcept override;
    virtual void HideWindowSaveStateToFile() noexcept override;
    virtual void HideWindowCopyStateToClipboard() noexcept override;
    void SaveCutedImageToFile(HBITMAP bmp) noexcept;
    void CopyCutedImageToClipboard(HBITMAP bmp) noexcept;
    bool OnKeyboardHookLL(KeyboardMessages message, KBDLLHOOKSTRUCT *args) noexcept override;
    App(HINSTANCE hInstance);
    int Run();
};