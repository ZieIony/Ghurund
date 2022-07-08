#include "Ghurund.Core.h"

#include "core/application/Application.h"
#include <ui/gdi/font/Font.h>

using namespace Ghurund::Core;
using namespace Ghurund::UI::GDI;

namespace Samples {
    class SampleApplication:public Ghurund::Core::Application {
    public:
        virtual void onInit() override {
            Font* f = ghnew Font();
            FilePath filePath(_T("E:/Ghurund/resources/fonts/lato_regular.ttf"));
            File file(filePath);
            file.read();
            f->init(file.Data, file.Size);
            f->init(_T("ABCDEFGHIJK"));
            f->release();
        }
    };
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Core::main<Samples::SampleApplication>();
    return 0;
}
