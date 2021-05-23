#include "Ghurund.h"

#include "DemoApplication.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Settings settings;
    settings.parse(GetCommandLine());
    Ghurund::main<Demo::DemoApplication>(settings);
    return 0;
}