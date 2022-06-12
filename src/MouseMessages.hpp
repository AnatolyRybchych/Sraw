#pragma once
#include "UnicodeWindows.hpp"

enum class MouseMessages: UINT{
    LeftDown = WM_LBUTTONDOWN,
    LeftUp = WM_LBUTTONUP,
    RightDown = WM_RBUTTONDOWN,
    RightUp = WM_RBUTTONUP,
    Move = WM_MOUSEMOVE,
    Wheel = WM_MOUSEWHEEL,
    HWheel = 0x020E,
};
    