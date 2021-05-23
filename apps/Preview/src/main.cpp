#include "Ghurund.h"

#include "PreviewApplication.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Settings settings;
    settings.parse(cmdLine);
    Ghurund::main<Preview::PreviewApplication>(settings);
    return 0;
}