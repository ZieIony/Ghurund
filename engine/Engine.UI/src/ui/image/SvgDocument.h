#pragma once

#include "core/math/Size.h"
#include "ui/image/Image.h"

struct ID2D1SvgDocument;

#include "reflection_7471ad87_25b0_4e74_9cd4_92dc567fe17c.h"

namespace Ghurund::UI {
    class SvgDocument:public Resource {
        reflection_7471ad87_25b0_4e74_9cd4_92dc567fe17c

    private:
        ID2D1SvgDocument* svgDocument = nullptr;

    protected:
        virtual Status loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options);
        virtual Status saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options)const;

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

        FloatSize getSize();

        __declspec(property(get = getSize)) FloatSize Size;

        static const Array<ResourceFormat>& getFormats() {
            static const Array<ResourceFormat> formats = {
                ResourceFormat(L"svg", true, false)
            };
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat>& Formats;
    };
}