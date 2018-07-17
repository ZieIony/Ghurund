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
        shared_ptr<Ghurund::Texture> texture;

        static const List<ResourceFormat> formats;

    protected:
        virtual bool isVersioned()const {
            return true;
        }

        virtual unsigned int getVersion()const {
            return 0;
        }

        virtual Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size);

        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size)const;

        virtual void clean() {
            shader.reset();
            texture.reset();
        }

    public:

        Material() {}

        Material(shared_ptr<Shader> shader){
            this->shader = shader;
        }

        void set(ID3D12GraphicsCommandList *commandList) {
            shader->set(commandList);

            commandList->SetGraphicsRootDescriptorTable(2, texture->descHandle.getGpuHandle());
        }

        shared_ptr<Shader> getShader() {
            return shader;
        }

        void setShader(shared_ptr<Shader> shader) {
            this->shader = shader;
        }

        __declspec(property(get = getShader, put = setShader)) shared_ptr<Shader> Shader;

        shared_ptr<Texture> getTexture() {
            return texture;
        }

        void setTexture(shared_ptr<Texture> texture) {
            this->texture = texture;
        }

        __declspec(property(get = getTexture, put = setTexture)) shared_ptr<Texture> Texture;

        virtual const List<ResourceFormat> &getFormats() const override {
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::MATERIAL;
        }
    };
}