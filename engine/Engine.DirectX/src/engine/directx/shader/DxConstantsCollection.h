#pragma once

#include "variables/DxBufferConstantInfo.h"
#include "variables/DxTextureConstantInfo.h"
#include <engine/directx/CommandList.h>
#include "engine/graphics/shader/ConstantsCollection.h"

namespace Ghurund::Engine::DirectX {
    class DxConstantsCollection:public ConstantsCollection {
    public:
        DxConstantsCollection() {}

        void init(
            const List<DxBufferConstantInfo*>& bufferConstantInfos,
            const List<DxTextureConstantInfo*>& textureConstantInfos,
            const List<DxTextureConstantInfo*>& uavConstantInfos
        );

		void apply(CommandList& commandList);
    };
}
