#pragma once

#include "engine/graphics/material/Material.h"

#include <DirectXMath.h>

namespace Ghurund::UI {
	using namespace Ghurund::Engine;
	using namespace ::DirectX;

	class Theme;

	class UIInputs {
	private:
		Float2Input* sizeInput = nullptr;
		Float2Input* positionInput = nullptr;

	public:
		UIInputs() {}

		UIInputs(const UIInputs& other):sizeInput(sizeInput), positionInput(positionInput) {}

		inline void init(MaterialInputCollection& inputs) {
			sizeInput = (Float2Input*)inputs.get("size");
			positionInput = (Float2Input*)inputs.get("position");
		}

		inline void setSize(const XMFLOAT2& size) {
			sizeInput->Value = size;
		}

		__declspec(property(put = setSize)) const XMFLOAT2& Size;

		inline void setPosition(const XMFLOAT2& pos) {
			positionInput->Value = pos;
		}

		__declspec(property(put = setPosition)) const XMFLOAT2& Position;
	};

	enum class ThemeParameterType {
		COLOR, DIMENSION
	};

	struct ThemeParameter {
		AString name;
		AString key;
		ThemeParameterType type;
	};

	class UIMaterial:public Material {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = UIMaterial::GET_TYPE();
#pragma endregion

	private:
		UIInputs uiInputs = {};

	protected:
		virtual void initInputs() override {
			__super::initInputs();

			uiInputs.init(Inputs);
		}

	protected:
		UIMaterial(const UIMaterial& other):Material(other), uiInputs(other.uiInputs) {}

	public:
		UIMaterial(IGPUMemoryManager& memoryManager):Material(memoryManager) {}

		inline UIInputs& getUIInputs() {
			return uiInputs;
		}

		__declspec(property(get = getUIInputs)) UIInputs& UIInputs;

		List<ThemeParameter> themeParameters;

		void setTheme(const Theme* theme);
	};
}