#pragma once

#include "core/math/Size.h"
#include "graphics/texture/Image.h"

struct ID2D1SvgDocument;

namespace Ghurund::UI {
    using namespace DirectX;

    class SvgImage:public Resource {
    private:
        ID2D1SvgDocument* svgDocument = nullptr;

    protected:
        virtual Status loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options);
        virtual Status saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options)const;

        static const Ghurund::Type& GET_TYPE();

    public:
        ~SvgImage() {
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

        FloatSize getSize();

        __declspec(property(get = getSize)) FloatSize Size;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        static const Array<ResourceFormat*>& getFormats() {
            static const Array<ResourceFormat*> formats = { (ResourceFormat*)&ResourceFormat::SVG };
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*>& Formats;
    };
}