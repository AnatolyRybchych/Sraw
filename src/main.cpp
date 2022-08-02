#include "App.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    App app(GetModuleHandleW(NULL));
    return app.Run();
}
