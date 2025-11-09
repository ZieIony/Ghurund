#pragma once

#include "core/Color.h"
#include "core/math/Size.h"
#include "core/object/Initializable.h"
#include "core/object/Noncopyable.h"
#include "core/object/NotNull.h"
#include "core/window/SystemWindow.h"
#include "RenderingStatistics.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class RenderingContext:public Noncopyable, public Initializable {
    protected:
        SystemWindow& window;
        RenderingStatistics stats;

    public:
        RenderingContext(SystemWindow& window):window(window) {}

        // TODO: why is this return value a reference?
        RenderingStatistics& getStatistics() {
            return stats;
        }

        __declspec(property(get = getStatistics)) RenderingStatistics& Statistics;

        virtual void startFrame() = 0;

        virtual void finishFrame() = 0;

        virtual void clear(const Color* clearColor) = 0;

        virtual void setSize(IntSize size) = 0;

        __declspec(property(put = setSize)) IntSize Size;
    };
}