#include "wintoastlib.h"

using namespace WinToastLib;

class CustomHandler : public IWinToastHandler {
public:
    void toastActivated() const {
        std::wcout << L"The user clicked in this toast" << std::endl;
    }

    void toastDismissed(WinToastDismissalReason state) const {
        switch (state) {
        case UserCanceled:
            std::wcout << L"The user dismissed this toast" << std::endl;
            break;
        case TimedOut:
            std::wcout << L"The toast has timed out" << std::endl;
            break;
        case ApplicationHidden:
            std::wcout << L"The application hid the toast using ToastNotifier.hide()" << std::endl;
            break;
        default:
            std::wcout << L"Toast not activated" << std::endl;
            break;
        }
    }

    void toastFailed() const {
        std::wcout << L"Error showing current toast" << std::endl;
    }
};

int wmain(int argc, LPWSTR *argv)
{
    if (WinToast::isCompatible()) {
        std::wcerr << L"Error, your system in not supported!" << std::endl;
        return 1;
    }

    WinToast::instance()->setAppName(L"Console WinToast Example");
    WinToast::instance()->setAppUserModelId(L"WinToast Console Example");
    if (!WinToast::instance()->initialize()) {
        std::wcerr << L"Error, your system in not compatible!" << std::endl;
        return 1;
    }

    WinToastTemplate templ = WinToastTemplate(WinToastTemplate::Text01);
    templ.setTextField(L"Hello, world!", WinToastTemplate::FirstLine);

    if (WinToast::instance()->showToast(templ, new CustomHandler()) < 0) {
        std::wcerr << L"Could not launch your toast notification!";
        return 1;
    }

    // Give the handler a chance for 15 seconds
    Sleep(15000);

    return 0;
}
