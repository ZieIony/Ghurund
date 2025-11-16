#pragma once

#include "core/collection/Map.h"
#include "core/math/Size.h"
#include "core/object/IntrusivePointer.h"
#include "core/resource/Resource.h"
#include "core/reflection/Type.h"
#include "FontAtlas.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

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
        String familyName;
        bool italic = false;
        uint32_t weight = 400;

        TEXTMETRIC tm;
        HANDLE handle = INVALID_HANDLE_VALUE;

        Map<tchar, Map<tchar, int>> kerning;
        IntrusivePointer<FontAtlas> atlas;

        void initMetrics(HDC hdc);

        void initKerning(HDC hdc);

        void initAtlas(HDC hdc, const String& characters);

    protected:
        ~Font() {
            uninit();
        }

    public:
        const Ghurund::Core::String& getFamilyName() const {
            return familyName;
        }

        __declspec(property(get = getFamilyName)) const Ghurund::Core::String& FamilyName;

        void init(const String& family, uint32_t weight = 400, bool italic = false, const String& supportedCharacters = FontAtlas::DEFAULT_CHARACTER_SET);

        void init(const void* data, size_t size, const String& supportedCharacters = FontAtlas::DEFAULT_CHARACTER_SET);

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

        FontAtlas* getAtlas() const {
            return atlas.get();
        }

        __declspec(property(get = getAtlas)) FontAtlas* Atlas;

        FloatSize measureText(const String& text) const;

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