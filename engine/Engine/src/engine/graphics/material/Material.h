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
        GraphicsShader* shader = nullptr;
        List<IntrusivePointer<ConstantBuffer>> constantBuffers;
        List<BaseValueInput*> valueInputs;
        List<TextureInput*> textureInputs;
        List<CubeMapInput*> cubeMapInputs;

    protected:
        Material(const Material& other);

        ~Material() {
            unload();
        }

	public:
		Material() {}

		void init(NotNull<IGPUMemoryManager> memoryManager);

		inline void deinit() {
			if (State != ResourceState::INITIALIZED)
				return;
			valueInputs.clear();
			textureInputs.clear();
			cubeMapInputs.clear();
			inputs.clear();
			State = ResourceState::LOADED;
		}

		inline void unload() {
			safeRelease(shader);
			inputs.clear();
			State = ResourceState::EMPTY;
		}

		inline MaterialInputCollection& getInputs() {
			return inputs;
		}

		__declspec(property(get = getInputs)) MaterialInputCollection& Inputs;

		inline GraphicsShader* getShader() const {
			return shader;
		}

		inline void setShader(GraphicsShader* shader) {
			deinit();
			setPointer(this->shader, shader);
			if (shader) {
				dataSize.system = sizeof(*this);
				State = ResourceState::LOADED;
			} else {
				dataSize.system = sizeof(*this);
				State = ResourceState::EMPTY;
			}
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
        static const inline ResourceFormat FORMAT_XML = ResourceFormat(L"xml", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD, 1);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_XML };
#pragma endregion
    };
}
