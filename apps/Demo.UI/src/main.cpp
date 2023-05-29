#include "Ghurund.Engine.h"

#include "DemoApplication.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Core::main<Demo::DemoApplication>();
    return 0;
}