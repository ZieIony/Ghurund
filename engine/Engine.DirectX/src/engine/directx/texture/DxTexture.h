#pragma once

#include "core/image/Image.h"
#include "engine/directx/buffer/DescriptorHeap.h"
#include "engine/directx/CommandList.h"
#include "engine/graphics/texture/ITexture.h"

namespace Ghurund::Engine::DirectX {
    class DxTexture:public ITexture {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = DxTexture::GET_TYPE();
#pragma endregion

    private:
		ComPtr<ID3D12Resource> textureResource;
        DescriptorHandle descHandle;

        Ghurund::Core::Image* image = nullptr;

        bool uploaded = false;

    protected:
        virtual bool getIsValidInternal() const override {
			return __super::getIsValidInternal() && image != nullptr && image->IsValid && uploaded;
        }

        ~DxTexture() {
            finalize();
        }

    public:
        void finalize() {
            uploaded = false;
            textureResource.Reset();
            if (image != nullptr)
                image->release();
        }

        virtual void invalidate() {
            finalize();
            image = nullptr;
            __super::invalidate();
        }

        void init(Ghurund::Core::Image& image, class DxGPUMemoryManager& memoryManager);

        inline Ghurund::Core::Image* getImage() {
            return image;
        }

        __declspec(property(get = getImage)) Ghurund::Core::Image* Image;

        virtual const IntSize& getSize() const override {
            return image->Size;
        }

        void set(CommandList& commandList, unsigned int index) {
            commandList.addResourceRef(textureResource.Get());
            commandList.get()->SetGraphicsRootDescriptorTable(index, descHandle.getGpuHandle());
        }

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return DxTexture::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_XML = ResourceFormat(L"xml", ResourceFormatOptions::CAN_LOAD);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_XML };

        static const inline uint32_t VERSION = 0;
#pragma endregion
    };
}
