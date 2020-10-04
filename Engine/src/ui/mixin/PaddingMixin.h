#pragma once

#include "ui/control/PaddingContainer.h"

namespace Ghurund::UI {
    class PaddingMixin {
    protected:
        PaddingContainer* paddingContainer = nullptr;

    public:
        inline Padding& getPadding() const {
            return paddingContainer->Padding;
        }

        __declspec(property(get = getPadding)) Padding& Padding;
    };

    class PaddingLayoutMixin {
    protected:
        PaddingContainer* paddingContainer;

    public:
        PaddingLayoutMixin() {
            paddingContainer = ghnew Ghurund::UI::PaddingContainer();
        }

        ~PaddingLayoutMixin() {
            paddingContainer->release();
        }

        inline PaddingContainer* getPaddingContainer() const {
            return paddingContainer;
        }

        __declspec(property(get = getPaddingContainer)) PaddingContainer* PaddingContainer;
    };
}