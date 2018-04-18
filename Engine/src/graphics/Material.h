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
        shared_ptr<Shader> shader;
        shared_ptr<Image> image;
        shared_ptr<Texture> texture;

    protected:
        virtual bool isVersioned()const {
            return true;
        }

        virtual unsigned int getVersion()const {
            return 0;
        }

        virtual Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size, unsigned int flags = 0);

        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size, unsigned int flags = 0)const;

        virtual void clean() {
            shader.reset();
            image.reset();
            texture.reset();
        }

    public:

        void set(ID3D12GraphicsCommandList *commandList) {
            shader->set(commandList);

            ID3D12DescriptorHeap* descriptorHeaps[] = {texture->srvHeap.Get()};
            commandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

            commandList->SetGraphicsRootDescriptorTable(1, texture->srvHeap->GetGPUDescriptorHandleForHeapStart());
        }

        shared_ptr<Shader> getShader() {
            return shader;
        }

        void setShader(shared_ptr<Shader> shader) {
            this->shader = shader;
        }

        __declspec(property(get = getShader, put = setShader)) shared_ptr<Shader> Shader;
    };
}