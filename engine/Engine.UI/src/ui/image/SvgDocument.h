#pragma once

#include "core/math/Size.h"
#include "ui/image/Image.h"

#include <d2d1svg.h>

namespace Ghurund::Core {
    template<>
    const Type& getType<ID2D1SvgDocument>();
}

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class SvgDocument:public Ghurund::Core::Resource {
#pragma region reflection
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();
        virtual const Ghurund::Core::Type& getType() const override { return TYPE; }
#pragma endregion

    private:
        ID2D1SvgDocument* svgDocument = nullptr;

    protected:
        virtual Status loadInternal(
            const Ghurund::Core::DirectoryPath& workingDir,
            Ghurund::Core::MemoryInputStream& stream,
            Ghurund::Core::LoadOption options
        );

        virtual Status saveInternal(
            const Ghurund::Core::DirectoryPath& workingDir,
            Ghurund::Core::MemoryOutputStream& stream,
            Ghurund::Core::SaveOption options
        ) const;

    public:
        ~SvgDocument() {
            finalize();
        }

        void finalize();

        virtual void invalidate() {
            finalize();
            svgDocument = nullptr;
            __super::invalidate();
        }

        virtual bool isValid() {
            return svgDocument != nullptr && __super::Valid;
        }

        inline ID2D1SvgDocument* getData() {
            return svgDocument;
        }

        __declspec(property(get = getData)) ID2D1SvgDocument* Data;

        Ghurund::Core::FloatSize getSize();

        __declspec(property(get = getSize)) Ghurund::Core::FloatSize Size;

        static const Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& getFormats() {
            static const Ghurund::Core::Array<Ghurund::Core::ResourceFormat> formats = { Ghurund::Core::ResourceFormat(L"svg", true, false) };
            return formats;
        }

        __declspec(property(get = getFormats)) Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& Formats;
    };
}