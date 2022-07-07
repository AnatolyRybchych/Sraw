#include "Fonts.hpp"
#include "../paths.hpp"

std::unique_ptr<Fonts> Fonts::intance = nullptr;

const Fonts &Fonts::Get() noexcept{
    if(intance == nullptr){
        intance = std::unique_ptr<Fonts>(new Fonts());
    }
    return *intance.get();
}

Fonts::Fonts(){
    FT_Error err = FT_New_Face(FreeType::GetLib(), FileFontArial, 0, &arial);
    if(err) std::runtime_error(std::string() + "cannot open face " + FileFontArial);
}

FT_Face Fonts::GetArial() const noexcept{
    return arial;
}
