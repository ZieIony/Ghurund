#include "ghuid2dpch.h"
#include "TextFormat.h"

#include "core/logging/Logger.h"
#include "core/reflection/TypeBuilder.h"

#include <commdlg.h>
#include <dwrite.h>

namespace Ghurund::UI::Direct2D {
    const Ghurund::Core::Type& TextFormat::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<TextFormat>(NAMESPACE_NAME, GH_STRINGIFY(TextFormat))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    TextFormat::~TextFormat() {
        if (format)
            format->Release();
    }

    void TextFormat::init(IDWriteFactory5& dwriteFactory) {
        if (FAILED(dwriteFactory.CreateTextFormat(
            Font->FamilyName.Data,
            ((Ghurund::UI::Direct2D::Font*)Font)->Collection,
            (DWRITE_FONT_WEIGHT)Weight,
            Italic ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            Size * 96.0f / 72.0f,
            Locale.Data,
            &format))) {
            Logger::log(LogType::ERR0R, _T("CreateTextFormat failed\n"));
            throw CallFailedException();
        }

        if (FAILED(format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING))) {
            Logger::log(LogType::ERR0R, _T("SetTextAlignment failed\n"));
            throw CallFailedException();
        }

        if (FAILED(format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR))) {
            Logger::log(LogType::ERR0R, _T("SetParagraphAlignment failed\n"));
            throw CallFailedException();
        }
    }
}