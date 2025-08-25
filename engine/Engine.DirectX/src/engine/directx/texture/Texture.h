#pragma once

#include "engine/directx/DxGraphics.h"
#include "engine/directx/Fence.h"
#include "engine/directx/CommandList.h"
#include "core/image/Image.h"
#include "engine/graphics/ITexture.h"

namespace Ghurund::Engine::DirectX {
    class Texture:public ITexture {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Texture::GET_TYPE();
#pragma endregion

    private:
		ComPtr<ID3D12Resource> textureResource;
        ComPtr<ID3D12Resource> textureUploadHeap;

        Ghurund::Core::Image* image = nullptr;

        bool uploaded = false;

    protected:
        virtual void loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options);
        virtual void saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options)const;

    public:
        DescriptorHandle descHandle;

        ~Texture() {
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
            return image != nullptr && image->Valid && __super::Valid&&uploaded;
        }

        void init(DxGraphics& graphics, CommandList& commandList, Ghurund::Core::Image& image);

        inline Ghurund::Core::Image* getImage() {
            return image;
        }

        __declspec(property(get = getImage)) Ghurund::Core::Image* Image;

        void set(CommandList& commandList, unsigned int index) {
            commandList.addResourceRef(textureResource.Get());
            commandList.addResourceRef(textureUploadHeap.Get());

            commandList.get()->SetGraphicsRootDescriptorTable(index, descHandle.getGpuHandle());
        }

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return Texture::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_JPG = ResourceFormat(L"jpg", ResourceFormatOptions::CAN_LOAD);
        static const inline ResourceFormat FORMAT_JPEG = ResourceFormat(L"jpeg", ResourceFormatOptions::CAN_LOAD);
        static const inline ResourceFormat FORMAT_PNG = ResourceFormat(L"png", ResourceFormatOptions::CAN_LOAD);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_JPG, FORMAT_JPEG, FORMAT_PNG };
#pragma endregion
    };
}