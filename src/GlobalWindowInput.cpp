#include "GlobalWindowInput.hpp"

GlobalWindowInput *GlobalWindowInput::instance = nullptr;


LRESULT CALLBACK LowLevelkeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam){
    if(nCode < 0) 
        return CallNextHookEx(NULL, nCode, wParam, lParam);
    else
        GlobalWindowInput::instance->keyboardLL.OnKeyboardHookLL((KeyboardMessages)wParam, (KBDLLHOOKSTRUCT*)lParam);
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

GlobalWindowInput::GlobalWindowInput(KeyboardLowLevelHandler &keyboardLL):keyboardLL(keyboardLL){
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelkeyboardHookProc, NULL, 0);
    if(keyboardHook == nullptr)
        throw std::runtime_error("cannot register WH_KEYBOARD_LL");
}

void GlobalWindowInput::Init(KeyboardLowLevelHandler &keyboardLL){
    if(instance == nullptr)
        instance = new GlobalWindowInput(keyboardLL);
    else
        throw std::logic_error("InputManager is already initialized");
}

void GlobalWindowInput::Dispose(){
    if(instance == nullptr)
        std::logic_error("InputManager is not initialized");
    
    delete instance;
    instance = nullptr;
}

GlobalWindowInput::~GlobalWindowInput() noexcept{
    UnhookWindowsHookEx(keyboardHook);
}
