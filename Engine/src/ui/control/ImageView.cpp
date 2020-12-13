#include "ImageView.h"

namespace Ghurund::UI {
    void ImageView::onMeasure(float parentWidth, float parentHeight) {
        if (preferredSize.width == PreferredSize::Width::WRAP) {
            measuredSize.width = std::max(minSize.width, image ? (float)image->PreferredSize.width : 0.0f);
        } else if (preferredSize.width != PreferredSize::Width::FILL) {
            measuredSize.width = (float)preferredSize.width;
        }

        if (preferredSize.height == PreferredSize::Height::WRAP) {
            measuredSize.height = std::max(minSize.height, image ? (float)image->PreferredSize.height : 0.0f);
        } else if (preferredSize.height != PreferredSize::Height::FILL) {
            measuredSize.height = (float)preferredSize.height;
        }
    }

    void ImageView::onDraw(Canvas& canvas) {
        if (!image)
            return;

        auto src = D2D1::RectF(0, 0, (float)image->PreferredSize.width, (float)image->PreferredSize.height);
        D2D1_RECT_F dst;

        if (scaleMode == ImageScaleMode::NONE) {
            dst.left = (Size.width - image->PreferredSize.width) / 2.0f;
            dst.top = (Size.height - image->PreferredSize.height) / 2.0f;
            dst.right = dst.left + image->PreferredSize.width;
            dst.bottom = dst.top + image->PreferredSize.height;
        } else if (scaleMode == ImageScaleMode::STRETCH) {
            dst.left = 0;
            dst.top = 0;
            dst.right = Size.width;
            dst.bottom = Size.height;
        } else if (scaleMode == ImageScaleMode::FIT) {
            float sx = Size.width / image->PreferredSize.width;
            float sy = Size.height / image->PreferredSize.height;
            float s = std::min(sx, sy);
            float width = image->PreferredSize.width * s;
            float height = image->PreferredSize.height * s;
            if (gravity.horizontal == Alignment::Horizontal::LEFT) {
                dst.left = 0;
            } else if (gravity.horizontal == Alignment::Horizontal::CENTER) {
                dst.left = (Size.width - width) / 2.0f;
            } else {
                dst.left = Size.width - width;
            }
            if (gravity.vertical == Alignment::Vertical::TOP) {
                dst.top = 0;
            } else if (gravity.vertical == Alignment::Vertical::CENTER) {
                dst.top = (Size.height - height) / 2.0f;
            } else {
                dst.top = Size.height - height;
            }
            dst.right = dst.left + width;
            dst.bottom = dst.top + height;
        } else if (scaleMode == ImageScaleMode::CROP) {
            float sx = Size.width / image->PreferredSize.width;
            float sy = Size.height / image->PreferredSize.height;
            float s = std::max(sx, sy);
            float width = image->PreferredSize.width * s;
            float height = image->PreferredSize.height * s;
            if (gravity.horizontal == Alignment::Horizontal::LEFT) {
                dst.left = 0;
            } else if (gravity.horizontal == Alignment::Horizontal::CENTER) {
                dst.left = (Size.width - width) / 2.0f;
            } else {
                dst.left = Size.width - width;
            }
            if (gravity.vertical == Alignment::Vertical::TOP) {
                dst.top = 0;
            } else if (gravity.vertical == Alignment::Vertical::TOP) {
                dst.top = (Size.height - height) / 2.0f;
            } else {
                dst.top = Size.height - height;
            }
            dst.right = dst.left + width;
            dst.bottom = dst.top + height;
        }

        image->Position = { dst.left, dst.top };
        image->Size = { dst.right-dst.left, dst.bottom-dst.top };
        image->draw(canvas);
    }
}