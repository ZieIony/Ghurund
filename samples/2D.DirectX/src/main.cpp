#include "Ghurund.Engine.2D.h"
#include "Ghurund.Engine.DirectX.h"

#include "SampleApplication.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Core::main<Sample::SampleApplication>();
    return 0;
}
