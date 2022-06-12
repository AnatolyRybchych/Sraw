#pragma once

#include "UnicodeWindows.hpp"

enum class KeyboardMessages:UINT{
    KeyDown = WM_KEYDOWN,
    KeyUp = WM_KEYUP,
    SysKeyUp = WM_SYSKEYUP,
    SysKeyDown = WM_SYSKEYDOWN,
};