#pragma once

#include "ValueInput.h"
#include "TextureInput.h"
#include "CubeMapInput.h"
#include "MaterialInputCollection.h"

#include "core/object/NotNull.h"
#include "core/resource/Resource.h"
#include "engine/graphics/memory/IGPUMemoryManager.h"
#include "engine/graphics/rendering/GraphicsShader.h"
#include "engine/parameter/ParameterCollection.h"

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
        MaterialInputCollection inputs;
        IGPUMemoryManager* memoryManager = nullptr;
        GraphicsShader* shader = nullptr;
        List<IntrusivePointer<ConstantBuffer>> constantBuffers;
        List<BaseValueInput*> valueInputs;
        List<TextureInput*> textureInputs;
        List<CubeMapInput*> cubeMapInputs;

        inline void finalize() {
            safeRelease(shader);
            inputs.clear();
        }

    protected:
        Material(const Material& other);

        ~Material() {
            finalize();
        }

        virtual void initInputs();

        virtual bool getIsValidInternal() const override {
            return __super::getIsValidInternal() && shader != nullptr && shader->IsValid;
        }

    public:
        Material() {}

        void init(NotNull<IGPUMemoryManager> memoryManager) {
            this->memoryManager = memoryManager.get();
        }

        virtual void invalidate() {
            finalize();
            __super::invalidate();
        }

        inline MaterialInputCollection& getInputs() {
            return inputs;
        }

        __declspec(property(get = getInputs)) MaterialInputCollection& Inputs;
        
        inline GraphicsShader* getShader() const {
            return shader;
        }

        inline void setShader(GraphicsShader* shader) {
            setPointer(this->shader, shader);
            valueInputs.clear();
            textureInputs.clear();
            cubeMapInputs.clear();
            inputs.clear();
            if (shader)
                initInputs();
        }

        __declspec(property(get = getShader, put = setShader)) GraphicsShader* Shader;

        inline bool getIsTransparencyEnabled() const {
            return shader->IsTransparencyEnabled;
        }

        __declspec(property(get = getIsTransparencyEnabled)) bool IsTransparencyEnabled;

        void applyInputs(ParameterCollection& defaults);

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

        static const inline uint32_t VERSION = 1;
#pragma endregion
    };
}
