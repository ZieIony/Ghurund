#pragma once

#include "resource/Resource.h"
#include "graphics/shader/Shader.h"
#include "core/MemoryStream.h"
#include "graphics/buffer/DynamicBuffer.h"
#include "graphics/Image.h"
#include "graphics/Texture.h"

namespace Ghurund {
    class Material:public Resource {
    private:
        Shader shader;
        Image image;
        Texture texture;

    protected:
        virtual bool isVersioned()const {
            return true;
        }

        virtual unsigned int getVersion()const {
            return 0;
        }

        Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size, unsigned int flags = 0);

        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size, unsigned int flags = 0)const;

    public:

        void set(ID3D12GraphicsCommandList *commandList) {
            shader.set(commandList);

            ID3D12DescriptorHeap* descriptorHeaps[] = {texture.srvHeap.Get()};
            commandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

            commandList->SetGraphicsRootDescriptorTable(1, texture.srvHeap->GetGPUDescriptorHandleForHeapStart());
        }
    };
}