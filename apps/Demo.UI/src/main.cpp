#include "Ghurund.Engine.h"

import Demo.DemoApplication;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Core::main<Demo::DemoApplication>();
    return 0;
}