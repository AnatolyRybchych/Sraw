#pragma once

#include "MainWindow.hpp"
#include "GlobalWindowInput.hpp"
#include "Quitable.hpp"


class App: public KeyboardLowLevelHandler, public Quitable{
private:
    HINSTANCE hInstance;
    MainWindow *window;
public:
    virtual void QuitApp() noexcept override;
    virtual void HideWindow() noexcept override;
    virtual void HideWindowAndResoreState() noexcept override;
    virtual void HideWindowSaveStateToFile() noexcept override;
    virtual void HideWindowCopyStateToClipboard() noexcept override;
    bool OnKeyboardHookLL(KeyboardMessages message, KBDLLHOOKSTRUCT *args) noexcept override;
    App(HINSTANCE hInstance);
    int Run();
};