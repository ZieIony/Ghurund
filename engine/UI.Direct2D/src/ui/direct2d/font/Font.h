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

        inline static const Ghurund::Core::Type& TYPE = Font::GET_TYPE();
#pragma endregion

    private:
        IDWriteFontCollection* collection = nullptr;

    public:
        void init(IDWriteFontCollection* collection) {
            this->collection = collection;

            IDWriteFontFamily* fontFamily;
            UINT32 fontFamilyCount = collection->GetFontFamilyCount();
            HRESULT hr = collection->GetFontFamily(0, &fontFamily);
            IDWriteLocalizedStrings* localizedStrings = nullptr;
            UINT32 fontCount = fontFamily->GetFontCount();
            if (FAILED(fontFamily->GetFamilyNames(&localizedStrings)))
                throw CallFailedException();
            uint32_t strLength;
            localizedStrings[0].GetStringLength(0, &strLength);
            wchar_t* str = ghnew wchar_t[strLength + 1];
            localizedStrings[0].GetString(0, str, strLength + 1);
            //familyName = str;
            delete[] str;
        }

        IDWriteFontCollection* getCollection() {
            return collection;
        }

        __declspec(property(get = getCollection)) IDWriteFontCollection* Collection;
        
#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return Font::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_TTF = ResourceFormat(L"ttf", ResourceFormatOptions::CAN_LOAD);
        static const inline ResourceFormat FORMAT_OTF = ResourceFormat(L"otf", ResourceFormatOptions::CAN_LOAD);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_TTF, FORMAT_OTF };
#pragma endregion
    };
}