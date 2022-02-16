#include "Ghurund.Engine.h"

#include "MessengerApplication.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    using namespace Ghurund;

    Settings settings;
    settings.set(Settings::WIDTH, 200);
    settings.set(Settings::HEIGHT, 300);
    settings.parse(GetCommandLine());

    std::unique_ptr<LogOutput> logOutput = std::make_unique<CustomConsoleLogOutput>(_T("logs"));
    main<Messenger::MessengerApplication>(&settings, std::move(logOutput));
    return 0;
}