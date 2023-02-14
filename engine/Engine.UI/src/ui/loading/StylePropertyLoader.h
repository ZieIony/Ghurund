#pragma once

#include "PropertyLoader.h"

namespace Ghurund::UI {

    class AStringPropertyLoader:public PropertyLoader {
    public:
        virtual void loadAttr(Object& obj, const BaseProperty& property, const AString& text) override {
            if (styleAttr) {
                AString s = styleAttr->Value();
                s.replace('\\', '/');
                uint32_t value = 0;
                if (s.startsWith(LayoutLoader::THEME_STYLE)) {
                    StyleKey styleKey = s.substring(lengthOf(LayoutLoader::THEME_STYLE));
                    if (!loader.Theme) {
                        throw InvalidStateException("Loader does not have a theme set.");
                    } else if (loader.Theme->Styles.containsKey(styleKey)) {
                        Style = loader.Theme->Styles[styleKey];
                    } else {
                        auto text = std::format(_T("Style '{}' not found.\n"), styleKey.str);
                        Logger::log(LogType::WARNING, text.c_str());
                    }
                }
            } else if (loader.Theme && loader.Theme->Styles.containsKey(StyleKey(Type.Name))) {
                Style = loader.Theme->Styles[StyleKey(Type.Name)];
            }

            property.setRaw(&obj, &t);
        }
    };
}