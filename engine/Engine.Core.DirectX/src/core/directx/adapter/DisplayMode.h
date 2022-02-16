#pragma once

#pragma warning(push, 0)
#include <dxgi1_4.h>
#pragma warning(pop)

#include "core/string/String.h"
#include "core/Object.h"

namespace Ghurund::Core::DirectX {
    using namespace Ghurund::Core;

    class DisplayMode: public Object {
    private:
        unsigned int width, height;
        float refreshRate;
        DXGI_FORMAT format;

    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        DisplayMode(DXGI_MODE_DESC mode) {
            width = mode.Width;
            height = mode.Height;
            refreshRate = (float)mode.RefreshRate.Numerator / mode.RefreshRate.Denominator;
            format = mode.Format;
        }

        unsigned int getWidth() {
            return width;
        }

        unsigned int getHeight() {
            return height;
        }

        float getRefreshRate() {
            return refreshRate;
        }

        DXGI_FORMAT getFormat() {
            return format;
        }

        static const Ghurund::Core::Type& GET_TYPE();
    };
}