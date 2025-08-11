#pragma once

#include "core/math/Size.h"
#include <core/window/SystemWindow.h>
#include <core/Color.h>
#include "core/object/NotNull.h"
#include "RenderingStatistics.h"

namespace Ghurund::Engine {
    class RenderingContext {
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

        virtual void init() = 0;

        virtual void uninit() = 0;

        virtual void startFrame() = 0;

        virtual void finishFrame() = 0;

        virtual void clear(const Ghurund::Core::Color* clearColor) = 0;

        virtual void setSize(Ghurund::Core::IntSize size) = 0;
    };
}