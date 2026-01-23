#include "ghuipch.h"
#include "UIMaterial.h"

#include "ui/theme/Theme.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& UIMaterial::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = Ghurund::Core::TypeBuilder<UIMaterial>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void UIMaterial::setTheme(const Theme* theme) {
		if (!theme)
			return;
		for (auto& param : themeParameters) {
			if (param.type == ThemeParameterType::COLOR) {
				Float4Input* input = (Float4Input*)Inputs.get(param.name);
				input->Value = theme->Colors.get(param.key).toVector();
			} else {
				// TODO: dimensions
			}
		}
	}

	template<>
	UIMaterial* resolveThemeValue(const Theme& theme, const MaterialKey& key) {
		auto iterator = theme.Materials.find(key);
		if (iterator != theme.Materials.end()) {
			return iterator->value->get();
		} else {
			return nullptr;
		}
	}
}

namespace Ghurund::Core {
	template<>
	const Type& getType<Ghurund::UI::ThemedMaterial>() {
        static Type TYPE = TypeBuilder<Ghurund::UI::ThemedMaterial>();
        return TYPE;
    }
}
