#include "Ghurund.Core.h"
#include "Ghurund.Engine.h"
#include "Ghurund.Engine.OpenGL.h"

#include "DemoApplication.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Core::main<Demo::DemoApplication>();
    return 0;
}