#include "Ghurund.Core.h"
#include "Ghurund.Engine.h"
#include "Ghurund.Engine.OpenGL.h"

#include "SampleApplication.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Core::main<Sample::SampleApplication>();
    return 0;
}
