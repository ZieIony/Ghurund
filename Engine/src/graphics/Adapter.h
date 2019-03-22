#pragma once

#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include "d3dx12.h"

#include "Ghurund.h"
#include "collection/List.h"
#include "collection/String.h"
#include "core/Object.h"
#include "core/Logger.h"

#include <wrl.h>

using namespace DirectX;
using namespace Microsoft::WRL;

namespace Ghurund {
    class DisplayMode: public Object {
    private:
        unsigned int width, height;
        float refreshRate;
        DXGI_FORMAT format;

    public:
        DisplayMode(DXGI_MODE_DESC mode) {
            width = mode.Width;
            height = mode.Height;
            refreshRate = (float)mode.RefreshRate.Numerator/mode.RefreshRate.Denominator;
            format = mode.Format;
        }

        unsigned int getWidth() {
            return width;
        }

        unsigned int getHeight() {
            return height;
        }

        float getRefreshRate() {
            return refreshRate;
        }

        DXGI_FORMAT getFormat() {
            return format;
        }

        const static Ghurund::Type& TYPE;

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

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

            DXGI_MODE_DESC *modes = ghnew DXGI_MODE_DESC[num];
            output->GetDisplayModeList(format, flags, &num, modes);

            for(unsigned int i = 0; i<num; i++)
                displayModes.add(ghnew DisplayMode(modes[i]));

            delete[] modes;
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

        String &getName() {
            return name;
        }

        List<DisplayMode*> &getDisplayModes() {
            return displayModes;
        }

        const static Ghurund::Type& TYPE;

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    class Adapter: public Object {
    private:
        ComPtr<IDXGIAdapter1> adapter;
        DXGI_ADAPTER_DESC1 desc;
        String name;
        List<AdapterOutput*> outputs;

        Status initOutputs() {
            ComPtr<IDXGIOutput> output;
            unsigned int outputIndex = 0;
            while(true) {
                if(DXGI_ERROR_NOT_FOUND == adapter->EnumOutputs(outputIndex, &output))
                    break;

                outputs.add(ghnew AdapterOutput(output));
                outputIndex++;
            }

            return outputs.Size>0 ? Status::OK : Status::DIRECTX12_NOT_SUPPORTED;
        }

    public:
        Adapter(ComPtr<IDXGIAdapter1> adapter) {
            this->adapter = adapter;
            adapter->GetDesc1(&desc);

            name = desc.Description;

            initOutputs();
        }

        ~Adapter() {
            outputs.deleteItems();
        }

        ComPtr<IDXGIAdapter1> get() {
            return adapter;
        }

        String &getName() {
            return name;
        }

        unsigned int getDedicatedVideoMemory() {
            return desc.DedicatedVideoMemory;
        }

        List<AdapterOutput*> &getOutputs() {
            return outputs;
        }

        const static Ghurund::Type& TYPE;

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}