#pragma once

#include "core/directx/Graphics.h"
#include "core/directx/Fence.h"
#include "core/directx/CommandList.h"
#include "core/image/Image.h"

namespace Ghurund::Core::DirectX {
    class Texture:public Resource {
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

    protected:
        virtual void loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options);
        virtual void saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options)const;

    public:
        DescriptorHandle descHandle;

        ~Texture() {
            finalize();
        }

        void finalize() {
            textureResource.ReleaseAndGetAddressOf();
            textureUploadHeap.ReleaseAndGetAddressOf();
            if (image != nullptr)
                image->release();
        }

        virtual void invalidate() {
            finalize();
            image = nullptr;
            __super::invalidate();
        }

        virtual bool isValid() {
            return image != nullptr && image->Valid && __super::Valid;
        }

        Status init(Graphics& graphics, CommandList& commandList, Ghurund::Core::Image& image);

        inline Ghurund::Core::Image* getImage() {
            return image;
        }

        __declspec(property(get = getImage)) Ghurund::Core::Image* Image;

        void set(CommandList& commandList, unsigned int index) {
            commandList.addResourceRef(textureResource.Get());
            commandList.addResourceRef(textureUploadHeap.Get());

            commandList.get()->SetGraphicsRootDescriptorTable(index, descHandle.getGpuHandle());
        }

        static const inline ResourceFormat FORMAT_JPG = ResourceFormat(L"jpg", true, false);
        static const inline ResourceFormat FORMAT_JPEG = ResourceFormat(L"jpeg", true, false);
        static const inline ResourceFormat FORMAT_PNG = ResourceFormat(L"png", true, false);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_JPG, FORMAT_JPEG, FORMAT_PNG };

        virtual const Array<ResourceFormat>& getFormats() const override {
            return FORMATS;
        }
    };
}