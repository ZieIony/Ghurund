#pragma once

#include "core/Timer.h"
#include "core/reflection/Type.h"

namespace Ghurund {
    class RenderingStatistics {
    private:
        double renderingTime = 0;

        Ghurund::Core::Timer timer;

    public:
        size_t modelsCulled = 0;
        size_t modelsRendered = 0;
        size_t trianglesRendered = 0;
        size_t materialChanges = 0;

        double getRenderingTime() const {
            return renderingTime;
        }

        __declspec(property(get = getRenderingTime)) double RenderingTime;

        void startFrame() {
            renderingTime = 0;
            modelsCulled = 0;
            modelsRendered = 0;
            trianglesRendered = 0;
            materialChanges = 0;
            timer.tick();
        }

        void finishFrame() {
            timer.tick();
            renderingTime = timer.FrameTime;
        }
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::RenderingStatistics>();
}
