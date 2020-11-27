#include "ImageView.h"

namespace Ghurund::UI {
    void ImageView::onMeasure(float parentWidth, float parentHeight) {
        if (preferredSize.width == PreferredSize::Width::WRAP) {
            measuredSize.width = std::max(minSize.width, image ? image->Size.width : 0.0f);
        } else if (preferredSize.width != PreferredSize::Width::FILL) {
            measuredSize.width = (float)preferredSize.width;
        }

        if (preferredSize.height == PreferredSize::Height::WRAP) {
            measuredSize.height = std::max(minSize.height, image ? image->Size.height : 0.0f);
        } else if (preferredSize.height != PreferredSize::Height::FILL) {
            measuredSize.height = (float)preferredSize.height;
        }
    }

    void ImageView::onDraw(Canvas& canvas) {
        if (!image||!image->Data)
            return;

        auto src = D2D1::RectF(0, 0, (float)image->Size.width, (float)image->Size.height);
        D2D1_RECT_F dst;

        if (scaleMode == ImageScaleMode::NONE) {
            dst.left = (Size.width - image->Size.width) / 2.0f;
            dst.top = (Size.height - image->Size.height) / 2.0f;
            dst.right = dst.left + image->Size.width;
            dst.bottom = dst.top + image->Size.height;
        } else if (scaleMode == ImageScaleMode::STRETCH) {
            dst.left = 0;
            dst.top = 0;
            dst.right = Size.width;
            dst.bottom = Size.height;
        } else if (scaleMode == ImageScaleMode::FIT) {
            float sx = Size.width / image->Size.width;
            float sy = Size.height / image->Size.height;
            float s = std::min(sx, sy);
            float width = image->Size.width * s;
            float height = image->Size.height * s;
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
            float sx = Size.width / image->Size.width;
            float sy = Size.height / image->Size.height;
            float s = std::max(sx, sy);
            float width = image->Size.width * s;
            float height = image->Size.height * s;
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

        if (tint) {
            canvas.drawImage(*image, dst, tint);
        } else {
            canvas.drawImage(*image, dst);
        }
    }
}