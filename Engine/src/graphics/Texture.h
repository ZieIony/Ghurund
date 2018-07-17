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

        shared_ptr<Image> image;

        static const List<ResourceFormat> formats;

        Status init(Graphics &graphics, ID3D12GraphicsCommandList *commandList, Image *image);

    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size) {
            image.reset(ghnew Image());
            Status result = image->load(resourceManager, data, size);
            if(result!=Status::OK)
                return result;
            return init(resourceManager.Graphics, resourceManager.getCommandList()->get(), image.get());
        }

        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size)const {
            return image->save(resourceManager, data, size);
        }

        virtual void clean() {
            textureResource.Reset();
            textureUploadHeap.Reset();
            image.reset();
        }

    public:
        DescriptorHandle descHandle;
   
        ~Texture() {
            clean();
        }

        virtual const List<ResourceFormat> &getFormats() const override {
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::JPG;
        }
    };
}