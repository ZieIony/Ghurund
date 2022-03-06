#pragma once

#include "AdapterOutput.h"
#include "Status.h"

namespace Ghurund::Core::DirectX {
    using namespace Microsoft::WRL;
    using namespace Ghurund::Core;

    class GraphicsAdapter: public Object {
    private:
        ComPtr<IDXGIAdapter1> adapter;
        DXGI_ADAPTER_DESC1 desc;
        WString name;
        List<AdapterOutput*> outputs;

        Status initOutputs() {
            ComPtr<IDXGIOutput> output;
            unsigned int outputIndex = 0;
            while (true) {
                if (DXGI_ERROR_NOT_FOUND == adapter->EnumOutputs(outputIndex, &output))
                    break;

                outputs.add(ghnew AdapterOutput(output));
                outputIndex++;
            }

            return outputs.Size > 0 ? Status::OK : Status::DIRECTX12_NOT_SUPPORTED;
        }

    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        GraphicsAdapter(ComPtr<IDXGIAdapter1> adapter) {
            this->adapter = adapter;
            adapter->GetDesc1(&desc);

            name = desc.Description;

            initOutputs();
        }

        ~GraphicsAdapter() {
            outputs.deleteItems();
        }

        ComPtr<IDXGIAdapter1> get() {
            return adapter;
        }

        WString& getName() {
            return name;
        }

        size_t getDedicatedVideoMemory() {
            return desc.DedicatedVideoMemory;
        }

        List<AdapterOutput*>& getOutputs() {
            return outputs;
        }

        static const Ghurund::Core::Type& GET_TYPE();
    };
}