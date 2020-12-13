#pragma once

#include "application/log/Logger.h"
#include "graphics/texture/Image.h"

#include <dxgi1_6.h>
#include <d2d1_3.h>

namespace Ghurund::UI {
    using namespace DirectX;
    using Microsoft::WRL::ComPtr;

    class SvgImage:public Resource {
    private:
        ID2D1SvgDocument* svgDocument = nullptr;

        static inline const auto& CONSTRUCTOR = NoArgsConstructor<SvgImage>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(SvgImage))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::TYPE);

            return TYPE;
        }

    protected:
        virtual Status loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options);
        virtual Status saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options)const;

    public:
        DescriptorHandle descHandle;

        ~SvgImage() {
            finalize();
        }

        void finalize() {
            if (svgDocument != nullptr)
                svgDocument->Release();
        }

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

        inline IntSize getSize() {
            if (!svgDocument)
                return { 0,0 };
            auto size = svgDocument->GetViewportSize();
            return { (uint32_t)size.width, (uint32_t)size.height };
        }

        __declspec(property(get = getSize)) IntSize Size;

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