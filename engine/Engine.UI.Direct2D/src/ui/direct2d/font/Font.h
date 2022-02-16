#pragma once

#include "ui/font/Font.h"
#include "core/resource/Resource.h"
#include "core/reflection/Type.h"

#include <dwrite_3.h>

namespace Ghurund::Core {
    template<>
    const Type& getType<IDWriteFontCollection>();
}

namespace Ghurund::UI::Direct2D {
    using namespace Ghurund::Core;

    class Font:public Ghurund::UI::Font {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();
#pragma endregion

    private:
        IDWriteFontCollection* collection = nullptr;

    public:
        Status init(IDWriteFontCollection* collection) {
            this->collection = collection;

            IDWriteFontFamily* fontFamily;
            UINT32 fontFamilyCount = collection->GetFontFamilyCount();
            HRESULT hr = collection->GetFontFamily(0, &fontFamily);
            IDWriteLocalizedStrings* localizedStrings = nullptr;
            UINT32 fontCount = fontFamily->GetFontCount();
            if (FAILED(fontFamily->GetFamilyNames(&localizedStrings)))
                return Status::CALL_FAIL;
            uint32_t strLength;
            localizedStrings[0].GetStringLength(0, &strLength);
            wchar_t* str = ghnew wchar_t[strLength + 1];
            localizedStrings[0].GetString(0, str, strLength + 1);
            familyName = str;
            delete[] str;

            Valid = true;
            return Status::OK;
        }

        IDWriteFontCollection* getCollection() {
            return collection;
        }

        __declspec(property(get = getCollection)) IDWriteFontCollection* Collection;
        
        static const inline Ghurund::Core::ResourceFormat FORMAT_TTF = Ghurund::Core::ResourceFormat(L"ttf", true, false);
        static const inline Ghurund::Core::ResourceFormat FORMAT_OTF = Ghurund::Core::ResourceFormat(L"otf", true, false);

        inline static const Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& FORMATS = { FORMAT_TTF, FORMAT_OTF };

        virtual const Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& getFormats() const override {
            return FORMATS;
        }
    };
}