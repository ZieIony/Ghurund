#include "Ghurund.Engine.h"

import Preview.PreviewApplication;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Core::Settings settings;
    settings.parse(GetCommandLine());
    Ghurund::Core::main<Preview::PreviewApplication>(&settings);
    return 0;
}