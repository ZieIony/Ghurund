#pragma once

#include "core/object/NotNull.h"
#include "core/resource/Resource.h"
#include "engine/graphics/shader/Shader.h"
#include "engine/parameter/ParameterProvider.h"
#include "engine/graphics/shader/ValueInput.h"
#include "engine/graphics/shader/TextureInput.h"
#include "engine/parameter/TextureParameter.h"
#include "engine/parameter/ValueParameter.h"
#include <engine/graphics/memory/IGPUMemoryManager.h>

namespace Ghurund::Engine {

    class Material:public Ghurund::Core::Resource, public ParameterProvider {
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
        IGPUMemoryManager& memoryManager;
        Shader* shader = nullptr;
        List< IntrusivePointer<ConstantBuffer>> constantBuffers;
        List<std::pair<ValueInput*, IntrusivePointer<BaseValueParameter>>> valueParameters;
        List<std::pair<TextureInput*, IntrusivePointer<TextureParameter>>> textureParameters;

        void initParameters();

        inline void finalize() {
            safeRelease(shader);
            parameters.clear();
        }

    protected:
        Material(const Material& other);

        ~Material() {
            finalize();
        }

    public:
        Material(IGPUMemoryManager& memoryManager):memoryManager(memoryManager) {}

        Material(
            IGPUMemoryManager& memoryManager,
            NotNull<Shader> shader
        ):memoryManager(memoryManager), shader(shader.get()) {
            shader->addReference();
            initParameters();
        }

        virtual void invalidate() {
            finalize();
            __super::invalidate();
        }

        virtual bool isValid() const override {
            return shader != nullptr && shader->Valid && __super::Valid;
        }

        Shader* getShader() {
            return shader;
        }

        inline void setShader(Shader* shader) {
            setPointer(this->shader, shader);
            valueParameters.clear();
            textureParameters.clear();
            parameters.clear();
            if (shader)
                initParameters();
        }

        __declspec(property(get = getShader, put = setShader)) Shader* Shader;

        bool getIsTransparencyEnabled() const {
            return shader->IsTransparencyEnabled;
        }

        __declspec(property(get = getIsTransparencyEnabled)) bool IsTransparencyEnabled;

        void setParameters(ParameterManager& parameterManager);

        virtual Material* clone() const {
            return ghnew Material(*this);
        }

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