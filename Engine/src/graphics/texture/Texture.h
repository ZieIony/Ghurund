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
        virtual Status loadInternal(ResourceManager &resourceManager, ResourceContext &context, const DirectoryPath &workingDir, MemoryInputStream &stream, LoadOption options) {
            Status result;
            image = (Image*)resourceManager.load(context, workingDir, stream, &result, options);
            if(filterStatus(result, options)!=Status::OK)
                return result;
            return init(context, *image);
        }

        virtual Status saveInternal(ResourceManager &resourceManager, ResourceContext &context, const DirectoryPath &workingDir, MemoryOutputStream &stream, SaveOption options)const {
            return resourceManager.save(*image, context, workingDir, stream, options);
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

        void set(CommandList &commandList, unsigned int index) {
            commandList.addResourceRef(textureResource.Get());
            commandList.addResourceRef(textureUploadHeap.Get());

            commandList.get()->SetGraphicsRootDescriptorTable(index, descHandle.getGpuHandle());
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