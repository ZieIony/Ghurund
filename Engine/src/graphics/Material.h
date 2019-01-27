#pragma once

#include "core/MemoryStream.h"
#include "graphics/buffer/DynamicBuffer.h"
#include "graphics/shader/Shader.h"
#include "graphics/texture/Image.h"
#include "graphics/texture/Texture.h"
#include "resource/Resource.h"

namespace Ghurund {
    class Material:public Resource, public ParameterProvider {
    private:
        Shader *shader = nullptr;
        PointerMap<ASCIIString, Texture*> textures;
        bool supportsTransparency = false;

        void finalize() {
            safeRelease(shader);
        }

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
            finalize();
        }

        virtual void invalidate() {
            finalize();
            textures.clear();
            __super::invalidate();
        }

        virtual bool isValid() const override {
            for(size_t i = 0; i<textures.Size; i++)
                if(!textures.getValue(i)->Valid)
                    return false;
            return shader!=nullptr&&shader->Valid&&__super::Valid;
        }

        virtual void initParameters(ParameterManager &parameterManager) override {
            shader->initParameters(parameterManager);
        }

        virtual void updateParameters() override {
            shader->updateParameters();
        }

        virtual Array<Parameter*> &getParameters() override {
            return shader->Parameters;
        }

        bool set(Graphics &graphics, CommandList &commandList) {
            bool changed = shader->set(graphics, commandList);

            if(textures.Size>0) // TODO: handle textures properly
                textures.getValue(0)->set(commandList);

            return changed;
        }

        Shader *getShader() {
            return shader;
        }

        void setShader(Shader *shader) {
            setPointer(this->shader, shader);
        }

        __declspec(property(get = getShader, put = setShader)) Shader *Shader;

        PointerMap<ASCIIString, Texture*> &getTextures() {
            return textures;
        }

        __declspec(property(get = getTextures)) PointerMap<ASCIIString, Texture*> &Textures;

        bool getSupportsTransparency() {
            return supportsTransparency;
        }

        void setSupportsTransparency(bool supportsTransparency) {
            if(this->supportsTransparency!=supportsTransparency) {
                this->supportsTransparency = supportsTransparency;
                shader->makePipelineState(supportsTransparency);
            }
        }

        __declspec(property(get = getSupportsTransparency, put = setSupportsTransparency)) bool SupportsTransparency;

        virtual const Ghurund::Type &getType() const override {
            return Type::MATERIAL;
        }

        static const Array<ResourceFormat*> &getFormats() {
            static const Array<ResourceFormat*> formats = {(ResourceFormat*)&ResourceFormat::MATERIAL};
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*> &Formats;
    };
}