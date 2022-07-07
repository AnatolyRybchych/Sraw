#pragma once
#include "FreeType.hpp"
#include <memory>

class Fonts{
private:
    static std::unique_ptr<Fonts> intance;

    FT_Face arial = nullptr;
public:
    static const Fonts &Get() noexcept;
    Fonts();
    FT_Face GetArial() const noexcept;
};