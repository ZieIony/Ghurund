#pragma once

#include "core/directx/Graphics.h"
#include "core/directx/Fence.h"
#include "core/directx/CommandList.h"
#include "core/image/Image.h"

namespace Ghurund::Core::DirectX {
    class Texture:public Resource {
    private:
		ComPtr<ID3D12Resource> textureResource;
        ComPtr<ID3D12Resource> textureUploadHeap;

        Ghurund::Core::Image* image = nullptr;

    protected:
        virtual Status loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options);
        virtual Status saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options)const;

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

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

        static const Ghurund::Core::Type& GET_TYPE();

        static const inline ResourceFormat FORMAT_JPG = ResourceFormat(L"jpg", true, false);
        static const inline ResourceFormat FORMAT_JPEG = ResourceFormat(L"jpeg", true, false);
        static const inline ResourceFormat FORMAT_PNG = ResourceFormat(L"png", true, false);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_JPG, FORMAT_JPEG, FORMAT_PNG };

        virtual const Array<ResourceFormat>& getFormats() const override {
            return FORMATS;
        }
    };
}