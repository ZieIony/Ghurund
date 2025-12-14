#pragma once

#include "TextMetrics.h"
#include "TextDocument.h"

#include "core/Color.h"
#include "core/math/Size.h"
#include "core/string/String.h"
#include "ui/font/Font.h"
#include "TextLine.h"
#include "ITextMeshFactory.h"

namespace Ghurund::UI {
    class TextLayout {
    protected:
        Ghurund::Core::IntSize size, preferredSize;
        Ghurund::UI::TextDocument* document = nullptr;
        List<TextLine> lines;
        List<DrawPacket> textMeshes;

        bool valid = false;

    public:
        bool breakWords = true;

        TextLayout() {}

        TextLayout(const Ghurund::Core::WString& text, NotNull<Font> font, const Color& color)
            :document(ghnew Ghurund::UI::TextDocument(text, font, color)) {
        }

        ~TextLayout() {
            if (document)
                document->release();
        }

        inline Ghurund::UI::TextDocument* getDocument() {
            return document;
        }

        inline void setDocument(Ghurund::UI::TextDocument* document) {
            if (this->document != document) {
                setPointer(this->document, document);
                valid = false;
            }
        }

        __declspec(property(get = getDocument, put = setDocument)) Ghurund::UI::TextDocument* Document;

        inline const Ghurund::Core::IntSize& getPreferredSize() const {
            return preferredSize;
        }

        inline void setPreferredSize(const Ghurund::Core::IntSize& size) {
            setPreferredSize(size.Width, size.Height);
        }

        inline void setPreferredSize(uint32_t w, uint32_t h) {
            if (preferredSize.Width != w || preferredSize.Height != h) {
                preferredSize = { w, h };
                valid = false;
            }
        }

        __declspec(property(get = getPreferredSize, put = setPreferredSize)) const Ghurund::Core::IntSize& PreferredSize;

        inline const Ghurund::Core::IntSize& getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) const Ghurund::Core::IntSize& Size;

        inline const List<TextLine>& getLines() const {
            return lines;
        }

        __declspec(property(get = getLines)) const List<TextLine>& Lines;

        virtual TextMetrics getMetrics();

        __declspec(property(get = getMetrics)) TextMetrics TextMetrics;

        virtual Ghurund::Core::Array<Ghurund::UI::LineMetrics> getLineMetrics();

        __declspec(property(get = getLineMetrics)) Ghurund::Core::Array<Ghurund::UI::LineMetrics> LineMetrics;

        virtual Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> getClusterMetrics();

        __declspec(property(get = getClusterMetrics)) Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> ClusterMetrics;

        virtual HitTestMetrics hitTestTextPosition(uint32_t textPosition, bool isTrailingHit, float* pointX, float* pointY);

        virtual Ghurund::Core::Array<HitTestMetrics> hitTestTextRange(uint32_t textPosition, uint32_t textLength, float originX, float originY);

        virtual HitTestMetrics hitTestPoint(float pointX, float pointY, bool* isTrailingHit);

        inline void invalidate() {
            valid = false;
        }

        virtual void refresh();

        void initMeshes(ITextMeshFactory& textMeshFactory, IMaterial* material);

        virtual void insertTextAt(uint32_t position, const Ghurund::Core::WString& textToInsert);

        virtual void removeTextAt(uint32_t position, uint32_t lengthToRemove);

        virtual void draw(RenderGroup& group);

        uint32_t measureWidth();

        uint32_t measureHeight();

#ifdef _DEBUG
        bool validate() const;
#endif
    };
}