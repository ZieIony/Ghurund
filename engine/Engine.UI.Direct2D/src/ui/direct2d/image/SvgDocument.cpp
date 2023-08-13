#include "ghuidxpch.h"
#include "SvgDocument.h"

#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/TypeBuilder.h"

#include <Shlwapi.h>
#include <wrl.h>

namespace Ghurund::Core {
    template<>
    const Type& getType<ID2D1SvgDocument>() {
        static Type TYPE = Type("", "ID2D1SvgDocument", sizeof(ID2D1SvgDocument*));
        return TYPE;
    }
}

namespace Ghurund::UI::Direct2D {
    const Ghurund::Core::Type& SvgDocument::GET_TYPE() {
        using namespace Ghurund::Core;

        static auto PROPERTY_DATA = Property<SvgDocument, ID2D1SvgDocument*>("Data", &getData);
        static auto PROPERTY_SIZE = Property<SvgDocument, FloatSize>("Size", &getSize);

        static const Ghurund::Core::Type TYPE = TypeBuilder<SvgDocument>(Ghurund::UI::NAMESPACE_NAME, "SvgDocument")
            .withProperty(PROPERTY_DATA)
            .withProperty(PROPERTY_SIZE)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    const Array<ResourceFormat>& SvgDocument::GET_FORMATS() {
        static const Ghurund::Core::Array<Ghurund::Core::ResourceFormat> formats = { Ghurund::Core::ResourceFormat(L"svg", true, false) };
        return formats;
    }

    void SvgDocument::loadInternal(
        const Ghurund::Core::DirectoryPath& workingDir,
        Ghurund::Core::MemoryInputStream& stream,
        Ghurund::Core::LoadOption options
    ) {
        Microsoft::WRL::ComPtr<IStream> memStream = SHCreateMemStream((const BYTE*)stream.Data, (UINT)stream.Size);
        //context.Graphics2D.DeviceContext->CreateSvgDocument(memStream.Get(), D2D1::SizeF(100, 100), &svgDocument);
        ID2D1SvgElement* root;
        svgDocument->GetRoot(&root);
        FLOAT width = 0.0f, height = 0.0f;
        if (root->IsAttributeSpecified(L"width"))
            root->GetAttributeValue(L"width", &width);
        if (root->IsAttributeSpecified(L"height"))
            root->GetAttributeValue(L"height", &height);
        if (width > 0 && height > 0)
            svgDocument->SetViewportSize({ width, height });
        root->Release();
    }

    void SvgDocument::saveInternal(
        const Ghurund::Core::DirectoryPath& workingDir,
        Ghurund::Core::MemoryOutputStream& stream,
        Ghurund::Core::SaveOption options
    ) const {
        throw NotSupportedException();
    }

    void SvgDocument::finalize() {
        if (svgDocument != nullptr)
            svgDocument->Release();
    }

    Ghurund::Core::FloatSize SvgDocument::getSize() {
        if (!svgDocument)
            return { 0,0 };
        auto size = svgDocument->GetViewportSize();
        return { size.width, size.height };
    }
}