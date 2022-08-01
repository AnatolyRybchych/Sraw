#pragma once

class DrawingTarget{
public: 
    virtual void Redraw() const noexcept = 0;
};