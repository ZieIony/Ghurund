#include "Ghurund.Engine.h"

#include "PreviewApplication.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Core::main<Preview::PreviewApplication>();
    return 0;
}