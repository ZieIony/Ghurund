#include "Ghurund.Engine.h"

import Preview.PreviewApplication;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Core::main<Preview::PreviewApplication>();
    return 0;
}