#ifndef TOASTHANDLER_H
#define TOASTHANDLER_H
#include "Photino.h"
#include "Photino.Notification.h"
#include "Dependencies/wintoastlib.h"
#include <WinUser.h>

using namespace WinToastLib;

class WinToastHandler : public IWinToastHandler
{
private:
    Photino* _window;
    PhotinoNotification* _notification;

public:
    WinToastHandler(PhotinoNotification* notification)
    {
        this->_notification = notification;
    }

    void toastActivated() const
    {
        ShowWindow(this->_window->getHwnd(), SW_SHOW);    // Make the window visible if it was hidden
        ShowWindow(this->_window->getHwnd(), SW_RESTORE); // Next, restore it if it was minimized
        SetForegroundWindow(this->_window->getHwnd());    // Finally, activate the window

        _notification->InvokeActivated();
    }

    void toastActivated(int actionIndex) const
    {
        std::vector<AutoString> actions = _notification->GetActions();

        AutoString action = actions.at(actionIndex);

        _notification->InvokeAction(action);
    }

    void toastDismissed(WinToastDismissalReason state) const
    {
        switch (state)
        {
            case WinToastDismissalReason::UserCanceled:
                _notification->InvokeDismissed(PhotinoNotificationDismissalReason::UserCanceled);
                break;

            case WinToastDismissalReason::ApplicationHidden:
                _notification->InvokeDismissed(PhotinoNotificationDismissalReason::ApplicationHidden);
                break;

            case WinToastDismissalReason::TimedOut:
                _notification->InvokeDismissed(PhotinoNotificationDismissalReason::TimedOut);
                break;
        }
    }

    void toastFailed() const
    {
        //
    }
};
#endif