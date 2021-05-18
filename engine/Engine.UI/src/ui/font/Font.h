#pragma once

#include "core/Buffer.h"
#include "core/resource/Resource.h"

#include <dwrite_3.h>

#include "reflection_46e5e19d_74d7_4800_af96_b064e3336b89.h"

namespace Ghurund::UI {
    class Font:public Resource {
        reflection_46e5e19d_74d7_4800_af96_b064e3336b89

    private:
        WString familyName;
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

        const WString& getFamilyName() const {
            return familyName;
        }

        __declspec(property(get = getFamilyName)) const WString& FamilyName;

        IDWriteFontCollection* getCollection() {
            return collection;
        }

        __declspec(property(get = getCollection)) IDWriteFontCollection* Collection;

        static const inline ResourceFormat FORMAT_TTF = ResourceFormat(L"ttf", true, false);
        static const inline ResourceFormat FORMAT_OTF = ResourceFormat(L"otf", true, false);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_TTF, FORMAT_OTF };

        virtual const Array<ResourceFormat>& getFormats() const override {
            return FORMATS;
        }
    };
}