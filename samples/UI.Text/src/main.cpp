#include "Ghurund.Core.h"

#include "core/application/Application.h"

namespace Samples {
    class SampleApplication:public Ghurund::Core::Application {
    public:
        virtual void onInit() override {
        }
    };
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Core::Settings settings;
    settings.parse(GetCommandLine());
    Ghurund::Core::main<Samples::SampleApplication>(&settings);
    return 0;
}
