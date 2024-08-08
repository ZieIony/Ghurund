#pragma once

#include "core/math/Size.h"
#include "core/reflection/Type.h"
#include "ui/image/VectorImage.h"

#include <d2d1svg.h>

namespace Ghurund::Core {
    template<>
    const Type& getType<ID2D1SvgDocument>();
}

namespace Ghurund::UI::Direct2D {
    using namespace Ghurund::Core;

    class SvgDocument:public Ghurund::UI::VectorImage {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = SvgDocument::GET_TYPE();
#pragma endregion

    private:
        ID2D1SvgDocument* svgDocument = nullptr;

    protected:
        virtual void loadInternal(
            const Ghurund::Core::DirectoryPath& workingDir,
            Ghurund::Core::MemoryInputStream& stream,
            Ghurund::Core::LoadOption options
        );

        virtual void saveInternal(
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

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return SvgDocument::FORMATS;
        }

    public:
        static const inline Ghurund::Core::ResourceFormat FORMAT_SVG = Ghurund::Core::ResourceFormat(L"svg", true, false);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_SVG };
#pragma endregion
    };
}