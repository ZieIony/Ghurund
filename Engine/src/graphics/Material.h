#pragma once

#include "resource/Resource.h"
#include "graphics/shader/Shader.h"
#include "core/MemoryStream.h"
#include "graphics/buffer/DynamicBuffer.h"
#include "graphics/Image.h"
#include "graphics/Texture.h"

namespace Ghurund {
    class Material:public Resource, ParameterProvider {
    private:
        shared_ptr<Shader> shader;
        Map<ASCIIString, shared_ptr<Ghurund::Texture>> textures;

    protected:
        virtual bool isVersioned()const {
            return true;
        }

        virtual unsigned int getVersion()const {
            return 0;
        }

        virtual Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size, unsigned long *bytesRead);
        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size)const;

        virtual void clean() {
            shader.reset();
            for(size_t i = 0; i<textures.Size; i++)
                textures.getValue(i).reset();
            textures.clear();
        }

    public:

        Material() {}

        Material(shared_ptr<Shader> shader) {
            this->shader = shader;
        }

        void set(ID3D12GraphicsCommandList *commandList) {
            shader->set(commandList);

            commandList->SetGraphicsRootDescriptorTable(2, textures.getValue(0)->descHandle.getGpuHandle());
        }

        shared_ptr<Shader> getShader() {
            return shader;
        }

        void setShader(shared_ptr<Shader> shader) {
            this->shader = shader;
        }

        __declspec(property(get = getShader, put = setShader)) shared_ptr<Shader> Shader;

        Map<ASCIIString, shared_ptr<Texture>> &getTextures() {
            return textures;
        }

        __declspec(property(get = getTextures)) Map<ASCIIString, shared_ptr<Texture>> &Textures;

        virtual const Array<ResourceFormat> &getFormats() const override {
            static const Array<ResourceFormat> formats = {ResourceFormat::AUTO, ResourceFormat::MATERIAL};
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::MATERIAL;
        }
    };
}