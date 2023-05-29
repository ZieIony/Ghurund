#include "Ghurund.Engine.h"

#include "EditorApplication.h"
#include "core/application/CommandLine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Settings settings = Ghurund::Core::CommandLine(cmdLine).Parameters;
    Ghurund::main<Ghurund::Editor::EditorApplication>(_T("Ghurund::Editor"), &settings);
    return 0;
}