#include "ghcdxpch.h"
#include "AdapterOutput.h"

namespace Ghurund::Core::DirectX {
    void AdapterOutput::initModes() {
        unsigned int num = 0;
        DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
        unsigned int flags = DXGI_ENUM_MODES_SCALING;

        output->GetDisplayModeList(format, flags, &num, 0);

        DXGI_MODE_DESC* modes = ghnew DXGI_MODE_DESC[num];
        output->GetDisplayModeList(format, flags, &num, modes);

        for (unsigned int i = 0; i < num; i++)
            displayModes.add(makeShared<DisplayMode>(modes[i]));

        delete[] modes;
    }
    
    AdapterOutput::AdapterOutput(ComPtr<IDXGIOutput> output):output(output) {
        output->GetDesc(&desc);

        name = desc.DeviceName;

        initModes();
    }
}
