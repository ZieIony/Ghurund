#pragma once

#include "core/application/Application.h"
#include <engine/audio/AudioFeature.h>
#include <engine/graphics/GraphicsFeature.h>
#include <engine/graphics/GraphicsFeatureFactory.h>

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class GameApplication:public Application {
    public:
        GameApplication() {
            Features.add<GraphicsFeature, GraphicsFeatureFactory>();
            Features.add<AudioFeature>();
        }
    };
}
