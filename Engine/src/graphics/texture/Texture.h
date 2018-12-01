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
        PointerList<CommandList*> commandLists;

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
            for(size_t i = 0; i<commandLists.Size; i++)
                if(commandLists.get(i)->references(*this))
                    commandLists.get(i)->wait();

            textureResource.Reset();
            textureUploadHeap.Reset();
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
            commandLists.add(&commandList);
            commandList.addResourceRef(*this);

            commandList.get()->SetGraphicsRootDescriptorTable(2, descHandle.getGpuHandle());
        }

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