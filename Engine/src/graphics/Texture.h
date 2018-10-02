#pragma once

#include "Graphics.h"
#include "Fence.h"
#include "core/Logger.h"
#include "Image.h"

namespace Ghurund {
    class Texture:public Resource {
    private:
        ComPtr<ID3D12Resource> textureResource;
        ComPtr<ID3D12Resource> textureUploadHeap;

        Image *image = nullptr;

    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, MemoryInputStream &stream, LoadOption options) {
            image = ghnew Image();
            Status result = image->load(resourceManager, stream.readUnicode(), nullptr, options);
            if(result!=Status::OK)
                return result;
            return init(resourceManager, *image);
        }

        virtual Status saveInternal(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options)const {
            stream.writeUnicode(image->FileName);
            return Status::OK;
        }

    public:
        DescriptorHandle descHandle;

        ~Texture() {
            textureResource.Reset();
            textureUploadHeap.Reset();
            if(image!=nullptr)
                image->release();
        }

        Status init(ResourceManager &resourceManager, Image &image);

        virtual const Ghurund::Type &getType() const override {
            return Type::TEXTURE;
        }

        virtual const Array<ResourceFormat> &getFormats() const override {
            static const Array<ResourceFormat> formats = {ResourceFormat::AUTO, ResourceFormat::JPG};
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::JPG;
        }
    };
}