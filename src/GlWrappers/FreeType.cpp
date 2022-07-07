#include "FreeType.hpp"

FT_Library FreeType::lib = nullptr;

FT_Library FreeType::GetLib(){
    if(lib == nullptr){
        FT_Error err = FT_Init_FreeType(&lib);
        if(err){
            std::runtime_error("cannot load freetype library");
        }
    }

    return lib;
}
