#include "Font.h"
#include "ui/Canvas.h"
#include "application/log/Logger.h"
#include "ui/Graphics2D.h"

#include <commdlg.h>

namespace Ghurund::UI {
    Font::Font(const UnicodeString& file, const UnicodeString& family, float size, unsigned int weight, bool italic, const UnicodeString& locale)
        :file(file), familyName(family), size(size), weight(weight), italic(italic), locale(locale) {}

    Font::Font(IDWriteTextLayout* textLayout, UINT32 position) {
        Array<wchar_t> fontFamilyName(100);
        fontFamilyName.set(0, L'\0');
        textLayout->GetFontFamilyName(position, fontFamilyName.begin(), fontFamilyName.Size);
        familyName = fontFamilyName.begin();

        Array<wchar_t> localeName(LOCALE_NAME_MAX_LENGTH);
        localeName.set(0, L'\0');
        textLayout->GetLocaleName(position, localeName.begin(), localeName.Size);
        locale = localeName.begin();

        DWRITE_FONT_WEIGHT fontWeight;
        textLayout->GetFontWeight(position, &fontWeight);
        weight = (DWRITE_FONT_WEIGHT)fontWeight;

        DWRITE_FONT_STYLE fontStyle;
        textLayout->GetFontStyle(position, &fontStyle);
        italic = fontStyle == DWRITE_FONT_STYLE_ITALIC;

        DWRITE_FONT_STRETCH fontStretch;
        textLayout->GetFontStretch(position, &fontStretch);
        stretch = (DWRITE_FONT_STRETCH)fontStretch;

        textLayout->GetFontSize(position, &size);

        BOOL hasUnderline;
        textLayout->GetUnderline(position, &hasUnderline);
        underline = hasUnderline;

        BOOL hasStrikethrough;
        textLayout->GetStrikethrough(position, &hasStrikethrough);
        strikethrough = hasStrikethrough;
    }

    Status Font::init(Graphics2D& graphics2d) {
        this->graphics2d = &graphics2d;
        IDWriteFontCollection* fontCollection;
        if (FAILED(graphics2d.FontLoader->createFontCollection(file, &fontCollection)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, "createFontCollection failed\n");
        if (FAILED(graphics2d.DWriteFactory->CreateTextFormat(
            familyName,
            fontCollection,
            (DWRITE_FONT_WEIGHT)weight,
            italic ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            size * 96.0f / 72.0f,
            locale.getData(),
            &textFormat)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, "CreateTextFormat failed\n");

        if (FAILED(textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, "SetTextAlignment failed\n");

        if (FAILED(textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, "SetParagraphAlignment failed\n");

        return Status::OK;
    }
}