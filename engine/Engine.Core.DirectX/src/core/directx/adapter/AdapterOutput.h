#pragma once

#include "DisplayMode.h"

#include <wrl.h>

namespace Ghurund::Core::DirectX {
    using namespace Microsoft::WRL;
    using namespace Ghurund::Core;

    class AdapterOutput: public Object {
    private:
        DXGI_OUTPUT_DESC desc;
        WString name;
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

        static const Ghurund::Core::Type& GET_TYPE();

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

        WString& getName() {
            return name;
        }

        List<DisplayMode*>& getDisplayModes() {
            return displayModes;
        }

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}