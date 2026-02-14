#pragma once

#include "core/image/Image.h"
#include "engine/directx/CommandList.h"
#include "engine/directx/DxGraphics.h"
#include "engine/graphics/texture/ITexture.h"

#include <dxgiformat.h>

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
        ComPtr<ID3D12Resource> textureUploadHeap;

        Ghurund::Core::Image* image = nullptr;

        bool uploaded = false;

        DXGI_FORMAT adjustFormat(DXGI_FORMAT format, TextureType textureType);

    public:
        DescriptorHandle descHandle;

        ~DxTexture() {
            finalize();
        }

        void finalize() {
            uploaded = false;
            textureResource.Reset();
            textureUploadHeap.Reset();
            if (image != nullptr)
                image->release();
        }

        virtual void invalidate() {
            finalize();
            image = nullptr;
            __super::invalidate();
        }

        virtual bool isValid() {
			return image != nullptr && image->Valid && __super::Valid && uploaded;
        }

        void init(DxGraphics& graphics, CommandList& commandList, Ghurund::Core::Image& image, TextureType textureType);

        inline Ghurund::Core::Image* getImage() {
            return image;
        }

        __declspec(property(get = getImage)) Ghurund::Core::Image* Image;

        virtual const IntSize& getSize() const override {
            return image->Size;
        }

        void set(CommandList& commandList, unsigned int index) {
            commandList.addResourceRef(textureResource.Get());
            commandList.addResourceRef(textureUploadHeap.Get());

            commandList.get()->SetGraphicsRootDescriptorTable(index, descHandle.getGpuHandle());
        }

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return DxTexture::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_JPG = ResourceFormat(L"jpg", ResourceFormatOptions::CAN_LOAD);
        static const inline ResourceFormat FORMAT_JPEG = ResourceFormat(L"jpeg", ResourceFormatOptions::CAN_LOAD);
        static const inline ResourceFormat FORMAT_PNG = ResourceFormat(L"png", ResourceFormatOptions::CAN_LOAD);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_JPG, FORMAT_JPEG, FORMAT_PNG };
#pragma endregion
    };
}