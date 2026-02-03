#include "Ghurund.Engine.2D.h"
#include "Ghurund.Engine.DirectX.h"

#include "DemoApplication.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Core::main<Demo::DemoApplication>();
    return 0;
}