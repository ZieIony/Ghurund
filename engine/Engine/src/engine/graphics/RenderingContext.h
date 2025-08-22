#pragma once

#include "core/math/Size.h"
#include <core/window/SystemWindow.h>
#include <core/Color.h>
#include "core/object/NotNull.h"
#include "RenderingStatistics.h"
#include "core/object/Initializable.h"

namespace Ghurund::Engine {
    class RenderingContext: public Ghurund::Core::Initializable {
    protected:
        Ghurund::Core::SystemWindow* window;
        RenderingStatistics stats;

    public:
        RenderingContext(Ghurund::Core::NotNull<Ghurund::Core::SystemWindow> window):window(&window) {}

        virtual ~RenderingContext() = 0 {}

        RenderingStatistics& getStatistics() {
            return stats;
        }

        __declspec(property(get = getStatistics)) RenderingStatistics& Statistics;

        virtual void startFrame() = 0;

        virtual void finishFrame() = 0;

        virtual void clear(const Ghurund::Core::Color* clearColor) = 0;

        virtual void setSize(Ghurund::Core::IntSize size) = 0;
    };
}