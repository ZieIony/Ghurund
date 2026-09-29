#include "ghedxpch.h"
#include "DxTexture.h"

#include "core/reflection/TypeBuilder.h"
#include "engine/directx/memory/DxGPUMemoryManager.h"

namespace Ghurund::Engine::DirectX {
    const Ghurund::Core::Type& DxTexture::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<DxTexture>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<DxTexture>()
            .withSupertype(__super::GET_TYPE())
            .withConstructor(CONSTRUCTOR);

        return TYPE;
    }

    void DxTexture::init(
        Ghurund::Core::Image& image,
        DxGPUMemoryManager& memoryManager
    ) {
        setPointer(this->image, &image);

        memoryManager.resetUpload();

        textureResource = memoryManager.makeTexture(image);
        descHandle = memoryManager.makeTextureRV(textureResource, image.Format);

        memoryManager.executeUploads();

        uploaded = true;
    }
}
