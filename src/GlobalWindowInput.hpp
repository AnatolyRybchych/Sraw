#pragma once
#include <stdexcept>

#include "UnicodeWindows.hpp"
#include "MouseMessages.hpp"
#include "MouseLowLevelHandler.hpp"
#include "KeyboardLowLevelHandler.hpp"

LRESULT CALLBACK LowLevelkeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam);

class GlobalWindowInput{
    friend LRESULT CALLBACK LowLevelkeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam);
private:
    static GlobalWindowInput *instance;
    KeyboardLowLevelHandler &keyboardLL;
    
    GlobalWindowInput(KeyboardLowLevelHandler &keyboardLL);
protected:
    HHOOK keyboardHook;
public:
    static void Init(KeyboardLowLevelHandler &keyboardLL);
    static void Dispose();

    ~GlobalWindowInput() noexcept;
};