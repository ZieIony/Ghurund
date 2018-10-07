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
        Shader *shader = nullptr;
        Map<ASCIIString, Texture*> textures;

    protected:
        virtual bool isVersioned()const {
            return true;
        }

        virtual unsigned int getVersion()const {
            return 0;
        }

        virtual Status loadInternal(ResourceManager &resourceManager, ResourceContext &context, MemoryInputStream &stream, LoadOption options);
        virtual Status saveInternal(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options) const;

    public:

        Material() {}

        Material(Shader *shader) {
            setPointer(this->shader, shader);
        }

        ~Material() {
            shader->release();
            for(size_t i = 0; i<textures.Size; i++)
                textures.getValue(i)->release();
        }

        void set(CommandList &commandList, ParameterManager &parameterManager) {
            shader->set(commandList, parameterManager);

            commandList.get()->SetGraphicsRootDescriptorTable(2, textures.getValue(0)->descHandle.getGpuHandle());
        }

        Shader *getShader() {
            return shader;
        }

        void setShader(Shader *shader) {
            this->shader = shader;
        }

        __declspec(property(get = getShader, put = setShader)) Shader *Shader;

        Map<ASCIIString, Texture*> &getTextures() {
            return textures;
        }

        __declspec(property(get = getTextures)) Map<ASCIIString, Texture*> &Textures;

        virtual const Ghurund::Type &getType() const override {
            return Type::MATERIAL;
        }

        virtual const Array<ResourceFormat> &getFormats() const override {
            static const Array<ResourceFormat> formats = {ResourceFormat::AUTO, ResourceFormat::MATERIAL};
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::MATERIAL;
        }
    };
}