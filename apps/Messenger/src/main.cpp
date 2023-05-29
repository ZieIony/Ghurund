#include "Ghurund.Engine.h"

#include "core/application/CommandLine.h"

#include "MessengerApplication.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    using namespace Ghurund;
    using namespace Ghurund::Core;

    Settings settings = CommandLine(cmdLine).Parameters;
    std::unique_ptr<LogOutput> logOutput = std::make_unique<CustomConsoleLogOutput>(_T("logs"));
    main<Messenger::MessengerApplication>(&settings, std::move(logOutput));
    return 0;
}