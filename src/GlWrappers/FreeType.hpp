#pragma once 
#include <stdexcept>
#include <ft2build.h>
#include FT_FREETYPE_H

class FreeType{
private:
    static FT_Library lib;
public:
    static FT_Library GetLib();
};
