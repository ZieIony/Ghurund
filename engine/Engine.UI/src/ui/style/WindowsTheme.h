#pragma once

#include "ui/Color.h"

#include <windows.foundation.h>
#include <windows.ui.viewmanagement.h>
#include <wrl.h>

#pragma comment(lib, "WindowsApp.lib")

namespace Ghurund::UI {
    class WindowsTheme {
    private:
        WindowsTheme() = delete;

        static inline Color accentDark1 = 0;
        static inline Color accentDark2 = 0;
        static inline Color accentDark3 = 0;
        static inline Color accentLight1 = 0;
        static inline Color accentLight2 = 0;
        static inline Color accentLight3 = 0;
        static inline Color accentColor = 0;

    public:
        static Status init() {
            namespace abi_vm = ABI::Windows::UI::ViewManagement;
            namespace wrl = Microsoft::WRL;
            namespace wf = Windows::Foundation;

            wrl::ComPtr<abi_vm::IUISettings> settings;
            auto stringRef = wrl::Wrappers::HStringReference(RuntimeClass_Windows_UI_ViewManagement_UISettings);
            if (FAILED(wf::ActivateInstance(stringRef.Get(), &settings)))
                return Status::CALL_FAIL;

            abi_vm::IUISettings3* uiSettings = nullptr;
            if (FAILED(settings->QueryInterface(__uuidof(uiSettings), reinterpret_cast<void**>(&uiSettings))))
                return Status::CALL_FAIL;

            ABI::Windows::UI::Color color;
            uiSettings->GetColorValue(abi_vm::UIColorType_Accent, &color);
            accentColor = Color(color.R, color.G, color.B, color.A);

            uiSettings->GetColorValue(abi_vm::UIColorType_AccentDark1, &color);
            accentDark1 = Color(color.R, color.G, color.B, color.A);
            uiSettings->GetColorValue(abi_vm::UIColorType_AccentDark2, &color);
            accentDark2 = Color(color.R, color.G, color.B, color.A);
            uiSettings->GetColorValue(abi_vm::UIColorType_AccentDark3, &color);
            accentDark3 = Color(color.R, color.G, color.B, color.A);

            uiSettings->GetColorValue(abi_vm::UIColorType_AccentLight1, &color);
            accentLight1 = Color(color.R, color.G, color.B, color.A);
            uiSettings->GetColorValue(abi_vm::UIColorType_AccentLight2, &color);
            accentLight2 = Color(color.R, color.G, color.B, color.A);
            uiSettings->GetColorValue(abi_vm::UIColorType_AccentLight3, &color);
            accentLight3 = Color(color.R, color.G, color.B, color.A);

            return Status::OK;
        }

        static Color getAccentColor() { return accentColor; }

        static Color getAccentDark1() { return accentDark1; }
        static Color getAccentDark2() { return accentDark2; }
        static Color getAccentDark3() { return accentDark3; }

        static Color getAccentLight1() { return accentLight1; }
        static Color getAccentLight2() { return accentLight2; }
        static Color getAccentLight3() { return accentLight3; }
    };
}