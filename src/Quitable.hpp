#pragma once

class Quitable{
public:
    virtual void QuitApp() noexcept = 0;
    virtual void HideWindow() noexcept = 0;
    virtual void HideWindowAndResoreState() noexcept = 0;
    virtual void HideWindowSaveStateToFile() noexcept = 0;
    virtual void HideWindowCopyStateToClipboard() noexcept = 0;
};