#include "ghedxpch.h"
#include "GraphicsAdapter.h"

namespace Ghurund::Engine::DirectX {
    void GraphicsAdapter::initOutputs() {
        ComPtr<IDXGIOutput> output;
        unsigned int outputIndex = 0;
        while (true) {
            if (DXGI_ERROR_NOT_FOUND == adapter->EnumOutputs(outputIndex, &output))
                break;

            outputs.add(makeShared<AdapterOutput>(output));
            outputIndex++;
        }
    }
}