#pragma once

#include "ui/font/Font.h"
#include "core/resource/Resource.h"
#include "core/reflection/Type.h"

namespace Ghurund::UI::OpenGL {
    using namespace Ghurund::Core;

    class Font:public Ghurund::UI::Font {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Ghurund::UI::OpenGL::Font::GET_TYPE();
#pragma endregion


#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return Ghurund::UI::OpenGL::Font::FORMATS;
        }

    public:
        static const inline Ghurund::Core::ResourceFormat FORMAT_TTF = Ghurund::Core::ResourceFormat(L"ttf", true, false);
        static const inline Ghurund::Core::ResourceFormat FORMAT_OTF = Ghurund::Core::ResourceFormat(L"otf", true, false);

        inline static const Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& FORMATS = { FORMAT_TTF, FORMAT_OTF };
#pragma endregion
    };
}