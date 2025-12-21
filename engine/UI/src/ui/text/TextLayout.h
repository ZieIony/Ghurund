#pragma once

#include "TextMetrics.h"
#include "TextDocument.h"

#include "core/Color.h"
#include "core/math/Size.h"
#include "core/string/String.h"
#include "TextLine.h"
#include "ITextMeshFactory.h"
#include "engine/graphics/texture/ITextureFactory.h"

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

        TextLayout(const Ghurund::Core::WString& text, NotNull<TextStyle> textStyle, const Color& color)
            :document(ghnew Ghurund::UI::TextDocument(text, textStyle, color)) {
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

        TextMetrics getMetrics();

        __declspec(property(get = getMetrics)) TextMetrics TextMetrics;

        Ghurund::Core::Array<Ghurund::UI::LineMetrics> getLineMetrics();

        __declspec(property(get = getLineMetrics)) Ghurund::Core::Array<Ghurund::UI::LineMetrics> LineMetrics;

        Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> getClusterMetrics();

        __declspec(property(get = getClusterMetrics)) Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> ClusterMetrics;

        HitTestMetrics hitTestTextPosition(uint32_t textPosition, bool isTrailingHit, float* pointX, float* pointY);

        Ghurund::Core::Array<HitTestMetrics> hitTestTextRange(uint32_t textPosition, uint32_t textLength, float originX, float originY);

        HitTestMetrics hitTestPoint(float pointX, float pointY, bool* isTrailingHit);

        inline void invalidate() {
            valid = false;
            textMeshes.clear();
        }

        void refresh();

        void initMeshes(
            ITextMeshFactory& textMeshFactory,
            ITextureFactory& textureFactory,
            NotNull<IMaterial> material
        );

        void insertTextAt(uint32_t position, const Ghurund::Core::WString& textToInsert);

        void removeTextAt(uint32_t position, uint32_t lengthToRemove);

        void draw(RenderGroup& group, const XMFLOAT2& position);

#ifdef _DEBUG
        bool validate() const;
#endif
    };
}