#pragma once

#include "core/object/NotNull.h"
#include "core/resource/Resource.h"
#include "engine/graphics/shader/IShader.h"
#include "engine/parameter/ParameterProvider.h"
#include "engine/graphics/shader/ValueInput.h"
#include "engine/graphics/shader/TextureInput.h"
#include "engine/parameter/TextureParameter.h"
#include "engine/parameter/ValueParameter.h"

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
        IShader* shader = nullptr;
        List<std::pair<ValueInput*, IntrusivePointer<BaseValueParameter>>> valueParameters;
        List<std::pair<TextureInput*, IntrusivePointer<TextureParameter>>> textureParameters;

        inline void initParameters() {
            for (auto& vi : shader->ValueInputs) {
                auto p = IntrusivePointer(vi.makeParameter());
                valueParameters.add({ &vi, p });
                parameters.put(p.get());
            }
            for (auto& ti : shader->TextureInputs) {
                auto p = IntrusivePointer(ti.makeParameter());
                textureParameters.add({ &ti, p });
                parameters.put(p.get());
            }
        }

        inline void finalize() {
            safeRelease(shader);
            parameters.clear();
        }

    protected:
        Material(const Material& other):Resource(other), shader(other.shader) {
            if (shader) {
                shader->addReference();
                for (auto& vp : other.valueParameters) {
                    auto p = IntrusivePointer((BaseValueParameter*)vp.second->clone());
                    valueParameters.add({ vp.first, p });
                    parameters.put(p.get());
                }
                for (auto& tp : other.textureParameters) {
                    auto p = IntrusivePointer(tp.second->clone());
                    textureParameters.add({ tp.first, p });
                    parameters.put(p.get());
                }
            }
        }

        ~Material() {
            finalize();
        }

    public:
        Material() {}

        Material(NotNull<IShader> shader):shader(shader.get()) {
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

        IShader* getShader() {
            return shader;
        }

        void setShader(IShader* shader) {
            setPointer(this->shader, shader);
            valueParameters.clear();
            textureParameters.clear();
            parameters.clear();
            if (shader)
                initParameters();
        }

        __declspec(property(get = getShader, put = setShader)) IShader* Shader;

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