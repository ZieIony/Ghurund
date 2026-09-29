#pragma once

#include "core/image/Image.h"
#include "engine/directx/buffer/DescriptorHeap.h"
#include "engine/directx/CommandList.h"
#include "engine/graphics/cubemap/ICubeMap.h"

namespace Ghurund::Engine::DirectX {
    class DxCubeMap:public ICubeMap {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = DxCubeMap::GET_TYPE();
#pragma endregion

    private:
		ComPtr<ID3D12Resource> textureResource;
        DescriptorHandle descHandle;

        Array<Ghurund::Core::Image*> images = 6;

        bool uploaded = false;

        void finalize();

    protected:
        virtual bool getIsValidInternal() const override;

        ~DxCubeMap() {
            finalize();
        }

    public:
        virtual void invalidate();

        void init(
            Ghurund::Core::Image& imageTop,
            Ghurund::Core::Image& imageBottom,
            Ghurund::Core::Image& imageLeft,
            Ghurund::Core::Image& imageRight,
            Ghurund::Core::Image& imageFront,
            Ghurund::Core::Image& imageBack,
            class DxGPUMemoryManager& memoryManager
        );

        /*inline Ghurund::Core::Image* getImage() {
            return image;
        }

        __declspec(property(get = getImage)) Ghurund::Core::Image* Image;*/

        virtual const IntSize& getSize() const override {
            return images[0]->Size;
        }

        void set(CommandList& commandList, unsigned int index) {
            commandList.addResourceRef(textureResource.Get());
            commandList.get()->SetGraphicsRootDescriptorTable(index, descHandle.getGpuHandle());
        }

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return DxCubeMap::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_XML = ResourceFormat(L"xml", ResourceFormatOptions::CAN_LOAD);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_XML };

        static const inline uint32_t VERSION = 0;
#pragma endregion
    };
}
