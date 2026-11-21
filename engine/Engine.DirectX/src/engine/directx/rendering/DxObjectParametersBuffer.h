#pragma once

#include "core/Buffer.h"
#include "engine/directx/CommandList.h"
#include "engine/graphics/rendering/ObjectParameters.h"

namespace Ghurund::Engine::DirectX {
    class DxObjectParametersBuffer {
    private:
        Buffer* buffer = nullptr;
        ID3D12Resource* resource = nullptr; // this is the memory on the gpu where our constant buffer will be placed.

        DxObjectParametersBuffer(const DxObjectParametersBuffer& other) = delete;

    public:
        DxObjectParametersBuffer() {}

        ~DxObjectParametersBuffer() {
            deinit();
        }

        void init(ComPtr<ID3D12Resource> uploadHeap);

        void deinit();

        void setValue(const ObjectParameters& value, size_t index);

        void set(CommandList& commandList, uint32_t bindSlot);
    };
}
