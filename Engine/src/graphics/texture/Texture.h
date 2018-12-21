#pragma once

#include "graphics/Graphics.h"
#include "graphics/Fence.h"
#include "core/Logger.h"
#include "Image.h"

namespace Ghurund {
    class Texture:public Resource {
    private:
        ComPtr<ID3D12Resource> textureResource;
        ComPtr<ID3D12Resource> textureUploadHeap;

        Image *image = nullptr;

    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, ResourceContext &context, MemoryInputStream &stream, LoadOption options) {
            image = ghnew Image();
            Status result = image->load(resourceManager, context, stream.readUnicode(), nullptr, options);
            if(result!=Status::OK)
                return result;
            return init(context, *image);
        }

        virtual Status saveInternal(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options)const {
            stream.writeUnicode(image->FileName);
            return Status::OK;
        }

    public:
        DescriptorHandle descHandle;

        ~Texture() {
            finalize();
        }

        void finalize() {
            textureResource.ReleaseAndGetAddressOf();
            textureUploadHeap.ReleaseAndGetAddressOf();
            if(image!=nullptr)
                image->release();
        }

        virtual void invalidate() {
            finalize();
            image = nullptr;
            __super::invalidate();
        }

        virtual bool isValid() {
            return image!=nullptr&&image->Valid&&__super::Valid;
        }

        Status init(ResourceContext &context, Image &image);

        void set(CommandList &commandList) {
            commandList.addResourceRef(textureResource.Get());
            commandList.addResourceRef(textureUploadHeap.Get());

            commandList.get()->SetGraphicsRootDescriptorTable(2, descHandle.getGpuHandle());
        }

        virtual const Ghurund::Type &getType() const override {
            return Type::TEXTURE;
        }

        static const Array<ResourceFormat*> &getFormats() {
            static const Array<ResourceFormat*> formats = {(ResourceFormat*)&ResourceFormat::JPG};
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*> &Formats;
    };
}