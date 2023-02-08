#pragma once

#include "ui/font/Font.h"
#include "core/math/Size.h"
#include "core/math/Rect.h"
#include "core/resource/Resource.h"
#include "core/reflection/Type.h"
#include "core/image/Image.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class Font:public Ghurund::Core::Resource {
    private:
        static inline const tchar* DEFAULT_CHARACTER_SET = _T("BaAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPrqQRsStTuUvVwWxXyYzZ 0123456789/*-+[]{};':\",./<>?!@#$%^&*()`~Û”??????????????");

        struct Glyph {
            FloatRect tightRect, fullRect;
        };

        float size;
        String familyName;
        bool italic = false;
        uint32_t weight = 400;

        TEXTMETRIC tm;
        HANDLE handle = INVALID_HANDLE_VALUE;

        Map<tchar, Glyph> glyphs;
        Map<tchar, Map<tchar, int>> kerning;
        Ghurund::Core::Image* atlas = nullptr;

        void initKerning(HFONT hf);

        void initMsdf(HFONT hf, const tchar* characters);

        //IntSize initAtlas(HDC context, const tchar* characters, unsigned int width);

        HBITMAP makeDIB(HDC context, BITMAPINFO& bmi, unsigned int width, unsigned int height, int32_t** pixels);

#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();
#pragma endregion

    public:
        const Ghurund::Core::String& getFamilyName() const {
            return familyName;
        }

        __declspec(property(get = getFamilyName)) const Ghurund::Core::String& FamilyName;

        ~Font() {
            uninit();
        }

        void init(const tchar* supportedCharacters = nullptr);

        void init(const String& family, uint32_t weight = 400, bool italic = false, const tchar* supportedCharacters = nullptr) {
            this->familyName = family;
            this->weight = weight;
            this->italic = italic;
            init(supportedCharacters);
        }

        void init(const void* data, size_t size);

        void uninit();

        long getAscent() const {
            return tm.tmAscent;
        }

        long getDescent() const {
            return tm.tmDescent;
        }

        long getInternalLeading() const {
            return tm.tmInternalLeading;
        }

        long getExternalLeading() const {
            return tm.tmExternalLeading;
        }

        long getHeight() const {
            return tm.tmHeight;
        }

        uint32_t getWeight() const {
            return weight;
        }

        FloatSize measureText(const String& text) const;

        static const inline Ghurund::Core::ResourceFormat FORMAT_TTF = Ghurund::Core::ResourceFormat(L"ttf", true, false);
        static const inline Ghurund::Core::ResourceFormat FORMAT_OTF = Ghurund::Core::ResourceFormat(L"otf", true, false);
        static const inline Ghurund::Core::ResourceFormat FORMAT_ATLAS = Ghurund::Core::ResourceFormat(L"fontatlas", true, false);

        inline static const Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& FORMATS = { FORMAT_TTF, FORMAT_OTF, FORMAT_ATLAS };

        virtual const Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& getFormats() const override {
            return FORMATS;
        }
    };
}