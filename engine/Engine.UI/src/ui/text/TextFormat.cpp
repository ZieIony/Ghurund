#include "ghuipch.h"
#include "TextFormat.h"

#include "ui/font/FontCollectionLoader.h"

#include <commdlg.h>
#include <dwrite.h>

namespace Ghurund::UI {
    TextFormat::~TextFormat() {
        if (font)
            font->release();
        if (format)
            format->Release();
    }

    Status TextFormat::init(IDWriteFactory5& dwriteFactory) {
        if (FAILED(dwriteFactory.CreateTextFormat(
            font->FamilyName.Data,
            font->Collection,
            (DWRITE_FONT_WEIGHT)weight,
            italic ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            size * 96.0f / 72.0f,
            locale.Data,
            &format)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, "CreateTextFormat failed\n");

        if (FAILED(format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, "SetTextAlignment failed\n");

        if (FAILED(format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, "SetParagraphAlignment failed\n");

        return Status::OK;
    }
}