#pragma once

#include "engine/directx/shader/DxShader.h"
#include "engine/graphics/IMaterial.h"
#include "engine/parameter/ParameterManager.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Engine::DirectX;

    class Material:public IMaterial {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Material::GET_TYPE();
#pragma endregion

    private:
        DxShader* shader = nullptr;
        bool supportsTransparency = false;

        void finalize() {
            safeRelease(shader);
        }

    protected:
        virtual void loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options);
        virtual void saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const;

    public:

        Material() {}

        Material(DxShader* shader) {
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

        void initParameters(ParameterManager& parameterManager) {
            //shader->initParameters(parameterManager);
            //OnParametersChanged();
        }

        void updateParameters() {
            //shader->updateParameters();
        }

        bool set(Graphics& graphics, CommandList& commandList) {
            return shader->set(graphics, commandList);
        }

        DxShader* getShader() {
            return shader;
        }

        void setShader(DxShader* shader) {
            setPointer(this->shader, shader);
        }

        __declspec(property(get = getShader, put = setShader)) DxShader* Shader;

        bool getSupportsTransparency() {
            return supportsTransparency;
        }

        void setSupportsTransparency(bool supportsTransparency) {
            if (this->supportsTransparency != supportsTransparency) {
                this->supportsTransparency = supportsTransparency;
                //shader->makePipelineState(supportsTransparency);
            }
        }

        __declspec(property(get = getSupportsTransparency, put = setSupportsTransparency)) bool SupportsTransparency;

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return Material::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_MATERIAL = ResourceFormat(L"material", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_MATERIAL };

        static const inline uint32_t VERSION = 0;
#pragma endregion
    };
}