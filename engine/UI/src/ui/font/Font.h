#pragma once

#include "core/collection/Map.h"
#include "core/math/Size.h"
#include "core/math/Point.h"
#include "core/resource/Resource.h"
#include "core/reflection/Type.h"
#include "core/image/Image.h"
#include "ui/image/BitmapFactory.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    struct Glyph {
        IntSize shapeSize, bitmapSize;
        int32_t originY;
        IntPoint offset;
    };

    class Font:public Ghurund::Core::Resource {
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
        static inline const tchar* DEFAULT_CHARACTER_SET = _T("aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPrqQRsStTuUvVwWxXyYzZ 0123456789*-+[]{};':\",.\\/<>?!@#$%^&*()`~");
        static inline const uint32_t PADDING = 8;
        static inline const uint32_t MAX_DIST = 8;
        static inline const uint32_t BITMAP_SIZE = 64;

        String familyName;
        bool italic = false;
        uint32_t weight = 400;

        TEXTMETRIC tm;
        HANDLE handle = INVALID_HANDLE_VALUE;

        Map<tchar, Glyph> glyphs;
        Map<tchar, Map<tchar, int>> kerning;
        Ghurund::UI::Bitmap* atlas = nullptr;

        void initAtlas(const String& supportedCharacters, const IBitmapFactory& bitmapFactory);

        void initKerning(HFONT hf);

        void initGlyphs(HFONT hf, const String& characters);

        bool fitAllGlyphs(const List<Glyph*>& sortedGlyphs, uint32_t width, uint32_t height);

        IntSize getAtlasSize();

        void initMsdf(HFONT hf, const String& characters, const IBitmapFactory& bitmapFactory);

        HBITMAP makeDIB(HDC context, BITMAPINFO& bmi, unsigned int width, unsigned int height, int32_t** pixels);

    protected:
        ~Font() {
            uninit();
        }

    public:
        const Ghurund::Core::String& getFamilyName() const {
            return familyName;
        }

        __declspec(property(get = getFamilyName)) const Ghurund::Core::String& FamilyName;

        void init(const IBitmapFactory& bitmapFactory, const String& family, uint32_t weight = 400, bool italic = false, const String& supportedCharacters = DEFAULT_CHARACTER_SET) {
            this->familyName = family;
            this->weight = weight;
            this->italic = italic;
            initAtlas(supportedCharacters, bitmapFactory);
        }

        void init(const IBitmapFactory& bitmapFactory, const void* data, size_t size, const String& supportedCharacters = DEFAULT_CHARACTER_SET);

        void uninit();

        uint32_t getAscent() const {
            return tm.tmAscent;
        }

        __declspec(property(get = getAscent)) uint32_t Ascent;

        uint32_t getDescent() const {
            return tm.tmDescent;
		}

        __declspec(property(get = getDescent)) uint32_t Descent;

        uint32_t getInternalLeading() const {
            return tm.tmInternalLeading;
        }

        __declspec(property(get = getInternalLeading)) uint32_t InternalLeading;

        uint32_t getExternalLeading() const {
            return tm.tmExternalLeading;
        }

        __declspec(property(get = getExternalLeading)) uint32_t ExternalLeading;

        uint32_t getHeight() const {
            return tm.tmHeight;
        }

        __declspec(property(get = getHeight)) uint32_t Height;

        uint32_t getWeight() const {
            return weight;
        }

        __declspec(property(get = getWeight)) uint32_t Weight;

        Ghurund::UI::Bitmap* getAtlas() const {
            return atlas;
        }

        __declspec(property(get = getAtlas)) const Ghurund::UI::Bitmap* Atlas;

        FloatSize measureText(const String& text) const;

        inline const Map<tchar, Glyph>& getGlyphs() const {
            return glyphs;
        }

        __declspec(property(get = getGlyphs)) const Map<tchar, Glyph>& Glyphs;

        inline int getKerning(tchar c1, tchar c2) const {
            auto it = kerning.find(c1);
            if (it != kerning.end()) {
                auto it2 = it->value.find(c2);
                if (it2 != it->value.end())
                    return it2->value;
            }
            return 0;
        }

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return Font::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_TTF = ResourceFormat(L"ttf", ResourceFormatOptions::CAN_LOAD);
        static const inline ResourceFormat FORMAT_OTF = ResourceFormat(L"otf", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_ATLAS = ResourceFormat(L"fontatlas", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_TTF, FORMAT_OTF, FORMAT_ATLAS };
#pragma endregion
    };
}