#include "App.hpp"

int main(int argc, char const *argv[]){
    App app(GetModuleHandleW(NULL));
    return app.Run();
}
