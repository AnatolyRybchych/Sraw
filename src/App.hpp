#pragma once
#include <iostream>
#include "UnicodeWindows.hpp"
#include "MainWindow.hpp"
#include "GlobalWindowInput.hpp"


class App: public KeyboardLowLevelHandler{
private:
    HINSTANCE hInstance;
    MainWindow *window;
public:
    bool OnKeyboardHookLL(KeyboardMessages message, KBDLLHOOKSTRUCT *args) noexcept override;
    App(HINSTANCE hInstance);
    int Run();
};