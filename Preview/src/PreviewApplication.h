#include "PreviewWindow.h"

namespace Preview {
    class PreviewApplication:public Ghurund::Application {
    public:
        void onInit() {
            auto window = ghnew PreviewWindow(*this);
            window->Size = Settings.windowSize;
            Windows.add(window);
            window->activate();
        }
    };
}
