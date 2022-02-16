#include "Ghurund.Engine.h"

#include "EditorApplication.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Settings settings;
    settings.parse(GetCommandLine());
    Ghurund::main<Ghurund::Editor::EditorApplication>(_T("Ghurund::Editor"), &settings);
    return 0;
}