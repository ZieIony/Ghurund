#include "Ghurund.Engine.h"

#include "core/Int.h"

import Messenger.MessengerApplication;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    using namespace Ghurund;
    using namespace Ghurund::Core;

    Settings settings;
    settings.set(Settings::WIDTH, 200);
    settings.set(Settings::HEIGHT, 300);
    settings.parse(GetCommandLine());

    std::unique_ptr<LogOutput> logOutput = std::make_unique<CustomConsoleLogOutput>(_T("logs"));
    main<Messenger::MessengerApplication>(&settings, std::move(logOutput));
    return 0;
}