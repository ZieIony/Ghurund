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

        void initAtlas(const String& supportedCharacters);

        void initKerning(HFONT hf);

        void initMsdf(HFONT hf, const String& characters);

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

        void init(const String& family, uint32_t weight = 400, bool italic = false, const String& supportedCharacters = DEFAULT_CHARACTER_SET) {
            this->familyName = family;
            this->weight = weight;
            this->italic = italic;
            initAtlas(supportedCharacters);
        }

        void init(const void* data, size_t size, const String& supportedCharacters = DEFAULT_CHARACTER_SET);

        void uninit();

        long getAscent() const {
            return tm.tmAscent;
        }

        __declspec(property(get = getAscent)) long Ascent;

        long getDescent() const {
            return tm.tmDescent;
        }

        __declspec(property(get = getDescent)) long Descent;

        long getInternalLeading() const {
            return tm.tmInternalLeading;
        }

        __declspec(property(get = getInternalLeading)) long InternalLeading;

        long getExternalLeading() const {
            return tm.tmExternalLeading;
        }

        __declspec(property(get = getExternalLeading)) long ExternalLeading;

        long getHeight() const {
            return tm.tmHeight;
        }

        __declspec(property(get = getHeight)) long Height;

        uint32_t getWeight() const {
            return weight;
        }

        __declspec(property(get = getWeight)) uint32_t Weight;

        Image* getAtlas() const {
            return atlas;
        }

        __declspec(property(get = getAtlas)) const Image* Atlas;

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