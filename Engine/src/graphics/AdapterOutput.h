#pragma once

#include "DisplayMode.h"

namespace Ghurund {
    using namespace DirectX;
    using namespace Microsoft::WRL;

    class AdapterOutput: public Object {
    private:
        DXGI_OUTPUT_DESC desc;
        String name;
        ComPtr<IDXGIOutput> output;
        List<DisplayMode*> displayModes;

        void initModes() {
            unsigned int num = 0;
            DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
            unsigned int flags = DXGI_ENUM_MODES_SCALING;

            output->GetDisplayModeList(format, flags, &num, 0);

            DXGI_MODE_DESC* modes = ghnew DXGI_MODE_DESC[num];
            output->GetDisplayModeList(format, flags, &num, modes);

            for (unsigned int i = 0; i < num; i++)
                displayModes.add(ghnew DisplayMode(modes[i]));

            delete[] modes;
        }

        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(AdapterOutput))
                .withSupertype(Object::TYPE);

            return TYPE;
        }

    public:
        AdapterOutput(ComPtr<IDXGIOutput> output) {
            this->output = output;
            output->GetDesc(&desc);

            name = desc.DeviceName;

            initModes();
        }

        ~AdapterOutput() {
            displayModes.deleteItems();
        }

        String& getName() {
            return name;
        }

        List<DisplayMode*>& getDisplayModes() {
            return displayModes;
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}