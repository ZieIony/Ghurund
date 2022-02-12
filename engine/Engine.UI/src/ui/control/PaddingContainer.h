#pragma once

#include "ControlContainer.h"
#include "ui/Padding.h"

namespace Ghurund::UI {
    class PaddingContainer: public ControlContainer {
    private:
        Padding padding;

    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        PaddingContainer() {}

        PaddingContainer(float all) {
            padding.All = all;
        }

        PaddingContainer(float left, float top, float right, float bottom) {
            padding.left = left;
            padding.top = top;
            padding.right = right;
            padding.bottom = bottom;
        }

        inline Padding& getPadding() {
            return padding;
        }

        inline void setPadding(const Padding& padding) {
            this->padding = padding;
        }

        __declspec(property(get = getPadding, put = setPadding)) Padding& Padding;

        virtual void onMeasure(float parentWidth, float parentHeight) override;

        virtual void onLayout(float x, float y, float width, float height) override;

        virtual void load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}