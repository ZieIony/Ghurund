#include "Ghurund.h"

#include "DemoApplication.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Settings settings;
    settings.parse(cmdLine);
    Ghurund::main<Demo::DemoApplication>(settings);
    return 0;
}