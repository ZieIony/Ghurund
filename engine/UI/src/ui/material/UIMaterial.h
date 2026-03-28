#pragma once

#include "ThemeParameter.h"
#include "UIInputs.h"

#include "engine/graphics/material/Material.h"
#include "ui/theme/AttributeKey.h"
#include "ui/theme/ThemedValue.h"

namespace Ghurund::UI {
	using namespace Ghurund::Engine;
	using namespace ::DirectX;

	class Theme;

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
		UIMaterial() {}

		inline UIInputs& getUIInputs() {
			return uiInputs;
		}

		__declspec(property(get = getUIInputs)) UIInputs& UIInputs;

		List<ThemeParameter> themeParameters;

		void setTheme(const Theme* theme);

		virtual UIMaterial* clone() const {
			return ghnew UIMaterial(*this);
		}
	};

	using MaterialKey = AttributeKey<UIMaterial>;
	using ThemedMaterial = ThemedValue<MaterialKey, UIMaterial>;

	template<>
	UIMaterial* resolveThemeValue(const Theme& theme, const MaterialKey& key);;
}

namespace Ghurund::Core {
	template<>
	const Type& getType<Ghurund::UI::ThemedMaterial>();
}
