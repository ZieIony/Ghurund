#include "ghedxpch.h"
#include "DxCubeMap.h"

#include "core/reflection/TypeBuilder.h"
#include "engine/directx/memory/DxGPUMemoryManager.h"

namespace Ghurund::Engine::DirectX {
    const Ghurund::Core::Type& DxCubeMap::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<DxCubeMap>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<DxCubeMap>()
            .withSupertype(__super::GET_TYPE())
            .withConstructor(CONSTRUCTOR);

        return TYPE;
    }

    void DxCubeMap::init(
        DxGPUMemoryManager& memoryManager
    ) {
        memoryManager.resetUpload();

        Array<List<IntrusivePointer<Ghurund::Core::Image>>> images = {
            imagesRight, imagesLeft,
            imagesTop, imagesBottom,
            imagesFront, imagesBack
        };
        textureResource = memoryManager.makeCubeMap(images);
        descHandle = memoryManager.makeCubeMapRV(textureResource, images[0][0]->Format, imagesTop.Size);

        memoryManager.executeUploads();
        State = ResourceState::INITIALIZED;
    }

    void DxCubeMap::setImages(
        List<IntrusivePointer<Ghurund::Core::Image>>& imagesTop,
        List<IntrusivePointer<Ghurund::Core::Image>>& imagesBottom,
        List<IntrusivePointer<Ghurund::Core::Image>>& imagesLeft,
        List<IntrusivePointer<Ghurund::Core::Image>>& imagesRight,
        List<IntrusivePointer<Ghurund::Core::Image>>& imagesFront,
        List<IntrusivePointer<Ghurund::Core::Image>>& imagesBack
    ) {
        if (State != ResourceState::EMPTY) {
            deinit_internal();
            unload_internal();
        }

        size = imagesTop[0]->Size;
        format = imagesTop[0]->Format;

        this->imagesTop = imagesTop;
        this->imagesBottom = imagesBottom;
        this->imagesLeft = imagesLeft;
        this->imagesRight = imagesRight;
        this->imagesFront = imagesFront;
        this->imagesBack = imagesBack;

        dataSize.system = sizeof(*this);

        State = ResourceState::LOADED;
    }
}
