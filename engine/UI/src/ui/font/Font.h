#pragma once

#include "core/resource/Resource.h"
#include "core/reflection/Type.h"

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
        uint32_t weight = 400;
        bool italic = false;

        HANDLE handle = INVALID_HANDLE_VALUE;

    protected:
        ~Font() {
            uninit();
        }

    public:
        const Ghurund::Core::String& getFamilyName() const {
            return familyName;
        }

        __declspec(property(get = getFamilyName)) const Ghurund::Core::String& FamilyName;

        inline uint32_t getWeight() const {
            return weight;
        }

        __declspec(property(get = getWeight)) uint32_t Weight;

        inline bool getItalic() const {
            return italic;
        }

        __declspec(property(get = getItalic)) bool Italic;

        void init(const void* data, size_t size);

        void uninit();

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