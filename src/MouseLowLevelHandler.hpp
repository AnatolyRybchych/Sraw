#pragma once
#include "UnicodeWindows.hpp"
#include "MouseMessages.hpp"

class MouseLowLevelHandler
{
public:
    virtual bool OnMouseHookLL(MouseMessages message, MSLLHOOKSTRUCT *args) noexcept = 0;
};