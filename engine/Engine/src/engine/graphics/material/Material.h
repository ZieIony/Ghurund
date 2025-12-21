#pragma once

#include "core/resource/Resource.h"
#include "engine/parameter/ParameterCollection.h"
#include <engine/graphics/shader/IShader.h>

namespace Ghurund::Engine {

    class Material:public Ghurund::Core::Resource {
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

        void finalize() {
            safeRelease(shader);
        }

    protected:
        Material(const Material& other):Resource(other) {
            setPointer(this->shader, other.shader);
        }

        ~Material() {
            finalize();
        }

    public:
        Material() {}

        Material(NotNull<IShader> shader):shader(shader.get()) {
            shader->addReference();
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
        }

        __declspec(property(get = getShader, put = setShader)) IShader* Shader;

        bool getIsTransparencyEnabled() const {
            return shader->IsTransparencyEnabled;
        }

        __declspec(property(get = getIsTransparencyEnabled)) bool IsTransparencyEnabled;

        inline const ParameterCollection& getParameters() const {
            return shader->Parameters;
        }

        __declspec(property(get = getParameters)) const ParameterCollection& Parameters;

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