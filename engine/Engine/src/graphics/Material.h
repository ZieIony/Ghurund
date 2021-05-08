#pragma once

#include "graphics/shader/Shader.h"
#include "core/resource/Resource.h"

namespace Ghurund {
    class Material:public Resource, public ParameterProvider {
    private:
        Shader* shader = nullptr;
        bool supportsTransparency = false;

        void finalize() {
            safeRelease(shader);
        }

        static const Ghurund::Type& GET_TYPE();

    protected:
        virtual bool isVersioned()const {
            return true;
        }

        virtual unsigned int getVersion()const {
            return 0;
        }

        virtual Status loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options);
        virtual Status saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const;

    public:

        Material() {}

        Material(Shader* shader) {
            setPointer(this->shader, shader);
        }

        ~Material() {
            finalize();
        }

        virtual void invalidate() {
            finalize();
            __super::invalidate();
        }

        virtual bool isValid() const override {
            return shader != nullptr && shader->Valid && __super::Valid;
        }

        virtual void initParameters(ParameterManager& parameterManager) override {
            shader->initParameters(parameterManager);
            OnParametersChanged();
        }

        virtual void updateParameters() override {
            shader->updateParameters();
        }

        virtual const PointerArray<Parameter*>& getParameters() const override {
            return shader->Parameters;
        }

        bool set(Graphics& graphics, CommandList& commandList) {
            return shader->set(graphics, commandList);
        }

        Shader* getShader() {
            return shader;
        }

        void setShader(Shader* shader) {
            setPointer(this->shader, shader);
        }

        __declspec(property(get = getShader, put = setShader)) Shader* Shader;

        bool getSupportsTransparency() {
            return supportsTransparency;
        }

        void setSupportsTransparency(bool supportsTransparency) {
            if (this->supportsTransparency != supportsTransparency) {
                this->supportsTransparency = supportsTransparency;
                shader->makePipelineState(supportsTransparency);
            }
        }

        __declspec(property(get = getSupportsTransparency, put = setSupportsTransparency)) bool SupportsTransparency;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        static const Array<ResourceFormat>& getFormats() {
            static const Array<ResourceFormat> formats = {
                ResourceFormat(L"material", true, true)
            };
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat>& Formats;
    };
}