#pragma once

#include "AdapterOutput.h"

namespace Ghurund::Engine::DirectX {
    using namespace Microsoft::WRL;
    using namespace Ghurund::Core;

	class DirectX12NotSupportedException:public std::exception {};

    class GraphicsAdapter {
    private:
        ComPtr<IDXGIAdapter1> adapter;
        size_t dedicatedVideoMemory, sharedSystemMemory;
        WString name;
        List<SharedPointer<AdapterOutput>> outputs;

        void initOutputs();

    public:
        GraphicsAdapter(ComPtr<IDXGIAdapter1> adapter):adapter(adapter) {
            DXGI_ADAPTER_DESC1 desc;
            adapter->GetDesc1(&desc);

            name = desc.Description;
            dedicatedVideoMemory = desc.DedicatedVideoMemory;
            sharedSystemMemory = desc.SharedSystemMemory;

            initOutputs();
        }

		GraphicsAdapter(const GraphicsAdapter& other):
            adapter(other.adapter),
            dedicatedVideoMemory(other.dedicatedVideoMemory),
            sharedSystemMemory(other.sharedSystemMemory),
            name(other.name),
            outputs(other.outputs) {}

        GraphicsAdapter(GraphicsAdapter&& other) noexcept:
            adapter(std::move(other.adapter)),
            dedicatedVideoMemory(std::move(other.dedicatedVideoMemory)),
            sharedSystemMemory(std::move(other.sharedSystemMemory)),
            name(std::move(other.name)),
            outputs(std::move(other.outputs)) {}

        ComPtr<IDXGIAdapter1> get() {
            return adapter;
        }

        const WString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const WString& Name;

        size_t getDedicatedVideoMemory() const {
            return dedicatedVideoMemory;
        }

        __declspec(property(get = getDedicatedVideoMemory)) size_t DedicatedVideoMemory;

        size_t getSharedSystemMemory() const {
            return sharedSystemMemory;
        }

        __declspec(property(get = getSharedSystemMemory)) size_t SharedSystemMemory;

        const List<SharedPointer<AdapterOutput>>& getOutputs() const {
            return outputs;
        }

        __declspec(property(get = getOutputs)) const List<SharedPointer<AdapterOutput>> Outputs;
    };
}