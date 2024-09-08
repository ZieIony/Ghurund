#pragma once

#include "core/collection/Array.h"
#include "ui/StrokeStyle.h"

#include <d2d1_3.h>

namespace Ghurund::UI::Direct2D {
    using namespace Ghurund::Core;

    class StrokeStyle:public IStrokeStyle {
    private:
        ID2D1StrokeStyle* strokeStyle = nullptr;

    public:
        ~StrokeStyle() {
            if (strokeStyle)
                strokeStyle->Release();
        }

        void init(ID2D1Factory6& d2dFactory, const Array<float>& dashes) {
            if (strokeStyle)
                return;
            HRESULT hr = d2dFactory.CreateStrokeStyle(
                D2D1::StrokeStyleProperties(
                    D2D1_CAP_STYLE_FLAT,
                    D2D1_CAP_STYLE_FLAT,
                    D2D1_CAP_STYLE_ROUND,
                    D2D1_LINE_JOIN_MITER,
                    10.0f,
                    D2D1_DASH_STYLE_CUSTOM,
                    0.0f),
                &(*(dashes.begin())),
                (UINT32)dashes.Size,
                &strokeStyle
            );
        }

        inline void uninit() {
            if (strokeStyle) {
                strokeStyle->Release();
                strokeStyle = nullptr;
            }
        }

        ID2D1StrokeStyle* get() {
            return strokeStyle;
        }
    };
}