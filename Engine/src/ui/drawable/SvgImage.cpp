#include "SvgImage.h"
#include "resource/ResourceContext.h"
#include "ui/Graphics2D.h"

namespace Ghurund::UI {
    Status SvgImage::loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
        ComPtr<IStream> memStream = SHCreateMemStream((const BYTE*)stream.Data, (UINT)stream.Size);
        context.Graphics2D.DeviceContext->CreateSvgDocument(memStream.Get(), D2D1::SizeF(100, 100), &svgDocument);
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
        return Status::OK;
    }

    Status SvgImage::saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
        return Status::NOT_SUPPORTED;
    }
}