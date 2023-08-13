#include "Ghurund.Core.h"

#include "core/application/Application.h"
#include "ui/font/Font.h"

using namespace Ghurund::Core;
using namespace Ghurund::UI;

namespace Samples {
    class SampleApplication:public Ghurund::Core::Application {
    public:
        virtual void onInit() override {
            Font* f = ghnew Font();
            FilePath filePath(_T("resources/fonts/lato_regular.ttf"));
            File file(filePath);
            Buffer buffer;
            file.read(buffer);
            f->init(buffer.Data, buffer.Size);

            ResourceManager.save(*f->Atlas, FilePath(_T("output.png")), DirectoryPath());

            f->release();
        }
    };
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Core::main<Samples::SampleApplication>();
    return 0;
}
