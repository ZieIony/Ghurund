#pragma once

#include "DxConstantBuffer.h"

#include "variables/DxBufferConstantInfo.h"
#include "variables/DxTextureConstantInfo.h"
#include "engine/directx/CommandList.h"
#include "engine/graphics/shader/ConstantCollection.h"
#include "engine/directx/rendering/DxObjectParametersBuffer.h"

namespace Ghurund::Engine::DirectX {
    class DxConstantCollection:public ConstantCollection {
    private:
        uint32_t globalParametersSlot, objectParametersSlot;

    public:
        DxConstantCollection() {}

        void init(
            const List<DxBufferConstantInfo*>& bufferConstantInfos,
            const List<DxTextureConstantInfo*>& textureConstantInfos,
            const List<DxBufferConstantInfo*>& srvConstantInfos,
            const List<DxTextureConstantInfo*>& uavConstantInfos
        );

		void apply(
            CommandList& commandList, 
            DxConstantBuffer& globalParameters,
            DxObjectParametersBuffer& objectParameters
        );

        void apply(CommandList& commandList);
    };
}
