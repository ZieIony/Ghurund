#pragma once

#include "Font.h"
#include "FontAtlas.h"
#include "FontMetrics.h"
#include "KerningPairs.h"

#include "core/object/NotNull.h"
#include "core/resource/Resource.h"

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	class TextStyle:public Resource {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = TextStyle::GET_TYPE();
#pragma endregion

    private:
        String familyName;
        float size;
        FontMetrics fontMetrics;
        KerningPairs kerning;
        IntrusivePointer<FontAtlas> atlas;

        void initMetrics(HDC hdc);

        void initAtlas(HDC hdc, const String& characters);

    protected:
        ~TextStyle() {
            uninit();
        }

    public:
        inline const FontMetrics& getFontMetrics() const {
            return fontMetrics;
        }

        __declspec(property(get = getFontMetrics)) const FontMetrics& FontMetrics;

        void init(const String& family, float size, uint32_t weight = 400, bool italic = false, const String& supportedCharacters = FontAtlas::DEFAULT_CHARACTER_SET);

        void init(const Font& font, float size, const String& supportedCharacters = FontAtlas::DEFAULT_CHARACTER_SET);

        void init(const Ghurund::UI::FontMetrics& fontMetrics, NotNull<FontAtlas> atlas, const KerningPairs& kerning) {
            this->fontMetrics = fontMetrics;
            atlas->addReference();
            this->atlas.set(atlas.get());
            this->kerning = kerning;
        }

        void uninit();

        inline FontAtlas* getAtlas() const {
            return atlas.get();
        }

        __declspec(property(get = getAtlas)) FontAtlas* Atlas;

        FloatSize measureText(const String& text) const;

        inline const KerningPairs& getKerning() const {
            return kerning;
        }

        __declspec(property(get = getKerning)) const KerningPairs& Kerning;

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return TextStyle::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_XML = ResourceFormat(L"xml", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);
        static const inline ResourceFormat FORMAT_BIN = ResourceFormat(L"bin", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_XML, FORMAT_BIN };
#pragma endregion
	};
}