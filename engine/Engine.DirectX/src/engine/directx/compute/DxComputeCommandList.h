#pragma once

#include "engine/directx/CommandList.h"
#include "core/object/NotNull.h"

namespace Ghurund::Engine::DirectX {
    class DxGraphics;

    class DxComputeCommandList: public CommandList {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = DxComputeCommandList::GET_TYPE();
#pragma endregion

    public:
        void init(DxGraphics& graphics, NotNull<ID3D12CommandQueue> queue);

        bool setRootSignature(ID3D12RootSignature* rootSignature);
    };
}
