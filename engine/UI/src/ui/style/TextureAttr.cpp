#include "ghuipch.h"
#include "TextureAttr.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& TextureAttr::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<TextureAttr>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    const Ghurund::Core::Type& TextureValue::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<TextureValue>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    const Ghurund::Core::Type& TextureRef::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<TextureRef>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    IntrusivePointer<ITexture> TextureRef::resolve(const Theme& theme) const {
        auto iterator = theme.Textures.find(key);
        if (iterator == theme.Textures.end()) {
            Logger::log(LogType::WARNING, std::format(_T("Texture '{}' not found in the current theme.\n"), key.Value).c_str());
            return IntrusivePointer<ITexture>(nullptr);
        }
        return iterator->value->get();
    }

}
