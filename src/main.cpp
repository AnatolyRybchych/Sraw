#include <iostream>
#include "UnicodeWindows.hpp"
#include "MainWindow.hpp"

static int run(HINSTANCE instance);
static MainWindow *window;

int main(int argc, char const *argv[]){
    return run(GetModuleHandleW(NULL));
}

static int run(HINSTANCE instance){
    window = new MainWindow(instance);

    window->Show();
    
    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return msg.wParam;
}
