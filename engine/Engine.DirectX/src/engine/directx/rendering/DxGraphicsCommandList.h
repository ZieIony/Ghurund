#pragma once

#include "engine/directx/Fence.h"

#include "core/object/NotNull.h"
#include "engine/directx/CommandList.h"

namespace Ghurund::Engine::DirectX {
    class DxGraphics;

    class DxGraphicsCommandList: public CommandList {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = DxGraphicsCommandList::GET_TYPE();
#pragma endregion

    public:
        DxGraphicsCommandList() {}

        ~DxGraphicsCommandList();

        void init(DxGraphics& graphics, NotNull<ID3D12CommandQueue> queue);

        bool setRootSignature(ID3D12RootSignature* rootSignature);
    };
}
