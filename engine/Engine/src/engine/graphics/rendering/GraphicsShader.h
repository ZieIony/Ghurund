#pragma once

#include "engine/graphics/shader/Shader.h"
#include "engine/graphics/material/MaterialInputCollection.h"
#include "engine/graphics/material/ValueInput.h"
#include "engine/graphics/material/TextureInput.h"
#include "engine/graphics/material/CubeMapInput.h"
#include "engine/graphics/memory/IGPUMemoryManager.h"

namespace Ghurund::Engine {
    class GraphicsShader:public Shader {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = GraphicsShader::GET_TYPE();
#pragma endregion

    private:
        MaterialInputCollection inputs;
        List<BaseValueInput*> valueInputs;
        List<TextureInput*> textureInputs;
        List<CubeMapInput*> cubeMapInputs;

    protected:
        bool isTransparencyEnabled = false;

        ~GraphicsShader() {
            unload();
        }

    public:
        void init(NotNull<IGPUMemoryManager> memoryManager);

        inline void deinit() {
            valueInputs.clear();
            textureInputs.clear();
            cubeMapInputs.clear();
            inputs.clear();
        }

        inline void unload() {
            inputs.clear();
        }

        inline MaterialInputCollection& getInputs() {
            return inputs;
        }

        __declspec(property(get = getInputs)) MaterialInputCollection& Inputs;

        bool getIsTransparencyEnabled() {
            return isTransparencyEnabled;
        }

        __declspec(property(get = getIsTransparencyEnabled)) bool IsTransparencyEnabled;

        void applyInputs();
    };
}
