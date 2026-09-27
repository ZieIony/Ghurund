#include "ghedxpch.h"
#include "DxCubeMap.h"

#include "core/reflection/TypeBuilder.h"
#include "engine/directx/memory/DxGPUMemoryManager.h"

namespace Ghurund::Engine::DirectX {
    const Ghurund::Core::Type& DxCubeMap::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<DxCubeMap>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void DxCubeMap::finalize() {
        uploaded = false;
        textureResource.Reset();
        for (Image* image : images) {
            if (image)
                image->release();
        }
    }

    void DxCubeMap::invalidate() {
        finalize();
		for (size_t i = 0; i < images.Size; i++)
			images[i] = nullptr;
        __super::invalidate();
    }

    bool DxCubeMap::getIsValid() const {
        bool imagesValid = [&] {
            for (Image* image : images) {
                if (!image || !image->IsValid)
                    return false;
            }
            return true;
        }();
		return __super::getIsValid() && imagesValid && uploaded;
    }

    void DxCubeMap::init(
        Ghurund::Core::Image& imageTop,
        Ghurund::Core::Image& imageBottom,
        Ghurund::Core::Image& imageLeft,
        Ghurund::Core::Image& imageRight,
        Ghurund::Core::Image& imageFront,
        Ghurund::Core::Image& imageBack,
        DxGPUMemoryManager& memoryManager
    ) {
        setPointer(images[0], &imageRight);
        setPointer(images[1], &imageLeft);
        setPointer(images[2], &imageTop);
        setPointer(images[3], &imageBottom);
        setPointer(images[4], &imageFront);
        setPointer(images[5], &imageBack);

        memoryManager.resetUpload();

        Array<NotNull<Image>> imagesNotNull = { images[0], images[1], images[2], images[3], images[4], images[5] };
        textureResource = memoryManager.makeCubeMap(imagesNotNull);
        descHandle = memoryManager.makeCubeMapRV(textureResource, images[0]->Format);

        memoryManager.executeUploads();

        uploaded = true;
    }
}
