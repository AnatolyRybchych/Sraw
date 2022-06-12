#include "App.hpp"

App::App(HINSTANCE hInstance){
    this->hInstance = hInstance;
}

int App::Run(){
    window = new MainWindow(hInstance);
    GlobalWindowInput::Init(*this);

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return msg.wParam;
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
        window->Show();
    }

    return true;
}
