#include "ghuigdipch.h"
#include "TextFormat.h"

#include "core/reflection/TypeBuilder.h"
#include "ui/gdi/font/FontCollectionLoader.h"

#include <commdlg.h>
#include <dwrite.h>

namespace Ghurund::UI::GDI {
    const Ghurund::Core::Type& TextFormat::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<TextFormat>(NAMESPACE_NAME, GH_STRINGIFY(TextFormat))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    TextFormat::~TextFormat() {
        if (format)
            format->Release();
    }

    Status TextFormat::init(IDWriteFactory5& dwriteFactory) {
        if (FAILED(dwriteFactory.CreateTextFormat(
            Font->FamilyName.Data,
            ((Ghurund::UI::GDI::Font*)Font)->Collection,
            (DWRITE_FONT_WEIGHT)Weight,
            Italic ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            Size * 96.0f / 72.0f,
            Locale.Data,
            &format)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("CreateTextFormat failed\n"));

        if (FAILED(format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("SetTextAlignment failed\n"));

        if (FAILED(format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("SetParagraphAlignment failed\n"));

        return Status::OK;
    }
}