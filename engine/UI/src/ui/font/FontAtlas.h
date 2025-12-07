#pragma once

#include "core/collection/Map.h"
#include "core/math/Size.h"
#include "core/object/IntrusivePointer.h"
#include "core/resource/Resource.h"
#include "core/reflection/Type.h"
#include "core/image/Image.h"
#include "GlyphMetrics.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class FontAtlas:public Ghurund::Core::Resource {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = FontAtlas::GET_TYPE();
#pragma endregion

    private:
        static inline const uint32_t MAX_DIST = 8;
        static inline const uint32_t BITMAP_SIZE = 64;

        Map<tchar, GlyphMetrics> glyphs;
        IntrusivePointer<Ghurund::Core::Image> atlas;

        void initGlyphs(HDC hdc, const String& characters);

        bool fitAllGlyphs(const List<GlyphMetrics*>& sortedGlyphs, uint32_t width, uint32_t height);

        IntSize getAtlasSize();

    protected:
        ~FontAtlas() {
            uninit();
        }

    public:
        static inline const tchar* DEFAULT_CHARACTER_SET = _T("aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPrqQRsStTuUvVwWxXyYzZ 0123456789*-+[]{};'`:\",.\\/<>?!@#$%^&*()`~ó¿Ÿæñ¹ê³");

        void init(HDC hdc, const String& supportedCharacters);

        void uninit();

        Ghurund::Core::Image* getImage() const {
            return atlas.get();
        }

        __declspec(property(get = getImage)) Ghurund::Core::Image* Image;

        inline const Map<tchar, GlyphMetrics>& getGlyphs() const {
            return glyphs;
        }

        __declspec(property(get = getGlyphs)) const Map<tchar, GlyphMetrics>& Glyphs;

        inline uint32_t getPadding() const {
            return MAX_DIST;
        }

        __declspec(property(get = getPadding)) uint32_t Padding;

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return FontAtlas::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_ATLAS = ResourceFormat(L"fontatlas", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_ATLAS };
#pragma endregion
    };
}