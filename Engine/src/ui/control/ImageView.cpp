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
        if (!image)
            return;

        auto src = Gdiplus::RectF(0, 0, (float)image->image->GetWidth(), (float)image->image->GetHeight());
        Gdiplus::RectF dst;
        if (scaleMode == ImageScaleMode::NONE) {
            dst.X = (Size.width - src.Width) / 2.0f;
            dst.Y = (Size.height - src.Height) / 2.0f;
            dst.Width = src.Width;
            dst.Height = src.Height;
        } else if (scaleMode == ImageScaleMode::STRETCH) {
            dst.X = 0;
            dst.Y = 0;
            dst.Width = Size.width;
            dst.Height = Size.height;
        } else if (scaleMode == ImageScaleMode::FIT) {
            float sx = Size.width / src.Width;
            float sy = Size.height / src.Height;
            float s = std::min(sx, sy);
            dst.Width = src.Width * s;
            dst.Height = src.Height * s;
            if (gravity.horizontal == Alignment::Horizontal::LEFT) {
                dst.X = 0;
            } else if (gravity.horizontal == Alignment::Horizontal::CENTER) {
                dst.X = (Size.width - dst.Width) / 2.0f;
            } else {
                dst.X = Size.width - dst.Width;
            }
            if (gravity.vertical == Alignment::Vertical::TOP) {
                dst.Y = 0;
            } else if (gravity.vertical == Alignment::Vertical::TOP) {
                dst.Y = (Size.height - dst.Height) / 2.0f;
            } else {
                dst.Y = Size.height - dst.Height;
            }
        } else if (scaleMode == ImageScaleMode::CROP) {
            float sx = Size.width / src.Width;
            float sy = Size.height / src.Height;
            float s = std::max(sx, sy);
            dst.Width = src.Width * s;
            dst.Height = src.Height * s;
            dst.X = (Size.width - dst.Width) / 2.0f;
            dst.Y = (Size.height - dst.Height) / 2.0f;
            if (gravity.horizontal == Alignment::Horizontal::LEFT) {
                dst.X = 0;
            } else if (gravity.horizontal == Alignment::Horizontal::CENTER) {
                dst.X = (Size.width - dst.Width) / 2.0f;
            } else {
                dst.X = Size.width - dst.Width;
            }
            if (gravity.vertical == Alignment::Vertical::TOP) {
                dst.Y = 0;
            } else if (gravity.vertical == Alignment::Vertical::TOP) {
                dst.Y = (Size.height - dst.Height) / 2.0f;
            } else {
                dst.Y = Size.height - dst.Height;
            }
        }
        if (tint) {
            canvas.drawImage(*image, src, dst, tint);
        } else {
            canvas.drawImage(*image, src, dst);
        }
    }
}