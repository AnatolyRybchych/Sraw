#pragma once

#include "UnicodeWindows.hpp"
#include "KeyboardMessages.hpp"

class KeyboardLowLevelHandler
{
public:
    virtual bool OnKeyboardHookLL(KeyboardMessages message, KBDLLHOOKSTRUCT *args) noexcept = 0;
};