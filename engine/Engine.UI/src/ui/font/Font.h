#pragma once

#include "core/Buffer.h"
#include "core/resource/Resource.h"

#include <dwrite_3.h>

namespace Ghurund::Core {
    template<>
    const Type& getType<IDWriteFontCollection>();
}

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class Font:public Ghurund::Core::Resource {
#pragma region reflection
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();
        virtual const Ghurund::Core::Type& getType() const override { return TYPE; }
#pragma endregion

    private:
        Ghurund::Core::WString familyName;
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

        const Ghurund::Core::WString& getFamilyName() const {
            return familyName;
        }

        __declspec(property(get = getFamilyName)) const Ghurund::Core::WString& FamilyName;

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