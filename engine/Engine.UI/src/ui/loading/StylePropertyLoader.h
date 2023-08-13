#pragma once

#include "PropertyLoader.h"
#include "ui/theme/Theme.h"
#include "ui/style/StyleAttr.h"

namespace Ghurund::UI {

	class StylePropertyLoader :public PropertyLoader {
	private:
		static inline const char* THEME_STYLE = "theme://style/";

	public:
		virtual const Type& getType() const override {
			return Ghurund::Core::getType<std::unique_ptr<StyleAttr>>();
		}

		virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override;
	};
}