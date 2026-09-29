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

    void DxCubeMap::finalize() {
        uploaded = false;
        textureResource.Reset();
        imagesTop.clear();
        imagesBottom.clear();
        imagesLeft.clear();
        imagesRight.clear();
        imagesFront.clear();
        imagesBack.clear();
    }

    bool DxCubeMap::getIsValidInternal() const {
        bool imagesValid = [&] {
            for (auto& image : imagesTop) {
                if (image == nullptr || !image->IsValid)
                    return false;
            }
            for (auto& image : imagesBottom) {
                if (image == nullptr || !image->IsValid)
                    return false;
            }
            for (auto& image : imagesLeft) {
                if (image == nullptr || !image->IsValid)
                    return false;
            }
            for (auto& image : imagesRight) {
                if (image == nullptr || !image->IsValid)
                    return false;
            }
            for (auto& image : imagesFront) {
                if (image == nullptr || !image->IsValid)
                    return false;
            }
            for (auto& image : imagesBack) {
                if (image == nullptr || !image->IsValid)
                    return false;
            }
            return true;
        }();
		return __super::getIsValidInternal() && imagesValid && uploaded;
    }

    void DxCubeMap::invalidate() {
        finalize();
        __super::invalidate();
    }

    void DxCubeMap::init(
        List<IntrusivePointer<Ghurund::Core::Image>>& imagesTop,
        List<IntrusivePointer<Ghurund::Core::Image>>& imagesBottom,
        List<IntrusivePointer<Ghurund::Core::Image>>& imagesLeft,
        List<IntrusivePointer<Ghurund::Core::Image>>& imagesRight,
        List<IntrusivePointer<Ghurund::Core::Image>>& imagesFront,
        List<IntrusivePointer<Ghurund::Core::Image>>& imagesBack,
        DxGPUMemoryManager& memoryManager
    ) {
        size = imagesTop[0]->Size;
        format = imagesTop[0]->Format;

        this->imagesTop = imagesTop;
        this->imagesBottom = imagesBottom;
        this->imagesLeft = imagesLeft;
        this->imagesRight = imagesRight;
        this->imagesFront = imagesFront;
        this->imagesBack = imagesBack;
        memoryManager.resetUpload();

        Array<List<IntrusivePointer<Ghurund::Core::Image>>> images = {
            imagesRight, imagesLeft,
            imagesTop, imagesBottom,
            imagesFront, imagesBack
        };
        textureResource = memoryManager.makeCubeMap(images);
        descHandle = memoryManager.makeCubeMapRV(textureResource, images[0][0]->Format, imagesTop.Size);

        memoryManager.executeUploads();

        uploaded = true;
    }
}
