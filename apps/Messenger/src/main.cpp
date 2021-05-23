#include "Ghurund.h"

#include "MessengerApplication.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Settings settings;
    settings.windowSize = { 200,300 };
    settings.parse(cmdLine);
    std::unique_ptr<Ghurund::LogOutput> logOutput = std::make_unique<Ghurund::CustomConsoleLogOutput>(_T("logs"));
    Ghurund::main<Messenger::MessengerApplication>(settings, std::move(logOutput));
    return 0;
}