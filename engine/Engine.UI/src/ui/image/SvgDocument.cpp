#include "ghuipch.h"
#include "SvgDocument.h"

#include <Shlwapi.h>
#include <d2d1svg.h>

namespace Ghurund::UI {
    Status SvgDocument::loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
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
        return Status::OK;
    }

    Status SvgDocument::saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
        return Status::NOT_SUPPORTED;
    }
    
    void SvgDocument::finalize() {
        if (svgDocument != nullptr)
            svgDocument->Release();
    }
    
    FloatSize SvgDocument::getSize() {
        if (!svgDocument)
            return { 0,0 };
        auto size = svgDocument->GetViewportSize();
        return { size.width, size.height };
    }
}